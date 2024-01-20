#include "parser/tokenizer.h"
#include "parser/helpers.h"
#include "stdio.h"

int main (int argc, char** args) {
    if (argc != 2) {
        printf("Invalid program usage. Expected one argument with path to markdown file.\neg: `markdown ./main.md`\n");
        return 1;
    }

    Error err;
    Tokens tokens = tokenize(&err, read_file(args[1]));

    printf("\nTokens:   ----------- \n");
    for (size_t i = 0; i < tokens.size; i++) {
        debug_token(tokens.tokens[i]);
    }

    printf("\n--------------------- \n");
    return 0;
}