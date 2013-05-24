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
} Symbol;

void addSymbol(char* label, int address);

void solveUnresolvedSymbols(int* objectCode);

void solveSymbol(char* label, int codePosition, int* objectCode);

#endif
