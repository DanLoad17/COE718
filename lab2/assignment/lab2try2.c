#include "LPC17xx.h"
#include "bitband.h"
#include "bitband.c"
#include "Barrel_shifting.c"
#include "cond_ex.c"

// Bit-banding alias addresses for LEDs
#define LED1_BB_ALIAS (*((volatile unsigned long *)0x233800B0) // P1.28
#define LED2_BB_ALIAS (*((volatile unsigned long *)0x23380408) // P2.2

// Function to perform barrel shifting
int barrelShiftExample(int a, int b) {
    return (a << b) | (a >> (32 - b));
}

// Function to display a value on an LCD (simulated)
void displayOnLCD(int value) {
    // Code to display 'value' on an LCD
    // Replace with your actual LCD code
}

int main() {
    // Initialize GPIO pins for LEDs
    LPC_PINCON->PINSEL3 &= ~(3 << 24);  // P1.28 as GPIO
    LPC_GPIO1->FIODIR |= (1 << 28);     // P1.28 as output
    LPC_PINCON->PINSEL4 &= ~(3 << 4);   // P2.2 as GPIO
    LPC_GPIO2->FIODIR |= (1 << 2);      // P2.2 as output

    while (1) {
        // Bit-banding method with conditional execution ('s' suffix)
        LED1_BB_ALIAS = 1; // Turn on LED1 (P1.28) using bit-banding
        LED2_BB_ALIAS = 1; // Turn on LED2 (P2.2) using bit-banding

        // Delay for a while
        for (int i = 0; i < 1000000; i++);

        LED1_BB_ALIAS = 0; // Turn off LED1 (P1.28) using bit-banding
        LED2_BB_ALIAS = 0; // Turn off LED2 (P2.2) using bit-banding

        // Delay for a while
        for (int i = 0; i < 1000000; i++);

        // Mask method
        LPC_GPIO1->FIOPIN |= (1 << 28);  // Turn on LED1
        LPC_GPIO2->FIOPIN |= (1 << 2);   // Turn on LED2

        // Delay for a while
        for (int i = 0; i < 1000000; i++);

        LPC_GPIO1->FIOPIN &= ~(1 << 28); // Turn off LED1
        LPC_GPIO2->FIOPIN &= ~(1 << 2);  // Turn off LED2

        // Delay for a while
        for (int i = 0; i < 1000000; i++);

        // Function method
        // You can call functions to control LEDs here
        // Example: LED2_On(); to turn on LED2

        // Perform barrel shifting and display the result on an LCD
        int result = barrelShiftExample(0x12345678, 3);
        displayOnLCD(result);
    }

    return 0;
}
