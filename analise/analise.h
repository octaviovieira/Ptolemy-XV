
#include <time.h>
//#include "rtc.h"

/*#define MEGA_SRAM 8192

static int free_sram()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v-(__brkval ==0?(int)&__heap_start:(int) __brkval);
}

unsigned int memory_usage(void)
{
    return MEGA_SRAM - free_sram();
}*/

unsigned long int cycles_of_clocks_for_execution( void(*rot)(void) )
{
    unsigned long int ti, tf;
    ti = micros();
    rot();
    tf = micros();
    return (tf - ti) * clockCyclesPerMicrosecond();
}

unsigned long int time_for_execution( void(*rot)(void) )
{
    unsigned long int ti, tf;
    ti = millis();
    rot();
    tf = millis();
    return (tf - ti);
}
