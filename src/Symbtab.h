#include "Token.h"
#include <stdbool.h>

#ifndef SYMBTAB_H
#define SYMBTAB_H

// Une ligne de la table des symboles.
typedef struct Symbol {
    char *lexeme;
    Token token;
    float value;
} Symbol;


// Stocke les infos des symboles du code source.
// En fait c'est une énorme dynamic array.
typedef struct Symbtab {
    Symbol *symboles;
    int count;
    int capacity;
} Symbtab;

// Créer des fonctions d'allocations pour la table des symboles.
// Problèmes qu'il pourrait y avoir :
// Comment suivre en temps réel la table des symboles qui grossit.

void initSymbTab(Symbtab *symbtab);
int addSymbol(Symbtab *symbtab, const char *lexeme, Token token); // Pour l'ajout de symboles.
char *getToken(Symbtab *symbtab, int i);
void setValue(Symbtab *symbtab, int i, float val);
float getValue(Symbtab *symbtab, int i);
int lookup(Symbtab *symbtab, const char *lexeme);
void freeSymbTab(Symbtab *symbtab);
void reallocate(Symbtab *symbtab);
bool checkCapacity(Symbtab *symbtab);

// Juste pour le débogage.
char *getLexeme(Symbtab *symbtab, int i);
void affichSymbTab(Symbtab *symbtab);

#endif
