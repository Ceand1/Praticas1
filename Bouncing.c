/**
 * @file    Switch_LED.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
typedef struct{
	uint32_t PCR[32];
}PORTRegs_t;

#define PORT_A ((PORTRegs_t *) 0x40049000)
#define PORT_E ((PORTRegs_t *) 0x4004D000)

typedef struct{
	 uint32_t PDOR;
	 uint32_t PSOR;
	 uint32_t PCOR;
	 uint32_t PTOR;
	 uint32_t PDIR;
	 uint32_t PDDR;
}GPIORegs_t;

#define GPIO_A ((GPIORegs_t *) 0x400FF000)
#define GPIO_E ((GPIORegs_t *) 0x400FF100)
/*
 * @brief   Application entry point.
 */
int main(void) {
		SIM->SCGC5 |= (1 << 9) | (1 << 13);

		//configura os pinos como GPIO
		PORT_E->PCR[1] |= (1 << 8);

		PORT_A->PCR[12] |= (1 << 8) | (1 << 1) | (1 << 0);

		//configura o pino E_1 como saída
		GPIO_E->PDDR |= (1 << 1);

		//deslida o led
		GPIO_E->PSOR |= (1 << 1);

		while(1){
			if(GPIO_A->PDIR & (1 << 12)){
				// LED OFF
				GPIO_E->PSOR |= (1 << 1);
			}else{
				//LED ON
				GPIO_E->PCOR |= (1 << 1);
			}

		}
    return 0 ;
}

