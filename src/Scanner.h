#include <stdio.h>
#include <stdbool.h>
#include "Tuple.h"
#include "Symbtab.h"

#ifndef SCANNER_H
#define SCANNER_H

typedef struct Scanner {
    Symbtab *symbtab;
    FILE *fichier_source; // Le fichier qui va être scanné.
    int start; // Là où notre automate sera positionné.
    int ligne; // Numéro de la ligne, pour reporter les erreurs.
} Scanner;

void initScanner(Scanner *scanner, Symbtab *symbtab);
void closeScanner(Scanner *scanner, Symbtab *symbtab);
Tuple nextToken(Scanner *scanner, Symbtab *symbtab);
int fail(Scanner *scanner);

// Pour détecter les lettres et les chiffres.
bool isLetter(char c);
bool isNumber(char c);

#endif
