/**
 * AD7386 ADC Driver - Register level SPI+DAM for 2 channels (expandable to 4)
 * STM32H743ZI, 20 kHz sampling
 */
#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>

#define ADC_CS_PORT GPIOA
#define ADC_CS_PIN  GPIO_PIN_4
#define ADC_SPI     SPI1

void adc_init(void);
void adc_trigger_conversion(void);
void adc_dma_start(volatile uint16_t *buffer, uint32_t len);

#endif
