#include "Symbtab.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Les fonctions de la table des symboles.
void initSymbTab(Symbtab *symbtab) {
    symbtab->symboles = NULL;
    symbtab->count = 0;
    symbtab->capacity = 10;

    return;
}

// Pour ajouter un symbole, l'accroissement de la liste se fait automatiquement.
void addSymbol(Symbtab *symbtab, const char *lexeme, Token token) {
    if (checkCapacity(symbtab)) {
        reallocate(symbtab);
    }

    Symbol new_symbol;
    new_symbol.lexeme = strdup(lexeme);
    new_symbol.token = token;

    symbtab->symboles[symbtab->count] = new_symbol;
    symbtab->count++;

    return;
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

int lookup(Symbtab *symbtab, const char *lexeme) {
    int p = 0;
    for (size_t i = 0; i < symbtab->count; ++i) {
        if (strcmp(symbtab->symboles[i].lexeme, lexeme) == 0) {
            return p;
        }
        else p++;
    }

    return -1;
}

void freeSymbTab(Symbtab *symbtab) {
    for (size_t i = 0; i < symbtab->count; ++i) {
        free(symbtab->symboles[i].lexeme);
    }

    free(symbtab->symboles);

    return;
}

Token getToken(Symbtab *symbtab, int i) {
    return symbtab->symboles[i].token;
}