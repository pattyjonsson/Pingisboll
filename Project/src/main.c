/**
* main.c
*
* Den här klassen initierar alla funktioner vi behöver för att göra en pid-reglering samt skicka värden till matlab
*
* Author: Martin och Patricia
*/
#include <asf.h>
#include "task_PID.h"
#include "task_komm.h"
#include "consoleFunctions.h"
#include "ADCFunctions.h"
#include "PWMFunctions.h"
#include "communication.h"
#include "PinInit.h"

/*
* Initierar alla funktioner vi behöver såsom PWM,ADC,ConfigureConsole,setupUArt etc.
*/
int main (void)
{
	sysclk_init();
	board_init();
	configureConsole();
	setupUART();
	PWMInit();		
	ADCInit();
	Init_pins();
/*Startar tasks*/
if(xTaskCreate(task_komm,(const signed char * const)"lamp",TASK_KOMM_STACK_SIZE,NULL, TASK_KOMM_STACK_PRIORITY,NULL) != pdPASS){
	printf("Failed to create test lamp task\r\n");
}
if(xTaskCreate(task_PID,(const signed char * const) "Led",TASK_LED_STACK_SIZE,NULL,TASK_LED_STACK_PRIORITY, NULL) != pdPASS){
	printf("Failed to create test led task\r\n");
}

vTaskStartScheduler();
}
