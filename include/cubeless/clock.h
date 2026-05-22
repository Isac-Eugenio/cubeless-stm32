#ifndef CLOCK_H
#define CLOCK_H

#include "stm32g4xx_hal.h"
#include "stdint.h"

typedef enum {
    CLOCK_SRC_HSI,
    CLOCK_SRC_PLL
} ClockSource_t;

typedef enum {
    CLOCK_OK = 0,
    CLOCK_ERROR_OSC,
    CLOCK_ERROR_CLOCK,
    CLOCK_ERROR_PLL_INVALID
} ClockStatus_t;

typedef struct {

    ClockSource_t source;

    uint32_t target_freq;

} ClockConfig_t;

ClockStatus_t clock_init(ClockConfig_t *conf);

const char *clock_error_str(ClockStatus_t status);
#endif