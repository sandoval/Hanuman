//
//  LexicalAnalyser.c
//  Hanuman
//
//  Created by Daniel Sandoval on 23/05/2013.
//  Copyright (c) 2013 LoopEC. All rights reserved.
//

#include "LexicalAnalyser.h"

int hashString29 (char* string);

const char* opTokens[29] = {"const", //0
                          "",
                          "jmpn", //2
                          "space", //3 (2)
                          "jmpp", //4
                          "div", //5 (4)
                          "store", //6
                          "add", //7
                          "jmp", //8
                          "input", //9
                          "load", //10
                          "sub", //11
                          "copy", //12 (8)
                          "",
                          "jmpz", //14
                          "mult", //15
                          "",
                          "",
                          "",
                          "stop", //19
                          "",
                          "",
                          "output", //22
                          "",
                          "",
                          "",
                          "",
                          "",
                          ""};
const int opCodes[23] = {16, //0
    -1,
    6, //2
    15, //3 (2)
    7, //4
    4, //5 (4)
    11, //6
    1, //7
    5, //8
    12, //9
    10, //10
    2, //11
    9, //12 (8)
    -1,
    8, //14
    3, //15
    -1,
    -1,
    -1,
    14, //19
    -1,
    -1,
    13, //22
};

int translateOperationToken(char* token) {
    register int hash = hashString29(token);
    register int i;
    if (strcmp(token, opTokens[hash]) == 0) {
        return opCodes[hash];
    }
    for (i = hash+1; i<29; i++) {
        if (strcmp(token, opTokens[i]) == 0) {
            return opCodes[i];
        }
    }
    return -1;
}

void preprocessLine(char* line) {
    register char* semicolonPos = strchr(line, ';');
    register int pos = 0;
    if (semicolonPos != NULL) {
        line[semicolonPos-line] = '\0';
    }
    while (line[pos] != '\0') {
        if ((line[pos] < 48 && line[pos] != 10 && line[pos] != 32 && line[pos] != 9 && line[pos] != 44 && line[pos] != 45) || (line[pos] > 59 && line[pos] < 65) || (line[pos] > 90 && line[pos] < 95) || line[pos] == 96 || line[pos] > 122) {
            printf("ERRO: Encontrado caracter inválido no programa: ASCII %d\n", line[pos]);
            exit(1);
        }
        if (line[pos] >= 65 && line[pos] <= 90) {
            line[pos] += 32;
        }
        pos++;
    }
}

int hashString29 (char* string) {
	register int i = 0;
	register int hash = 0;
	while (string[i] != '\0') {
		hash += string[i];
		i++;
	}
	return hash%29;
}