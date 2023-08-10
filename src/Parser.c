#include "Parser.h"
#include "Symbtab.h"
#include "Scanner.h"
#include "Token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialisation du Parser, renvoie -1 si échec sinon renvoie 0.
int initParser(Parser *parser, Scanner *scanner, Symbtab *symbtab) {

    parser->scanner = scanner;
    parser->symbtab = symbtab;

    if (scanner == NULL || symbtab == NULL) {
        return -1;
    }

    return 0;
}

void match(Parser *parser, Token token) {
    if (strcmp(getTokenName(token), parser->lookahead.token)) {
        parser->lookahead = nextToken(parser->scanner, parser->symbtab);
    }
    else {
        fprintf(stderr, "Erreur syntaxique ligne: %d, %s attendu", parser->scanner->ligne, getTokenName(token));

        return;
    }

    return;
}