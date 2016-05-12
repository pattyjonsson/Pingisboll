/*
* PWMFunctions.c
*
* Klassen initierar PWM:en och väljer vilken pinne man vill använda PWM på samt sätter utvärdet till PWM:en.
*
* Author: Patricia och Martin
*/
#include <asf.h>
#include "PWMFunctions.h"

pwm_channel_t PWMPin40;

/*
* Initierar Pulse Width modulation som används till fläcken.
*/
void PWMInit(void){
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_disable(PWM, PWM_CHANNEL_3);
	
	pwm_clock_t clock_setting = {
		.ul_clka = 1000 * 1000,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &clock_setting);
	
	InitPIN40();	/* Anropar InitPin40 för att initiera vilken pinne vi vill sätta PWM till.*/
}

/*
* Initierar digial pinne 40 på Arduino Due.
*/
void InitPIN40(void)
{
	PWMPin40.channel = PWM_CHANNEL_3;
	PWMPin40.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWMPin40.ul_duty = 0;
	PWMPin40.ul_period = 100;
	pwm_channel_init(PWM, &PWMPin40);
	pio_set_peripheral(PIOC, PIO_PERIPH_B, PIO_PC8B_PWML3);
	pwm_channel_enable(PWM, PWM_CHANNEL_3);
}

/*
* Tar in ett värde som argument som då är värdet på fläcken.
*/
void CalculateFanValue(uint32_t dutyCycle)
{
	if(dutyCycle>100)
	{
		dutyCycle=100;
	}
	if(dutyCycle <= 100 && dutyCycle >=0)
	{
		pwm_channel_update_duty(PWM, &PWMPin40, dutyCycle);
	}
}