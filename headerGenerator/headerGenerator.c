/***************************************************************
    Compilation: $ gcc headerGenerator.c -o headerGenerator.out
    Execution:   $ ./headerGenerator.out file.c
    Description: This program generates a header file named file.h which contains
                 the declarations of all the functions defined 
                 (functions with a body) in the input .c file.

                 The program supports the most commonly used code
                 styles: 
                 1.
                    void fn(int a, int b) {
                    }
                 2. 
                    void fn(int a, int b)
                    {  
                    }
                
                 The header file will look like:
                    void fn(int a, int b);     
    
    Since:       2018 Feb 20  
    Version:     v0.1
    Author:      Kevin Sun
***************************************************************/

#include <stdio.h>
#include <string.h>
#ifdef DEBUG
    #define debug(s,x) printf(s,x)
#else
    #define debug(s,x) 
#endif

const unsigned int maxFileNameLen = 256;
const unsigned int maxLineLen = 1024;

int isStyle_1(char* str);
void changeToHeaderName(char* headerName);

int main(int argc, char* argv[]) {
    
    if(argc != 2) {
        printf("Error: This program takes exactly one argument: the name of a .c file.\n");
        return -1;
    }

    char cFileName[maxFileNameLen];
    strcpy(cFileName, argv[1]);
    char hFileName[maxFileNameLen]; 
    strcpy(hFileName, argv[1]);
    hFileName[strlen(hFileName)-1] = 'h';    
    
    // use int increment decrement to simulate stack push-pop behavior
    unsigned int stack = 0;

    FILE* code = fopen(cFileName,"r");
    if(code == NULL) {
        return -1;
    }

    FILE* linePtr = fopen(cFileName,"r");
    if(linePtr == NULL) {
        return -1;
    }

    FILE* header = fopen(hFileName,"w");

    char line[maxLineLen];
    char prevLine[maxLineLen];
    fgets(line, maxLineLen, linePtr);

    char c;
    while( ( c=fgetc(code) ) != EOF ) {
        if(c == '{') {
            if(stack == 0) {
                char* str;
                if(isStyle_1(line)) {
                    debug("style 1, line=%s\n",line);
                    str = line;

                }else{
                    debug("style 2, prevline=%s\n",prevLine);
                    str = prevLine;
                }

                for(int i = 0; str[i] != ')'; i++) {
                    fputc(str[i], header);
                }
                fputc(')', header);
                fputc(';', header);
                fputc('\n', header);
            }
            stack++;
        }

        if(c == '}') {
            stack--;
        }

        if(c == '\n') {
            strcpy(prevLine, line);
            fgets(line, maxLineLen, linePtr);   
        }
    }

    if(stack != 0) {
        printf("stack not empty.\n");
        return -1;
    }

    fclose(linePtr);
    fclose(code);
    fclose(header);
    return 0;
}

int isStyle_1(char* str) {
    
    for(int i = 0; str[i] != '{'; i++) {
        if( str[i] != ' ' && str[i] != '\t' ) {
            return 1;
        }       
    }
    return 0;
}

