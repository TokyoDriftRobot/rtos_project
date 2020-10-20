// port a pins
#define LED_PTA1 1
#define LED_PTA2 2
#define LED_PTA4 4
#define LED_PTA5 5
#define LED_PTA12 12
#define LED_PTA13 13
#define LED_PTA16 16
#define LED_PTA17 17

// port b pins
#define LED_PTB0 0 // audio
#define LED_PTB1 1
#define LED_PTB2 2
#define LED_PTB3 3 // red led
#define LED_PTB8 8 // red led
#define LED_PTB9 9 // red led
#define LED_PTB10 10 // red led
#define LED_PTB11 11 // red led

// port c pins
#define LED_PTC0 0
#define LED_PTC1 1 // red led
#define LED_PTC2 2 // red led
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

// port d pins
#define LED_PTD0 0
#define LED_PTD1 1
#define LED_PTD2 2
#define LED_PTD3 3
#define LED_PTD4 4
#define LED_PTD5 5
#define LED_PTD6 6
#define LED_PTD7 7

// port e pins
#define LED_PTE0 0
#define LED_PTE1 1
#define LED_PTE2 2 // red led
#define LED_PTE3 3
#define LED_PTE4 4 // left motor
#define LED_PTE5 5 // left motor
#define LED_PTE20 20 // right motor
#define LED_PTE21 21 // right motor
#define LED_PTE22 22
#define LED_PTE23 23
#define LED_PTE29 29 // red led
#define LED_PTE30 30 // red led

// robot states
typedef enum {
	ROBOT_STATE_STOP,
	ROBOT_STATE_MOVE,
	ROBOT_STATE_START,
	ROBOT_STATE_END,
} robot_state_t;
typedef enum {
	ROBOT_DIRECTION_LEFT,
	ROBOT_DIRECTION_RIGHT,
	ROBOT_DIRECTION_FORWARD,
	ROBOT_DIRECTION_BACKWARD
} robot_direction_t;

extern robot_state_t ROBOT_STATE;
extern robot_direction_t ROBOT_DIRECTION;

// debugging
#define LED_RED_PIN 18 
#define LED_GREEN_PIN 19 
#define LED_BLUE_PIN 1 

// misc
#define CLOCK_FREQ 48000000
#define MASK(x) (1 << (x))
