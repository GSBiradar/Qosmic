/**
 * Minimal stm32h7xx_hal.h STUB for local build/syntax verification only.
 *
 * This is NOT the STMicroelectronics HAL. It provides just enough register
 * declarations and macros for the sources in this repository to compile and
 * link on a host with arm-none-eabi-gcc. Do not use this header for real
 * hardware: replace it with the STM32CubeH7 HAL/CMSIS include tree.
 */
#ifndef STM32H7XX_HAL_H
#define STM32H7XX_HAL_H

#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RCR;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t BDTR;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
    volatile uint32_t OR1;
    volatile uint32_t CCMR3;
    volatile uint32_t CCR5;
    volatile uint32_t CCR6;
    volatile uint32_t AF1;
    volatile uint32_t AF2;
    volatile uint32_t TISEL;
} TIM_TypeDef;

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CFG1;
    volatile uint32_t CFG2;
    volatile uint32_t IER;
    volatile uint32_t SR;
    volatile uint32_t ICR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
} SPI_TypeDef;

#define GPIOA ((GPIO_TypeDef *)0x58020000UL)
#define TIM1  ((TIM_TypeDef *)0x40010000UL)
#define SPI1  ((SPI_TypeDef *)0x40013000UL)

#define GPIO_PIN_0  ((uint16_t)0x0001U)
#define GPIO_PIN_1  ((uint16_t)0x0002U)
#define GPIO_PIN_2  ((uint16_t)0x0004U)
#define GPIO_PIN_3  ((uint16_t)0x0008U)
#define GPIO_PIN_4  ((uint16_t)0x0010U)
#define GPIO_PIN_5  ((uint16_t)0x0020U)
#define GPIO_PIN_6  ((uint16_t)0x0040U)
#define GPIO_PIN_7  ((uint16_t)0x0080U)

typedef enum {
    GPIO_PIN_RESET = 0U,
    GPIO_PIN_SET = 1U
} GPIO_PinState;

#define TIM_SR_UIF (1UL << 0)

static inline void HAL_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin,
                                     GPIO_PinState state)
{
    if (state == GPIO_PIN_SET) {
        port->BSRR = pin;
    } else {
        port->BSRR = (uint32_t)pin << 16;
    }
}

#define __HAL_RCC_SPI1_CLK_ENABLE()  do { } while (0)
#define __HAL_RCC_DMA1_CLK_ENABLE()  do { } while (0)

#endif /* STM32H7XX_HAL_H */
