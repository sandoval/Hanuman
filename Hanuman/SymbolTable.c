//
//  SymbolTable.c
//  Hanuman
//
//  Created by Daniel Sandoval on 23/05/2013.
//  Copyright (c) 2013 LoopEC. All rights reserved.
//

#include "SymbolTable.h"

Symbol* symbolList = NULL;
Symbol* initializeSymbol();
void validateSymbol(char* symbol);

void addSymbol(char* label, int address) {
    validateSymbol(label);
    if (symbolList == NULL) {
        //Lista de símbolos está vazia, basta adicionar.
        symbolList = initializeSymbol();
        symbolList->label = (char*)malloc((strlen(label)+1)*sizeof(char));
        strcpy(symbolList->label, label);
        symbolList->address = address;
    } else {
        //Vamos adicionar ao final da lista de símbolos e interromper o programa caso haja duplicatas.
        register Symbol* currentSymbol = symbolList;
        register Symbol* lastSymbol = NULL;
        while (currentSymbol != NULL) {
            if (strcmp(label, currentSymbol->label) == 0) {
                if (currentSymbol->address != -1) {
                    printf("ERRO! Redeclaracao de rotulo: %s", label);
                    exit(1);
                } else {
                    currentSymbol->address = address;
                    return;
                }
            }
            lastSymbol = currentSymbol;
            currentSymbol = currentSymbol->nextEntry;
        }
        currentSymbol = initializeSymbol();
        lastSymbol->nextEntry = currentSymbol;
        currentSymbol->label = (char*)malloc((strlen(label)+1)*sizeof(char));
        strcpy(currentSymbol->label, label);
        currentSymbol->address = address;
    }
}

void solveSymbol(char* label, int codePosition, short int* objectCode) {
    if (symbolList == NULL) {
        symbolList = initializeSymbol();
        symbolList->label = (char*)malloc((strlen(label)+1)*sizeof(char));
        strcpy(symbolList->label, label);
        objectCode[codePosition] = -1;
        symbolList->lateBindingReference = codePosition;
    } else {
        register Symbol* currentSymbol = symbolList;
        register Symbol* lastSymbol = NULL;
        while (currentSymbol != NULL) {
            if (strcmp(label, currentSymbol->label) == 0) {
                if (currentSymbol->address != -1) {
                    //Esse símbolo já foi resolvido!
                    objectCode[codePosition] = currentSymbol->address;
                    return;
                }
                //Símbolo não resolvido!
                objectCode[codePosition] = currentSymbol->lateBindingReference;
                currentSymbol->lateBindingReference = codePosition;
                return;
            }
            lastSymbol = currentSymbol;
            currentSymbol = currentSymbol->nextEntry;
        }
        //Símbolo não resolvido e não consta na tabela!
        currentSymbol = initializeSymbol();
        lastSymbol->nextEntry = currentSymbol;
        currentSymbol->label = (char*)malloc((strlen(label)+1)*sizeof(char));
        strcpy(currentSymbol->label, label);
        currentSymbol->lateBindingReference = codePosition;
        objectCode[codePosition] = -1;
    }
}

void solveUnresolvedSymbols(short int* objectCode) {
    register Symbol* currentSymbol = symbolList;
    while (currentSymbol != NULL) {
        if (currentSymbol->address == -1) {
            printf("ERRO! Ha referencia nao resolvida: %s", currentSymbol->label);
            exit(1);
        }
        if (currentSymbol->lateBindingReference != -1) {
            register int currentReference = currentSymbol->lateBindingReference;
            register int nextReference;
            while (currentReference != -1) {
                nextReference = objectCode[currentReference];
                objectCode[currentReference] = currentSymbol->address;
                currentReference = nextReference;
            }
        }
        currentSymbol = currentSymbol->nextEntry;
    }
}

void validateSymbol(char* symbol) {
    register char* ch = symbol;
    if (*symbol >= 48 && *symbol <= 57) {
        printf("Rotulo invalido! Comeca com um numero: %s.\n", symbol);
        exit(1);
    }
    while (*ch != '\0') {
        if ((*ch < 48) || (*ch > 57 && *ch < 97) || (*ch > 122)) {
            printf("Rotulo invalido! Contem caracter nao permitido: %s.\n", symbol);
            exit(1);
        }
        ch++;
    }
}


Symbol* initializeSymbol() {
    register Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->lateBindingReference = -1;
    symbol->address = -1;
    symbol->nextEntry = NULL;
    symbol->label = NULL;
    return symbol;
}