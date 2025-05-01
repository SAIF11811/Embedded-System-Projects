#include "DIO.h"

void button_vInit(unsigned char portname,unsigned char pinnumber)
{
	DIO_vsetPINDir(portname,pinnumber,0);//Set the given pin in the given port as an input
	DIO_vconnectpullup(portname,pinnumber,1);//Connect a pull up resistor to the given pin at the given port
}

unsigned char button_u8read(unsigned char portname,unsigned char pinnumber)
{
	unsigned char x;
	x=DIO_u8read(portname,pinnumber);//return the current status of the given pin
	return x ;
}