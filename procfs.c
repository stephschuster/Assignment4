#include "types.h"
#include "stat.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"

#define DESZ sizeof(struct dirent)
#define MAX_BUF (5 + NPROC) * DESZ

extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int procMaking(int inum, char *buf);
int pidMaking(int inum, char *buf);
char* stateInString(struct proc *p);
int getName(int inum, char *buf);
int getStatus(int inum , char *buf);
int getIde(int inum , char *buf);
int getFilestat(int inum , char *buf);
int inodeInfoMaking(int inum , char *buf);
int getInode(int inum , char *buf);

//returns zero if the file represented by ip is not a directory and a non-zero
//value otherwise
int 
procfsisdir(struct inode *ip) {
  if(ip->inum == namei("/proc")->inum){
    return 1;
  }
  if((ip->inum % 500 == 0) || (ip->inum == 19) || (ip->inum == 440)){
    return 1;
  }
  return 0;
}

// is ip a dir or file
void 
procfsiread(struct inode* dp, struct inode *ip) {
  ip->major = PROCFS;
  ip->type = T_DEV;
  ip->valid = 1;
  ip->nlink = 1;
  if(procfsisdir((ip))){
    ip->minor = T_DIR;
  }else{
    ip->minor = T_FILE;
  }
}

//  make the dirents list, max number
int
procfsread(struct inode *ip, char *dst, int off, int n) {
  int caseNum = (ip->inum % 500);
  int size = 0;
  char buffer[MAX_BUF];
  memset(buffer , 0 , MAX_BUF);
  if(caseNum == namei("/proc")->inum){
    size = procMaking(ip->inum , buffer);
  }else{
    switch (caseNum)
    {
      case 0: //PID
        size = pidMaking(ip->inum, buffer);
      break;
      case 10: //name
        size = getName(ip->inum , buffer);
      break;
      case 20: //status
        size = getStatus(ip->inum , buffer);
      break;
      case 420: //ideinfo
        size = getIde(ip->inum, buffer);
      break;
      case 430: //filestat
        size = getFilestat(ip->inum, buffer);
      break;
      case 440: //inodeinfo
        size = inodeInfoMaking(ip->inum , buffer);
      break;
      default:
          if((caseNum > 440) && (caseNum < 500)){
            size = getInode(ip->inum, buffer);
          }
      break;
      }
  }
  memmove(dst, buffer + off, n);

  if(size - off > n) {
    return n;
  }
  else {
    return (size - off);
  }
}

int
procfswrite(struct inode *ip, char *buf, int n)
{
  return 0;
}

void
procfsinit(void)
{
  devsw[PROCFS].isdir = procfsisdir;
  devsw[PROCFS].iread = procfsiread;
  devsw[PROCFS].write = procfswrite;
  devsw[PROCFS].read = procfsread;
}



int
procMaking(int inum , char *buf){
  int offset = 0;
  struct dirent de;
  struct proc *p;
  char pidBuf[20];

  // adding info to proc
  de.inum = inum;
  strncpy(de.name, ".\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;

  de.inum = 1;
  strncpy(de.name, "..\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;

  de.inum = 420;
  strncpy(de.name, "ideinfo\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;

  de.inum = 430;
  strncpy(de.name, "filestat\0", DIRSIZ);
  memmove(buf + (DESZ * offset) , (char *)&de, DESZ);
  offset++;

  de.inum = 440;
  strncpy(de.name, "inodeinfo\0", DIRSIZ);
  memmove(buf + (DESZ * offset) , (char *)&de, DESZ);
  offset++;
  tryToAcquire();
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED )
    continue;
    else {
      de.inum = 500 *  p->pid;
      itoa(p->pid, pidBuf);
      strncpy(de.name, pidBuf, DIRSIZ);
      memmove(buf + (DESZ * offset), (char *)&de, DESZ);
      offset++;
    }
  }
  tryToRelease();
  return (DESZ * offset);
}

int
pidMaking(int inum, char *buf) {
  struct dirent de;
  int offset = 0;
  de.inum = inum;
  strncpy(de.name, ".\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;
  de.inum = namei("/proc")->inum;
  strncpy(de.name, "..\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;
  de.inum = 10 + inum;
  strncpy(de.name, "name\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;
  de.inum = 20 + inum;
  strncpy(de.name, "status\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;

  return (DESZ * offset);
}

//make the file with  right status
//dir inum is pid*500+20
int
getStatus(int inum , char *buf){
  struct proc *p;
  struct proc *wanted = 0;
  int found = 0;
  int wantedPid = (inum - 20)/500;
  char* procstat;
  char sz[20];
  // find proc wanted
  tryToAcquire();
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED) {
      continue;
    }
    else {
      if(p->pid == wantedPid){
        wanted = p;
        found = 1;
      }
    }
  }
  tryToRelease();
  if(found) {
    procstat = stateInString(wanted);
    itoa(wanted->sz, sz);
    strncpy(buf, "state: ", strlen("state:  "));
    strncpy(buf + strlen(buf), procstat, strlen(procstat) + 1);
    strncpy(buf + strlen(buf), " Size: ", strlen(" Size:  "));
    strncpy(buf + strlen(buf), sz, strlen(sz) + 1);
    strncpy(buf + strlen(buf), "\n", strlen("\n") + 1);
    return strlen(buf);
  }
  else{
      panic(" not find pid?");
  }
}

char*
stateInString(struct proc *p){
   switch(p->state){
    case UNUSED:
      return "UNUSED";
    case EMBRYO:
      return "EMBRYO";
    case SLEEPING:
      return "SLEEPING";
    case RUNNABLE:
      return "RUNNABLE";
    case RUNNING:
      return "RUNNING";
    case ZOMBIE:
      return "ZOMBIE";
    default:
      return "impossible";
  }
}

int
getIde(int inum , char *buf){
  int size = 0;
  size = getIdeInfo(buf);
  return size;
}

int
getName(int inum , char *buf){
  struct proc *p;
  struct proc *wanted = 0;
  int found = 0;
  int wantedPid = (inum - 10)/500;
  tryToAcquire();
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED )
    continue;
    else {
      if(p->pid == wantedPid){
        wanted = p;
        found = 1;
      }
    }
  }
  tryToRelease();
  if(found) {
    strncpy(buf, wanted->name, strlen(wanted->name));
    strncpy(buf + strlen(buf), "\n", strlen("\n"));
    return strlen(buf);
  }
  else{
    panic(" not find pid?");
  }
}

int
getFilestat(int inum , char *buf){
  int size = 0;
  size = getFilestatInfo(buf);
  return size;
}


int
inodeInfoMaking(int inum , char *buf){
  struct dirent de;
  int offset = 0;
  int openInodes[NINODE];
  int i = 0;
  char inodeBuf[20];
  memset(openInodes , 0 , NINODE);
  de.inum = inum;
  strncpy(de.name, ".\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;
  de.inum = namei("/proc")->inum;
  strncpy(de.name, "..\0", DIRSIZ);
  memmove(buf + (DESZ * offset), (char *)&de, DESZ);
  offset++;
  findOpenInode(openInodes);

  for(i = 0; openInodes[i]; i++){
      de.inum = inum + openInodes[i] + 1;
      itoa(openInodes[i] - 1, inodeBuf);
      strncpy(de.name, inodeBuf, DIRSIZ);
      memmove(buf + (DESZ * offset), (char *)&de, DESZ);
      offset++;
  }
  return (DESZ * offset);
}

int
getInode(int inum , char *buf){
  int inodeIndex = inum - 2 - 440;
  int size = 0;
  size = getInodeInfo(buf, inodeIndex);
  return size;
}