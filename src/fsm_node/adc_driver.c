#include "adc_driver.h"
#include "stm32h7xx_hal.h"

/* AD7386: 16-bit SAR, simultaneous sampling
 * t_CONVERT: ~ 1.0 us (from datasheet typical/max), t_ACQUIRE < 290ns, t_CYC >= (t_CONVERT+t_ACQUIRE)
 * At 20 kHz, period = 50 us. Must fit all three.
 */
void adc_init(void)
{
    /* CS pin, SPI1 configured as master, 16-bit data, CPOL/CPHA per AD7386 */
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    /* RCC bits required before first DMA transfer: AHB1ENR/DMA1ENR etc. (documented in tables) */
}

void adc_trigger_conversion(void)
{
    /* CS low, start conversion on rising edge of CNV / via SPI frame as per datasheet */
    HAL_GPIO_WritePin(ADC_CS_PORT, ADC_CS_PIN, GPIO_PIN_RESET);
    /* Transmit dummy frame to clock out result or use conversion start per mode */
    /* ... register level shown conceptually ... */
    HAL_GPIO_WritePin(ADC_CS_PORT, ADC_CS_PIN, GPIO_PIN_SET);
}

void adc_dma_start(volatile uint16_t *buffer, uint32_t len)
{
    /* DMA stream configured for SPI_RX, circular/normal per design */
    (void)buffer;
    (void)len;
}
