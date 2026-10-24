# Grand Challenge FDIR Table
| Firmware-visible failure | Detection method | Detection latency | Response (degrade-and-continue / safe-park) |
| --- | --- | --- | --- |
| QPD loss / no signal | SNR/ADC validity | < 1 ms | degrade-and-continue or reacquire |
| FSM deadline miss | TIM/monitor/cycle counter | < 50 us | safe-park (laser inhibit) |
| Gimbal comms lost (CAN) | heartbeat timeout | < 10 ms | safe-park / mount hold check |
| Encoder CRC fail | CRC counter | per frame < 1 ms | freeze then escalate to safe-park |
| Laser interlock fault | HW line readback | < 100 us | safe-park immediately |
| HV amp overtemp/fault | GPIO/ADC | < 1 ms | safe-park |
| Watchdog timeout | HW WDT | < WDT window | safe-park all subsystems |
