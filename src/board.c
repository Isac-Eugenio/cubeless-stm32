#include "cubeless/board.h"
#include "cubeless/clock.h"

BoardStatus_t board_init(
    Board_t *board,
    BoardConfig_t *config
){
    BoardStatus_t status = {0};

    if(config->enable.clock){
        status.clock =
            clock_init(&config->clock);
        SystemCoreClockUpdate();
    }

    if(config->enable.uart){

        uart_enable(config->uart.instance);
        status.uart =
            uart_init(board->uart, &config->uart);
    }

    if(config->enable.dma){
        dma_enable(config->dma.channel);
        status.dma =
            dma_init(board->dma, &config->dma);
    }

    return status;
}

/* =========================
 * SYSTICK
 * ========================= */
void SysTick_Handler(void)
{
    HAL_IncTick();
}