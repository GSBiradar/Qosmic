# QOSMIC — Embedded Firmware Solution

Solution to the QOSMIC Embedded Firmware Engineer technical interview: a free-space
optical (laser) ground-station terminal built around a fast steering mirror (FSM),
an Alt-Az gimbal, and a Linux supervisor.

The repository contains the firmware sources, control simulations, device-tree
fragment, engineering tables, and board-review notes requested by the assignment.
The original problem statement is in
`Technical_Interview_Embedded_Firmware_Engineer_QOSMIC.pdf`.

## System Overview

| Subsystem | Role | Compute / Interface |
| --- | --- | --- |
| FSM node | 20 kHz fine pointing loop, atmospheric tip-tilt rejection, 500 Hz closed-loop bandwidth | STM32H743ZI, SPI ADC/DAC, DMA |
| Gimbal node | 1 kHz position loop, coarse satellite tracking from ephemeris | STM32H7-class MCU, BiSS-C, EtherCAT, CAN-FD |
| Supervisor | Pass scheduling, TLE pointing, telemetry, field update | NXP i.MX8M Mini, Linux (PREEMPT_RT) |
| PAT FSM | Cold-start acquisition, mount-to-FSM handoff, fibre lock, fade hold, safe park | Integration layer |

## Repository Layout

```
src/
  fsm_node/        AD7386 ADC driver, 20 kHz control ISR, startup, main
  gimbal_node/     BiSS-C master, 1 kHz position loop + ephemeris interpolator
  pat_fsm/         Pointing, Acquisition and Tracking state machine
sim/               Python simulations (Bode/margins, closed-loop step, LEO pass)
dt/                i.MX8M Mini SPI sensor device-tree fragment
tables/            Memory/NVIC map, ISR WCET, CAN-FD cycle budget, FDIR table
docs/              Board review, reference list, build command
include/           Minimal stm32h7xx_hal.h stub (build verification only)
build_fsm.sh       FSM node build script
STM32H743ZI_FLASH.ld  Minimal linker script
```

## Building the Firmware

Sources compile with `arm-none-eabi-gcc` (Cortex-M7, hard-float, C11).

On Linux/macOS/WSL:

```bash
sudo apt install -y gcc-arm-none-eabi binutils-arm-none-eabi   # Debian/Ubuntu
cd "/mnt/c/Users/Guru SB/Downloads/Qosmic_Solution"            # WSL path
chmod +x build_fsm.sh
./build_fsm.sh
```

Equivalent command:

```bash
mkdir -p build
arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard \
  -O2 -Wall -Wextra -std=c11 -g -ffunction-sections -fdata-sections \
  -I include -T STM32H743ZI_FLASH.ld -nostdlib -fno-builtin \
  src/fsm_node/startup.c src/fsm_node/main.c \
  src/fsm_node/adc_driver.c src/fsm_node/control_isr.c \
  -o build/fsm_node.elf
arm-none-eabi-size build/fsm_node.elf
```

Included support files:

- `include/stm32h7xx_hal.h` — minimal HAL/register **stub** so the tree builds
  without STM32CubeH7. Replace it with the real HAL/CMSIS headers for hardware.
- `STM32H743ZI_FLASH.ld` — minimal STM32H743ZI linker script.
- `src/fsm_node/startup.c` — vector table and reset handler.
- `src/fsm_node/main.c` — minimal bring-up entry and DMA buffers.

> Note: `build_fsm.sh` builds the FSM node only. Gimbal and PAT sources are
> portable C and can be compiled with the same toolchain for a H7 target.
> Two `-Wunused` warnings come from the example compensator in `control_isr.c`.

## Running the Simulations

Requires Python 3 with `numpy` and `matplotlib`.

```bash
python sim/fsm_bode.py         # open-loop Bode with PM/GM annotations
python sim/fms_cl_step.py      # closed-loop step response
python sim/leo_pass_sim.py     # two-axis LEO pass tracking error
```

The scripts regenerate the plots already checked in:

- `sim/fsm_bode_margins.png`
- `sim/fsm_cl_step.png`
- `sim/leo_pass_tracking.png`

Run from the repository root so the relative `sim/...` output paths resolve.

## Deliverable Tables

| File | Contents |
| --- | --- |
| `tables/q1_memory_nvic.md` | Q1 memory map, DMA regions, NVIC priorities |
| `tables/q1_isr_wcet.md` | 20 kHz ISR WCET budget in cycles and µs |
| `tables/q2_cycle_canfd.md` | Q2 1 ms cycle budget and CAN-FD bit timing |
| `tables/grand_challenge_fdir.md` | FDIR: failure, detection, latency, response |
| `docs/board_review.md` | Board review: defect, failure mode, fix |

## Key Design Decisions

- **FSM node:** bare-metal, timer-driven 20 kHz loop; no RTOS on the hot path
  (single periodic activity, no worst-case scheduler jitter). ADC/DAC buffers
  live in cache-maintained AXI SRAM, not DTCM.
- **Watchdog:** independent window watchdog, refreshed only after a healthy
  loop cycle (deadline met, samples valid), not blindly at ISR entry.
- **Gimbal:** BiSS-C implemented on timer + DMA for deterministic sampling;
  position loop on the MCU, current loop on the EtherCAT drive.
- **Supervisor:** PREEMPT_RT Linux for scheduling/telemetry; the 1 kHz motion
  loop stays off Linux because its worst-case latency does not meet the budget.
- **Safety:** laser emission gated in hardware; firmware can permit but not
  force emission.

## References

Datasheets, reference manuals, and standards used are listed by document
number and revision in `docs/references.md`.

## Notes

- The build uses `stm32h7xx_hal.h`; install the STM32H7 HAL/CMSIS package or
  the STM32CubeH7 firmware tree to compile against hardware headers.
- Numeric values in the tables and simulations are labelled calculated,
  simulated, measured, or estimated as required by the submission format.
