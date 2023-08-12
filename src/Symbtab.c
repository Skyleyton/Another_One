#include "Symbtab.h"
#include "Token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Les fonctions de la table des symboles.
void initSymbTab(Symbtab *symbtab) {
    symbtab->capacity = 10;
    symbtab->symboles = malloc(symbtab->capacity * sizeof(Symbol));
    symbtab->count = 0;

    return;
}

// Pour ajouter un symbole, l'accroissement de la liste se fait automatiquement.
int addSymbol(Symbtab *symbtab, const char *lexeme, Token token) {
    if (checkCapacity(symbtab)) {
        reallocate(symbtab);
    }

    Symbol new_symbol;
    new_symbol.lexeme = strdup(lexeme);
    new_symbol.token = token;

    symbtab->symboles[symbtab->count] = new_symbol;
    symbtab->count++;

    return symbtab->count;
}

/* Pour renvoyer le token à la position "i", utilise getTokenName pour traduire le 
token en string. */
char *getToken(Symbtab *symbtab, int i) {
    if (symbtab->count < i) {
        fprintf(stderr, "Accès à un token qui n'est pas dans la table des symboles.\n");

        return "NULL";
    }

    return getTokenName(symbtab->symboles[i].token);
}

// Pour la réallocation, se fait automatiquement en ajoutant des symboles.
void reallocate(Symbtab *symbtab) {
    int new_capacity = symbtab->capacity * 2;
    Symbol *new_liste = realloc(symbtab->symboles, new_capacity * sizeof(Symbol));
    if (new_liste == NULL) {
        fprintf(stderr, "Erreur de réallocation de la table des symboles.\n");
        return;
    }

    symbtab->capacity = new_capacity;
    symbtab->symboles = new_liste;

    return;
}

// Vérifie si le count est égal à la capacité pour permettre la réallocation.
bool checkCapacity(Symbtab *symbtab) {
    if (symbtab->count == symbtab->capacity) {
        return true;
    }

    return false;
}

// Pour chercher un lexeme.
int lookup(Symbtab *symbtab, const char *lexeme) {
    int p = 0;
    for (int i = 0; i < symbtab->count; ++i) {
        if (strcmp(symbtab->symboles[i].lexeme, lexeme) == 0) {
            return p;
        }
        else p++;
    }

    return -1;
}

// Pour désallouer la table des symboles.
void freeSymbTab(Symbtab *symbtab) {
    for (size_t i = 0; i < symbtab->count; ++i) {
        free(symbtab->symboles[i].lexeme);
    }

    free(symbtab->symboles);

    return;
}

// Pour récupérer le lexeme à la position i, va servir au débogage.
char *getLexeme(Symbtab *symbtab, int i) {
    return symbtab->symboles[i].lexeme;
}

// Fonction d'affichage de la table des symboles.
void affichSymbTab(Symbtab *symbtab) {

    printf("-------- SymbTab -------\n");
    printf("Lexeme\tToken\tPosition");

    for (int i = 0; i < symbtab->count; ++i) {
        printf("\n%s\t%s\t%d", getLexeme(symbtab, i), getToken(symbtab, i), i);
    }

    printf("\n------------------------\n");

    return;
}

void setValue(Symbtab *symbtab, int i, float val) {
    symbtab->symboles[i].value = val;

    return;
}

float getValue(Symbtab *symbtab, int i) {
    return symbtab->symboles[i].value;
}
