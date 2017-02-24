/**
  ******************************************************************************
  * @file    board_startup.h - for STM32F3 Discovery board
  * @author  DJM
  * @date    18/9/14
  * @brief   Header to match start up code that has been moved to board_startup.c
  ******************************************************************************/
  
#ifndef __BOARD_STARTUP_H
#define __BOARD_STARTUP_H
	
/* Board level definitions */
#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"

/* start up functions for STM32F3 Discovery board */
static void SystemClock_Config(void);
static void Error_Handler(void);
void board_startup(void);

#endif


