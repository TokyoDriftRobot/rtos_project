#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>
#include "constants.h"
#include "audio.h"

void tBrain(void *argument) {
	while(1);
}

void tMotorControl(void *argument) {
	while(1);
}

void tLED(void *argument) {
	while(1);
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


int main(void) {
	SystemCoreClockUpdate();
	osKernelInitialize();
	
	osThreadNew(tBrain, NULL, NULL);
	osThreadNew(tMotorControl, NULL, NULL);
	osThreadNew(tLED, NULL, NULL);
	osThreadNew(tAudio, NULL, NULL);
	
	osKernelStart();
	while(1);
}
