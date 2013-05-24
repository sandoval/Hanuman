//
//  LexicalAnalyser.h
//  Hanuman
//
//  Created by Daniel Sandoval on 23/05/2013.
//  Copyright (c) 2013 LoopEC. All rights reserved.
//

#ifndef Hanuman_LexicalAnalyser_h
#define Hanuman_LexicalAnalyser_h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int translateOperationToken(char* token);

void preprocessLine(char* line);

#endif
