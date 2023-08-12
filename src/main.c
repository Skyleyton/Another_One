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
    Parser parser;

    initSymbTab(&symbtab);
    initScanner(&scanner, &symbtab);
    // printf("etat: %d\n", scanner.start);
    printf("%s\n", nextToken(&scanner, &symbtab).token);
    // printf("etat: %d\n", scanner.start);

    /* for (int i = 0; i < 10; ++i) {
        printf("lexeme: %s ", getLexeme(&symbtab, i));
    }

    printf("\n");

    for (int i = 0; i < 10; ++i) {
        printf("token: %s ", getToken(&symbtab, i));
    } */

    affichSymbTab(&symbtab);

    parse(&parser);
    // printf("%s\n", getLexeme(&symbtab, 2));

    // Les essais à la main.
    /* addSymbol(&symbtab, "1", TOK_NUM);
    addSymbol(&symbtab, "z", TOK_ID);
    printf("%d\n", lookup(&symbtab, "1"));
    printf("%d\n", lookup(&symbtab, "z"));
    printf("Token à la position 0: %s\n", getToken(&symbtab, 0)); */

    //nextToken(&scanner, &symbtab);

    return 0;
}
