#include <stdlib.h>
#include <string.h>
#include "serpent-core.c"

char* ptolemy_serpent_enc(char* text, char* key)
{
    char* cryptogram = malloc((strlen(text)+1)*sizeof(char));
    WORD text_w[4], cryptogram_w[4], key_w[8];
    stringToWords(text, text_w, 4);
    stringToWords(key, key_w, 8);
    doOneBlockViaNIST(text_w, key, cryptogram_w, DIR_ENCRYPT, FALSE);
    wordsToString(cryptogram_w,4,cryptogram);
    return cryptogram;
}

char* ptolemy_serpent_dec(char* cryptogram, char* key)
{
    char* text = malloc((strlen(cryptogram)+1)*sizeof(char));
    WORD text_w[4], cryptogram_w[4], key_w[8];
    stringToWords(cryptogram, cryptogram_w, 4);
    stringToWords(key, key_w, 8);
    doOneBlockViaNIST(cryptogram_w, key, text_w, DIR_DECRYPT, FALSE);
    wordsToString(text_w,4,text);
    return text;
}
