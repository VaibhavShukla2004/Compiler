#include "lexer.h"


Token getNextToken(FILE *inputFile, int *lineNumber, int *columnNumber)
{
    Token token;

    //initialize token
    strcpy(token.tokenname,"END");
    strcpy(token.tokenType,"END");
    token.size = 0;

    // Implement logic to read from inputFile and populate the token structure
    return token;
}


TokenList getTokens(FILE *inputFile)
{
    TokenList tokens = {0}; // Assuming a maximum of 1024 tokens for simplicity

    int noOfTokens = 0,lineNumber = 0,columnNumber = 0;

    while(1){
        Token token = getNextToken(inputFile,&lineNumber,&columnNumber);
        if(strcmp(token.tokenType,"END") == 0){
            printf("\nLexing Done\n");
            tokens.noOfTokens = noOfTokens;
            break;
        }else{
            tokens.tokenArray[noOfTokens] = token;
            noOfTokens++;
            if(noOfTokens == 1024){
                printf("exceeded max no of tokens\n compilation will be done on first 1024 tokens\n");
                return tokens;
            }
        }
    }

    return tokens;
}