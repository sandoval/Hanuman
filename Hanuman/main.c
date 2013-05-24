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

void saveOutput(short int* objectCode, int codePosition, const char* filePath);

int main(int argc, const char * argv[])
{
    if((argc > 3) || (argc == 1) || (strcmp(argv[1],"-h") == 0) || ( strcmp(argv[1],"-H") == 0) || ( strcmp(argv[1], "--help") == 0 )){
        printf("\nManual de funcionamento do Hanuman:\n\n");
        printf("\t hanuman --help, -h, -H\t - Instruções\n\n");
        printf("\t hanuman [arquivo fonte] [arquivo de destino]\n");
        printf("\t\t  Monta o arquivo o codigo apresentado no arquivo fonte especificado\n\t\t e salva o mesmo no arquivo de destino\n");
        printf("\t\t  Caso nao seja especificado um segundo parametro, o arquivo \n\t\t sera salvo no diretorio atual com nome s.out\n\n");
        printf(" -- Created by Daniel Sandoval and Pedro Salum \t\t--\n -- Copyright (c) 2013 LoopEC. All rights reserved. -- \n\n");
        exit(0);
    }
    FILE* fp = fopen(argv[1], "r");
    char line[10000] = "";
    short int objectCode[65536];
    register int lineNumber = 0;
    register int codePosition = 0;
    register int opcode = 0;
    register char *tok;
    
    if (fp == NULL) {
        printf("ERRO! Nao foi possivel abrir o arquivo de entrada!\n");
        exit(1);
    }
    
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
    if (argc == 3) {
        saveOutput(objectCode, codePosition, argv[2]);
    } else {
        saveOutput(objectCode, codePosition, "s.out");
    }
    return 0;
}

void saveOutput(short int* objectCode, int codePosition, const char* filePath) {
    FILE *fp;
    fp = fopen(filePath, "wb");
    if (fp == NULL) {
        printf("ERRO! Nao foi possivel abrir o arquivo de saida.\n");
        exit(1);
    }
    fwrite(objectCode, sizeof(short int), codePosition, fp);
    fclose(fp);
}