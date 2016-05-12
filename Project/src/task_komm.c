/*
* task_komm.c
*
* Den h�r klassen hanterar kommunikationen med matlab.
*
* Created: 2016-02-26 10:54:21
*
* Author: Martin och Patricia
*/
#include "asf.h"
#include "task_komm.h"
#include "conf_clock.h"
#include "communication.h"
#include "task_PID.h"
#include "Global.h"
/*dessa v�rden anv�nds f�r att h�lla reda p� vilken "state" vi �r i  dvs, 
* ska vi skicka till matlab,ska vi ta emot fr�n matlab etc. Dessa variablerna h�ller reda p� det.*/
uint8_t flag = 0;
extern ready = 0;
uint8_t readyToSend=0;
uint8_t readyToReceive=0;

/* Dessa v�rden anv�nds f�r att ta emot v�rdena fr�n matlab och f�r �ver dom till double variabler*/
uint32_t tempborvarde  = 0;
double tempkp = 0.0;
double tempti = 0.0;
double tempdT = 0.0;
double tempTd  = 0.0;

double kptoPID = 0.0;
double titoPID = 0.0;
double tempdT2 = 0.0;
double tdtoPID  = 0.0;

/*V�rden som skickas till matlab och plottas*/
int32_t styrvardetomatlab = 0;
int32_t felmargitomatlab = 0;
uint32_t borvardetomatlab = 0;
int32_t averagesensorvaluetomatlab = 0;
/*
* Sj�lva tasken som hanterar kommunikationen med matlab.
*/
void task_komm(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		/*Matlab skickar 5:an som g�r att programmet �r redo f�r variablerna f�r PID.*/
		if(flag == 0){
			if(isReady()){
				if(readValue() ==  5)
				{
					printf("%d\n",1);
					flag = 5;
					readyToReceive=1;
					
				}
			}
		}
		/* Matlabskickar variablerna och sparar dom i uint-variabler,
		d�refter g�r vi om variablerna till dubbel och delar dom med 100 f�r att f� ut de korrekta v�rdena.*/
		if(flag == 5 && readyToReceive==1){
			uint16_t kpfrommatlab = 0;
			uint8_t tifrommatlab = 0;
			uint8_t dtfrommatlab = 0;
			uint8_t tdfrommatlab  = 0;
			uint8_t borvardefrommatlab = 0;
						
			waitUntilReady();
			kpfrommatlab=readValue();
			
			printf("%d\n",kpfrommatlab);
			
			waitUntilReady();
			tifrommatlab=readValue();
			
			printf("%d\n",tifrommatlab);
		
			waitUntilReady();
			tdfrommatlab=readValue();
			
			
			printf("%d\n",tdfrommatlab);
			
			waitUntilReady();
			borvardefrommatlab=readValue();
			printf("%d\n",borvardefrommatlab);

				tempkp=kpfrommatlab;
				tempti=tifrommatlab;
				tempTd=tdfrommatlab;
				
				kptoPID=(double) (tempkp/100);
				titoPID=(double) (tempti/100);
				tdtoPID=(double) (tempTd/100);


				setPIDvalues(kptoPID,titoPID,tdtoPID,borvardefrommatlab);/*Skickar v�rdena vi fick fr�n matlab till task_PID f�r att s�tta relgeringsvariablerna*/
				readyToSend=1;
				readyToReceive=0;				
				
		
		}
	/*Skickar styrv�rdet,felv�rdet,b�rv�rde och  AverageSensorValue(avst�ndet till pingisbollen) till matlab.*/
		if(flag == 5 && readyToSend==1){
			
		printf("%d\n", styrvardetomatlab);
		printf("%d\n", felmargitomatlab);
		printf("%d\n", borvardetomatlab);
		printf("%d\n", averagesensorvaluetomatlab);
		
		}

		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}
/*
* Tar in de aktuella v�rdena och skickar dom till matlab som plottar dom
*/
void updateinfoformatlab(int32_t tempstyrvarde, int32_t tempaverageSensorValue,int32_t tempfelmargi,uint32_t tempborvarde){
	styrvardetomatlab = tempstyrvarde;
	felmargitomatlab = (tempfelmargi*-1);
	borvardetomatlab = tempborvarde;
	averagesensorvaluetomatlab = tempaverageSensorValue;
	
}

