#include "cmsis_os.h"                                           // CMSIS RTOS header file

#include <stdio.h>
#include "LPC17xx.h"                       
#include "GLCD.h"
#include "LED.h"

#define __FI        1   
#define DELAY_VAL 	12

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
/*----------------------------------------------------------------------------
 *      Sample threads
 *---------------------------------------------------------------------------*/
unsigned int counta=0;
unsigned int countb=0;
unsigned int countc=0;
  
void Thread1 (void const *argument); // thread function
void Thread2 (void const *argument); // thread function
void Thread3 (void const *argument);


osThreadId tid_Thread; // thread id
osThreadDef (Thread1, osPriorityNormal, 1, 0);                   // thread object

osThreadId tid2_Thread; // thread id
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread object

osThreadId tid3_Thread;
osThreadDef(Thread3, osPriorityNormal, 1, 0);

#define __USE_LCD   0		

int Init_Thread (void) {
	
	LED_Init();
	#ifdef __USE_LCD
	GLCD_Init();
  GLCD_Clear(White);                         /* Clear graphical LCD display   */
 
	#endif

  tid_Thread = osThreadCreate (osThread(Thread1), NULL);
	tid2_Thread = osThreadCreate (osThread(Thread2), NULL);
	tid3_Thread = osThreadCreate (osThread(Thread3), NULL);
  if(!tid_Thread) return(-1);
  
  return(0);
}


void Thread2 (void const *argument) {
	
	  for(;;) {
			#ifdef __USE_LCD
			GLCD_DisplayString(0, 0, __FI, "2");
			#endif
			//osDelay(DELAY_VAL);
			countb++;
			LPC_GPIO1->FIOPIN &=  ~1UL<<31;
			LPC_GPIO1->FIOPIN &=  ~1UL<<29;
			LPC_GPIO2->FIOPIN |=  1UL<<2;
			osDelay(DELAY_VAL);
  }
}

void Thread1 (void const *argument) {
	
	 for(;;) {
			#ifdef __USE_LCD
			GLCD_DisplayString(0, 0, __FI, "1");
			#endif
		 //osDelay(DELAY_VAL);
		 counta++;	
		 LPC_GPIO2->FIOPIN &=  ~1UL<<2;
		 LPC_GPIO1->FIOPIN &=  ~1UL<<31;
		 LPC_GPIO1->FIOPIN |=  1UL<<29;
		 osDelay(DELAY_VAL);
  }
}

void Thread3 (void const *argument){
	
	for(;;){
			#ifdef __USE_LCD
			GLCD_DisplayString(0, 0, __FI, "3");
			#endif
		//osDelay(DELAY_VAL);
		countc++;
		LPC_GPIO2->FIOPIN &=  ~1UL<<2;
		LPC_GPIO1->FIOPIN &=  ~1UL<<29;
		LPC_GPIO1->FIOPIN |=  1UL<<31;
		osDelay(DELAY_VAL);
	}
		
}
