#include "Scanner.h"
#include "Symbtab.h"
#include "Token.h"
#include "Tuple.h" // Pour la génération des tuples

#include <stdio.h>
#include <stdlib.h>

/* Voici le scanner/lexer, c'est lui qui se charge de lire
 * le fichier source caractères par caractères. */

void initScanner(Scanner *scanner, Symbtab *symbtab) {
    scanner->symbtab = symbtab;
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

void closeScanner(Scanner *scanner, Symbtab *symbtab) {
    freeSymbTab(symbtab);
    fclose(scanner->fichier_source);

    return;
}

// Pour changer l'état de la machine.
// On en aura besoin pour nextToken().
int fail(Scanner *scanner) {
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

    return scanner->start;
}


// Voir comment reculer la tête de lecture.
Tuple nextToken(Scanner *scanner, Symbtab *symbtab) {
    // Pour initialiser le scanner.
    initScanner(scanner, symbtab);

    char c;
    int state; // Etat de la machine.
    char *lexbuf = ""; // Buffer pour rajouter des caractères.

    while ((c = fgetc(scanner->fichier_source)) != EOF) {
        // Les espaces/commentaires
        if (state == 0) {
            if (c == ' ') {
                // Ne fais rien.
            }
            else if (c == '\t') {
                // Ne fais rien, continue d'avancer.
            }
            else if (c == '\n' || c == '\r') scanner->ligne++; // Saut de ligne.

            else if (c == '#') scanner->ligne++; // Lecture de commentaires

            else {
                state = fail(scanner);
                // Pour une erreur à voir.
                Tuple error = {TOK_ERROR, "Erreur lexicale"};
                return error;
            }
        }
        // Les noms de variable: TOK_ID
        else if (state == 3) {
            // Détecter les lettres avec isLetter(char c)
            if (isLetter(c)) {
                lexbuf = lexbuf + c; // Ajoute le caractère dans le buffer.
                state = 4;
            }
            else state = fail(scanner);
        }
        else if (state == 4) {
            if (isLetter(c) || isNumber(c)) {
                lexbuf = lexbuf + c;
            }
            else state = 5;
        }
        else if (state == 5) {
            state = fail(scanner);
            Tuple num = {TOK_ID, "Var"};

            return num;
        }
    }

    Tuple eof = {TOK_EOF, NULL};
    return eof;
}

// Va servir à la reconnaissance des chiffres.
bool isNumber(char c) {
    char chiffres[] = {
        '0', '1',
        '2', '3',
        '4', '5',
        '6', '7',
        '8', '9'
    };
    
    for (int i = 0; i < 10; ++i) {
        if (c == chiffres[i]) {
            return true;
        }
    }

    return false;
}

// Reconnaissance des lettres.
bool isLetter(char c) {
    char lettres[] = {
        'a', 'b', 'c',
        'd', 'e', 'f',
        'g', 'h', 'i',
        'j', 'k', 'l',
        'm', 'n', 'o',
        'p', 'q', 'r',
        's', 't', 'u',
        'v', 'w', 'x',
        'y', 'z'
    };

    for (int i = 0; i < 26; ++i) {
        if (c == i) {
            return true;
        }
    }

    return false;
}