/*
 * Calculator.c
 * Author : SAIF
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "KEYPAD.h"

int stringToInt(char* str)
{
	int result = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

void intToString(int num, char* str)
{
	char temp[8];
	int i = 0, j = 0;
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	if (num < 0)
	{
		str[j++] = '-';
		num = -num;
	}
	while (num != 0)
	{
		temp[i++] = (num % 10) + '0';
		num /= 10;
	}
	temp[i] = '\0';
	for (i = i - 1; i >= 0; --i)
	{
		str[j++] = temp[i];
	}
	str[j] = '\0';
}

int main(void)
{
	LCD_vInit();
	keypad_vInit();
	
	long res = 0;
	char num1[9] = {0}, num2[9] = {0}, op = '\0', resultStr[8];
	unsigned char n1 = 0, n2 = 0;
	unsigned char isFirstNum = 1;

	while (1)
	{
		unsigned char key = NOTPRESSED;
		do
		{
			key = keypad_u8Read();
		} while (key == NOTPRESSED);
		
		if (key >= '0' && key <= '9')
		{
			if (isFirstNum)
			{
				num1[n1++] = key;
				num1[n1] = '\0';
			}
			else
			{
				num2[n2++] = key;
				num2[n2] = '\0';
			}
			LCD_vSend_char(key);
		}
		else if (key == '+' || key == '-' || key == '*' || key == '/')
		{
			if (!isFirstNum)
			{
				LCD_vSend_string(" Err");
				_delay_ms(1000);
				LCD_clearscreen();
				n1 = n2 = 0;
				isFirstNum = 1;
				num1[0] = num2[0] = '\0';
			}
			else if (n1 > 0)
			{
				op = key;
				isFirstNum = 0;
				LCD_vSend_char(key);
			}
			else
			{
				LCD_vSend_string(" Err");
				_delay_ms(1000);
				LCD_clearscreen();
			}
		}
		else if (key == '=' && op != '\0' && n2 > 0)
		{
			int number1 = stringToInt(num1);
			int number2 = stringToInt(num2);
			switch (op)
			{
				case '+':
				res = number1 + number2;
				break;
				
				case '-':
				res = number1 - number2;
				break;
				
				case '*':
				res = number1 * number2;
				break;
				
				case '/':
				if (number2 == 0)
				{
					LCD_vSend_string(" Err");
					_delay_ms(1000);
					LCD_clearscreen();
					n1 = n2 = 0;
					isFirstNum = 1;
					num1[0] = num2[0] = '\0';
					op = '\0';
					continue;
				}
				res = number1 / number2;
				break;
				
				default:
				LCD_vSend_string(" Err");
				_delay_ms(1000);
				LCD_clearscreen();
				n1 = n2 = 0;
				isFirstNum = 1;
				num1[0] = num2[0] = '\0';
				op = '\0';
				continue;
			}
			LCD_vSend_char('=');
			intToString(res, resultStr);
			LCD_vSend_string(resultStr);
			
			n1 = n2 = 0;
			isFirstNum = 1;
			num1[0] = num2[0] = '\0';
			op = '\0';
		}
		else if (key == 'C')
		{
			LCD_clearscreen();
			n1 = n2 = 0;
			isFirstNum = 1;
			num1[0] = num2[0] = '\0';
			op = '\0';
		}
		else
		{
			LCD_vSend_string(" Err");
			_delay_ms(1000);
			LCD_clearscreen();
		}
		_delay_ms(200);
	}
}