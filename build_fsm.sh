#!/bin/bash
set -e

mkdir -p build

arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard \
  -O2 -Wall -Wextra -std=c11 -g \
  -ffunction-sections -fdata-sections \
  -I include \
  -T STM32H743ZI_FLASH.ld \
  -nostdlib -fno-builtin \
  src/fsm_node/startup.c src/fsm_node/main.c \
  src/fsm_node/adc_driver.c src/fsm_node/control_isr.c \
  -o build/fsm_node.elf

arm-none-eabi-size build/fsm_node.elf
