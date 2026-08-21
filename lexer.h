#ifndef LEXER_H
#define LEXER_H

typedef struct Token {
    char tokenname[100];
    char tokenType[100];
    int size;
}Token;

typedef struct {
    Token TokenArray[1024];
    int noOfTokens;
}TokenList;

TokenList getTokens(FILE *inputFile);

#endif 