/* Minimal application entry for local build verification.
 * Replace with the real board bring-up (clock tree, NVIC, timers, DMA).
 */
#include <stdint.h>
#include "adc_driver.h"

volatile uint16_t adc_dma_buf[4] __attribute__((aligned(32)));
volatile uint16_t dac_dma_buf[4] __attribute__((aligned(32)));

int main(void)
{
    adc_init();
    adc_dma_start(adc_dma_buf, 4U);

    for (;;) {
    }
}
