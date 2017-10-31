#include <stdlib.h>
#include <string.h>
#include "./aes.h"
int main(int argc, char* argv[])
{
	
    char* text = "00000000000000000000000000000000";
    char* key = "80000000000000000000000000000000";
    BYTE* ct = ptolemy_aes_enc(text, key);

    
    printf("TEXT: %s\n", text);
    printf("KEY:  %s\n", key);
    printf("OUT:  %s\n", ct);
    printf("OUT: ");
    while(*ct)
    {
        printf("%02x", *ct);
        ++ct;
    }
}

