//
//  main.c
//  Hanuman
//
//  Created by Daniel Sandoval and Pedro Salum on 04/05/2013.
//  Copyright (c) 2013 LoopEC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SOURCE_FILE_MAX_CHARS 100000
#define TESTMODE

char* loadFileToMemory(const char* path);

int main(int argc, const char * argv[])
{
    
#ifndef TESTMODE
    if (argc < 2) {
        printf("\n\tEntre com a opção --help para obter ajuda\n\n");
        exit(1);
    }
    else{
        if((strcmp(argv[1],"-h") == 0) || ( strcmp(argv[1],"-H") == 0) || ( strcmp(argv[1], "--help") ==0 )){
            printf("\nManual de funcionamento do Hanuman:\n\n");
            printf("\t --help, -h, -H\t - Instruções\n\n");
            printf("\t [nome do .s] [nome do .bin]\n");
            printf("\t\t Monta o arquivo .s especificado e salva o mesmo no .bin\n\n");
            printf("\t\t Caso nao seja especificado um segundo paramentro, o arquivo \n\t\tde saida tera o mesmo nome do de entrada\n\n");
            printf("\n\n -- Created by Daniel Sandoval and Pedro Salum --\n -- Copyright (c) 2013 LoopEC. All rights reserved. -- \n\n");
            exit(2);
            
        }
        else if (strlen(argv[1]) >= 3) {

            char* code = loadFileToMemory(argv[1]);
            puts(code);
            
        }
        
    }
#endif

#ifdef TESTMODE
        char* code = loadFileToMemory("/Users/sandoval/Desktop/Hanuman/Hanuman/teste.txt");
        puts(code);

#endif

    
    
    return 0;

}

char* loadFileToMemory(const char* path) {
    FILE* fp = fopen(path, "r");
    char* code = (char*)malloc(sizeof(char)*SOURCE_FILE_MAX_CHARS);
    register int c;
    register long position = 0;
    
    if (fp == NULL) {
        printf("ERRO: não foi possível abrir o arquivo para leitura!\n");
        exit(1);
    }
    c = fgetc(fp);
    while (c != EOF) {
        if (position >= (SOURCE_FILE_MAX_CHARS-2)) {
            printf("ERRO: Arquivo fonte muito grande para processar!");
            exit(1);
        }
        if ((c < 48 && c != 10 && c != 32) || (c > 59 && c < 65) || (c > 90 && c < 97) || c > 122) {
            printf("ERRO: Encontrado caracter inválido no programa: %d\n", c);
            exit(1);
        }
        if (c == ';') {
            while (c != '\n' && c != EOF)
                c = fgetc(fp);
            continue;
        }
        if (c == '\t' || c == ' ') {
            c = fgetc(fp);
            while (c == '\t' || c == ' ')
                c = fgetc(fp);
            code[position++] = ' ';
            continue;
        }
        if (c == '\n') {
            c = fgetc(fp);
            while (c == '\n')
                c = fgetc(fp);
            code[position++] = '\n';
            continue;
        }
        code[position++] = c;
        c = fgetc(fp);
    }
    if (code[position-1] != '\n')
        code[position++] = '\n';
    code[position] = '\0';
    
    fclose(fp);
    return code;
}

