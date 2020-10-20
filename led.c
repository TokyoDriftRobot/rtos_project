#include <MKL25Z4.h> 
#include "constants.h"
#include "led.h"

void green_led_init() {
	PORTB->PCR[LED_GREEN_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_GREEN_PIN] |= PORT_PCR_MUX(1);
	
	// Set pins to output
	PTB->PDDR |= MASK(LED_GREEN_PIN);
	
	// Turn off leds
	PTB->PDOR |= (MASK(LED_GREEN_PIN)); 
}

void green_led_running() {
	PTB->PTOR |= MASK(LED_GREEN_PIN);
}

void green_led_on() {
  PTB->PDOR &= ~MASK(LED_GREEN_PIN);
}

void red_led_init() {
	// Enable pins as gpio
	PORTB->PCR[LED_RED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_RED_PIN] |= PORT_PCR_MUX(1);

	// Set pins to output
	PTB->PDDR |= MASK(LED_RED_PIN);
	
	// Turn off leds
	PTB->PDOR |= (MASK(LED_RED_PIN)); 
}

void red_led_toggle() {
	PTB->PTOR |= MASK(LED_RED_PIN);
}
