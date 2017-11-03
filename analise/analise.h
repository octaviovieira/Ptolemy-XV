
#include <time.h>
#include "rtc.h"

unsigned long int cycles_clocks_for_execution( void*(*enc_dec_rot)(void*,void*), void* arg1, void* arg2, void** resp )
{
    unsigned long int ti, tf;
    ti = micros();
    if( resp != NULL ) *resp = enc_dec_rot(arg1,arg2);
    else enc_dec_rot(arg1,arg2);
    tf = micros();
    return (tf - ti) * clockCyclesPerMicrosecond();
}

unsigned long int time_for_execution( void*(*enc_dec_rot)(void*,void*), void* arg1, void* arg2, void** resp )
{
    unsigned long int ti, tf;
    ti = rtc_get_time();
    if( resp != NULL ) *resp = enc_dec_rot(arg1,arg2);
    else enc_dec_rot(arg1,arg2);
    tf = rtc_get_time();
    return (tf - ti) * 1000;
}
