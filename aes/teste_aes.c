#include <stdlib.h>
#include <string.h>
#include "./rijndael-api-fst.c"
#include "./rijndael-api-fst.h"
#include "./rijndael-alg-fst.c"
#include "./rijndael-alg-fst.h"

int main(int argc, char* argv[])
{
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

