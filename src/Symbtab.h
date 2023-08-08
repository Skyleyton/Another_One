#include "Token.h"
#include <stddef.h>

#ifndef SYMBTAB_H
#define SYMBTAB_H

// Une ligne de la table des symboles.
typedef struct Symbol {
    char *ligne, *lexeme;
    Token type;
} Symbol;


// Stocke les infos des symboles du code source.
// En fait c'est une énorme dynamic array.
typedef struct Symbtab {
    Symbol *symboles;
    size_t count;
} Symbtab;

// Créer des fonctions d'allocations pour la table des symboles.
// Problèmes qu'il pourrait y avoir :
// Comment suivre en temps réel la table dse symboles qui grossit.

void initSymbTab(Symbtab *symbtab);
void addSymbol(Symbtab *symbtab, const char *ligne, const char *lexeme, Token type);
Symbol *findSymbol(const Symbtab *symbtab, const char *nom);
void freeSymbTab(Symbtab *symbtab);

#endif
