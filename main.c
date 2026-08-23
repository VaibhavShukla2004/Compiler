#include "lexer.h"

int main(){
    char inputfileName[100];

    printf("Enter the input file name: ");
    scanf("%99s", inputfileName);

    FILE *inputFile = fopen(inputfileName, "r");

    if(inputFile == NULL){
        printf("Error opening file %s\n", inputfileName);
        return 1;
    }else{
        printf("File %s opened successfully\n", inputfileName);
    }

    //1.Lex the file and get the tokens
    TokenList tokenList = getTokens(inputFile);

    //2.Parse the tokens and build the AST
    //3. Generate the code from the AST

    return 0;
}