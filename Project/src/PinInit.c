/*
 * PinInit.c
 *
 * Sätter pin 12 och pin 9 till 1. Pinnarna används på motorshielden
 *
 * Created: 2016-05-05 12:52:23
 *
 *  Author: Patricia
 */ 
#include <asf.h>
#include "asf.h"
#include "PinInit.h"

#define pin_12 PIO_PD8_IDX
#define pin_9 PIO_PC21_IDX
#define pinMode ioport_set_pin_dir
#define digitalWrite ioport_set_pin_level

/*
* Sätter digital pinnar som ska anslutas till motorshieldens brake och direction
*/
void Init_pins(){
pinMode(pin_12, 1);
pinMode(pin_9,1);
digitalWrite(pin_12,HIGH);
digitalWrite(pin_9,LOW);	
}