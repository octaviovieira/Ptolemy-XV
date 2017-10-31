#include <stdlib.h>
#include <string.h>
#include "./rijndael-api-fst.c"
#include "./rijndael-api-fst.h"
#include "./rijndael-alg-fst.c"
#include "./rijndael-alg-fst.h"

int main(int argc, char* argv[])
{
    /*char* cryptogram = malloc((strlen(text)+1)*sizeof(char));
    WORD text_w[4], cryptogram_w[4], key_w[8];
    stringToWords(text, text_w, 4);
    stringToWords(key, key_w, 8);
    doOneBlockViaNIST(text_w, key, cryptogram_w, DIR_ENCRYPT, FALSE);
    wordsToString(cryptogram_w,4,cryptogram);
    return cryptogram;*/

    cipherInstance *cipher	= malloc(sizeof(cipherInstance));
    keyInstance *key 		= malloc(sizeof(keyInstance));
    BYTE *input 		= malloc(sizeof(BYTE[16]));
    BYTE *outBuffer 		= malloc(sizeof(BYTE[16]));
    int inputLength 		= 128;

    strcpy(input, "00000000000000000000000000000000");

    strcpy(key->keyMaterial, "40000000000000000000000000000000");    
    key->keyLen 		= 128;
    key->direction 		= DIR_ENCRYPT;
    
    cipher->mode 		= MODE_ECB;

    makeKey(key, DIR_ENCRYPT, inputLength, key->keyMaterial);
    
    blockEncrypt(cipher, key, input, inputLength, outBuffer);
    
    printf("TEXT: %s\n", input);
    printf("KEY:  %s\n", key->keyMaterial);
    printf("OUT:  %s\n", outBuffer);
    printf("OUT: ");
    while(*outBuffer)
    {
        printf("%02x", *outBuffer);
        ++outBuffer;
    }
    return 0;
}

