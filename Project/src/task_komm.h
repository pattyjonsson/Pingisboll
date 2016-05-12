/*
 * task_komm.h
 *
 * Created: 2016-02-26 10:54:37
 *
 *  Author: Martin och Patricia
 */ 


#ifndef TASK_KOMM_H_
#define TASK_KOMM_H_


#define TASK_KOMM_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_KOMM_STACK_PRIORITY (1)
void task_komm(void *pvParameters);
void updateinfoformatlab(int32_t tempstyrvarde,int32_t tempaverageSensorValue,int32_t tempfelmargi,uint32_t tempborvarde);

#endif /* TASK_KOMM_H_ */