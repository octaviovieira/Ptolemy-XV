#include <stdlib.h>
#include <string.h>
#include "./rijndael-api-fst.c"
#include "./rijndael-api-fst.h"
#include "./rijndael-alg-fst.c"
#include "./rijndael-alg-fst.h"

char* ptolemy_aes_enc(char* text, char* key)
{
    cipherInstance *cipher	= malloc(sizeof(cipherInstance));
    keyInstance *keyI 		= malloc(sizeof(keyInstance));
    BYTE *input 		= text;
    BYTE *outBuffer 		= malloc(sizeof(BYTE[16]));
    int inputLength 		= 128;

    strcpy(keyI->keyMaterial, key);    
    keyI->keyLen 		= 128;
    keyI->direction 		= DIR_ENCRYPT;
    
    cipher->mode 		= MODE_ECB;

    makeKey(keyI, DIR_ENCRYPT, inputLength, keyI->keyMaterial);
    blockEncrypt(cipher, keyI, input, inputLength, outBuffer);
    
    return outBuffer;
}

char* ptolemy_aes_dec(char* cryptogram, char* key)
{
    /*char* text = malloc((strlen(cryptogram)+1)*sizeof(char));
    WORD text_w[4], cryptogram_w[4], key_w[8];
    stringToWords(cryptogram, cryptogram_w, 4);
    stringToWords(key, key_w, 8);
    doOneBlockViaNIST(cryptogram_w, key, text_w, DIR_DECRYPT, FALSE);
    wordsToString(text_w,4,text);
    return text;*/
}
