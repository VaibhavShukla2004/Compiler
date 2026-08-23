#include "../lexer.h"

int main(void)
{
    FILE *inputFile = fopen("tests/input.c", "r");

    if (inputFile == NULL) {
        perror("Could not open tests/input.c");
        return 1;
    }

    TokenList tokens = getTokens(inputFile);
    fclose(inputFile);

    for (int i = 0; i < tokens.noOfTokens; i++) {
        printf(
            "Token: %-15s Type: %-10s Row: %u Col: %u\n",
            tokens.tokenArray[i].tokenName,
            tokens.tokenArray[i].tokenType,
            tokens.tokenArray[i].row,
            tokens.tokenArray[i].col
        );
    }

    return 0;
}