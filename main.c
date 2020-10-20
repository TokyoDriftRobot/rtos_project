#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>

#define MASK(x) (1 << (x))

#define LED_PTA1 1
#define LED_PTA2 2
#define LED_PTA4 4
#define LED_PTA5 5
#define LED_PTA12 12
#define LED_PTA13 13
#define LED_PTA16 16
#define LED_PTA17 17

#define LED_PTB0 0
#define LED_PTB1 1
#define LED_PTB2 2
#define LED_PTB3 3
#define LED_PTB8 8
#define LED_PTB9 9
#define LED_PTB10 10
#define LED_PTB11 11

#define LED_PTC0 0
#define LED_PTC1 1 
#define LED_PTC2 2
#define LED_PTC3 3
#define LED_PTC4 4
#define LED_PTC5 5
#define LED_PTC6 6
#define LED_PTC7 7
#define LED_PTC8 8
#define LED_PTC9 9
#define LED_PTC10 10
#define LED_PTC11 11
#define LED_PTC12 12
#define LED_PTC13 13
#define LED_PTC16 16
#define LED_PTC17 17

#define LED_PTD0 0
#define LED_PTD1 1
#define LED_PTD2 2
#define LED_PTD3 3
#define LED_PTD4 4
#define LED_PTD5 5
#define LED_PTD6 6
#define LED_PTD7 7

#define LED_PTE0 0
#define LED_PTE1 1
#define LED_PTE2 2
#define LED_PTE3 3
#define LED_PTE4 4
#define LED_PTE5 5
#define LED_PTE20 20
#define LED_PTE21 21
#define LED_PTE22 22
#define LED_PTE23 23
#define LED_PTE29 29
#define LED_PTE30 30

// LEDs for debugging
#define LED_PTB18 18
#define LED_PTB19 19
#define LED_PTD1 1


typedef enum {
    LED_RED_COLOR,
    LED_BLUE_COLOR,
    LED_GREEN_COLOR,
} color_t;


void led_init_gpio(void) {
	// Enable Clock to PORTB and PORTD
	SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTD_MASK));
	// Configure MUX settings to make all 3 pins GPIO
	PORTB->PCR[LED_PTB18] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_PTB18] |= PORT_PCR_MUX(1);
	PORTB->PCR[LED_PTB19] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_PTB19] |= PORT_PCR_MUX(1);
	PORTD->PCR[LED_PTD1] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[LED_PTD1] |= PORT_PCR_MUX(1);
	// Set Data Direction Registers for PortB and PortD
	PTB->PDDR |= (MASK(LED_PTB18) | MASK(LED_PTB19));
	PTD->PDDR |= MASK(LED_PTD1);
}

void led_off_rgb() {
	PTD->PDOR = MASK(LED_PTD1);
	PTB->PDOR = (MASK(LED_PTB18) | MASK(LED_PTD1)); 
}

void led_red_thread(void *argument) {
	for (;;) {
		PTB->PDOR |= (MASK(LED_PTB18));
		osDelay(1000);
		PTB->PDOR &= (~MASK(LED_PTB18));
		osDelay(1000);
	}
}

void led_green_thread(void *argument) {
	for (;;) {
		PTB->PDOR |= (MASK(LED_PTB19));
		osDelay(1000);
		PTB->PDOR &= (~MASK(LED_PTB19));
		osDelay(1000);
	}
}

int main(void) {
	SystemCoreClockUpdate();
	led_init_gpio();
	led_off_rgb();
	osKernelInitialize();
	osThreadNew(led_red_thread, NULL, NULL);
	osThreadNew(led_green_thread, NULL, NULL);
	osKernelStart();
	while(1);
}
