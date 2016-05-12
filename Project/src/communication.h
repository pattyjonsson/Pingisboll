/*
 * communication.h
 *
 * Created: 2016
 *  Author: Patricia J�nsson och Martin Br�hagen
 */ 


#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

void setupUART(void);
uint8_t readValue(void);
uint32_t isReady(void);
uint32_t waitUntilReady(void);

#endif /* COMMUNICATION_H_ */