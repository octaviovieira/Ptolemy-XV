#include <string.h>
#include <time.h>
#include "serpent/serpent.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  /*char* t = malloc(33*sizeof(char));
  char* k = malloc(65*sizeof(char));
  strcpy(t,"76b69e932663857482e183479aa57766");
  strcpy(k,"00000000000000000000000000000000");
  Serial.print( ptolemeu_serpent_dec(t,k) );
  Serial.print( "\n" );
  delay(10000);*/
  Serial.print(clockCyclesPerMicrosecond());
}
