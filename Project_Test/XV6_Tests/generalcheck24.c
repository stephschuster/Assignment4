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
#define NELEM(x) (sizeof(x)/sizeof((x)[0]))
#define READ   0
#define WRITE  1
#define NINODE 50
#define NDIRECT 12
#define NINDIRECT (BSIZE / sizeof(uint))

struct inode {
    int device;
    int inodeNumber;
    int isValid;
    char type[20]; 
    int major;
    int minor;
    int hard_links;
    int blocks_used;
};

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
void executeLSNDdataRetrieve();
void executeLSND(int *fd);
void printFromLSND();
void parseFromFD(int fd);
void parseInodeDataPart(int inodesDataIndex, int partNum, char *buf);
void printInodesData();
void assertFileInLSNDparsingData(char *name, int major);
int fileTypeToInt(char *type);
void printFileStat(struct stat st);
void createAndOpenFile(char *name, int numBlocks, int numLinks);
void createAndOpenFileInBlocks(char *name, int numBlocks, int numLinks);
void createAndOpenDir(char *name);
void increaseLinks(char *name, int numLinks);
void getProcDir(char *name);

struct inode inodesData[NINODE];
int numOfInodesData;

int main(int argc, char *argv[]){
    printf(1,"\n%s test starting...\n",argv[0]);
    char theDir2[16];
    int pid;

    char *theFile1 = "/proc/ideinfo";
    char *theFile2 = "/proc/filestat";
    char *theFile3 = "aFile3";

    char *theDir1 = "/proc/inodeinfo";
    getProcDir(theDir2);
    char *theDir3 = "aDir3";

    if((pid = fork()) == 0){
      open(theFile1,O_RDONLY);
      open(theFile2,O_RDONLY);
      createAndOpenFileInBlocks(theFile3, NDIRECT + 5, 7);

      open(theDir1,O_RDONLY);
      open(theDir2,O_RDONLY);
      createAndOpenDir(theDir3);

      printf(1,"finished open files in sub process\n");
      sleep(99999999);
      exit();
    }else if(pid < 0){
      printf(1,"fork failed\n");
      exit();
    }else{
      printf(1,"waiting 2 min for all files to be created\n");
      sleep(12000);
    }

    executeLSNDdataRetrieve();
    
    assertFileInLSNDparsingData(theFile1,2);
    assertFileInLSNDparsingData(theFile2,2);
    assertFileInLSNDparsingData(theFile3,0);

    assertFileInLSNDparsingData(theDir1,2);
    assertFileInLSNDparsingData(theDir2,2);
    assertFileInLSNDparsingData(theDir3,0);

    printf(1,"%s test exiting...\n",argv[0]);
    exit();
}

void createAndOpenFileInBlocks(char *name, int numBlocks, int numLinks){
  int fd;
  int n;
  int currentSize = 0;
  char buf[BSIZE];

  if((fd = open(name,O_CREATE | O_RDWR)) < 0){
    printf(1,"error writing to %s file\n",name);
    exit();
  }

  while((n = write(fd, buf, BSIZE)) > 0){
    currentSize += n;

    if(currentSize >= (numBlocks * BSIZE)){
      break;
    }
  }

  if(currentSize < (numBlocks * BSIZE)){
    close(fd);
    printf(1,"error writing to %s file\n",name);
    exit();
  }

  increaseLinks(name, numLinks - 1);
}

void getProcDir(char *name){
  name[0] = '/';
  name[1] = 'p';
  name[2] = 'r';
  name[3] = 'o';
  name[4] = 'c';
  name[5] = '/';
  char *pidDir = name + 6;
  
  itoa(getpid(),pidDir,10);

  open(name,O_RDONLY);
}

void executeLSNDdataRetrieve(){
  int fd[2];

  printFromLSND();
  executeLSND(fd);
  parseFromFD(fd[READ]);
  printInodesData();

  close(fd[READ]);
  close(fd[WRITE]);
}

void executeLSND(int *fd){
  int pid;
  char *args[2];

  pipe(fd);

  if((pid = fork()) == 0){
    close(fd[READ]);
    close(1);
    dup(fd[WRITE]);

    args[0] = "lsnd";
    args[1] = 0;
    exec(args[0],args);
    printf(1,"exec failed\n");
    exit();
  }else if(pid < 0){
    printf(1,"fork failed\n");
    exit();
  }else{
    close(fd[WRITE]);
  }
}

void printFromLSND(){
  int pid;
  char *args[2];

  printf(1,"\n\nPrinting lsnd raw data\n\n");
  if((pid = fork()) == 0){
    args[0] = "lsnd";
    args[1] = 0;
    exec(args[0],args);
    printf(1,"exec failed\n");
    exit();
  }else if(pid < 0){
    printf(1,"fork failed\n");
    exit();
  }
  wait();
}

void parseFromFD(int fd){
  int n;
  char buf[512];
  char inodeDataPart[50];
  int inodesDataIndex = 0;
  int sizeOfDataPart = 0;
  int partNumber = 0;
  int parsingState = 0;
  int increment_inodesDataIndex = 0;
  int openParenNum = 0;
  int closeParenNum = 0;
  int commaNum = 0;
  
  while((n = read(fd, buf, 512)) > 0){
    for(int i = 0;i < n;i++){
      if(buf[i] == '('){
        openParenNum++;
      }else if(buf[i] == ','){
        commaNum++;
      }else if(buf[i] == ')'){
        closeParenNum++;
      }

      if((buf[i] == '(' && partNumber != 4) || 
         (buf[i] == '(' &&  openParenNum > 1)){
        printf(1,"parsing error of lsnd data\n");
        exit();
      }

      if((buf[i] == ',' && !((partNumber == 4 && parsingState) || partNumber == 5)) || 
         (buf[i] == ',' &&  commaNum > 1)){
        printf(1,"parsing error of lsnd data\n");
        exit();
      }

      if((buf[i] == ')' && !((partNumber == 5 && parsingState) || partNumber == 6)) || 
         (buf[i] == ')' &&  closeParenNum > 1)){
        printf(1,"parsing error of lsnd data\n");
        exit();
      }

      if(buf[i] == '(' || buf[i] == ')' || buf[i] == ','){
        buf[i] = ' ';
      }

      if(buf[i] == '\n'){
        buf[i] = ' ';
        increment_inodesDataIndex = 1;
      }

      if(buf[i] == ' ' && parsingState){
        parsingState = 0;

        parseInodeDataPart(inodesDataIndex, partNumber, inodeDataPart);
        partNumber++;

        if(increment_inodesDataIndex){
          increment_inodesDataIndex = 0;
          inodesDataIndex++;
          partNumber = 0;
          parsingState = 0;
          sizeOfDataPart = 0;
          openParenNum = 0;
          closeParenNum = 0;
          commaNum = 0;
        }

        sizeOfDataPart = 0;

        continue;
      }else if(buf[i] != ' ' && parsingState == 0){
        parsingState = 1;
      }
      
      if(increment_inodesDataIndex){
        increment_inodesDataIndex = 0;
        inodesDataIndex++;
        partNumber = 0;
        parsingState = 0;
        sizeOfDataPart = 0;
        openParenNum = 0;
        closeParenNum = 0;
        commaNum = 0;
        continue;
      }

      if(parsingState){
        inodeDataPart[sizeOfDataPart] = buf[i];
        inodeDataPart[++sizeOfDataPart] = '\0';
      }
    }
  }

  numOfInodesData = inodesDataIndex;
}

void parseInodeDataPart(int inodesDataIndex, int partNum, char *buf){
  switch(partNum){
    case 0:
      inodesData[inodesDataIndex].device = atoi(buf);
      break;

    case 1:
      inodesData[inodesDataIndex].inodeNumber = atoi(buf);
      break;

    case 2:
      inodesData[inodesDataIndex].isValid = atoi(buf);
      break;

    case 3:
      strcpy(inodesData[inodesDataIndex].type,buf);
      break;

    case 4:
      inodesData[inodesDataIndex].major = atoi(buf);
      break;

    case 5:
      inodesData[inodesDataIndex].minor = atoi(buf);
      break;

    case 6:
      inodesData[inodesDataIndex].hard_links = atoi(buf);
      break;

    case 7:
      inodesData[inodesDataIndex].blocks_used = atoi(buf);
      break;

    default:
      printf(1,"parsing error of lsnd data\n");
      exit();
  }
}

void printInodesData(){
  printf(1,"\n\nPrinting parsed data from lsnd...\n");

  for(int i = 0;i < numOfInodesData;i++){
    printf(1,"\n-------------------------------\n");
    printf(1,"Device: %d\n",inodesData[i].device);
    printf(1,"Inum: %d\n",inodesData[i].inodeNumber);
    printf(1,"Is Valid: %d\n",inodesData[i].isValid);
    printf(1,"Type: %s\n",inodesData[i].type);
    printf(1,"Major: %d\n",inodesData[i].major);
    printf(1,"Minor: %d\n",inodesData[i].major);
    printf(1,"Hard Links: %d\n",inodesData[i].hard_links);
    printf(1,"Blocks Used: %d",inodesData[i].blocks_used);
    printf(1,"\n-------------------------------\n\n");
  }
}

void assertFileInLSNDparsingData(char *name, int major){
  struct stat st;
  int found = 0;

  struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
};

  if(stat(name, &st) < 0){
        printf(1, "cannot stat %s\n", name);
        exit();
  }

  printf(1,"\n\nPrinting file stat to be asserted in lsnd parsing data\n");
  printFileStat(st);

  for(int i = 0;i < numOfInodesData;i++){
    if(fileTypeToInt(inodesData[i].type) == st.type && 
       inodesData[i].device == st.dev &&
       inodesData[i].inodeNumber == st.ino &&
       inodesData[i].hard_links == st.nlink &&
       inodesData[i].blocks_used == (st.size / BSIZE) + ((st.size % BSIZE) != 0 ? 1 : 0) &&
       inodesData[i].major == major &&
       inodesData[i].isValid == 1){
         found = 1;
         break;
       }
  }

  if(found == 0){
    printf(1,"could not find open file in lsnd data\n");
    exit();
  }
}

int fileTypeToInt(char *type){
  if(strcmp(type, "DIR") == 0){
    return T_DIR;
  }else if(strcmp(type, "FILE") == 0){
    return T_FILE;
  }else if(strcmp(type, "DEV") == 0){
    return T_DEV;
  }else{
    printf(1,"error in file type to int conversion: unkown file type\n");
    exit();
  }
}

void printFileStat(struct stat st){
  printf(1,"\n------------------------------------\n");
  printf(1,"Device: %d\n",st.dev);
  printf(1,"Inum: %d\n",st.ino);
  printf(1,"Type: %d\n",st.type);
  printf(1,"Hard Links: %d\n",st.nlink);
  printf(1,"Size: %d",st.size);
  printf(1,"\n------------------------------------\n");
}

void createAndOpenFile(char *name, int numBlocks, int numLinks){
  createFileToRead(name, numBlocks);
  
  if(open(name, O_RDONLY) < 0){
    printf(1,"error opening file\n");
  };

  increaseLinks(name, numLinks - 1);
}

void createAndOpenDir(char *name){
  int pid;
  char *args[3];

  if((pid = fork()) == 0){
    args[0] = "mkdir";
    args[1] = name;
    args[2] = 0;
    exec(args[0],args);
    printf(1,"exec failed\n");
    exit();
  }else if(pid < 0){
    printf(1,"fork failed\n");
    exit();
  }else{
    wait();
  }

  if(open(name, O_RDONLY) < 0){
    printf(1,"error opening dir\n");
  };
}

void increaseLinks(char *name, int numLinks){
  char buf[50];
  int pid;
  char *args[4];

  if(numLinks > 0 && numLinks < 10){
    strcpy(buf, name);
    int length = strlen(buf);
    buf[length] = '_';
    buf[length + 1] = '\0';
    length = strlen(buf);
    char *linkNum = buf + length;

    for(int i = 0;i < numLinks;i++){
      linkNum = itoa(i, linkNum, 10);

      if((pid = fork()) == 0){
        args[0] = "ln";
        args[1] = name;
        args[2] = buf;
        args[3] = 0;
        exec(args[0],args);
        printf(1,"exec failed\n");
        exit();
      }else if(pid < 0){
        printf(1,"fork failed\n");
        exit();
      }else{
        wait();
      }
    }
  }

  if(numLinks >= 10){
    printf(1,"error in test implementation, increaseLinks only support up to 9 links\n");
    exit();
  }
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
    printf(1,"error writing to %s file\n",name);
    exit();
  }

  while((n = write(fd, name, strlen(name))) > 0){
    currentSize += n;

    if(currentSize >= (numOfBlocks * BSIZE)){
      close(fd);
      return;
    }
  }

  close(fd);
  printf(1,"error writing to %s file\n",name);
  exit();
}

void executeOpenFileInSubProcess(char *name, int sleepTime){
  int pid;

  if((pid = fork()) == 0){
    sleep(100);
    open(name, O_RDONLY);
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
    open(name, O_RDONLY | O_CREATE);
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
    printf(1,"exec failed\n");
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
    if(strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0){
      memmove(p, de.name, DIRSIZ);
      readFile(buf,50);
    }
  }

  close(fd);
}