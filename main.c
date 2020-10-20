#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>

#define MASK(x) (1 << (x))

// Port A Pins
#define LED_PTA1 1
#define LED_PTA2 2
#define LED_PTA4 4
#define LED_PTA5 5
#define LED_PTA12 12
#define LED_PTA13 13
#define LED_PTA16 16
#define LED_PTA17 17

// Port B Pins
#define LED_PTB0 0
#define LED_PTB1 1
#define LED_PTB2 2
#define LED_PTB3 3
#define LED_PTB8 8
#define LED_PTB9 9
#define LED_PTB10 10
#define LED_PTB11 11

// Port C Pins
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

// Port D Pins
#define LED_PTD0 0
#define LED_PTD1 1
#define LED_PTD2 2
#define LED_PTD3 3
#define LED_PTD4 4
#define LED_PTD5 5
#define LED_PTD6 6
#define LED_PTD7 7

// Port E Pins
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

// Audio
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Underwolrd tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
int game_over [] = {
  NOTE_C5, NOTE_G4, NOTE_E4, 
  NOTE_A4, NOTE_B4, NOTE_A4,
	NOTE_GS4, NOTE_AS4, NOTE_GS4,
  NOTE_G4, NOTE_D4, NOTE_E4,  
};
int game_over_tempo [] = {
	4, 4, 4, 
	8, 8, 8,
	8, 8, 8,
	8, 8, 2
};
// Misc
#define CLOCK_FREQ 48000000


int pwn_calculate_period(int clock, int freq, int ps) {
	return clock / (freq * ps);
}  

int pwm_calculate_duty_cycle(int clock, int freq, int ps, float dc) {
	return (int) (dc * (clock / (freq * ps)));
}  

void pwm_init(int pwn_period, int pwm_duty_cycle) {
	/* Enable clock on PTB */
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	/* Select PTB0 to connect to TPM */
	PORTB->PCR[LED_PTB0] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_PTB0] |= PORT_PCR_MUX(3);
	
	/* Select PTB1 to connect to TPM */
	PORTB->PCR[LED_PTB1] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_PTB1] |= PORT_PCR_MUX(3);	

  /* Enable clock to TPM1 */
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	/* Select MCGFLLCLK as timer counter clock */
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

	/* Disable timer while configuring */
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	
	/* Select prescaler for timer */
	TPM1->SC|= TPM_SC_PS(7);
	/* Select counter increment on counter clock */
	TPM1->SC |= TPM_SC_CMOD(1);
	
	/* Select counter to operate in up counting mode */
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);

	/* Determine EPWM period */
	TPM1->MOD = pwn_period;
	
  /* Set timer to EPWM mode for PTB0 */
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
  /* Set timer to EPWM mode for PTB1 */
	TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	/* Determine pulse width (duty cycle) */
	TPM1_C0V = pwm_duty_cycle;
	TPM1_C1V = pwm_duty_cycle;
}

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
	int n_notes = sizeof(melody) / sizeof(int);
	const int ps = 128;
	
	while (1) {
		counter = counter % n_notes;
	  int pwm_period = pwn_calculate_period(CLOCK_FREQ, melody[counter], ps); 
    int pwm_duty_cycle = pwm_calculate_duty_cycle(CLOCK_FREQ, melody[counter], ps, 0.1); 
		pwm_init(pwm_period, pwm_duty_cycle);
		int noteDuration = 1000 / tempo[counter];
		int pauseBetweenNotes = noteDuration * 1.30;
    osDelay(pauseBetweenNotes);
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
