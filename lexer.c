#include "lexer.h"

const char *keywords[] = {
    "int",
    "main",
    "return",
    "if",
    "else",
    "for",
    "printf"
};

const int noOfKeywords = sizeof(keywords) / sizeof(keywords[0]);


// Check whether a word is a keyword
int isKeyWord(char *word)
{
    for (int i = 0; i < noOfKeywords; i++) {
        if (strcmp(keywords[i], word) == 0) {
            return 1;
        }
    }

    return 0;
}


// Get the next token from the input file
Token getNextToken(FILE *inputFile, int *row, int *col)
{
    Token token;

    // Initialize token
    strcpy(token.tokenName, "END");
    strcpy(token.tokenType, "END");
    token.row = *row;
    token.col = *col;

    int c;

    while ((c = fgetc(inputFile)) != EOF) {

        // -----------------------------------------
        // Newline
        // -----------------------------------------
        if (c == '\n') {
            (*row)++;
            *col = 1;
            continue;
        }


        // -----------------------------------------
        // Whitespace
        // -----------------------------------------
        if (isspace((unsigned char)c)) {
            (*col)++;
            continue;
        }


        // -----------------------------------------
        // Preprocessor directives
        // Example:
        // #include <stdio.h>
        // #define MAX 10
        // -----------------------------------------
        if (c == '#') {

            while ((c = fgetc(inputFile)) != '\n' && c != EOF) {
                (*col)++;
            }

            if (c == '\n') {
                (*row)++;
                *col = 1;
            }

            continue;
        }


        // -----------------------------------------
        // Comments and division operator
        // -----------------------------------------
        if (c == '/') {

            int next = fgetc(inputFile);

            // Single-line comment
            if (next == '/') {

                (*col) += 2;

                while ((c = fgetc(inputFile)) != '\n' && c != EOF) {
                    (*col)++;
                }

                if (c == '\n') {
                    (*row)++;
                    *col = 1;
                }

                continue;
            }


            // Multiline comment
            if (next == '*') {

                (*col) += 2;

                int previous = 0;

                while ((c = fgetc(inputFile)) != EOF) {

                    if (c == '\n') {
                        (*row)++;
                        *col = 1;
                    }
                    else {
                        (*col)++;
                    }

                    if (previous == '*' && c == '/') {
                        break;
                    }

                    previous = c;
                }

                continue;
            }


            // Not a comment, so it is division '/'
            if (next != EOF) {
                ungetc(next, inputFile);
            }

            // Continue below and treat '/' as an operator
        }


        // -----------------------------------------
        // Save starting position of token
        // -----------------------------------------
        token.row = *row;
        token.col = *col;


        // -----------------------------------------
        // Identifiers and Keywords
        // -----------------------------------------
        if (isalpha((unsigned char)c) || c == '_') {

            int i = 0;

            token.tokenName[i++] = (char)c;

            while (1) {

                c = fgetc(inputFile);

                if (isalnum((unsigned char)c) || c == '_') {

                    if (i < 99) {
                        token.tokenName[i++] = (char)c;
                    }

                }
                else {
                    break;
                }
            }

            // Put back the character which does not belong
            // to the identifier, unless it is EOF.
            if (c != EOF) {
                ungetc(c, inputFile);
            }

            token.tokenName[i] = '\0';

            *col += i;


            // Keyword
            if (isKeyWord(token.tokenName)) {
                strcpy(token.tokenType, token.tokenName);
            }

            // Identifier
            else {
                strcpy(token.tokenType, "ID");
            }

            return token;
        }


        // -----------------------------------------
        // Numerical constants
        // -----------------------------------------
        if (isdigit((unsigned char)c)) {

            int i = 0;

            token.tokenName[i++] = (char)c;

            while (1) {

                c = fgetc(inputFile);

                if (isdigit((unsigned char)c)) {

                    if (i < 99) {
                        token.tokenName[i++] = (char)c;
                    }

                }
                else {
                    break;
                }
            }

            if (c != EOF) {
                ungetc(c, inputFile);
            }

            token.tokenName[i] = '\0';

            *col += i;

            strcpy(token.tokenType, "NUM");

            return token;
        }


        // -----------------------------------------
        // String literals
        // -----------------------------------------
        if (c == '"') {

            int i = 0;
            int escaped = 0;
            int terminated = 0;

            while ((c = fgetc(inputFile)) != EOF) {

                // End of string
                if (c == '"' && !escaped) {
                    terminated = 1;
                    break;
                }


                // Track newline
                if (c == '\n') {
                    (*row)++;
                    *col = 1;
                }
                else {
                    (*col)++;
                }


                // Store character
                if (i < 99) {
                    token.tokenName[i++] = (char)c;
                }


                // Handle escape characters
                if (c == '\\' && !escaped) {
                    escaped = 1;
                }
                else {
                    escaped = 0;
                }
            }

            token.tokenName[i] = '\0';


            // Unterminated string
            if (!terminated) {
                strcpy(token.tokenType, "Unknown");
                return token;
            }


            // Include opening and closing quotes
            *col += 2;

            strcpy(token.tokenType, "string");

            return token;
        }


        // -----------------------------------------
        // Operators
        // -----------------------------------------
        token.tokenName[0] = (char)c;
        token.tokenName[1] = '\0';


        if (strchr("+-*/%=!><&|", c) != NULL) {

            int next = fgetc(inputFile);

            /*
                Compound operators:

                ==
                !=
                <=
                >=
                ++
                --
                &&
                ||
            */

            if (
                next == '=' ||
                (c == '+' && next == '+') ||
                (c == '-' && next == '-') ||
                (c == '&' && next == '&') ||
                (c == '|' && next == '|')
            ) {

                token.tokenName[1] = (char)next;
                token.tokenName[2] = '\0';

                *col += 2;
            }

            else {

                if (next != EOF) {
                    ungetc(next, inputFile);
                }

                *col += 1;
            }

            strcpy(token.tokenType, token.tokenName);

            return token;
        }


        // -----------------------------------------
        // Special symbols
        // -----------------------------------------
        if (strchr("(){}[],.;", c) != NULL) {

            strcpy(token.tokenType, token.tokenName);

            (*col)++;

            return token;
        }


        // -----------------------------------------
        // Unknown character
        // -----------------------------------------
        strcpy(token.tokenType, "Unknown");

        (*col)++;

        return token;
    }


    // -----------------------------------------
    // EOF
    // -----------------------------------------
    return token;
}


// Get all tokens from the input file
TokenList getTokens(FILE *inputFile)
{
    TokenList tokens = {0};

    int noOfTokens = 0;

    // Start line and column numbering from 1
    int lineNumber = 1;
    int columnNumber = 1;


    while (1) {

        Token token = getNextToken(
            inputFile,
            &lineNumber,
            &columnNumber
        );


        // End of file
        if (strcmp(token.tokenType, "END") == 0) {

            printf("\nLexing Done\n");

            tokens.noOfTokens = noOfTokens;

            break;
        }


        // Maximum token limit
        if (noOfTokens >= 1024) {

            printf(
                "Exceeded maximum number of tokens.\n"
                "Compilation will be done on the first 1024 tokens.\n"
            );

            tokens.noOfTokens = noOfTokens;

            return tokens;
        }


        // Store token
        tokens.tokenArray[noOfTokens] = token;

        noOfTokens++;
    }


    return tokens;
}