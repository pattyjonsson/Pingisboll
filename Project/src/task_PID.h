/*
 * PID.h
 *
 * Created: 2016-02-26 10:42:57
 *  Author: Yggdrasil
 */ 


#ifndef PID_H_
#define PID_H_
#define TASK_LED_STACK_SIZE     (2048/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (2)


void task_PID(void *pvParameters);
int32_t PIDreglering(int32_t felmargi1,int32_t felmargibefore1, int32_t sum1, double kp1, double Ti1,double Td1,double dT1);
void setPIDvalues(double tempkp, double tempti, double temptd, uint32_t tempborvarde);
#endif /* PID_H_ */