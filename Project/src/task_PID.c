/*
* PID.c
*
* Hanterar PID-regleringen av pingisbollen.
*
* Created: 2016-02-26 10:42:28
*
* Author: Martin och Patricia
*/
#include <asf.h>
#include "task_PID.h"
#include "PWMFunctions.h"
#include "ADCFunctions.h"
#include "communication.h"
#include "task_komm.h"
#include "Global.h"
/*Används för att beräkna "moving average på fläcken.*/
#define POSITIONS 5
static int32_t ValuesoFFan[POSITIONS] = {0};

/*PID-variablerna.*/
int32_t averageFanValue= 0;
uint32_t currentValuesensor = 0;
int32_t felmargi = 0;
int32_t felmargibefore;
int32_t styrvarde;
int32_t sum;

double Kp = 0;
double Td = 0;
double Ti = 0;
double dT = 0.1;
uint8_t borvarde=0;

/*När man har mottagit varibalerna i task_komm ska sätts variabeln till 1 vilket innebär att PID-regleringen börjar.*/
int32_t readyforPID = 0;

static uint32_t samplingTimeMS = 100;
//static double samplingTime=0.1;

/*
* Funktionen som hanterar PID-regleringen
*/
void task_PID(void *pvParameters)
{
	portTickType xLastWakeTime;
	portTickType xSampleTime;

	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
		xSampleTime = (portTickType)samplingTimeMS;
		vTaskDelayUntil(&xLastWakeTime, xSampleTime);
		
		if(flag == 0){
			readyforPID =0;
			flag = 0;
			felmargibefore=0;
			felmargi=0;
			sum=0;
			CalculateFanValue(0);
		}
		
	
		/*Vi kollar att flag har fått värdet 5 från matlab och att readyforPID är 1, vilket indikerar att vi har fått värdena från matlab
		därefter sätts PID-regleringen igång.*/
		if((readyforPID == 1) && (flag==5)){
			ValuesoFFan[0] = ReadFanValue();
			int32_t averageSensorValue = 0;
			
			for(int i = 0; i<POSITIONS; i++)
			{
				averageSensorValue = averageSensorValue + ValuesoFFan[i];/*Gå igenom array:n och beräknar summan.*/
			}
			
			averageSensorValue = (averageSensorValue / POSITIONS); /*Beräknar medelvärdet på avståndet till pingisbollen.*/
			
			/*Flyttar värdet man la in i position 1 ett steg uppåt.*/
			for(int i = 0; i<POSITIONS-1; i++)
			{
				ValuesoFFan[i+1] = ValuesoFFan[i];
			}
			felmargibefore= felmargi;
			sum = sum + felmargibefore;					/*summan av felen.*/
			felmargi = borvarde - averageSensorValue;	/* felvärdet.*/
			
			
			felmargi = felmargi *-1;
			
			styrvarde = PIDreglering(felmargi, felmargibefore, sum, Kp, Ti, Td, dT);/*PID beräkningen*/
			
			if (styrvarde< 0)
			{
				styrvarde = 0;
			}
			if(styrvarde > 100)
			{
				styrvarde = 100;
			}
						
			CalculateFanValue(styrvarde);					/*Sätter ett värde till PWM:n -> fläcken.*/
			updateinfoformatlab(styrvarde,averageSensorValue,felmargi,borvarde);/*anropar metoden updateinfoformatlab i task_komm för att uppdatera värdena man skickar till matlab.*/
		}
		
	}
}

/*
* Funktionen beräknar PID.
*/
int32_t PIDreglering(int32_t felmargi1,int32_t felmargibefore1, int32_t sum1, double kp1, double Ti1,double Td1,double dT1){
	double p_DELEN;
	double i_DELEN;
	double d_delen;
	int32_t finalsignal;
	
	p_DELEN = (double)felmargi1;
	i_DELEN = (double)sum1 * (dT1/Ti1);
	d_delen = ((double)felmargi1- (double)felmargibefore1) * (Td1 / dT1);
	finalsignal = kp1* (p_DELEN + i_DELEN + d_delen);
	
	return finalsignal;
}
/*
* Sätter variablerna till kp,ti,td,börvärde som används i PID-regleringen.
* readyforPID sätts till 1 vilket betyder att PID-reglering kör igång då vi har alla variabler vi behöver.
*/
void setPIDvalues(double tempkp, double tempti, double temptd, uint32_t tempborvarde){
	
	Kp = tempkp;
	Ti = tempti;
	Td = temptd;
	borvarde = tempborvarde;
	readyforPID = 1;
}