#include "cmsis_os.h"
#include <stdio.h>
#include "string.h"

// Define thread IDs
osThreadId tid_MemoryManagement, tid_CPUManagement, tid_ApplicationInterface, tid_DeviceManagement, tid_UserInterface;


// Bit Band Macros used to calculate the alias address at run time
#define ADDRESS(x)    (*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))
volatile unsigned long * bit;


char logger[512]; // Assuming logger is a character array for logging with sufficient capacity

// Define thread function prototypes
void MemoryManagement(void const *argument);
void CPUManagement(void const *argument);
void ApplicationInterface(void const *argument);
void DeviceManagement(void const *argument);
void UserInterface(void const *argument);

osThreadDef(MemoryManagement, osPriorityHigh, 1, 0);
osThreadDef(CPUManagement, osPriorityHigh, 1, 0);
osThreadDef(ApplicationInterface, osPriorityNormal, 1, 0);
osThreadDef(DeviceManagement, osPriorityNormal, 1, 0);
osThreadDef(UserInterface, osPriorityBelowNormal, 1, 0);


// Define global variables for task-specific functionality
int memory_access_counter = 0;
int cpu_management_access_counter = 0;
int global_counter = 0;
int i,j,k,l,m;
int cpuCounter10 = 0;

unsigned int user_counter = 0;

// Create a binary semaphore (mutex) to signal logger availability
osMutexId logger_mutex;
osMutexDef(logger_mutex);

osSemaphoreId mem_cpu_mgmt_sema; // Semaphore for Memory and CPU Management
osSemaphoreDef(mem_cpu_mgmt_sema);
osSemaphoreId app_dev_mgmt_sema; // Semaphore for Application and Device Management
osSemaphoreDef(app_dev_mgmt_sema);
osSemaphoreId device_done_semaphore; // Semaphore for Device Management
osSemaphoreDef(device_done_semaphore);

int Init_Thread(void) {

    // Create the shared semaphore
    mem_cpu_mgmt_sema = osSemaphoreCreate(osSemaphore(mem_cpu_mgmt_sema), 0);
    app_dev_mgmt_sema = osSemaphoreCreate(osSemaphore(app_dev_mgmt_sema), 0);
    device_done_semaphore = osSemaphoreCreate(osSemaphore(device_done_semaphore), 0);

    logger_mutex = osMutexCreate(osMutex(logger_mutex));

	// Create Memory Management thread
    tid_MemoryManagement = osThreadCreate(osThread(MemoryManagement), NULL);
    
	// Create CPU Management thread
    tid_CPUManagement = osThreadCreate(osThread(CPUManagement), NULL);
    
	// Create Application Interface thread
    tid_ApplicationInterface = osThreadCreate(osThread(ApplicationInterface), NULL);
    
	// Create Device Management thread
    tid_DeviceManagement = osThreadCreate(osThread(DeviceManagement), NULL);
	
	// Create User Interface thread
    tid_UserInterface = osThreadCreate(osThread(UserInterface), NULL);
		
		if(!tid_MemoryManagement) return(-1);
		if(!tid_CPUManagement) return(-1);
		if(!tid_ApplicationInterface) return(-1);
		if(!tid_DeviceManagement) return(-1);
		if(!tid_UserInterface) return(-1);
  
		return(0);
}

// Implement Memory Management task
void MemoryManagement(void const *argument) {
   for(i=0;i<90000;i++) {

        // Increment memory access counter
        memory_access_counter++; 
        
        // Implement bit band computation to a volatile memory location (simulate this)
        bit = &BitBand(0x2009c034, 29);		
        *bit = 0;
        osDelay(1);
        *bit = 1;
        osDelay(1);
        *bit = 0;
        
        // Pass control to CPU Management
        osSemaphoreRelease(mem_cpu_mgmt_sema);

        // Wait for control to be passed back by CPU Management
        osSemaphoreWait(mem_cpu_mgmt_sema, osWaitForever);

        // Delay the OS for one tick
        osDelay(1); 

        
   } 
	 // Terminate Memory Management task
        osThreadTerminate(NULL);
}

// Implement CPU Management task
void CPUManagement(void const *argument) {
    for (j=0;j<20000;j++) {

        // Increment CPU management access counter
        cpu_management_access_counter++; 

        // Create conditional execution and barrel shifting scenario (simulate this)
        if(cpu_management_access_counter > 10){
            cpuCounter10++;
        }

        // Signal back to Memory Management 
        osSemaphoreRelease(mem_cpu_mgmt_sema);

        // Wait for control to be passed by Memory Management
        osSemaphoreWait(mem_cpu_mgmt_sema, osWaitForever);
        
        
    } 
		// Terminate CPU Management task
        osThreadTerminate(NULL);
}

// Implement Application Interface task
void ApplicationInterface(void const *argument) {
    for (k=0;k<90000;k++) { 
        
        // Ensure that Application executes before Device Management
        //osSemaphoreRelease(app_dev_mgmt_sema);

        // Access the global variable logger using a mutex
        osMutexWait(logger_mutex, osWaitForever);

        // Write a partial message to logger
        strcat(logger, "Partial Message from App Interface\n");
				//global_counter++;
			
        // wait for Device Management to finish
        //osSemaphoreWait(device_done_semaphore, osWaitForever);

        // Release the mutex after writing to logger
        osMutexRelease(logger_mutex);

        // Increase the global counter
        global_counter++;
			
        // Delay the OS for one tick
        osDelay(1); 
    

    } 
		        // Terminate Application Interface task
        osThreadTerminate(NULL);
		
}

// Implement Device Management task
void DeviceManagement(void const *argument) {
    for (l=0;l<90000;l++) { 
        // Ensure Application executes before Device Management
        //osSemaphoreWait(app_dev_mgmt_sema, osWaitForever);

        // Write the ending to the logger variable started by the Application Interface
        osMutexWait(logger_mutex, osWaitForever);
        strcat(logger, "Ending by Device Management\n");
        osMutexRelease(logger_mutex);

        // Signal back to the Application Interface
        //osSemaphoreRelease(app_dev_mgmt_sema);

        //Icnrease the global counter
        global_counter++;

        // Delay the OS for one tick
        osDelay(1);

        
    }   
		// Terminate Device Management task
        osThreadTerminate(NULL);
		
}

// Implement User Interface task
void UserInterface(void const *argument) {
    for (m=0;m<90000;m++) { 
        // Increment the number of users
        user_counter++;
        
        // Delay the OS for one tick
        osDelay(1);
        
         
    }
		// Delete itself
        osThreadTerminate(NULL);
}
