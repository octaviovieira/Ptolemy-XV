#include "../../../../serpent/serpent.h"
#include "../../../mem_data.h"

void algorithm(void)
{
  BYTE* ct = ptolemy_serpent_enc( data_256() , "80000000000000000000000000000000" );
  free(ct);
}

void setup() {
    Serial.begin(9600);
}

void loop() {
  algorithm();
  Serial.println("|");
}
