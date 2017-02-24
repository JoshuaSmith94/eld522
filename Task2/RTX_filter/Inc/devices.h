// Definitions for the Device Drivers on STM32F3 Discovery Board
// DJM 18/9/14

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DD_H
#define __DD_H

#include "stdint.h" 

// port base addresses for stm32f3_discovery
// these are at PERIPH_BASE (0x40000000) + AHB2PERIPH_BASE (0x08000000) + offset for port
#define GPIO_A_BASE_ADDR  0x48000000  // offset for port A is 0x00000000
#define GPIO_E_BASE_ADDR  0x48001000  // offset for port E is 0x00001000

// define the structure of the ports and port access operations
typedef struct
{
    volatile uint32_t MODER;        /*!< GPIO port mode register,               Address offset: 0x00      */
    volatile uint32_t OTYPER;       /*!< GPIO port output type register,        Address offset: 0x04      */
    volatile uint32_t OSPEEDR;      /*!< GPIO port output speed register,       Address offset: 0x08      */
    volatile uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    volatile uint32_t IDR;          /*!< GPIO port input data register,         Address offset: 0x10      */
    volatile uint32_t ODR;          /*!< GPIO port output data register,        Address offset: 0x14      */
    volatile uint16_t BSRRL;        /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */
    volatile uint16_t BSRRH;        /*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
    volatile uint32_t LCKR;         /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    volatile uint32_t AFR[2];       /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    volatile uint32_t BRR;          /*!< GPIO bit reset register,               Address offset: 0x28 */
} GPIOs;

// pointer to port E
extern GPIOs *GPIO_E;

// mapping of LEDs to port E
#define LED4  0x0100  // Blue2   GPIO_E_PIN_8
#define LED3  0x0200  // Red2    GPIO_E_PIN_9
#define LED5  0x0400  // Orange2 GPIO_E_PIN_10
#define LED7  0x0800  // Green2  GPIO_E_PIN_11
#define LED9  0x1000  // Blue    GPIO_E_PIN_12
#define LED10 0x2000  // Red     GPIO_E_PIN_13
#define LED8  0x4000  // Orange  GPIO_E_PIN_14
#define LED6  0x8000  // Green   GPIO_E_PIN_15

#endif /* __DD_H */
