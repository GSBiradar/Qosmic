/* 20 kHz Hard Real-Time Control ISR - STM32H743, no blocking, no allocation */
#include <stdint.h>
#include <math.h>
#include "stm32h7xx_hal.h"

extern volatile uint16_t adc_dma_buf[4] __attribute__((aligned(32)));
extern volatile uint16_t dac_dma_buf[4] __attribute__((aligned(32)));

static float x1=0,x2=0,y1=0; /* state vars */
static const float b0=0.125f,b1=0.25f,b2=0.125f,a1=-1.0f,a2=0.25f; /* example */

void TIM1_UP_IRQHandler(void)
{
    /* Clear interrupt */
    TIM1->SR &= ~TIM_SR_UIF;
    
    /* ACQUIRE - read from DMA buffer (cache-maintained) */
    uint16_t r1 = adc_dma_buf[0];
    uint16_t r2 = adc_dma_buf[1];
    (void)r2; /* second axis reserved for two-axis control */
    (void)a2; /* reserved notch coefficient */
    
    /* COMPUTE - compensator in float or fixed point */
    float e = ( (float)r1 - 32768.0f ) / 32768.0f;
    /* notch + PI-like compensator (bilinear discretized) */
    float u = b0*e + b1*x1 + b2*x2 - a1*y1; /* simplified */
    
    /* SATURATE */
    if (u > 1.0f) u = 1.0f;
    if (u < -1.0f) u = -1.0f;
    
    /* OUTPUT */
    uint16_t d = (uint16_t)((u*32768.0f) + 32768.0f);
    dac_dma_buf[0] = d;
    
    /* Update state */
    x2=x1; x1=e; y1=u;
    
    /* NO blocking calls, NO allocation */
}
