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
        printf("                                                 \n");
        printf("     .                               .......                       .            \n");
        printf("     .             .                ...MM~,      .                              \n");
        printf("       .             ..            ...,DN .  . . .        .       .       .     \n");
        printf("     .          .                  ...,=M,Z..... ..                             \n");
        printf(" .   .  ...                       ...$M,..?MM=..+ .                             \n");
        printf("   .... ..                         .MMM... ..I.:M,                              \n");
        printf("     .   . .    .  ..  .    ..  . .NMM. .DZ.MN:+M.. ... . ..        .. .  . ..  \n");
        printf("   ..          .  .             . :M.II,,?M?::.MI. .           .   ....        .\n");
        printf("       .       .                .7M?N,.M~$?,7Z,IZ?N.              ...I. ..      \n");
        printf("                                .NN.OO,M..+MNMMZ8ND.                          . \n");
        printf("     .                          .MZ..NM:,,..:MNN.....                           \n");
        printf("       .             .          .MD:M......MMMZZMN7..     .                     \n");
        printf("      .   .  ..      .          .MNM.  ...MMDMNMNNM..        .                  \n");
        printf("     .        ..,.,,,.        ..+MN.D...=MNMD.MM,MM,                            \n");
        printf(" ..  . .  ..,.:MMMMMMM..   ...,MN...=,,,:MMMMMMMMMMN..         .                \n");
        printf("...  .  .. :MDO.,...MMMN... .,MN..,...ZMMMMMMMMMMMMMM...     ......             \n");
        printf("     .  .,MM~...  ...:MM~.  ~ND...  ...DMMMMMMMMMMMMM=.      .,,..         . .  \n");
        printf("      ,.,MM:..       .:MD,..MD:....$...:NMMMMMM7$NMM8..   ..,MNMN.              \n");
        printf(" .    ..MD ..        ..MN....M7.,,~MN ..MMMMMMMMMZ..=..   .,NNOMM....           \n");
        printf("       NN,...   .    ..MM, ..MNMM.,NMMMMNMMMMMMMMMM....  ..IM~MMM:,. .    .     \n");
        printf(".  .. ,M,..     .    .,MD...NNMMN:.$MMMMMMMD...,,~.,. ..MN:MMNMMMM..            \n");
        printf("    ,NNM,..    . .   ..M7.,MMMMMMMN..?MMMMMM~.... .. ...MMMMMMMMM. .            \n");
        printf("  . DMMMM~           .=M~.MMMMMMMMM=,..$MMMMMO.....   .$MMMMMMMMM.              \n");
        printf("   .DMMMMM.           MM.MMMMMMMMMMMM..,.INMMM..:,.   .NMMMMMMMM~.              \n");
        printf("    DMMMMM.   .     .IMN,NMMMMMMMMMMMN.. .,?MD,.OM .. .ONMMMMNMM,..     .    .  \n");
        printf(".   $MMMMM.      ....MN.~MMMMMMMMMMMMNN. ,.......MM. ..$MD.MMM8...    . ..    . \n");
        printf("    .8MMMN.     ....NM..8MMMMMMMMMMMMMM,+M...MD..MMD...?+:+Z,.,          .      \n");
        printf("  ....MMM:.      .,:M=,.8MMMMMMMMMMMMMN..M....O.7MMM .N+,8..                    \n");
        printf("  ..  OMM..      .=M8...8MMM$$MMMMMMMMMM8.......?..,NMMMM.      . .  .        . \n");
        printf("       M7..   ....MM,. .8MMN...:MMMMMMMMMN,M~.  ,.$MMMMM....   . .        . .   \n");
        printf("      NM      .. MD... .8MMMN:,.NNMMM..~MM:.....NMMMMMM7...IND$,,.              \n");
        printf("   .,,N...     .MN=. . .MMMMMM$..MMMM,:N..,=.,MMMMMMMND.$MMMMMMMN...            \n");
        printf(".. .,...   ..  7MO.. .:MMMMMMMMM.,,MMN+ .OM =MMMMMMMMN,MMMMMMMMMMM .            \n");
        printf("            . .MM..... MMMMMMMMMMI...,7MMMM.NMMMMMMMD,MMMMMMMMMMMMM.            \n");
        printf("      . .   ..MM. ... .,MMMMMMMMMMM.,=NMMMMMMMMMMMNO.MMMMNMMMMMMMMM.         .. \n");
        printf("     .  .. . .NM,. ..MM~.7MMMMMMMMM?...NMMMMMMMMMM :MMMM~MMMMMMMMMN .           \n");
        printf("     . ...  .NM? . .M.ZMM,..DMMMMMN.. ..~MMMMMMM.,NNMM??MMMMMMMMMM .            \n");
        printf("        .   .MM ...MMMM,MMM?...=MM,.... ..,NM:..NMMMMM,MMMMMMMMMM ...   .       \n");
        printf("  .        ..MM ..ZMMMMMMMMMMD$.,,,,IDI..,...,,MMMMMM,NMMMMMMMMM+.       ..  .. \n");
        printf("     ..     .MM,.,MMMMMMMMMMMMMMMMMM?.,D.+?I+.MMMMMMM.MMMMMMMMMM..    ...$I+~ . \n");
        printf("     .       MM......7MNMMMMMMMMMM7..+MMMM.,,M+7MMMMN$MMMMMMMM$... .  .,MMMM. . \n");
        printf("            .IMI,,OM,.....==IMM=,..DMMMMMMM,,+MM8,,+8DMMMMMMM7...  .....MMMN?.. \n");
        printf("   .        ..NMI.ZMMMMN77:...,IMMMMMNN7.+OMMO....+.,=MMMMMM+.   ....7ON.MI.  . \n");
        printf("     .     ....MMMMMMMMMMMMMM.OMMMMMM$,7MMM...?$M7..7MI.MMN,. .... 8Z,+.......  \n");
        printf("     .        .,7MMMMMMMMMMM,DMMMMMM..MMD,,+MMMMMMMM...MM .   ...NNM.,          \n");
        printf("     .        . ....MMMMMN.7MMMMMMM.OMN,,MMMMMMMMMMMMM..MMD,..,MMM..  .         \n");
        printf(".                .:..IMO.?MNMMMMMM7.MN,,NMMMMMMMMMMMMMM, =D.?MMM,...            \n");
        printf("                 .ZMN+.,MMMMMMMMMM.MM.$MMMMMMMMMMMMMMMMM..8MMM:.... ..       .  \n");
        printf("    .  .        ..OMMMMM~,MMMMMMMM~N.,MMMMMMMMMMMMMMMM, DNMM, D,,.~MN,   .      \n");
        printf(" .   . .         ..MMMMMMMM,.NDMM,NM.8MMMMMMMMMMMNMD..MMMN,:.:.M:. INM.N:,,..   \n");
        printf("  .             ...MMMMMMMMMMD:.,.=M.MMMMMMMMMMMM:, NMMN.,MNMM..,,,IMM,:NN,..   \n");
        printf("                 .OMMMMMMMMMMMMMMMMMO:::.NMMMMD:.:NMMM:.MMMMMMM,~M=MM. ,NM8...  \n");
        printf("         .  .   .?MMMMMM.. ..,~MMNZ:=MMMO...D.,?MMMM:,MMMMMMMMMM=NM:...MMN,,.   \n");
        printf("     .  ..    . .MMMMMM ...: MND7.N?MN:.7MMN:ZMMMD~,..IMMMMMMMMM.=MMMMMMM,...   \n");
        printf("             . ..MMMMMN.. ,?MN7~N.~MZ::M7MMMMMMMI:NMMMMMMMMMMMMM,...OMN,..      \n");
        printf("     ..       ..~MNMMMMN,.~MMMMMMNNM.N=NMMIONMM7IMMMMMMMMMMMMMN,.   .           \n");
        printf("      .        ..~N?OMMN,,NM.$MMM$.IMN~M=NMZ=MM$. .IMMMNMMMMMN=.        .       \n");
        printf("     .           ..NM,MM~MMM=.O,,8MM,OMN.M.M=NM$ ......,IIII=...                \n");
        printf("     .           . ......MMM=M.$Z=M:MD?MN.8MM.N$  .       ...       .           \n");
        printf(".                .. .   ,8MMMMNM$.?:IM?MM:N,8.DM                   .            \n");
        printf("                 .     ...MZ., ,MM,MMMM.MM:8MMM..           .                   \n");
        printf("     . . .             .. ,NN,N~NM8MZ~N,MMM,MMM  .                          ..  \n");
        printf("     .       .         .,IMMNM,.MM.M.NM.N=.MMM~. .                              \n");
        printf(" .      ..            ...Z$$Z?MM8.MMMMM:N?MMM+.                                 \n");
        printf("                 ..    .......7MMMMMMMMM,MMN...                             .   \n");
        printf("      .                      ...:MMMMMMMD,,..                   ...   .,        \n");
        printf(" .   . .                                          .             ..,..           \n");
        printf(" .   ....                                        .  .          ...:.            \n");
        printf("\n            _    _                                         \n");
        printf("           | |  | |                                        \n");
        printf("           | |__| | __ _ _ __  _   _ _ __ ___   __ _ _ __  \n");
        printf("           |  __  |/ _` | '_ \\| | | | '_ ` _ \\ / _` | '_ \\ \n");
        printf("           | |  | | (_| | | | | |_| | | | | | | (_| | | | |\n");
        printf("           |_|  |_|\\__,_|_| |_|\\__,_|_| |_| |_|\\__,_|_| |_|\n\n");
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
    register int stopAddress;
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
        Symbol* lineSymbol = NULL;
        
        //Get first token
        tok = strtok(line, " \t\n");
        if (tok == NULL)
            continue;
        //Get label if exists!
        if (tok[strlen(tok)-1] == ':') {
            tok[strlen(tok)-1] = '\0';
            lineSymbol = addSymbol(tok, codePosition);
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
            if (tok == NULL) {
                printf("Erro de sintaxe na linha %d. Esperando rotulo operando.\n", lineNumber);
                exit(0);
            }
            if (opcode == 4) {
                solveSymbol(tok, codePosition++, objectCode)->cannotBeConstZero = 1;
            } else if (opcode >= 5 && opcode <= 8) {
                solveSymbol(tok, codePosition++, objectCode)->cannotBeData = 1;
            } else if (opcode == 11) {
                solveSymbol(tok, codePosition++, objectCode)->isWritten = 1;
            } else {
                solveSymbol(tok, codePosition++, objectCode);
            }
            if (opcode == 9) {
                tok = strtok(NULL, " \t\n,");
                if (tok == NULL) {
                    printf("Erro de sintaxe na linha %d. Esperando rotulo operando.\n", lineNumber);
                    exit(0);
                }
                solveSymbol(tok, codePosition++, objectCode)->isWritten = 1;
            }
        } else if (opcode == 14) {
            stopAddress = codePosition;
            objectCode[codePosition++] = opcode;
        } else if (opcode == 15) {
            if (lineSymbol == NULL) {
                printf("Erro de sintaxe: utilizacao de SPACE sem rotulo.\n");
                exit(1);
            }
            objectCode[codePosition++] = 0;
        } else {
            if (lineSymbol == NULL) {
                printf("Erro de sintaxe: utilizacao de CONST sem rotulo.\n");
                exit(1);
            }
            lineSymbol->cannotBeWritten = 1;
            tok = strtok(NULL, " \t\n");
            if (tok == NULL) {
                printf("Erro de sintaxe na linha %d. Esperando valor absoluto.\n", lineNumber);
                exit(0);
            }
            register int constant =  (int)strtol(tok, NULL, 0);
            if (constant == 0) {
                lineSymbol->isConstZero = 1;
            }
            objectCode[codePosition++] = constant;
        }
    }
    solveUnresolvedSymbols(objectCode);
    verifyCodeConstraints(stopAddress);
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