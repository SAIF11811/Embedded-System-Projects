 #include "keypad.h"

 void keypad_vInit()
 {
	 DIO_vsetPINDir(KEYPAD_PORT,0,1);
	 DIO_vsetPINDir(KEYPAD_PORT,1,1);
	 DIO_vsetPINDir(KEYPAD_PORT,2,1);
	 DIO_vsetPINDir(KEYPAD_PORT,3,1);
	 
	 DIO_vsetPINDir(KEYPAD_PORT,4,0);
	 DIO_vsetPINDir(KEYPAD_PORT,5,0);
	 DIO_vsetPINDir(KEYPAD_PORT,6,0);
	 DIO_vsetPINDir(KEYPAD_PORT,7,0);
	 
	 DIO_vconnectpullup(KEYPAD_PORT,4,1);
	 DIO_vconnectpullup(KEYPAD_PORT,5,1);
	 DIO_vconnectpullup(KEYPAD_PORT,6,1);
	 DIO_vconnectpullup(KEYPAD_PORT,7,1);
 }

 char keypad_u8Read()
 {
	 char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
	 char row,coloumn,x;
	 char returnval=NOTPRESSED;
	 
	 for(row=0;row<4;row++)
	 {
		 DIO_write(KEYPAD_PORT,0,1);
		 DIO_write(KEYPAD_PORT,1,1);
		 DIO_write(KEYPAD_PORT,2,1);
		 DIO_write(KEYPAD_PORT,3,1);
		 
		 DIO_write(KEYPAD_PORT,row,0);
		 for(coloumn=0;coloumn<4;coloumn++)
		 {
			 x=DIO_u8read(KEYPAD_PORT,(coloumn+4));
			 if(x==0)
			 {
				 returnval=arr[row][coloumn];
				 break;
			 }
		 }
		 
		 if(x==0)
		 {
			 break;
		 }
	 }
	 
	 return returnval ;
 }