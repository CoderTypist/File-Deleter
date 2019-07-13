// author Christian Bargraser
// This is essentially my version of hexdump

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#define DEFAULT 10

void printFileHex(char *fileName, int bytesPerLine);

int main(int argc, char*argv[]){
    
    printf("\n");

    if( argc != 2 && argc != 3 || ( argc == 2 && 0 == strcmp(argv[1], "-help")) ){
        
        printf("USAGE INFO:\n\n");

        printf("./hexview file.txt\n");
        printf("Print hex contents of file\n\n");

        printf("./hexview file.txt bytesPerLine\n");
        printf("Prints bytesPerLine bytes on each line\n\n");

        printf("./hexview -help\n");
        printf("View usage info\n\n");

        return 0;
    }
  
    // user specified bytes per line
    if( argc == 3 ){
        printFileHex(argv[1], atoi(argv[2]));
    }
    
    // user did not specify bytes per line
    else{
        printFileHex(argv[1], DEFAULT);
    }
    
    printf("\n");

    return 0;
}

/* My code originally said:
 *
 *     while ( EOF != (char)c )
 *
 * This worked, however, after I made delFile.c,
 * the program would display less data than hexdump.
 * This was because delFile could randomly generate a character
 * that the condition in the while loop would interpret as EOF. 
 * To fix this issue, I used stat to get the number of bytes in the file and loop
 * that many times.
 */

void printFileHex(char *fileName, int bytesPerLine){

    FILE *file = fopen(fileName, "r");

    if( NULL == file ){
        printf("Could not open %s\n\n", fileName);
        return;
    }
     
    struct stat fileInfo;
    int statReturn = stat(fileName, &fileInfo);

    if( statReturn < 0 ){
        printf("\n\n\tError calling stat()\n");
        printf("\t\t%s\n\n", strerror(errno));
    }

    if( bytesPerLine <= 0 ){
        bytesPerLine = DEFAULT;
    }

    unsigned char c = fgetc(file);
    double curByteInFile = 0;
    double curByteInLine = 0;
    double bytesInFile = fileInfo.st_size;
    unsigned int location = 0x0;
    unsigned int add = 0x1;

    while( curByteInFile < bytesInFile ){
        
        if( curByteInLine == 0 ){
            printf("%08X    ", location);
        }
        
        printf("%02X ", c);
        curByteInFile++;
        curByteInLine++;
        location += add;

        if( curByteInLine == bytesPerLine ){
            curByteInLine = 0;
            printf("\n");
        }
        
        c = fgetc(file);
    }
    
    if( 0 == curByteInFile ){
        printf("The file is empty...");
    }
    
    fclose(file);

    printf("\n");
}

