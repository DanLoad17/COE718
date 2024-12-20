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
#include "Blinky.h"
#include "LPC17xx.h"                       
#include "GLCD.h"
#include "LED.h"
#include "KBD.h" ////////
//#include "Board_LED.h" 

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */

//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}
/////////////////////////////////////////////////////////

char text[10];
char text_l[10];
/////////////////////////////////THIS WAS COMMENTED
static volatile uint16_t AD_dbg;
//uint16_t AD_dbg; //and this was for demo version i believe (debug)

uint16_t ADC_last;                      // Last converted value
/* Import external variables from IRQ.c file                                  */
extern uint8_t  clock_ms;


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	//MAKE ALL THESE
	//int32_t  res;
  //uint32_t AD_sum   = 0U;
  //uint32_t AD_cnt   = 0U; THESE ARE NOT NEEDED AS WE DO NOT REQUIRE ADC NOW
  //uint32_t AD_value = 0U;
  //uint32_t AD_print = 0U;
	uint32_t joyst   = 0U;
  uint32_t leds = 0U;

  LED_Init();                                /* LED Initialization            */                             /* ADC Initialization            */
	//Joystick_Initialize(); //////////////// removed cuz did not choose to do with the API
	//ADC_Initialize(); ALSO REMOVED AS NO USE FOR ADC
	
#ifdef __USE_LCD
  GLCD_Init();                               /* Initialize graphical LCD (if enabled */

  GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, "     COE718 Demo    ");
	GLCD_SetTextColor(White);
  GLCD_DisplayString(1, 0, __FI, "       Blinky.c     ");
  GLCD_DisplayString(2, 0, __FI, "  Turn pot for LEDs ");
  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
  //GLCD_DisplayString(6, 0, __FI, "AD value:            ");
#endif

  //SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock/100);       /* Generate interrupt each 10 ms */

  while (1) {                                /* Loop forever                  */
			LPC_GPIO1->FIOCLR; //refresh GPIO for joystick
			joyst = get_button();
	

#ifdef __USE_LCD
			GLCD_SetTextColor(Red);
		
			GLCD_DisplayString(7, 0, __FI, "Joystick: ");
			
			
			leds = 0x01; // from IRQ.c found to set LEDs
			
			switch(joyst){
				case KBD_UP:
					leds <<= 0; //shifts LED based on the inputs
					LED_Out(leds); //turn the LED on (set the one thats on)
					GLCD_DisplayString(7, 12, __FI, " UP   ");
				  printf("UP");
					break;
				case KBD_DOWN:
					leds <<= 2;
					LED_Out(leds);
					GLCD_DisplayString(7, 12, __FI, " DOWN ");
				 printf("DOWN");
					break;
				case KBD_LEFT:
					leds <<= 4;
					LED_Out(leds);
					GLCD_DisplayString(7, 12, __FI, " LEFT ");		
					printf("LEFT");
					break;
				case KBD_RIGHT:
					leds <<= 6;
					LED_Out(leds);
					GLCD_DisplayString(7, 12, __FI, "RIGHT ");	
					printf("RIGHT");
					break;
				case KBD_SELECT:
					leds <<= 7;
					LED_Out(leds);
					GLCD_DisplayString(7, 12, __FI, "SELECT");	
					printf("SELECT");
					break;
			}
			
#endif
    

    /* Print message with AD value every 10 ms                               */
    if (clock_ms) {
      clock_ms = 0;
			printf("%d\n", joyst);
	
    }
  }
}
