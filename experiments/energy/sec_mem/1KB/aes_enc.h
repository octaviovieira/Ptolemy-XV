#include "../../../../aes/aes.h"
#include "../../../file.h"

void algorithm(void)
{
  file_crip_operation( ptolemy_aes_enc, "1KB.txt", "80000000000000000000000000000000" );
}

void setup() {
    Serial.begin(9600);
    begin_sd_controller();
}

void loop() {
  algorithm();
  Serial.println("|");
}
