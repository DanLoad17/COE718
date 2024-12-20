/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 * Note(s): __USE_LCD   - enable Output on LCD, uncomment #define in code to use
 *  				for demo (NOT for analysis purposes)
 *----------------------------------------------------------------------------
 * Copyright (c) 2008-2011 Keil - An ARM Company.
 * Name: Anita Tino
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "Blinky.h"
#include "LPC17xx.h"                       
#include "GLCD.h"
#include "LED.h"

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */
/*
//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

#define KBD_MASK 0x79

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}*/
/////////////////////////////////////////////////////////

char text[10];
char kbd_print[10];
/* Import external variables from IRQ.c file                                  */
extern uint8_t  clock_ms;


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

void delayFunction(int i){
		while(i > 0){
			__NOP();
			i--;
		}
}


int initBlinky (void) {

  LED_Init();                                /* LED Initialization            */
	
	
#ifdef __USE_LCD
  GLCD_Init();                               /* Initialize graphical LCD (if enabled */

  GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, "     COE718 Lab2    ");
	GLCD_SetTextColor(White);
  GLCD_DisplayString(1, 0, __FI, "       ");
  GLCD_DisplayString(2, 0, __FI, "");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(5, 0, __FI, "    a = b + (c*d)   ");
	GLCD_DisplayString(6, 0, __FI, "Method:             ");
	GLCD_DisplayString(7, 0, __FI, "    a =             ");
  GLCD_SetBackColor(White);
#endif

  //SystemCoreClockUpdate();
  //SysTick_Config(SystemCoreClock/100);       /* Generate interrupt each 10 ms *
	
}
