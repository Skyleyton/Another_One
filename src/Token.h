#ifndef TOKEN_H
#define TOKEN_H

// Anciennement TokenType.
// Les différents type de token reconnaissables pour l'instant :
typedef enum Token {
    TOK_NUM, // Constantes numériques
    TOK_ADD, // Opérateur
    TOK_MINUS,
    TOK_AFFECT,
    TOK_DIV,
    TOK_MULT,
    TOK_TYPE, // Type (f32, i32, u32)
    TOK_ID, // Les noms de variables 
    TOK_TRUE, // Bool
    TOK_FALSE,
    TOK_EOF,
    TOK_ERROR // Token signifiant une erreur dans l'analyse syntaxique.
} Token;

// à voir si besoin, je peux directement utiliser TokenType.
/* typedef struct Token {
    TokenType token;
} Token; */

char *getTokenName(Token token);

#endif
