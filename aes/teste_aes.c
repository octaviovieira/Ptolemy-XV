#include <stdlib.h>
#include <string.h>
#include "./aes.h"

int main(int argc, char* argv[])
{
    int a=0,b=0;
    char* text = "00000000000000000000000000000000";
    char* key = "80000000000000000000000000000000";
    BYTE* ct = ptolemy_aes_enc(text, key);
    BYTE* pt = ptolemy_aes_dec(ct, key);

    printf("TEXT: %s\n", text);
    printf("KEY:  %s\n", key);
    printf("CRP:  %s\n", ct);
    printf("PLT:  %s\n", pt);
    /*printf("OUT: ");
    while(a<16)
    {
        printf("%02x", *ct);
        ++ct;
        a++;
    }*/
}

