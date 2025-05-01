/*
 * EVM.c
 * Author : SAIF
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "BUTTON.h"

int main(void)
{
	int CA=0;
	int CB=0;
	int CC=0;
	int CD=0;
	
	LCD_vInit();
	LCD_vSend_cmd(CURSOR_OFF);
	button_vInit('B',3);
	button_vInit('B',4);
	button_vInit('B',5);
	button_vInit('B',6);
	button_vInit('B',7);
	
	LCD_vSend_string("A=0");
	LCD_movecursor(1,12);
	LCD_vSend_string("B=0");
	LCD_movecursor(2,1);
	LCD_vSend_string("C=0");
	LCD_movecursor(2,12);
	LCD_vSend_string("D=0");
	
	while (1) 
    {
		if (button_u8read('B',3)==0)
		{
			CA++;
			LCD_movecursor(1,3);
			if (CA<10)
			{
				LCD_vSend_char(CA+48);
			}
			else if (CA<100)
			{
				LCD_vSend_char(CA/10+48);
				LCD_vSend_char(CA%10+48);
			}
			while(button_u8read('B',3)==0);
		}
		
		else if(button_u8read('B',4)==0)
		{
			CB++;
			LCD_movecursor(1,14);
			if (CB<10)
			{
				LCD_vSend_char(CB+48);
			}
			else if (CB<100)
			{
				LCD_vSend_char(CB/10+48);
				LCD_vSend_char(CB%10+48);
			}
			while(button_u8read('B',4)==0);
		}
		
		else if(button_u8read('B',5)==0)
		{
			CC++;
			LCD_movecursor(2,3);
			if (CC<10)
			{
				LCD_vSend_char(CC+48);
			}
			else if (CC<100)
			{
				LCD_vSend_char(CC/10+48);
				LCD_vSend_char(CC%10+48);
			}
			while(button_u8read('B',5)==0);			
		}
		
		else if(button_u8read('B',6)==0)
		{
			CD++;
			LCD_movecursor(2,14);
			if (CD<10)
			{
				LCD_vSend_char(CD+48);
			}
			else if (CD<100)
			{
				LCD_vSend_char(CD/10+48);
				LCD_vSend_char(CD%10+48);
			}
			while(button_u8read('B',6)==0);
		}
		
		else if(button_u8read('B',7)==0)
		{
			CA=CB=CC=CD=0;
			LCD_movecursor(1,1);
			LCD_vSend_string("A=0 ");
			LCD_movecursor(1,12);
			LCD_vSend_string("B=0 ");
			LCD_movecursor(2,1);
			LCD_vSend_string("C=0 ");
			LCD_movecursor(2,12);
			LCD_vSend_string("D=0 ");
			LCD_movecursor(1,1);
		}
		_delay_ms(150);
    }
}