
#ifndef RTC_H
#define RTC_H

#include <Wire.h>

#define RTC_ADR 0x68
//#define ZERO 0x00
byte ZERO = 0x00;

static byte to_bcb(byte val)
{
	return ( (val/10*16) + (val%10) );
}

static byte to_dec(byte val)
{
	return ( (val/16*10) + (val%16) );
}

void rtc_begin()
{
    Wire.begin();
}

void rtc_adjust( byte dw, byte d, byte m, byte y, byte h, byte min, byte s )
{
    Wire.beginTransmission(RTC_ADR);
	Wire.write(ZERO);
	Wire.write(to_bcb(s));
	Wire.write(to_bcb(min));
	Wire.write(to_bcb(h));
	Wire.write(to_bcb(dw));
	Wire.write(to_bcb(d));
	Wire.write(to_bcb(m));
	Wire.write(to_bcb(h));
	Wire.write(ZERO);
	Wire.endTransmission();
}

unsigned long int rtc_get_time()
{
    int s,min,h,dw,d,m,y;
    Wire.beginTransmission(RTC_ADR);
	Wire.write(ZERO);
	Wire.endTransmission();

	Wire.requestFrom(RTC_ADR, 7);

	s = to_dec(Wire.read());
	min = to_dec(Wire.read());
	h = to_dec(Wire.read());
	dw = to_dec(Wire.read());
	d = to_dec(Wire.read());
	m = to_dec(Wire.read());
	y = to_dec(Wire.read());

	return (s+(min*60)+(h*24));
}

#endif
