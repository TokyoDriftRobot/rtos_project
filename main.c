#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>
#include "constants.h"
#include "audio.h"
#include "led.h"


robot_state_t ROBOT_STATE = ROBOT_STATE_STOP;

void tBrain(void *argument) {
	while(1);
}

void tMotorControl(void *argument) {
	while(1);
}

void tRedLED(void *argument) {
	red_led_init();
	while(1) {
		if (ROBOT_STATE == ROBOT_STATE_MOVE) {
		  red_led_toggle();
		  osDelay(RED_LED_MOVE_DELAY);
		} else {
		  red_led_toggle();
		  osDelay(RED_LED_STOP_DELAY);
		}
	};
}

void tGreenLED(void *argument) {
	green_led_init();
	while(1) {
		if (ROBOT_STATE == ROBOT_STATE_MOVE) {
		  green_led_running();
		  osDelay(RED_LED_MOVE_DELAY);
		} else {
		  green_led_on();
		  osDelay(RED_LED_STOP_DELAY);
		}
	};
}

void tAudio(void *argument) {
	int counter = 0;
	int n_notes = MAIN_THEME_SIZE;
	const float dc = 0.1;
	
	while (1) {
		counter = counter % n_notes;
		int pause_between_notes = play_main_theme(counter, dc);
    osDelay(pause_between_notes);
		counter += 1;
	}
}

// Supply power to ports
void clock_gating_init() {
	SIM->SCGC5 |= (
		(SIM_SCGC5_PORTA_MASK) |
		(SIM_SCGC5_PORTB_MASK) | 
		(SIM_SCGC5_PORTC_MASK) | 
		(SIM_SCGC5_PORTD_MASK) |
		(SIM_SCGC5_PORTE_MASK) 
	);
}

// Supply power to timers
void timer_gating_init () {
	/* Select MCGFLLCLK as timer counter clock */
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
  /* Enable clock to TPM0 */
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	/* Enable clock to TPM1 */
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;  
	/* Enable clock to TPM1 */
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;  
	
  /* Enable clock to PIT */	
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
}

int main(void) {
	SystemCoreClockUpdate();
	clock_gating_init();
	timer_gating_init();
	osKernelInitialize();
	
	osThreadNew(tBrain, NULL, NULL);
	osThreadNew(tMotorControl, NULL, NULL);
	osThreadNew(tRedLED, NULL, NULL);
	osThreadNew(tGreenLED, NULL, NULL);
	osThreadNew(tAudio, NULL, NULL);
	
	osKernelStart();
	while(1);
}
