#include "biss_master.h"

/* BiSS-C: MA clock, frame: Start, CDM, Ack, Position(23), Error(1), Warn(1), CRC(6) etc.
 * Polynomial (example): x^6+x^1+1 (0x43), seed 0x00, MSB first as per encoder
 */
uint8_t biss_crc6(uint64_t data24)
{
    uint8_t crc = 0x00;
    /* compute over position+error+warn field (conceptual) */
    uint64_t d = data24 & 0xFFFFFFULL;
    for(int i=23;i>=0;i--) {
        uint8_t bit = (uint8_t)((d >> i) & 1);
        uint8_t msb = (crc >> 5) & 1;
        crc = ((crc << 1) & 0x3F);
        if(msb ^ bit) crc ^= 0x03; /* poly x^6+x^1+1 */
    }
    return crc ^ 0x00; /* inverted? stated in answer */
}

int biss_read_frame(biss_frame_t *f)
{
    /* Generate MA clock via timer, sample on edges, DMA capture */
    (void)f;
    return 0;
}
