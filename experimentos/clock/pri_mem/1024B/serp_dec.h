#include "../../../../analise/analise.h"
#include "../../../../serpent/serpent.h"
#include "../../../mem_data.h"

void algorithm(void)
{
  BYTE* ct = ptolemy_serpent_dec( data_1024() , "80000000000000000000000000000000" );
  free(ct);
}

void setup() {
    Serial.begin(9600);
}

void loop() {
  unsigned long int c = cycles_of_clocks_for_execution( algorithm );
  Serial.println( c );
}
