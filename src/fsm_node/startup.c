/* Minimal Cortex-M7 startup for local build verification. */
#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);
extern void TIM1_UP_IRQHandler(void);

void Reset_Handler(void);
void Default_Handler(void);

void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata) {
        *dst++ = *src++;
    }
    for (dst = &_sbss; dst < &_ebss; ) {
        *dst++ = 0U;
    }

    (void)main();
    for (;;) {
    }
}

void Default_Handler(void)
{
    for (;;) {
    }
}

__attribute__((section(".isr_vector"), used))
void (*const g_pfnVectors[])(void) = {
    (void (*)(void))(&_estack),
    Reset_Handler,
    Default_Handler, /* NMI */
    Default_Handler, /* HardFault */
    Default_Handler, /* MemManage */
    Default_Handler, /* BusFault */
    Default_Handler, /* UsageFault */
    0, 0, 0, 0,
    Default_Handler, /* SVCall */
    Default_Handler, /* DebugMonitor */
    0,
    Default_Handler, /* PendSV */
    Default_Handler, /* SysTick */
    Default_Handler, /* IRQ0  WWDG */
    Default_Handler, /* IRQ1  PVD */
    Default_Handler, /* IRQ2  TAMP */
    Default_Handler, /* IRQ3  RTC_WKUP */
    Default_Handler, /* IRQ4  FLASH */
    Default_Handler, /* IRQ5  RCC */
    Default_Handler, /* IRQ6  EXTI0 */
    Default_Handler, /* IRQ7  EXTI1 */
    Default_Handler, /* IRQ8  EXTI2 */
    Default_Handler, /* IRQ9  EXTI3 */
    Default_Handler, /* IRQ10 EXTI4 */
    Default_Handler, /* IRQ11 DMA1_Stream0 */
    Default_Handler, /* IRQ12 DMA1_Stream1 */
    Default_Handler, /* IRQ13 DMA1_Stream2 */
    Default_Handler, /* IRQ14 DMA1_Stream3 */
    Default_Handler, /* IRQ15 DMA1_Stream4 */
    Default_Handler, /* IRQ16 DMA1_Stream5 */
    Default_Handler, /* IRQ17 DMA1_Stream6 */
    Default_Handler, /* IRQ18 ADC */
    Default_Handler, /* IRQ19 FDCAN1_IT0 */
    Default_Handler, /* IRQ20 FDCAN2_IT0 */
    Default_Handler, /* IRQ21 FDCAN1_IT1 */
    Default_Handler, /* IRQ22 FDCAN2_IT1 */
    Default_Handler, /* IRQ23 EXTI9_5 */
    Default_Handler, /* IRQ24 TIM1_BRK */
    TIM1_UP_IRQHandler, /* IRQ25 TIM1_UP */
    Default_Handler, /* IRQ26 TIM1_TRG_COM */
    Default_Handler, /* IRQ27 TIM1_CC */
};
