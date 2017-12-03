#include <stdlib.h>
#include <string.h>
#include "./rijndael-api-fst.c"
#include "./rijndael-api-fst.h"
#include "./rijndael-alg-fst.c"
#include "./rijndael-alg-fst.h"

BYTE* hex_str_to_str( BYTE* hex_str, int len )
{
    int i,j;
    BYTE* str = malloc(sizeof(BYTE[len*2+1]));
    strcpy(str,"");
    for( i=0, j=0; i < len; i++, j=j+2 )
        sprintf(str,"%s%02x", str, hex_str[i]);
    return str;
}

BYTE* str_to_hex_str( BYTE* str )
{
    int i, j, tam=strlen(str);
    BYTE aux[3];
    BYTE* hex = malloc(sizeof(BYTE[tam/2+1]));
    aux[2]='\0';
    for( i=0, j=0; i < tam-1; i=i+2, j++ )
    {
        aux[0]=str[i];
        aux[1]=str[i+1];
        hex[j]=strtol(aux,NULL,16);
    }
    hex[j]='\0';

    return hex;
}

BYTE* ptolemy_aes_enc(BYTE* text, BYTE* key)
{
//    Serial.println( text );
    text = str_to_hex_str( text );
//    printHex( text ); Serial.println();
//    text = hex_str_to_str( text, 16 );
//    Serial.println( text );

    cipherInstance *cipher	= malloc(sizeof(cipherInstance));
    keyInstance *keyI 		= malloc(sizeof(keyInstance));
    BYTE *input 		    = text;
    BYTE *outBuffer 		= malloc(sizeof(BYTE[17]));
    int inputLength 		= 128;

    strcpy(keyI->keyMaterial, key);
    keyI->keyLen 		= 128;
    keyI->direction 	= DIR_ENCRYPT;

    cipher->mode 		= MODE_ECB;

    makeKey(keyI, DIR_ENCRYPT, inputLength, keyI->keyMaterial);
    blockEncrypt(cipher, keyI, input, inputLength, outBuffer);

    //printHex( outBuffer );
    //return outBuffer;
    return hex_str_to_str( outBuffer , 16 );
}

BYTE* ptolemy_aes_dec(BYTE* cryptogram, BYTE* key)
{
    cryptogram = str_to_hex_str( cryptogram );
    cipherInstance *cipher	= malloc(sizeof(cipherInstance));
    keyInstance *keyI 		= malloc(sizeof(keyInstance));
    BYTE *input 		    = cryptogram;
    BYTE *outBuffer 		= malloc(sizeof(BYTE[16]));
    int inputLength 		= 128;

    strcpy(keyI->keyMaterial, key);
    keyI->keyLen 		= 128;
    keyI->direction 	= DIR_DECRYPT;

    cipher->mode 		= MODE_ECB;

    makeKey(keyI, DIR_DECRYPT, inputLength, keyI->keyMaterial);
    blockDecrypt(cipher, keyI, input, inputLength, outBuffer);

    return hex_str_to_str( outBuffer ,16);
}
