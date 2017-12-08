#include <Thread.h>
#include <ThreadController.h>
#include "../../../../analise/analise.h"
#include "../../../../aes/aes.h"
#include "../../../file.h"

ThreadController schedule;
Thread memory_monitor;
Thread program;

void show_memory_consumption()
{
	Serial.println( memory_usage() );
}

void algorithm()
{
  file_crip_operation( ptolemy_aes_enc, "1KB.txt", "80000000000000000000000000000000" );
}

void setup() {

  Serial.begin(9600);
  begin_sd_controller();

  memory_monitor.setInterval(50);
  memory_monitor.onRun( show_memory_consumption );

  program.setInterval(500);
  program.onRun( algorithm );

  schedule.add( &memory_monitor );
  schedule.add( &program );

  Serial.println( "INICIO" );
}

void loop() {
  schedule.run();
}
