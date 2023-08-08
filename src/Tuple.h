#include "Token.h"

#ifndef TUPLE_H
#define TUPLE_H


// Le scanner fournit des couples (token, attribut) au parser où attribut
// est :
// soit une information unique concernant 'token',
// soit un pointeur sur l'entrée de la table des symboles où les
// infos sur 'token' sont stockées,
// soit le pointeur NULL si aucune infos sur 'token' n'est nécessaire.

// Token token est le type (enum) de token que le scanner enverra au parser.
// void *attribut est l'information sur token.
typedef struct Tuple {
    Token token;
    void *attribut;
} Tuple;

#endif
