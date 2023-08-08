#include "Scanner.h"
#include "Symbtab.h"
#include "Token.h"
#include "Tuple.h" // Pour la génération des tuples

#include <stdio.h>
#include <stdlib.h>

/* Voici le scanner/lexer, c'est lui qui se charge de lire
 * le fichier source caractères par caractères. */


void initScanner(Scanner *scanner) {
    scanner->fichier_source = fopen("test/string.txt", "r");
    // scanner->fichier_source = fopen(filePath, "r");
    scanner->start = 0; // Le départ de l'automate
    scanner->ligne = 0;
    if (scanner->fichier_source == NULL) {
        fprintf(stderr, "Échec de l'ouverture du fichier\n");
        return;
    }

    return;
}

void closeScanner(Scanner *scanner) {
    fclose(scanner->fichier_source);

    return;
}

// Pour changer l'état de la machine.
// On en aura besoin pour nextToken().
void fail(Scanner *scanner) {
    if (scanner->start == 0) {
        scanner->start = 3;
    }
    else if (scanner->start == 3) {
        scanner->start = 6;
    }
    else if (scanner->start == 6) {
        scanner->start = 11;
    }
    else if (scanner->start == 11) {
        fprintf(stderr, "Erreur lexicale !\n");
    }
}

Tuple nextToken(Scanner *scanner) {
    // Pour initialiser le scanner.
    initScanner(scanner);

    char c;
    int state; // Etat de la machine.

    while ((c = fgetc(scanner->fichier_source)) != EOF) {
        // Les espaces
        if (state == 0) {
            if (c == ' ') {
                // Ne fais rien.
            }
            else if (c == '\t') {
                // Ne fais rien, continue d'avancer.
            }
            else if (c == '\n' || c == '\r') {
                scanner->ligne++; // Saut de ligne.
            }
            else {
                fail(scanner);
                // Pour une erreur à voir.
                Tuple error = {TOK_ERROR, "Erreur lexicale"};
                return error;
            }
        }
    }

    Tuple eof = {TOK_EOF, NULL};
    return eof;
}
