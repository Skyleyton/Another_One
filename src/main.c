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
    addSymbol(&symbtab, "1", TOK_NUM);
    addSymbol(&symbtab, "z", TOK_ID);
    printf("%d\n", lookup(&symbtab, "1"));
    printf("%d\n", lookup(&symbtab, "z"));
    printf("Token à la position 0: %s\n", getToken(&symbtab, 0));

    //nextToken(&scanner, &symbtab);

    return 0;
}
