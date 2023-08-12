#include "Parser.h"
#include "Symbtab.h"
#include "Scanner.h"
#include "Token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialisation du Parser, renvoie -1 si échec sinon renvoie 0.
int initParser(Parser *parser, Scanner *scanner, Symbtab *symbtab) {

    parser->scanner = scanner;
    parser->symbtab = symbtab;

    if (scanner == NULL || symbtab == NULL) {
        return -1;
    }

    return 0;
}

void match(Parser *parser, Token token) {
    if (strcmp(getTokenName(token), parser->lookahead.token)) {
        parser->lookahead = nextToken(parser->scanner, parser->symbtab);
    }
    else {
        fprintf(stderr, "Erreur syntaxique ligne: %d, %s attendu", parser->scanner->ligne, getTokenName(token));

        return;
    }

    return;
}

void parse(Parser *parser) {

    return;
}

// L -> I ; L | tok_eof
void L(Parser *parser) {
    if (parser->lookahead.token == getTokenName(TOK_ID)) {
        I(parser);
        match(parser, TOK_SCOLON);
        L(parser);
    }
    else match(parser, TOK_EOF);

    return;
}

// I -> tok_id tok_affect E {setValue(id_adr, E_val), print(getValue(id_adr))} | id tok_affect E relop E
void I(Parser *parser) {
    int *id_adr = parser->lookahead.attribut;
    match(parser, TOK_ID);
    match(parser, TOK_AFFECT);
    float E_val = E(parser);
    setValue(parser->symbtab, *id_adr, E_val);
    printf("%s = %f", getLexeme(parser->symbtab, *id_adr), getValue(parser->symbtab, *id_adr));

    return;
}

float E(Parser *parser) {
    float T_val = T(parser);
    float E_val = 0;
    if (parser->lookahead.token == getTokenName(TOK_ADD)) {
        match(parser, TOK_ADD);
        float E1_val = E(parser);
        E_val = T_val + E1_val;
    }
    else if (parser->lookahead.token == getTokenName(TOK_MINUS)) {
        match(parser, TOK_MINUS);
        float E1_val = E(parser);
        E_val = T_val - E1_val;
    }
    else {
        E_val = T_val;
    }

    return E_val;
}

float T(Parser *parser) {
    float F_val = F(parser);
    float T_val = 0;
    if (parser->lookahead.token == getTokenName(TOK_MULT)) {
        match(parser, TOK_MULT);
        float T1_val = T(parser);
        T_val = F_val * T1_val;
    }
    else if (parser->lookahead.token == getTokenName(TOK_DIV)) {
        match(parser, TOK_DIV);
        float T1_val = T(parser);
        T_val = F_val / T1_val;
    }
    else {
        T_val = F_val;
    }

    return T_val;
}

float F(Parser *parser) {
    float *F_val = 0;
    void *num_val = 0;
    void *id_adr = 0;
    if (parser->lookahead.token == getTokenName(TOK_L_PARENT)) {
        match(parser, TOK_L_PARENT);
        float E_val = E(parser);
        match(parser, TOK_R_PARENT);
        *F_val = E_val;
    }
    else if (parser->lookahead.token == getTokenName(TOK_NUM)) {
        char *lexeme = parser->lookahead.attribut;
        for (int i = 0; i < strlen(lexeme); ++i) {
            if (i == '.') {
                num_val = (float *) lexeme;
            }
            else {
                num_val = (int *) lexeme;
            }
            match(parser, TOK_NUM);
            F_val = num_val;
        }
    }
    else if (parser->lookahead.token == getTokenName(TOK_ID)) {
        id_adr = parser->lookahead.attribut;
        float val = getValue(parser->symbtab, *(int *)id_adr);
        if (val == -1.0) {
            char *var = getLexeme(parser->symbtab, *(int *)id_adr);
            fprintf(stderr, "Ligne: %d, la variable %s n'a pas de valeur\n", parser->scanner->ligne, var);
            exit(64);
        }
        match(parser, TOK_ID);
        *F_val = val;
    }
    else {
        char *error_msg = malloc(256 * sizeof(char));
        sprintf(error_msg, "Ligne: %d \'(\', TOK_NUM ou TOK_ID attendu\n", parser->scanner->ligne);
        fprintf(stderr, "%s", error_msg);
        exit(64);
    }

    return *F_val;
}