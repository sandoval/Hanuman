//
//  SymbolTable.h
//  Hanuman
//
//  Created by Daniel Sandoval on 23/05/2013.
//  Copyright (c) 2013 LoopEC. All rights reserved.
//

#ifndef Hanuman_SymbolTable_h
#define Hanuman_SymbolTable_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symbol_table_entry {
    char* label;
    int address;
    int lateBindingReference;
    struct symbol_table_entry* nextEntry;
    int cannotBeData;
    int cannotBeConstZero;
    int isConstZero;
    int cannotBeWritten;
    int isWritten;
} Symbol;

Symbol* addSymbol(char* label, int address);

void solveUnresolvedSymbols(short int* objectCode);

Symbol* solveSymbol(char* label, int codePosition, short int* objectCode);

void verifyCodeConstraints(int stopAddress);

#endif
