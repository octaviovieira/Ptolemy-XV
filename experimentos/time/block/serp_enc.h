#include "../../../analise/analise.h"
#include "../../../serpent/serpent.h"

void algorithm(void)
{
  BYTE* ct = ptolemy_serpent_enc("00000000000000000000000000000000", "80000000000000000000000000000000");
  free(ct);
}

void setup() {
    Serial.begin(9600);
}

void loop() {
  unsigned long int c = time_for_execution( algorithm );
  Serial.println( c );
}
