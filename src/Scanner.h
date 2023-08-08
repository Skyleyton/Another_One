#include <stdio.h>
#include "Tuple.h"

#ifndef SCANNER_H
#define SCANNER_H

typedef struct Scanner {
    FILE *fichier_source; // Le fichier qui va être scanné.
    int start; // Là où notre automate sera positionné.
    int ligne; // Numéro de la ligne, pour reporter les erreurs.
} Scanner;

void initScanner(Scanner *scanner);
void closeScanner(Scanner *scanner);
Tuple nextToken(Scanner *scanner);
void fail(Scanner *scanner);

#endif