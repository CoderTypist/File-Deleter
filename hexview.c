// author Christian Bargraser
// This is essentially my version of hexdump

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT 10

void printFileHex(FILE *file, int bytesPerLine);

int main(int argc, char*argv[]){
    
    printf("\n");

    if( argc != 2 && argc != 3 || ( argc == 2 && 0 == strcmp(argv[1], "-help")) ){
        
        printf("USAGE INFO:\n\n");

        printf("./viewFile file.txt\n");
        printf("Print hex contents of file\n\n");

        printf("./viewFile file.txt bytesPerLine\n");
        printf("Prints bytesPerLine bytes on each line\n\n");

        printf("./viewFile -help\n");
        printf("View usage info\n\n");

        return 0;
    }

    FILE *file = NULL;
    file = fopen(argv[1], "r");

    if( NULL == file ){
        printf("Could not open %s\n\n", argv[1]);
        return 0;
    }
        
    if( argc == 3 ){
        printFileHex(file, atoi(argv[2]));
    }

    else{
        printFileHex(file, DEFAULT);
    }
    
    printf("\n");

    fclose(file);

    return 0;
}

void printFileHex(FILE *file, int bytesPerLine){

    if( NULL == file ){
        printf("\tWarning: viewFile.c: printFileHex(): FILE *file was NULL\n\n");
        exit(0);
    }

    if( bytesPerLine <= 0 ){
        bytesPerLine = DEFAULT;
    }

    unsigned char c = fgetc(file);
    int curByte = 0;
    unsigned int location = 0x0;
    unsigned int add = 0x1;

    while( EOF != (char)c ){
        
        if( curByte == 0 ){
            printf("%08X    ", location);
        }
        
        printf("%02X ", c);
        curByte++;
        location += add;

        if( curByte == bytesPerLine ){
            curByte = 0;
            printf("\n");
        }
        
        c = fgetc(file);
    }

    printf("\n");
}

