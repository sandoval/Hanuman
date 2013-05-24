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

Symbol* addSymbol(char* label, int address) {
    validateSymbol(label);
    if (symbolList == NULL) {
        //Lista de símbolos está vazia, basta adicionar.
        symbolList = initializeSymbol();
        symbolList->label = (char*)malloc((strlen(label)+1)*sizeof(char));
        strcpy(symbolList->label, label);
        symbolList->address = address;
        return symbolList;
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
                    return currentSymbol;
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
        return currentSymbol;
    }
}

Symbol* solveSymbol(char* label, int codePosition, short int* objectCode) {
    if (symbolList == NULL) {
        symbolList = initializeSymbol();
        symbolList->label = (char*)malloc((strlen(label)+1)*sizeof(char));
        strcpy(symbolList->label, label);
        objectCode[codePosition] = -1;
        symbolList->lateBindingReference = codePosition;
        return symbolList;
    }
    register Symbol* currentSymbol = symbolList;
    register Symbol* lastSymbol = NULL;
    while (currentSymbol != NULL) {
        if (strcmp(label, currentSymbol->label) == 0) {
            if (currentSymbol->address != -1) {
                //Esse símbolo já foi resolvido!
                objectCode[codePosition] = currentSymbol->address;
                return currentSymbol;
            }
            //Símbolo não resolvido!
            objectCode[codePosition] = currentSymbol->lateBindingReference;
            currentSymbol->lateBindingReference = codePosition;
            return currentSymbol;
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
    return currentSymbol;
}

void solveUnresolvedSymbols(short int* objectCode) {
    register Symbol* currentSymbol = symbolList;
    while (currentSymbol != NULL) {
        if (currentSymbol->address == -1) {
            printf("ERRO! Ha referencia nao resolvida: %s\n", currentSymbol->label);
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
        if ((*ch < 48) || (*ch > 57 && *ch < 95) || (*ch > 95 && *ch < 97) || (*ch > 122)) {
            printf("Rotulo invalido! Contem caracter nao permitido: %s.\n", symbol);
            exit(1);
        }
        ch++;
    }
}

void verifyCodeConstraints(int stopAddress) {
    register Symbol* currentSymbol = symbolList;
    while (currentSymbol != NULL) {
        if (currentSymbol->isConstZero && currentSymbol->cannotBeConstZero) {
            printf("ERRO! Rotulo '%s' nao pode ser constante zero pois e usada em uma divisao.\n", currentSymbol->label);
            exit(1);
        }
        if (currentSymbol->isWritten && currentSymbol->cannotBeWritten) {
            printf("ERRO! Rotulo '%s' nao pode ser escrito por ser uma constante!\n", currentSymbol->label);
            exit(1);
        }
        if (currentSymbol->cannotBeData && (currentSymbol->address > stopAddress)) {
            printf("ERRO! Rotulo '%s' e do segmento de dados e nao pode ser utilizado em um salto.\n", currentSymbol->label);
            exit(1);
        }
        currentSymbol = currentSymbol->nextEntry;
    }
}

Symbol* initializeSymbol() {
    register Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->lateBindingReference = -1;
    symbol->address = -1;
    symbol->nextEntry = NULL;
    symbol->label = NULL;
    symbol->cannotBeData = 0;
    symbol->cannotBeConstZero = 0;
    symbol->isConstZero = 0;
    symbol->cannotBeWritten = 0;
    symbol->isWritten = 0;
    return symbol;
}