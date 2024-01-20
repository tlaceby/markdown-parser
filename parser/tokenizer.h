#ifndef __markdown_tokenizer__
#define __markdown_tokenizer__

#include "helpers.h"
#include "stdlib.h"

typedef enum TokenType {
    // Basic text and whitespace
    END_FILE,
    TEXT,
    WHITESPACE,
    TAB,
    NEW_LINE,

    // Inline formatting
    BOLD,          // **bold**
    ITALIC,        // *italic*
    STRIKETHROUGH, // ~~strikethrough~~
    CODE,          // `code`
    INLINE_CODE,   // `inline code`

    // Links and images
    LINK_TEXT,     // [text]
    URL,           // (url)
    IMAGE_TEXT,    // ![alt text]

    // Headers
    H1,       // # 
    H2,       // ##
    H3,       // ###
    H4,       // ####
    H5,       // #####
    H6,       // ######

    // Lists
    UNORDERED_LIST, // *, +, or -
    ORDERED_LIST,   // 1., 2., 3., etc.

    // Blockquotes
    BLOCKQUOTE,    // >

    // Code blocks
    CODE_BLOCK,    // ``` or ~~~

    // Horizontal rules
    HORIZONTAL_RULE, // --- or ***

    // Others
    ESCAPE,        // \ (to escape special characters)
} TokenType;

const char* tokentype_string (TokenType tt);

typedef struct Token {
    TokenType type;
    char* text;
} Token;


typedef struct Tokens {
    size_t size;
    size_t cap;
    Token* tokens;
} Tokens;

void debug_token (Token token);
Tokens tokenize (Error* status, char* source);

#endif