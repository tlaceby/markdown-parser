#include "tokenizer.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

const char TAB_CHAR = 0x09;
const char SPACE_CHAR = 0x20;
const char NEWLINE_CHAR = 0x0A;
const char CARRIAGE_RETURN_CHAR = 0x0D;

Token make_token (TokenType type, char* text) {
    Token tk;
    tk.text = text;
    tk.type = type;
 
    return tk;
}

void push_token (Tokens* tokens, Token token) {
    tokens->size += 1;
    if (tokens->cap == tokens->size) {
        tokens->cap *= 2;

        Token* new_tokens = (Token*)realloc(tokens->tokens, tokens->cap * sizeof(TokenType));
        
        if (!new_tokens) {
            exit(OutMemory);
        }

        tokens->tokens = new_tokens;
    }

    tokens->tokens[tokens->size - 1] = token;
}

const char* tokentype_string (TokenType tt) {
    switch (tt) {
    case END_FILE: return "END_FILE";
    case TEXT: return "TEXT";
    case WHITESPACE: return "WHITESPACE";
    case TAB: return "TAB";
    case NEW_LINE: return "NEW_LINE";
    case BOLD: return "BOLD";
    case ITALIC: return "ITALIC";
    case STRIKETHROUGH: return "STRIKETHROUGH";
    case CODE: return "CODE";
    case INLINE_CODE: return "INLINE_CODE";
    case LINK_TEXT: return "LINK_TEXT";
    case URL: return "URL";
    case IMAGE_TEXT: return "IMAGE_TEXT";
    case H1: return "H1";
    case H2: return "H2";
    case H3: return "H3";
    case H4: return "H4";
    case H5: return "H5";
    case H6: return "H6";
    case UNORDERED_LIST: return "UNORDERED_LIST";
    case ORDERED_LIST: return "ORDERED_LIST";
    case BLOCKQUOTE: return "BLOCKQUOTE";
    case CODE_BLOCK: return "CODE_BLOCK";
    case HORIZONTAL_RULE: return "HORIZONTAL_RULE";
    case ESCAPE: return "ESCAPE";
    default: return "UNKNOWN";
    }
}

int is_skippable (char c) {
    return !(c == SPACE_CHAR || c == NEWLINE_CHAR || c == CARRIAGE_RETURN_CHAR || c == EOF
    || c == 0 || c == '*' || c == '`' || c == '!' || c == '(');
}


void debug_token (Token token) {
    if (token.type == NEW_LINE) printf("Token(%s)\n", tokentype_string(token.type));
    else printf("Token(%s) %s\n", tokentype_string(token.type), token.text);
}

Tokens tokenize (Error* status, char* src) {
    Tokens tokens;
    tokens.cap = 16;
    tokens.size = 0;
    tokens.tokens = (Token*)malloc(sizeof(Token) * tokens.cap);

    size_t len = strlen(src);
    size_t pos = 0;

    while (pos < len) {
        switch (src[pos]) {
        case SPACE_CHAR:
            push_token(&tokens, make_token(WHITESPACE, alloc_slice(src, pos++, 1)));
            break;
        case NEWLINE_CHAR:
        case CARRIAGE_RETURN_CHAR:
            push_token(&tokens, make_token(NEW_LINE, alloc_slice(src, pos++, 1)));
            break;
        case TAB_CHAR:
            push_token(&tokens, make_token(TAB, alloc_slice(src, pos++, 1)));
            break;
        case '*':
            if (src[pos + 1] == '*') {
                push_token(&tokens, make_token(BOLD, alloc_slice(src, pos, 2)));
                pos += 2;
            } else {
                push_token(&tokens, make_token(ITALIC, alloc_slice(src, pos++, 1)));
            }
        case '`':
            if (src[pos + 1] == '`' && src[pos + 2] == '`') {
                // Parse Code Block
            } else {
                // Inline Snippet

            }

            break;
        case '#': {
            size_t token_size = 0;
            while (src[pos++] == '#' && ++token_size);

            char* text = alloc_slice(src, pos - token_size - 1, token_size);
            TokenType type = H1 + token_size - 1;
            push_token(&tokens, make_token(type, text));
            break;
        }

        
        default: {
            size_t token_size = 0;
            while (is_skippable(src[pos++]) && ++token_size);

            char* text = alloc_slice(src, pos - token_size - 1, token_size);
            push_token(&tokens, make_token(TEXT, text));
            pos--;
            break;
        }
        }
    }
    
    // Create a one byte EOF token for the final token. \0
    push_token(&tokens, make_token(END_FILE, calloc(1, sizeof(char))));
    return tokens;
}
