#include "Symbtab.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Les fonctions de la table des symboles.
void initSymbTab(Symbtab *symbtab) {
    symbtab->symboles = NULL;
    symbtab->count = 0;

    return;
}

void addSymbol(Symbtab *symbtab, const char *ligne, const char *lexeme, Token type) {
    Symbol new_symbol;
    new_symbol.ligne = strdup(ligne);
    new_symbol.lexeme = strdup(lexeme);
    new_symbol.type = type;

    // Augmentation de la taille du tableau dynamique.
    symbtab->symboles = realloc(symbtab->symboles, (symbtab->count + 1) * sizeof(Symbol));
    symbtab->symboles[symbtab->count] = new_symbol;
    symbtab->count++;

    return;
}

Symbol *findSymbol(const Symbtab *symbtab, const char *nom) {
    for (size_t i = 0; i < symbtab->count; ++i) {
        if (strcmp(symbtab->symboles[i].lexeme, nom) == 0) {
            return &symbtab->symboles[i];
        }
    }

    return NULL;
}

void freeSymbTab(Symbtab *symbtab) {
    for (size_t i = 0; i < symbtab->count; ++i) {
        free(symbtab->symboles[i].lexeme);
        free(symbtab->symboles[i].ligne);
    }

    free(symbtab->symboles);

    return;
}
