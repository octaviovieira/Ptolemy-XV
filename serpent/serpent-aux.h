
#ifndef _SERPENT_AUX_
#define _SERPENT_AUX_

#include "serpent-api.h"

EMBED_RCS(serpent_aux_h,
          "$Id: serpent-aux.h,v 1.3 1998/06/07 08:08:05 fms Exp $")



int checkHexNumber(char* s);
char hex(int n);
int stringToWords(char* s, WORD w[], int words);
char* wordsToString(WORD x[], int size, char* buffer);
void printHeader(char* filename, char* mode, char* test);
void render(char* label, WORD x[], int size);

#endif



