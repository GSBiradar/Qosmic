#include "pat_fsm.h"

void pat_init(pat_ctx_t *ctx)
{
    ctx->state = PAT_IDLE;
    ctx->t_entry_ms = 0;
    ctx->timeout_ms = 5000;
}

void pat_step(pat_ctx_t *ctx, const void *inputs)
{
    (void)inputs;
    switch(ctx->state) {
        case PAT_IDLE: break;
        case PAT_COARSE_SEARCH: break;
        case PAT_MOUNT_TRACK: break;
        case PAT_HANDOFF: break;
        case PAT_FINE_ACQ: break;
        case PAT_FIBER_LOCK: break;
        case PAT_TRACK: break;
        case PAT_FADE_HOLD: break;
        case PAT_SAFE_PARK: break;
        case PAT_FAULT: break;
        default: break;
    }
}
