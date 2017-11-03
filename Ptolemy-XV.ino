#include <string.h>
#include "aes/aes.h"
//#include "analise/analise.h"


void setup() {
  Serial.begin(9600);
  //rtc_begin();
  //rtc_adjust(5,2,11,2017,19,29,0);
}

void loop() {
    char* text = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    char* key = "80000000000000000000000000000000";
    BYTE* ct = ptolemy_aes_enc(text, key);
    int a=0;
    while(a<16)
    {
        Serial.print(*ct,HEX);
        Serial.print("|");
        ++ct;
        a++;
    }
    Serial.println("");
    //Serial.println( (char*)ct );
  //Serial.println( (char*)pt );
  //unsigned long int tmp;
  //unsigned char *c,*t;
  //c = ptolemy_aes_enc("00000000000000000000000000000000","80000000000000000000000000000000");
  //t = ptolemy_aes_dec(c,"80000000000000000000000000000000");
  //Serial.println(ptolemy_aes_enc("00000000000000000000000000000000","80000000000000000000000000000000"));
  //Serial.println(ptolemy_aes_dec("0edd33d3c621e546455bd8ba1418bec8","80000000000000000000000000000000"));
  //tmp = time_for_execution( ptolemy_aes_enc, "00000000000000000000000000000000", "80000000000000000000000000000000", NULL );
  //Serial.println( tmp );
  delay(9000);
}
