#include <stdio.h>
#include <stdlib.h>

int main(){
    char inputfileName[100];

    printf("Enter the input file name: ");
    scanf("%s", inputfileName);

    FILE *inputFile = fopen(inputfileName, "r");

    if(inputFile == NULL){
        printf("Error opening file %s\n", inputfileName);
        return 1;
    }else{
        printf("File %s opened successfully\n", inputfileName);
    }


    return 0;
}