#include "Token.h"
#include <stddef.h>
#include <stdbool.h>

#ifndef SYMBTAB_H
#define SYMBTAB_H

// Une ligne de la table des symboles.
typedef struct Symbol {
    char *lexeme;
    Token token;
} Symbol;


// Stocke les infos des symboles du code source.
// En fait c'est une énorme dynamic array.
typedef struct Symbtab {
    Symbol *symboles;
    size_t count;
    size_t capacity;
} Symbtab;

// Créer des fonctions d'allocations pour la table des symboles.
// Problèmes qu'il pourrait y avoir :
// Comment suivre en temps réel la table des symboles qui grossit.

void initSymbTab(Symbtab *symbtab);
void addSymbol(Symbtab *symbtab, const char *lexeme, Token token); // Pour l'ajout de symboles.
int lookup(Symbtab *symbtab, const char *lexeme);
void freeSymbTab(Symbtab *symbtab);
void reallocate(Symbtab *symbtab);
bool checkCapacity(Symbtab *symbtab);

#endif
