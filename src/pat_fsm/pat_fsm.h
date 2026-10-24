/* PAT State Machine - Pointing, Acquisition, Tracking */
#ifndef PAT_FSM_H
#define PAT_FSM_H

#include <stdint.h>

typedef enum {
    PAT_IDLE,
    PAT_COARSE_SEARCH,
    PAT_MOUNT_TRACK,
    PAT_HANDOFF,
    PAT_FINE_ACQ,
    PAT_FIBER_LOCK,
    PAT_TRACK,
    PAT_FADE_HOLD,
    PAT_SAFE_PARK,
    PAT_FAULT
} pat_state_t;

typedef struct {
    pat_state_t state;
    uint32_t t_entry_ms;
    uint32_t timeout_ms;
} pat_ctx_t;

void pat_init(pat_ctx_t *ctx);
void pat_step(pat_ctx_t *ctx, const void *inputs);

#endif
