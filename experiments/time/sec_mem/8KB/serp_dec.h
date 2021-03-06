#include "../../../../analise/analise.h"
#include "../../../../serpent/serpent.h"
#include "../../../file.h"

void algorithm(void)
{
  file_crip_operation( ptolemy_serpent_dec, "8KB.txt", "80000000000000000000000000000000" );
}

void setup() {
    Serial.begin(9600);
    begin_sd_controller();
}

void loop() {
  unsigned long int c = time_for_execution( algorithm );
  Serial.println( c );
}
