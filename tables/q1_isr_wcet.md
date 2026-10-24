# Q1 ISR WCET Budget
| Operation | Cycles (estimated) | us @ 480MHz | Measured with |
| --- | --- | --- | --- |
| Acquire (DMA read/copy) | 50 | 0.104 | DWT CYCCNT / ETM / logic analyzer |
| Compensator (float+notch) | 800 | 1.667 | DWT CYCCNT |
| Output (DAC update) | 40 | 0.083 | DWT CYCCNT |
| Overhead/ISR entry/exit | 60 | 0.125 | DWT CYCCNT |
| Total WCET | 950 | 1.979 | margin to 50us (20kHz) |
