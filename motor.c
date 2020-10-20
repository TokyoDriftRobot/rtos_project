#include <MKL25Z4.h> 
#include "constants.h"

void motor_stop() {
	PTE->PDOR &= ~(MASK(LED_PTE20)); 
	PTE->PDOR &= ~(MASK(LED_PTE5)); 	

	PTE->PDOR &= ~(MASK(LED_PTE21)); 
	PTE->PDOR &= ~(MASK(LED_PTE4)); 
}

void motor_forward() {
	PTE->PDOR |= (MASK(LED_PTE20)); 
	PTE->PDOR |= (MASK(LED_PTE5)); 	

	PTE->PDOR &= ~(MASK(LED_PTE21)); 
	PTE->PDOR &= ~(MASK(LED_PTE4)); 
}

void motor_backward() {
	PTE->PDOR &= ~(MASK(LED_PTE20)); 
	PTE->PDOR &= ~(MASK(LED_PTE5)); 	

	PTE->PDOR |= (MASK(LED_PTE21)); 
	PTE->PDOR |= (MASK(LED_PTE4)); 
}

void motor_left() {
	PTE->PDOR |= (MASK(LED_PTE20)); 
	PTE->PDOR &= ~(MASK(LED_PTE5)); 	

	PTE->PDOR |= (MASK(LED_PTE21)); 
	PTE->PDOR &= ~(MASK(LED_PTE4)); 
}

void motor_right() {
	PTE->PDOR &= ~(MASK(LED_PTE20)); 
	PTE->PDOR |= (MASK(LED_PTE5)); 	

	PTE->PDOR &= ~(MASK(LED_PTE21)); 
	PTE->PDOR |= (MASK(LED_PTE4)); 
}

void motor_init() {
	// Enable front right motor
	PORTE->PCR[LED_PTE20] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[LED_PTE20] |= PORT_PCR_MUX(1);
	PTE->PDDR |= MASK(LED_PTE20);
	
	// Enable back right motor
	PORTE->PCR[LED_PTE21] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[LED_PTE21] |= PORT_PCR_MUX(1);
	PTE->PDDR |= MASK(LED_PTE21);

	// Enable back left motor
	PORTE->PCR[LED_PTE5] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[LED_PTE5] |= PORT_PCR_MUX(1);
	PTE->PDDR |= MASK(LED_PTE5);
	
	// Enable back left motor
	PORTE->PCR[LED_PTE4] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[LED_PTE4] |= PORT_PCR_MUX(1);
	PTE->PDDR |= MASK(LED_PTE4);

	// Turn off pins
	motor_stop();
}

void motor_control () {
	if (ROBOT_STATE == ROBOT_STATE_MOVE) {
		if (ROBOT_DIRECTION == ROBOT_DIRECTION_FORWARD) {
			motor_forward();
		} else if (ROBOT_DIRECTION == ROBOT_DIRECTION_BACKWARD) {
			motor_backward();
		} else if (ROBOT_DIRECTION == ROBOT_DIRECTION_LEFT) {
			motor_left();
		} else if (ROBOT_DIRECTION == ROBOT_DIRECTION_RIGHT) {
		  motor_right();
		} else {
			motor_stop();
		}
	} else {
		motor_stop();
	}
}
