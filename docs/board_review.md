| # | Defect | Field failure mode | Fix |
| --- | --- | --- | --- |
| 1 | ADC DMA buf in DTCM @0x20000000 declared uint16_t[4] with D-cache enabled | Cache coherence: stale/corrupt samples | Use non-cacheable region or 32B aligned + SCB_CleanDCache/InvalidateDCache at DMA boundaries; prefer AXI SRAM non-cacheable |
| 2 | FreeRTOS NVIC group 2/2, control ISR calls xQueueSendFromISR | Priority inversion/jitter, API misuse if not ISR-safe; can block preempt | Control ISR must not call blocking RTOS APIs; use lock-free ring or publish outside ISR; set ISR priority >= configMAX_SYSCALL_INTERRUPT_PRIORITY |
| 3 | IWDG refreshed in control ISR only | Misses task starvation/lockups not visible to ISR; false alive | Refresh only when health checks pass (loop deadline met, sensors valid) from supervised context or use window WDT with conditions |
| 4 | VREF decoupled 2.2uF X7R to digital 3V3 via 100R | Reference noise/IR drop | Use dedicated clean analog reference, RC/PI filtered, separate regulator or ferrite+low ESR, reference to AGND |
| 5 | Ferrite isolates 3V3A; bulk cap on digital side of bead | HF return path broken, noise coupling | Put bulk/ceramic on analog side of bead, star to AGND, avoid splitting return |
| 6 | NRST no pull-up/cap, BOOT0 floating | Brownout/boot glitches | Add 10k pull-up to NRST, optional cap; BOOT0 pull-down or defined via strap |
| 7 | 25MHz HSE 22pF vs C_L=8pF | Frequency off, PLL unlock/jitter | Use correct load caps (series/parallel calc), match C_L |
| 8 | HV amp enable input during reset/40ms | Inadvertent enable/glitch | Drive via open-drain with pull-down, enable only after checks/power-good/seq complete |
