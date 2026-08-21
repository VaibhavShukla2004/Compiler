#include "lexer.h";

Token getNextToken(FILE *inputFile, int *lineNumber, int *columnNumber){
    Token token;
    // Implement logic to read from inputFile and populate the token structure
    return token;
}


TokenList getTokens(FILE *inputFile){
    TokenList tokens; // Assuming a maximum of 1024 tokens for simplicity

    int noOfTokens = 0,lineNumber = 0,columnNumber = 0;

    while(1){
        Token token = getNextToken(inputFile,&lineNumber,&columnNumber);
        if(strcmp(token.tokenType,"END") == 0){
            tokens.noOfTokens = noOfTokens;
            break;
        }else{
            tokens.tokenArray[noOfTokens] = token;
            noOfTokens++;
        }
    }

    return tokens;
}