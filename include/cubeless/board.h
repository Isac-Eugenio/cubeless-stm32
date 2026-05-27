#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "stm32g4xx_hal.h"

#include "clock.h"
#include "uart.h"
#include "dma.h"


/* =========================
 * BOARD HANDLERS
 * ========================= */
typedef struct {
    Uart_t *uart;
    Dma_t *dma;
} Board_t;


/* =========================
 * BOARD STATUS
 * ========================= */
typedef struct {
    ClockStatus_t clock;
    UartStatus_t uart;
    DmaStatus_t dma;
} BoardStatus_t;

/* =========================
 * ENABLE PERIPHERALS
 * ========================= */
typedef struct {

    bool clock;
    bool uart;
    bool dma;

} BoardEnable_t;

/* =========================
 * BOARD CONFIG
 * ========================= */
typedef struct {

    BoardEnable_t enable;

    ClockConfig_t clock;
    UartConfig_t uart;
    DmaConfig_t dma;

} BoardConfig_t;


BoardStatus_t board_init(Board_t *board, BoardConfig_t *board_config);

#endif /* BOARD_H */