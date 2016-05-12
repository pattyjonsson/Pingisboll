/*
* ADCFunctions.c
*
* Klassen hanterar ADC:en vilket innebär att den initierar ADC:n och tar ut avståndet till pingisbollen.
*
* Author: Patricia och Martin
*/
#include <asf.h>
#include "ADCFunctions.h"

/*
* Initierar ADC-omvandlaren.
* Channel 7 vilket är analog 0 på arduino due.
* 12-bitars resolution.
*/
void ADCInit(void)
{
	/*Konfigurera strömhantering av ADC timer klocka.*/
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 1000000, 8); 
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_7);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
}

/*
* Läser av Sensorn och gör om sensor-värdet till ett avstånd.
*
* Return: returnerar avståndet till pingisbollen
*/
uint32_t ReadFanValue(void)
{
	uint32_t Valuesensor;
	adc_start(ADC);												/* Startar adc.*/
	Valuesensor = adc_get_channel_value(ADC, ADC_CHANNEL_7);	/* Läser av sensorn och sparar den i ValueSensor.*/
	
	uint32_t distance = 0;

	if (Valuesensor <= 1150){
		distance = 50; // 50 cm
	}
	else if(Valuesensor <= 1270 && Valuesensor > 1150){
		distance = 45;// 45 cm
	}
	else if(Valuesensor <= 1360 && Valuesensor > 1270){
		distance = 40;// 40cm
	}
	else if(Valuesensor <= 1450 && Valuesensor > 1360){
		distance = 35;// 35cm
	}
	else if(Valuesensor <= 1560 && Valuesensor > 1450){
		distance = 30;// 30cm
	}
	else if(Valuesensor <= 1910 && Valuesensor >1560){
		distance = 25;// 25cm
	}
	else if(Valuesensor <= 2020 && Valuesensor >1910){
		distance = 20; // 20cm
	}
	else if(Valuesensor > 2020){
		distance = 15; // 15cm		
	}
	return distance;
	
}