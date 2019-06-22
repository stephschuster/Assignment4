#include "../../param.h"
#include "../../types.h"
#include "../../stat.h"
#include "../../user.h"
#include "../../fs.h"
#include "../../fcntl.h"
#include "../../syscall.h"
#include "../../traps.h"
#include "../../memlayout.h"

#define BSIZE 512
#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device
#define PGSIZE 4096

void readFile(char *name, int bytesPerRead);
void readFileWithOutPrint(char *name, int bytesPerRead);
void readDir(char *name);
char* fmtname(char *path);
void ls(char *path);
void executeOpenFileInSubProcess(char *name, int sleepTime);
void executeCreateAndOpenFileInSubProcess(int i, int sleepTime, int numOfBlocks);
void createFileToRead(char *name, int numOfBlocks);
void reverseString(char* str, int length);
char* itoa(int num, char* str, int base);
void executeSubProcessWithFunc(void (*func)(void));
void executeSubProcessWithExec(char *name);
void printStat(char *name);
void assertDevice(char *name);
void printDirFiles(char *name);
void lsPrintFiles(char *path);
void printProcDirAndFiles();
void makeAllocationSize(int size);

int main(int argc, char *argv[]){
  makeAllocationSize(200);
  
  int pid;
  int length;
  char name[50];
  name[0] = '/';
  name[1] = 'p';
  name[2] = 'r';
  name[3] = 'o';
  name[4] = 'c';
  name[5] = '/';
  char *pidDir = name + 6;
  
  pid = getpid();
  itoa(pid,pidDir,10);

  length = strlen(name);

  name[length] = '/';
  name[length + 1] = 'n';
  name[length + 2] = 'a';
  name[length + 3] = 'm';
  name[length + 4] = 'e';
  name[length + 5] = '\0';

  readFile(name,10);

  exit();
}

void printProcDirAndFiles(){
  int pid;
  char name[16];
  name[0] = '/';
  name[1] = 'p';
  name[2] = 'r';
  name[3] = 'o';
  name[4] = 'c';
  name[5] = '/';
  char *pidDir = name + 6;
  
  pid = getpid();
  itoa(pid,pidDir,10);

  readDir(name);
  printDirFiles(name);

  assertDevice(name);
}

void readFile(char *name, int bytesPerRead){
    int fd;
    int n;
    char buf[1000];

    printf(1,"\n------------------------------------\n");

    if((fd = open(name, O_RDONLY)) < 0){
        printf(1,"error reading %s file !!!\n",name);
        exit();
    }

    while((n = read(fd, buf, bytesPerRead)) > 0){
        buf[n] = '\0';
        printf(1,"%s",buf);
    }

    printf(1,"\n------------------------------------\n");
    close(fd);
}

void readFileWithOutPrint(char *name, int bytesPerRead){
  int fd;
  int n;
  char buf[1000];

  if((fd = open(name, O_RDONLY)) < 0){
      printf(1,"error reading %s file !!!\n",name);
      exit();
  }

  while((n = read(fd, buf, bytesPerRead)) > 0){
      buf[n] = '\0';
  }

  close(fd);
}

void readDir(char *name){
    printf(1,"\n------------------------------------\n");
    ls(name);
    printf(1,"\n------------------------------------\n");
}

char* fmtname(char *path){
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void ls(char *path){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    exit();
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    exit();
    return;
  }

  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      exit();
  }
  strcpy(buf, path);
  p = buf+strlen(buf);
  *p++ = '/';
  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        exit();
        continue;
    }
    printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
  }

  close(fd);
}

void createFileToRead(char *name, int numOfBlocks){
  int fd;
  int n;
  int currentSize = 0;

  if((fd = open(name,O_CREATE | O_RDWR)) < 0){
    printf(1,"1error writing to %s file\n",name);
    exit();
  }

  while((n = write(fd, name, strlen(name))) > 0){
    currentSize += n;

    if(currentSize >= (numOfBlocks * BSIZE)){
      return;
    }
  }

  printf(1,"error writing to %s file\n",name);
}

void executeOpenFileInSubProcess(char *name, int sleepTime){
  int pid;

  if((pid = fork()) == 0){
    sleep(100);
    readFileWithOutPrint(name,BSIZE);
    sleep(sleepTime);
    exit();
  }else if(pid < 0){
    printf(1,"fork failed\n");
    exit();
  }
}

void executeCreateAndOpenFileInSubProcess(int i, int sleepTime, int numOfBlocks){
  int pid;
  char name[16];
  name[0] = 'p';
  name[1] = 'i';
  name[2] = 'd';
  itoa(i, name + 3, 10);
  
  if((pid = fork()) == 0){
    sleep(100);
    createFileToRead(name, numOfBlocks);
    readFileWithOutPrint(name,BSIZE);
    sleep(sleepTime);
    exit();
  }else if(pid < 0){
    printf(1,"fork failed\n");
    exit();
  }
}

// Reversing string
void reverseString(char* str, int length){
  // Initializing
  char temp;

  // Reversing string
  for(int i = 0;i < length/2;i++){
    temp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = temp;
  }
}

// Implementation of itoa() From www.geeksforgeeks.org
char* itoa(int num, char* str, int base){   
  // Initializing
  int i = 0; 
  int isNegative = 0; 

  /* Handle 0 explicitely, otherwise empty string is printed for 0 */
  if (num == 0) 
  { 
      str[i++] = '0'; 
      str[i] = '\0'; 
      return str; 
  } 

  // In standard itoa(), negative numbers are handled only with  
  // base 10. Otherwise numbers are considered unsigned. 
  if (num < 0 && base == 10) 
  { 
      isNegative = 1; 
      num = -num; 
  } 

  // Process individual digits 
  while (num != 0) 
  { 
      int rem = num % base; 
      str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
      num = num/base; 
  } 

  // If number is negative, append '-' 
  if (isNegative) 
      str[i++] = '-'; 

  str[i] = '\0'; // Append string terminator 

  // Reverse the string 
  reverseString(str, i); 

  return str; 
}

void executeSubProcessWithFunc(void (*func)(void)){
  int pid;

  if((pid = fork()) == 0){
    func();
    exit();
  }else if(pid < 0){
    printf(1,"fork failed\n");
    exit();
  }
}

void executeSubProcessWithExec(char *name){
  int pid;
  char *args[2];

  if((pid = fork()) == 0){
    args[0] = name;
    args[1] = 0;
    exec(args[0],args);
    exit();
  }else if(pid < 0){
    printf(1,"fork failed\n");
    exit();
  }
}

void printStat(char *name){
  struct stat st;

  if(stat(name, &st) < 0){
        printf(1, "cannot stat %s\n", name);
        exit();
  }
  printf(1, "%s %d %d %d\n", name, st.type, st.ino, st.size);
}

void assertDevice(char *name){
  struct stat st;

  if(stat(name, &st) < 0){
        printf(1, "cannot stat %s\n", name);
        exit();
  }

  if(st.type != T_DEV){
    printf(1, "%s not a device file\n", name);
    exit();
  }
}

void printDirFiles(char *name){
  printf(1,"\n------------------------------------\n");
  lsPrintFiles(name);
  printf(1,"\n------------------------------------\n");
}

void lsPrintFiles(char *path){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    exit();
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    exit();
    return;
  }

  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      exit();
  }
  strcpy(buf, path);
  p = buf+strlen(buf);
  *p++ = '/';
  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    memmove(p, de.name, DIRSIZ);
    readFile(buf,50);
  }

  close(fd);
}

void makeAllocationSize(int size){
    char* currentSize;
    if((currentSize = sbrk(0)) == (char *)-1){
        printf(1,"makeAllocationSize failed, could not retrieve current size of memory. problem in test\n");
        exit();
    }

    int amountToIncrease = size * PGSIZE - (int)currentSize;

    if(amountToIncrease < 0){
        printf(1,"makeAllocationSize failed, amount to increase is negative. problem in test\n");
        exit();
    }
    
    if((currentSize = sbrk(amountToIncrease)) == (char *)-1){
        printf(1,"makeAllocationSize failed, could not increase memory size to requested size. problem in test\n");
        exit();
    }

    if((currentSize = sbrk(0)) == (char *)-1){
        printf(1,"makeAllocationSize failed, could not retrieve current size of memory after increase. problem in test\n");
        exit();
    }

    if(currentSize != (char*)(size * PGSIZE)){
        printf(1,"makeAllocationSize failed, memory size after increase is not as expected. problem in test\n");
        exit();
    }
}