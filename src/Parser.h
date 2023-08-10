#include "Scanner.h"
#include "Symbtab.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef PARSER_H
#define PARSER_H

// Analyse syntaxique.
typedef struct Parser {
    Scanner *scanner;
    Symbtab *symbtab;
    Tuple lookahead;
} Parser;

int initParser(Parser *parser, Scanner *scanner, Symbtab *symbtab);
void match(Parser *parser, Token token); // À voir si ça fonctionne.

#endif
