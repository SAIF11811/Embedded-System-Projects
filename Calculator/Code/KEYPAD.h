#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_

#define KEYPAD_PORT 'C'
#define NOTPRESSED 0xff
#include "DIO.h"

void keypad_vInit();
char keypad_u8Read();

#endif /* KEYPAD_DRIVER_H_ */