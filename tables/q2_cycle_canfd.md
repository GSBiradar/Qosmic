# Q2 Cycle Budget with CAN-FD Bit Timing
| Item | Time | Notes |
| --- | --- | --- |
| BiSS-C frame (MA ~1-2MHz) | ~10-20 us | timer+DMA |
| IMU (SPI) | ~10 us | |
| Temp sensor (I2C) | ~50 us (or interrupt) | |
| Control computation | ~200-500 us | dominates if heavy |
| Backbone publish (CAN-FD) | ~50-100 us | |
| Total | < 800 us | < 1000 us margin |

# CAN-FD Bit Timing (80 MHz kernel)
| Phase | Prescaler | TSEG1 | TSEG2 | SJW | Sample Point | Bit Time | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Arbitration 500 kbps | 8 | 13 | 2 | 1 | ~87.5% | 2000 ns | |
| Data 8 Mbps | 1 | 7 | 2 | 1 | ~80% | 125 ns | TCAN1042 loop delay must be accounted; TDC required if > ~1/2 bit |
