# Q1 Memory Map with NVIC Priorities
| Region | Physical/Start | Size | Notes |
| --- | --- | --- | --- |
| DMA ADC buffer (adc_rx) | 0x24000000 (AXI SRAM / or DTCM only with care) | 32B aligned, 4x uint16 | D-cacheable only if maintained; prefer non-cacheable or aligned+clean/invalidate |
| DMA DAC buffer (dac_tx) | 0x24000020 | 32B aligned | same |
| Control state block | 0x20000000 DTCM | 256B | hot, zero-wait, CPU only |
| Hot ISR code | ITCM 0x00000000 | 32KB | locked/placed |
| NVIC Priority Grouping | Group 4 (4 preempt, 0 sub) | - | configurable |
| Control timer (TIM1 UP) | Preempt 0 (highest) | - | hard real-time |
| ADC DMA complete (DMA1_Streamx) | Preempt 1 | - | |
| SPI error (SPI1) | Preempt 2 | - | |
| Comms (UART/CAN) | Preempt 3 | - | |
| Fault line (EXTI) | Preempt 4 | - | |
