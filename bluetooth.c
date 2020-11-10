#include <MKL25Z4.h> 
#include "constants.h"

void bluetooth_init(uint32_t baud_rate) {
	uint32_t divisor, bus_clock;
	
	PORTE->PCR[LED_PTE22] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[LED_PTE23] |= PORT_PCR_MUX(4);
		
	UART2->C2 &= ~(UART_C2_RE_MASK);
		
	bus_clock = (DEFAULT_SYSTEM_CLOCK) / 2;
	divisor = bus_clock / (baud_rate * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);
		
	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;

	UART2->C2 |= UART_C2_RE_MASK;
	UART2->C2 |= UART_C2_RIE_MASK;
	
	NVIC_SetPriority(UART2_IRQn, 128);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);		
}

void UART2_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART2_IRQn);
	myDataPkt myData;
	
	if (UART2->S1 & UART_S1_RDRF_MASK) {
		int rx_data = UART2->D;
		if (rx_data == 0) { // start
				myData.cmd = 0x01;
	      myData.data = 0x00;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);
		} else if (rx_data == 1) { // done
				myData.cmd = 0x04;
	      myData.data = 0x00;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);
		} else if (rx_data == 2) { // stop
				myData.cmd = 0x02;
	      myData.data = 0x00;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);
		} else if (rx_data == 3) { // forward straight
				myData.cmd = 0x03;
	      myData.data = 0x01;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);
		} else if (rx_data == 4) { // forward left
				myData.cmd = 0x03;
	      myData.data = 0x02;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);		
		} else if (rx_data == 5) { // forward right
				myData.cmd = 0x03;
	      myData.data = 0x03;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);	
		} else if (rx_data == 6) { // backward straight
				myData.cmd = 0x03;
	      myData.data = 0x04;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);			
		} else if (rx_data == 7) { // backward left
				myData.cmd = 0x03;
	      myData.data = 0x05;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);		
		} else if (rx_data == 8) { // backward right
				myData.cmd = 0x03;
	      myData.data = 0x06;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);		
		} else {
				myData.cmd = 0x02;
	      myData.data = 0x00;
       osMessageQueuePut(dataMsg, &myData, NULL, 0);
		}
	}
}
