#include "../../../../analise/analise.h"
#include "../../../../aes/aes.h"
#include "../../../file.h"

void algorithm(void)
{
  file_crip_operation( ptolemy_aes_enc, "4KB.txt", "80000000000000000000000000000000" );
}

void setup() {
    Serial.begin(9600);
    begin_sd_controller();
}

void loop() {
  unsigned long int c = cycles_of_clocks_for_execution( algorithm );
  Serial.println( c );
}
