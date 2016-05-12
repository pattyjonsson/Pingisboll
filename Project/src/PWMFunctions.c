/*
* PWMFunctions.c
*
* Klassen initierar PWM:en och v�ljer vilken pinne man vill anv�nda PWM p� samt s�tter utv�rdet till PWM:en.
*
* Author: Patricia och Martin
*/
#include <asf.h>
#include "PWMFunctions.h"

pwm_channel_t PWMPin40;

/*
* Initierar Pulse Width modulation som anv�nds till fl�cken.
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
	
	InitPIN40();	/* Anropar InitPin40 f�r att initiera vilken pinne vi vill s�tta PWM till.*/
}

/*
* Initierar digial pinne 40 p� Arduino Due.
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
* Tar in ett v�rde som argument som d� �r v�rdet p� fl�cken.
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