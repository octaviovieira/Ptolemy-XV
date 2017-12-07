#include <Thread.h>
#include <ThreadController.h>
#include "../../../../analise/analise.h"
#include "../../../../aes/aes.h"
#include "../../../mem_data.h"

ThreadController schedule;
Thread memory_monitor;
Thread program;

void show_memory_consumption()
{
	Serial.println( memory_usage() );
}

void algorithm()
{
  BYTE* ct = ptolemy_aes_dec( data_128() , "80000000000000000000000000000000" );
	free(ct);
}

void setup() {

  Serial.begin(9600);

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
