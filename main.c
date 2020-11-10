#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>
#include "constants.h"
#include "audio.h"
#include "led.h"
#include "motor.h"
#include "bluetooth.h"

uint32_t MSG_COUNT = 1;
volatile osMessageQueueId_t dataMsg;
volatile myDataPkt robotState;

void tBrain(void *argument) {
	bluetooth_init(BAUD_RATE);
	while(1);
}

void tMotorControl(void *argument) {
	motor_init();
	while(1) {
    if (robotState.cmd == 0x03) {
		  if (robotState.data == 0x01) {
			  motor_forward_straight();
		  } else if (robotState.data == 0x02) {
			  motor_forward_left();
		  } else if (robotState.data == 0x03) {
			  motor_forward_right();
		  } else if (robotState.data == 0x04) {
			  motor_backward_straight();
		  } else if (robotState.data == 0x05) {
			  motor_backward_left();
		  } else if (robotState.data == 0x06) {
			  motor_backward_right();
		  } else {
			  motor_stop();
		  }
	} else {
		motor_stop();
	}
	};
}

void tRedLED(void *argument) {
	red_led_init();
	while(1) {
		red_led_off();
		if (robotState.cmd == 0x03) {
		  osDelay(RED_LED_MOVE_DELAY);
		} else {
		  osDelay(RED_LED_STOP_DELAY);
		}
		red_led_on();
		if (robotState.cmd == 0x03) {
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
		if (robotState.cmd == 0x03) {
			counter = counter % 8;
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
		if (robotState.cmd == 0x00) {
			continue;
		} else if (robotState.cmd == 0x01) {
		  n_notes = UNDERWORLD_SIZE;
		} else if (robotState.cmd == 0x04) {
			n_notes = GAME_OVER_SIZE;
		} else {
			n_notes = MAIN_THEME_SIZE;
		}
		
		counter = counter % n_notes;
		int pause_between_notes = 0;
		if (robotState.cmd == 0x01) {
			pause_between_notes = play_underworld(counter, dc);
		} else if (robotState.cmd == 0x04) {
			pause_between_notes = play_game_over(counter, dc);
		} else {
			pause_between_notes = play_main_theme(counter, dc);
		}
		
    osDelay(pause_between_notes);
		counter += 1;
	}
}

void tDecodeMsg(void *argument) {
	myDataPkt myData;
	
	while (1) {
		osMessageQueueGet(dataMsg, &myData, NULL, osWaitForever);
		robotState = myData;
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
	
	robotState.cmd = 0x00;
	robotState.data = 0x00;
	
	osKernelInitialize();
	
	osThreadNew(tBrain, NULL, NULL);
	osThreadNew(tMotorControl, NULL, NULL);
	osThreadNew(tRedLED, NULL, NULL);
	osThreadNew(tGreenLED, NULL, NULL);
	osThreadNew(tAudio, NULL, NULL);
	osThreadNew(tDecodeMsg, NULL, NULL);
	
	dataMsg = osMessageQueueNew(MSG_COUNT, sizeof(myDataPkt), NULL);

	osKernelStart();
	while(1);
}
