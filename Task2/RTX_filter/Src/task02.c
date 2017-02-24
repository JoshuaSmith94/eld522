/**
  ******************************************************************************
  * @file    task02.c
  * @author  DJM
  * @version 0.1
  * @date    18 Dec 2016
  * @brief   Initial implementation of the coursework task 2
  ******************************************************************************
  */

// target board definitions
#include "board_startup.h"
#include "devices.h"

// RTX kernel and C functions */
#include "RTL.h"
#include <stdlib.h>

// length of generated data cycle
#define NUM_SAMPLES 64

// functions in this file
void SetUpPorts(void);

// task identifiers
OS_TID ID, GD, FD, UB, CV;
#define TASK_EVENT1 0x0004
#define TASK_EVENT2 0x0005
#define TASK_EVENT3 0x0006

// define an ID for communicating that the user button has been detected by the ISR
#define BUTTON_EVENT 0x0001

// forward reference 
__task void GenerateData(void);
__task void FilterData(void);
__task void GetUserInput(void);
__task void CalculateValue(void);

// pointer to port E
GPIOs *GPIO_E = (GPIOs *) GPIO_E_BASE_ADDR ;

// define a buffer to be an area of shared memory
#define BUFFER_LENGTH 5
#define FILTER_LENGTH 7

typedef struct 
{
	uint8_t buffer[BUFFER_LENGTH];
	uint16_t count;
	uint16_t head;
	uint16_t tail;
} data_stores;

typedef struct 
{
	float buffer[BUFFER_LENGTH];
	uint16_t count;
	uint16_t head;
	uint16_t tail;
} float_stores;

data_stores data_store, input_store;
float_stores process_store;
enum log_select {MEAN, VARIANCE, BOTH};
enum log_select selection;

// Interrupt service routine for handling externally generally interrupts
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == USER_BUTTON_PIN) 
	{ // check the user button has generated the interrupt
		 
    // indicate to UserButton that the event has happened
    isr_evt_set(BUTTON_EVENT, UB);     
  }
}

// toggle an LED
void ToggleLED(uint16_t Led)
{
  GPIO_E->ODR = GPIO_E->ODR ^ (uint16_t) Led;
  os_dly_wait(50);  // simulate processing for 500ms
}

// turn on an LED and pause (to simulate fixed task time)
// Argument: the location of the LED in the port
void LightLED(uint16_t Led)
{
  GPIO_E->ODR = GPIO_E->ODR | (uint16_t) Led;
  os_dly_wait(50);  // simulate processing for 500ms
}

// turn off  an LED and pause (to simulate fixed task time)
// Argument: the location of the LED in the port
void DimLED(uint16_t Led)
{
  GPIO_E->ODR = GPIO_E->ODR & ~((uint16_t) Led);
  os_dly_wait(50); // simulate processing for 500ms
}

/*----------------------------------------------------------------------------
 *   Task to receive data from the buffer
 *---------------------------------------------------------------------------*/
__task void InputData (void){
	
  // value read from buffer - nothing is done with this as yet so the compiler may warn
  uint8_t read_me;
	
  /* Obtain own system task identification number. */
  ID = os_tsk_self();

  /* Create task2 and obtain its task identification number. */
  GD = os_tsk_create(GenerateData, 1);
  FD = os_tsk_create(FilterData, 1);
	UB = os_tsk_create(GetUserInput, 1);
	CV = os_tsk_create(CalculateValue, 1);

  for (;;) {

    // signal ready to receive more data
    os_evt_set(TASK_EVENT1, GD); 
		
    // wait for data to be sent
    os_evt_wait_or(TASK_EVENT1, 0xffff); 

    // toggle the LED
    ToggleLED(LED4);
		
    // read from data store if there's data in there
    if (data_store.count) 
		{
      read_me = data_store.buffer[data_store.tail];
      data_store.tail = (++data_store.tail) % BUFFER_LENGTH;
      data_store.count--;
      
      input_store.buffer[input_store.head] = read_me;  
      input_store.head = (++input_store.head) % BUFFER_LENGTH;
      input_store.count++;
      
			os_evt_set(TASK_EVENT2, FD);  
    }	
  }	
}


/*----------------------------------------------------------------------------
 *   Task to simulate the generation of data and sending it to a buffer
 *---------------------------------------------------------------------------*/
__task void GenerateData(void) 
{
		
  // count through the values being generated
  uint32_t time_step;
		
  for (;;) {
		
    for(time_step=0; time_step<NUM_SAMPLES; time_step++) {
					
      // wait until data has been received
      os_evt_wait_or (TASK_EVENT1, 0xffff); 

      // toggle the LED
      ToggleLED(LED3);	

      // delay to simulate asynchronous data arrival
      os_dly_wait(rand() % 10);

      // calcuate the next signal value
      data_store.buffer[data_store.head] = time_step;  // generate a ramp of length NUM_SAMPLES
      data_store.head = (++data_store.head) % BUFFER_LENGTH;
      data_store.count++;

      // signal ready to send more data
      os_evt_set (TASK_EVENT1, ID);  
    }
  }
}


/*----------------------------------------------------------------------------
 *   Task to 
 *---------------------------------------------------------------------------*/
__task void FilterData (void)
{
  
	float weight_values[FILTER_LENGTH] = {-0.5,1.0,-2.0,3.0,-2.0,1.0,-0.5};
  float data_in[FILTER_LENGTH];
	float data_out;
  uint8_t data_start=0, n=0, buffer_full = 0;
  for (;;) {

    // wait for data to be sent
    os_evt_wait_or(TASK_EVENT2, 0xffff); 

		// toggle the LED
		ToggleLED(LED6);
		
    // read from data store if there's data in there
    if (input_store.count) {
      data_in[data_start] = input_store.buffer[input_store.tail];
      input_store.tail = (++input_store.tail) % BUFFER_LENGTH;
      input_store.count--;
      
      data_out = 0.0;
			if (buffer_full) {
				for (n=0; n<FILTER_LENGTH; n++)	{
					data_out += data_in[(data_start - n + FILTER_LENGTH) % FILTER_LENGTH] * weight_values[n];
				}
				
				
					
				process_store.buffer[process_store.head] = data_out;  
				process_store.head = (++process_store.head) % BUFFER_LENGTH;
				process_store.count++;
				
				os_evt_set(TASK_EVENT3, CV);
			}
			
			data_start++;
			if (data_start == FILTER_LENGTH){buffer_full=1;}
			data_start = data_start % FILTER_LENGTH;			
    }	
  }	
}

/*----------------------------------------------------------------------------
 *   Task to 
 *---------------------------------------------------------------------------*/
__task void CalculateValue (void)
{
  
  float data_in[BUFFER_LENGTH] = {0,0,0,0,0};
	float mean;
	float variance;
  uint8_t data_start=0, n=0, buffer_full = 0;

  for (;;) {

    // wait for data to be sent
    os_evt_wait_or(TASK_EVENT3, 0xffff); 

    // toggle the LED
    ToggleLED(LED8);
		
    // read from data store if there's data in there
    if (process_store.count) 
		{
      data_in[data_start] = process_store.buffer[process_store.tail];
      process_store.tail = (++process_store.tail) % BUFFER_LENGTH;
      process_store.count--;
						
			if (buffer_full) 
			{
				mean = 0;
				for (n=0; n<BUFFER_LENGTH; n++) 
				{
					mean += data_in[n]/BUFFER_LENGTH;
				}	
				//if (selection == MEAN || selection == BOTH) {
				//log
				//}
				if (selection == BOTH || selection == VARIANCE) 
				{
					variance = 0;
					for (n=0; n<BUFFER_LENGTH; n++) 
					{
						variance += (data_in[n]-mean) * (data_in[n]-mean);
					}
					//log
				}
			}
			data_start++;
			if (data_start == BUFFER_LENGTH){buffer_full=1;}
			data_start = data_start % BUFFER_LENGTH;	
    }	
  }	
}

/*----------------------------------------------------------------------------
 *   Task to respond to user button 
*---------------------------------------------------------------------------*/
__task void GetUserInput(void)
{
		
	LightLED(LED5);
	selection = MEAN;
	for (;;) 
	{		
		os_evt_wait_or(BUTTON_EVENT, 0xffff);
		selection = VARIANCE;
		LightLED(LED7);
		DimLED(LED5);
		os_dly_wait(1);
		
		os_evt_wait_or(BUTTON_EVENT, 0xffff);
		selection = BOTH;
		LightLED(LED5);
		os_dly_wait(1);		
		
		os_evt_wait_or(BUTTON_EVENT, 0xffff);
		selection = MEAN;
		LightLED(LED5);
		DimLED(LED7);
		os_dly_wait(1);
    
	}
}
// set up port E as output, create the semaphore and start RTX
int main(void)
{
  // STM32F3 Discovery Board initialization
  board_startup();

  // initialize port E for output	
  SetUpPorts();
	
  // turn all LEDs off
  GPIO_E->ODR = (uint16_t) 0x0000;
	
  // create the first task
  os_sys_init(InputData);
}


// set up port E for LED outputs 
void SetUpPorts()
{	
	// Configure User Button, connected to PE6 IOs in External Interrupt Mode with rising edge trigger detection
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  // Enable and set EXTI0 Interrupt to the lowest priority
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
  GPIO_E->MODER = (uint32_t) 0x55555555;  // output
  GPIO_E->OSPEEDR = (uint32_t) 0xFFFFFFFF;  // high speed
  GPIO_E->PUPDR = (uint32_t) 0xAAAAAAAA;  // pull down resistors
}

