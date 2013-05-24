//
//  main2.c
//  Hanuman
//
//  Created by Daniel Sandoval on 22/05/2013.
//  Copyright (c) 2013 LoopEC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"
#include "LexicalAnalyser.h"

void saveOutput(int* objectCode, int codePosition);

int main(int argc, const char * argv[])
{
    FILE* fp = fopen("/Users/sandoval/Desktop/Hanuman/Hanuman/calculadoraAsm.asm", "r");
    char line[10000] = "";
    int objectCode[65536];
    register int lineNumber = 0;
    register int codePosition = 0;
    register int opcode = 0;
    register char *tok;
    
    while (!feof(fp)) {
        lineNumber++;
        fgets(line, 10000, fp);
        preprocessLine(line);
        
        
        //Get first token
        tok = strtok(line, " \t\n");
        if (tok == NULL)
            continue;
        //Get label if exists!
        if (tok[strlen(tok)-1] == ':') {
            tok[strlen(tok)-1] = '\0';
            addSymbol(tok, codePosition);
            tok = strtok(NULL, " \t\n");
        }
        
        opcode = translateOperationToken(tok);
        if (opcode < 1) {
            printf("ERRO! Instrucao nao reconhecida: %s! (linha %d)", tok, lineNumber);
            exit(1);
        }
        //Operacao de duas ou tres posicoes na memoria
        if (opcode < 14) {
            objectCode[codePosition++] = opcode;
            tok = strtok(NULL, " \t\n,");
            solveSymbol(tok, codePosition++, objectCode);
            if (opcode == 9) {
                tok = strtok(NULL, " \t\n,");
                solveSymbol(tok, codePosition++, objectCode);
            }
        } else if (opcode == 14) {
            objectCode[codePosition++] = opcode;
        } else if (opcode == 15) {
            objectCode[codePosition++] = 0;
        } else {
            tok = strtok(NULL, " \t\n");
            objectCode[codePosition++] = (int)strtol(tok, NULL, 0);
        }
    }
    solveUnresolvedSymbols(objectCode);
    for (register int i = 0; i<codePosition; i++) {
        printf("%d\t", objectCode[i]);
    }
    saveOutput(objectCode, codePosition);
    
    return 0;
}

void saveOutput(int* objectCode, int codePosition) {
    FILE *fp;
    short int code[65536];
    fp = fopen("/Users/sandoval/Desktop/Hanuman/Hanuman/teste.bin", "wb");
    for (register int i = 0; i < codePosition; i++) {
        code[i] = (short int)objectCode[i];
    }
    fwrite(code, sizeof(short int), codePosition, fp);
    fclose(fp);
}