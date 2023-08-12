#include "Scanner.h"
#include "Symbtab.h"
#include "Token.h"
#include "Tuple.h" // Pour la génération des tuples

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Voici le scanner/lexer, c'est lui qui se charge de lire
 * le fichier source caractères par caractères. */

void initScanner(Scanner *scanner, Symbtab *symbtab) {
    scanner->symbtab = symbtab;
    scanner->fichier_source = fopen("test/string.txt", "r");
    // scanner->fichier_source = fopen(filePath, "r");
    scanner->start = 0; // Le départ de l'automate
    scanner->ligne = 1;
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
        fprintf(stderr, "Aucune ligne dans le fichier.\n");
        exit(64);
    }
    else {
        fprintf(stderr, "Erreur du scanner ligne: %d", scanner->ligne);
        exit(64);
    }

    return scanner->start;
}


// Voir comment reculer la tête de lecture.
Tuple nextToken(Scanner *scanner, Symbtab *symbtab) {
    // Pour initialiser le scanner.
    initScanner(scanner, symbtab);

    char c;
    int state = 0; // Etat de la machine.
    char *lexbuf = malloc(256 * sizeof(char)); // Buffer pour rajouter des caractères.
    // Pour récup la chaine de caractères qu'on va changer à chaque ajout de caractère.
    int p;
    long pos_pointeur = 0;

    //while ((c = fgetc(scanner->fichier_source)) != EOF) {
    while (true) {
        // Les espaces/commentaires
        if (state == 0) {
            c = fgetc(scanner->fichier_source);
            if (c == ' ' || c == '\t') {
                // Ne fais rien.
            }
            else if (c == '\n' || c == '\r') scanner->ligne++; // Saut de ligne.

            else if (c == '#') scanner->ligne++; // Lecture de commentaires

            else {
                state = fail(scanner);
                // Pour une erreur à voir.
                // Tuple error = {getTokenName(TOK_ERROR), "Erreur lexicale"};
                // return error;
            }
        }
        // Les noms de variable: TOK_ID
        else if (state == 3) {
            // Détecter les lettres avec isLetter(char c)
            if (isLetter(c)) {
                appendChar(lexbuf, c);
                state = 4;
            }
            else state = fail(scanner);
        }
        else if (state == 4) {
            // Pour récupérer la position et renvoyer au state 5.
            pos_pointeur = ftell(scanner->fichier_source);
            c = fgetc(scanner->fichier_source);
            if (isLetter(c) || isNumber(c)) {
                appendChar(lexbuf, c);
            }
            else state = 5;
        }
        else if (state == 5) {
            // state = fail(scanner);
            fseek(scanner->fichier_source, pos_pointeur, SEEK_SET);
            p = addSymbol(symbtab, lexbuf, TOK_ID);

            // Tuple result = {getToken(symbtab, p)};
            Tuple result = {getTokenName(TOK_ID), lexbuf};
            return result;
        }
        // Les nombres : TOK_NUM.
        else if (state == 6) {
            if (isNumber(c)) {
                appendChar(lexbuf, c);
                state = 7;
            }
            else state = fail(scanner);
        }
        else if (state == 7) {
            pos_pointeur = ftell(scanner->fichier_source);
            c = fgetc(scanner->fichier_source);
            if (isNumber(c)) {
                appendChar(lexbuf, c);
                // reste sur le state 7.
            }
            else if (c == '.') {
                appendChar(lexbuf, c);
                state = 8;
            }
            else if (isLetter(c)) {
                fprintf(stderr, "Erreur lexicale ligne (state 7): %d\n", scanner->ligne);
                exit(64);
            }
            else {
                state = 10;
            }
        }
        else if (state == 8) {
            c = fgetc(scanner->fichier_source);
            if (isNumber(c)) {
                appendChar(lexbuf, c);
                state = 9;
            }
            else {
                fprintf(stderr, "Erreur lexicale ligne (state 8): %d\n", scanner->ligne);
                exit(64);
            }
        }
        else if (state == 9) {
            pos_pointeur = ftell(scanner->fichier_source);
            c = fgetc(scanner->fichier_source);
            if (isNumber(c)) {
                appendChar(lexbuf, c);
                // reste sur le state 9.
            }
            else {
                state = 10;
            }
        }
        else if (state == 10) {
            fseek(scanner->fichier_source, pos_pointeur, SEEK_SET);
            p = addSymbol(symbtab, lexbuf, TOK_NUM);

            Tuple result = {getTokenName(TOK_NUM), lexbuf};
            return result;
        }
        else if (state == 11) {
            if (c == '+') {
                Tuple result = {getTokenName(TOK_ADD), NULL};
                return result;
            }
            else if (c == '=') {
                Tuple result = {getTokenName(TOK_AFFECT), NULL};
                return result;
            }
            else if (c == '-') {
                Tuple result = {getTokenName(TOK_MINUS), NULL};
                return result;
            }
            else if (c == '/') {
                Tuple result = {getTokenName(TOK_DIV), NULL};
                return result;
            }
            else if (c == '(') {
                Tuple result = {getTokenName(TOK_L_PARENT), NULL};
                return result;
            }
            else if (c == ')') {
                Tuple result = {getTokenName(TOK_R_PARENT), NULL};
                return result;
            }
            else if (c == ';') {
                Tuple result = {getTokenName(TOK_SCOLON), NULL};
                return result;
            }
            else state = fail(scanner);
        }
        else {
            fprintf(stderr, "Erreur lexicale ligne (EOF): %d", scanner->ligne);
        }
    }

    Tuple eof = {getTokenName(TOK_EOF), NULL};
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
        if (c == lettres[i] || c == toupper(lettres[i])) {
            return true;
        }
    }

    return false;
}

// Fonctions pour l'ajout de caractères dans le lexbuf.
int appendChar(char *chaine, char c) {
    int len = strlen(chaine);

    chaine[len] = c;
    chaine[len+1] = '\0';

    return 0;
}