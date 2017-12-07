#include "../../../analise/analise.h"
#include "../../../aes/aes.h"

void algorithm(void)
{
  BYTE* ct = ptolemy_aes_enc("00000000000000000000000000000000", "80000000000000000000000000000000");
  free(ct);
}

void setup() {
    Serial.begin(9600);
}

void loop() {
  algorithm();
}
