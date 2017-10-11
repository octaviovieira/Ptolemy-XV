
#include <time.h>

int number_of_clocks( void*(*enc_dec_rot)(void*,void*) )
{
    int nc = clockCyclesPerMicrosecond();
}
