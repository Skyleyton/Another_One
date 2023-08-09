#include <stdio.h>
#include <stdlib.h>

#include "Scanner.h"
#include "Parser.h"
#include "Symbtab.h"
#include "Token.h"

int main(int argc, char **argv) {

    /* if (argc != 2) {
        fprintf(stderr, "Veuillez renseigner un fichier.\n");
        return -1;
    } */

    Scanner scanner;
    Symbtab symbtab;

    initSymbTab(&symbtab);
    addSymbol(&symbtab, "x", TOK_ID);
    addSymbol(&symbtab, "z", TOK_ID);
    printf("%d\n", lookup(&symbtab, "x"));
    printf("%d\n", lookup(&symbtab, "z"));

    //nextToken(&scanner, &symbtab);

    return 0;
}
