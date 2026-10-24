/* BiSS-C Master - timer+DMA preferred for low jitter */
#ifndef BISS_MASTER_H
#define BISS_MASTER_H

#include <stdint.h>

typedef struct {
    uint32_t pos;
    uint8_t error;
    uint8_t warn;
    uint8_t crc_ok;
} biss_frame_t;

int biss_read_frame(biss_frame_t *f);
uint8_t biss_crc6(uint64_t data24);

#endif
