#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP "fileNameList.tmp"

int main(int argc, char* argv[]) {
    // create temp file that contains
    // the names of the files in the folder.
    system("ls >" TEMP);
    
    FILE* list = fopen(TEMP,"r");
    
    char fileName[200] = {0};
    char *ptrFN;
    char *ptrNN;
    while(fgets(fileName,200,list)) {
        ptrFN = fileName;
        char newName[200] = {0};
        ptrNN = newName;
        int rename = 0;

        // copy file name and replace ' ' with '_'
        while(*ptrFN) {
            if(*ptrFN != ' ') {
                *ptrNN = *ptrFN;
            } else {
                *ptrNN = '_';
                rename = 1;                
            }       
            ptrFN++;
            ptrNN++;
        }
        // rename the file if the name contains ' ' 
        if(rename) {
            char cmd[200];
            // concatenate the terminal command line string 
            // \" because the file name contains space,
            // so use " and " around the file name to escape space
            strcpy(cmd,"mv \"");
            strcat(cmd, fileName);
            // for some reason that I don't understand, 
            // there is a '\n' in cmd after strcat(cmd,fileName)
            // replace it with "
            *strchr(cmd,'\n') = '\"';
            strcat(cmd," ");
            strcat(cmd, newName);
            system(cmd);
        }
        
    }
    fclose(list);
    // remove temp file
    system("rm "TEMP);

    return 0;
}
