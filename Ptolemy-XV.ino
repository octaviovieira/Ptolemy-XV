
//#include "experiments/experiment_executor.h"
#include "aes/aes.h"
#include "experiments/file.h"

void setup()
{
  Serial.begin(9600);
  begin_sd_controller();
}

void loop()
{
  Serial.println("INI");
  file_crip_operation( ptolemy_aes_enc, "2K.txt", "80000000000000000000000000000000" );
  Serial.println("FIM");
  delay(100000);
}
