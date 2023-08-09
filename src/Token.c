#include "Token.h"

// Va servir à traduire le token en string, pour la fonction getToken.
char *getTokenName(Token token) {

    char *name;

    switch (token) {

        case TOK_NUM:
            name = "num";
            break;
        case TOK_ADD:
            name = "add";
            break;
        case TOK_MINUS:
            name = "minus";
            break;
        case TOK_DIV:
            name = "div";
            break;
        case TOK_MULT:
            name = "mult";
            break;
        case TOK_TYPE:
            name = "type_var";
            break;
        case TOK_ID:
            name = "id";
            break;
        case TOK_TRUE:
            name = "true";
            break;
        case TOK_FALSE:
            name = "false";
            break;
        case TOK_EOF:
            name = "eof";
            break;
        case TOK_ERROR:
            name = "error";
            break;
    }

    return name;
}