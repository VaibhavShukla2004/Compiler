#include "common.h"
#ifndef LEXER_H
#define LEXER_H

typedef struct Token {
    char tokenName[100];
    char tokenType[100];
    unsigned int row,col;
}Token;

typedef struct {
    Token tokenArray[1024];
    int noOfTokens;
}TokenList;

TokenList getTokens(FILE *inputFile);

#endif 