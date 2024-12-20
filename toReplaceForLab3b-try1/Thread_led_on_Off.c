
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "Board_LED.h"
#include <Math.h>

/*----------------------------------------------------------------------------
 *      ANALYSIS FILE
 *---------------------------------------------------------------------------*/
unsigned int counta=0;
unsigned int countb=0;
unsigned int countc=0;

unsigned int shared_variable=0;
int i,j,k,p,z;
int sumA = 0;
double resultB, resultC, resultD, resultE;
double pi = 3.14159265358979323846;  // Define the value of pi
double r = 2.0;  // Define the value of r
	
void Thread1 (void const *argument); // thread function
void Thread2 (void const *argument); // thread function
void Thread3 (void const *argument); // thread function
void Thread4 (void const *argument); // thread function
void Thread5 (void const *argument); // thread function


osThreadId tid_Thread; // thread id
osThreadDef (Thread1, osPriorityBelowNormal, 1, 0);                   // Task A

osThreadId tid2_Thread; // thread id
osThreadDef (Thread2, osPriorityLow, 1, 0);                   // Task B

osThreadId tid3_Thread; // thread id
osThreadDef (Thread3, osPriorityNormal, 1, 0);                   // Task C 

osThreadId tid4_Thread; // thread id
osThreadDef (Thread4, osPriorityBelowNormal, 1, 0);                   // Task D 

osThreadId tid5_Thread; // thread id
osThreadDef (Thread5, osPriorityLow, 1, 0);                   // Task E 

void delay_ms(uint32_t mills){
	uint32_t iterations = (mills*100000);
	uint32_t i;
	for (i = 0; i < iterations;i++){}
}

long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int Init_Thread (void) {
		
  tid_Thread = osThreadCreate (osThread(Thread1), NULL);
	tid2_Thread = osThreadCreate (osThread(Thread2), NULL);
	tid3_Thread = osThreadCreate (osThread(Thread3), NULL);
	tid4_Thread = osThreadCreate (osThread(Thread4), NULL);
	tid5_Thread = osThreadCreate (osThread(Thread5), NULL);
  if(!tid_Thread) return(-1);
  if(!tid2_Thread) return(-1);
	if(!tid3_Thread) return(-1);
	if(!tid4_Thread) return(-1);
	if(!tid5_Thread) return(-1);
  return(0);
}

void Thread5 (void const *argument) {
	for (z=0;z<1000;z++){
		int n;
		//	Task E
		for (n = 1; n <= 12; n++) {
			double term = n * pi * pow(r, 2);
			resultE += term; 
    }
		
		
		// LED Functionality
//		LED_On(0);
//		LED_Off(1);
//		LED_Off(2);
//		LED_Off(3);
//		LED_Off(4);
		
	}

}


void Thread4 (void const *argument) {
	for (p=0;p < 1000;p++){
		int n;
		//	Task D
		for (n = 0; n <= 5; n++) {
			double term = pow(5, n) / factorial(n);
			resultD += term;
    }
		
		
		// LED Functionality
//		LED_On(4);
//		LED_Off(0);
//		LED_Off(1);
//		LED_Off(2);
//		LED_Off(3);
		
	}

}

void Thread3 (void const *argument) { 
	for (i = 0; i < 1000; i++) {
		int n;
		// Task C
		for (n = 1; n <= 16; n++) {
			double term = (double)(n + 1) / n;
			resultC += term;
    }
			
//		LED_On(3);
//		LED_Off(0);
//		LED_Off(1);
//		LED_Off(2);
//		LED_Off(4);
	}   
	
	//osThreadTerminate(NULL);
}

void Thread2 (void const *argument) {
	for(j = 0;j < 1000;j++) {
		
		int n;
		double term;
		// Task B
		for (n = 1; n <= 16; n++) {
        long long numerator = 1;
        long long denominator = factorial(n);
	
				int  u;
			
        for (u = 1; u <= n; u++) {
            numerator *= 2;
        }
				
        term = (double)numerator / denominator;
				resultB += term;
    }
		
		// Turn on Specific LED
//		LED_On(2);
//		LED_Off(0);
//		LED_Off(1);
//		LED_Off(3);
//		LED_Off(4);
		
	}
	//osThreadTerminate(NULL);
}

void Thread1 (void const *argument) {
	for (k = 1; k < 1000; k++) {
		
		int x;
		// Task A
    for (x = 2; x <= 256; x++) {
        sumA += (x + (x + 2));
    }
		
//		LED_On(1);
//		LED_Off(0);
//		LED_Off(2);
//		LED_Off(3);
//		LED_Off(4);
	
	}
	//osThreadTerminate(NULL);
}
