#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>
#include "constants.h"
#include "audio.h"
#include "led.h"
#include "motor.h"
#include "bluetooth.h"

volatile robot_state_t ROBOT_STATE = ROBOT_STATE_INIT;
volatile robot_direction_t ROBOT_DIRECTION = ROBOT_DIRECTION_FORWARD;

#define BAUD_RATE 9600
#define UART_TX_PORTE22 22
#define UART_RX_PORTE23 23
#define UART2_INT_PRIO 128


void tBrain(void *argument) {
	bluetooth_init(BAUD_RATE);
	while(1);
}

void tMotorControl(void *argument) {
	motor_init();
	while(1) {
		motor_control();
	};
}

void tRedLED(void *argument) {
	red_led_init();
	while(1) {
		red_led_toggle();
		if (ROBOT_STATE == ROBOT_STATE_MOVE) {
		  osDelay(RED_LED_MOVE_DELAY);
		} else {
		  osDelay(RED_LED_STOP_DELAY);
		}
	};
}

void tGreenLED(void *argument) {
	green_led_init();
	int counter = 0;
	while(1) {
		if (ROBOT_STATE == ROBOT_STATE_MOVE) {
			counter = counter % 10;
		  green_led_running(counter);
			counter += 1;
		} else {
		  green_led_on();
			counter = 0;
		}
		osDelay(GREEN_LED_DELAY);
	};
}

void tAudio(void *argument) {
	int counter = 0;
	int n_notes = UNDERWORLD_SIZE;
	const float dc = 0.1;
	
	while (1) {
		if (ROBOT_STATE == ROBOT_STATE_INIT) {
			continue;
		} else if (ROBOT_STATE == ROBOT_STATE_START) {
		  n_notes = UNDERWORLD_SIZE;
		} else if (ROBOT_STATE == ROBOT_STATE_END) {
			n_notes = GAME_OVER_SIZE;
		} else {
			n_notes = MAIN_THEME_SIZE;
		}
		
		counter = counter % n_notes;
		int pause_between_notes = 0;
		if (ROBOT_STATE == ROBOT_STATE_START) {
			pause_between_notes = play_underworld(counter, dc);
		} else if (ROBOT_STATE == ROBOT_STATE_END) {
			pause_between_notes = play_game_over(counter, dc);
		} else {
			pause_between_notes = play_main_theme(counter, dc);
		}
		
    osDelay(pause_between_notes);
		counter += 1;
	}
}

void clock_gating_init() {
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	
	SIM->SCGC5 |= (
		(SIM_SCGC5_PORTA_MASK) |
		(SIM_SCGC5_PORTB_MASK) | 
		(SIM_SCGC5_PORTC_MASK) | 
		(SIM_SCGC5_PORTD_MASK) |
		(SIM_SCGC5_PORTE_MASK) 
	);
}

void timer_gating_init () {
	/* select mcgfliclk as timer counter clock */
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;  
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;  
	
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
