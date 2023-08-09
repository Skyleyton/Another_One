#include <stdio.h>
#include <stdlib.h>

#include "Scanner.h"
#include "Parser.h"
#include "Symbtab.h"

int main(int argc, char **argv) {

    /* if (argc != 2) {
        fprintf(stderr, "Veuillez renseigner un fichier.\n");
        return -1;
    } */

    Scanner scanner;
    Symbtab symbtab;

    nextToken(&scanner, &symbtab);

    return 0;
}
