#include "types.h"
#include "user.h"
#include "fcntl.h"

int
main(void){
    char helpBuff[600];
    char printBuff[600];
    int fd, j, offset;
    char* path = "proc/inodeinfo/\0\0\0\0\0";
    for(int i=0; i<50; i++){
        memset(helpBuff , 0 , 600);
        memset(printBuff , 0 , 600);
        offset = 0;
        if(i < 10){
            path[15] = '0' + i;
        }else{
            path[15] = '0' + i/10;
            path[16] = '0' + i%10;
        }
        if((fd = open(path, 0)) < 0){
        }else{
            if(read(fd, helpBuff, sizeof(helpBuff)) <= 0){
               printf(2, "lsnd: cannot read \n");
                exit();
            }
            close(fd);
            for(j = 0 ; j < strlen(helpBuff) ; j ++){
                if((helpBuff[j] >= '0') && (helpbuff[j] <= '9')){
                    printBuff[offset] = helpbuff[j];
                    offset++;
                }else if((helpbuff[j] >= 'A') && (helpBuff[j] <= 'Z')){
                    printBuff[offset] = helpbuff[j];
                    offset++;
                }else if(helpBuff[j] == '\n'){
                    printBuff[offset] = ' ';
                    offset++;
                }else if((helpBuff[j] == '(') || (helpBuff[j] == ')') || (helpBuff[j] == ',')){
                    printBuff[offset] = helpBuff[j];
                    offset++;
                }                  
            }
            printBuff[0] = printBuff[1];
            printBuff[1] = printBuff[2];
            for(j =  4; j < strlen(printBuff) ; j++){
                printBuff[j-2] = printBuff[j];
            }
            printBuff[j-2] = '\0';
            printBuff[j-1] = '\0';
            printf(0, "%s\n", printBuff);
        }
    }
    exit();
}
