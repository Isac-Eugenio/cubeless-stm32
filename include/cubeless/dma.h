#ifndef DMA_H
#define DMA_H

#include "stm32g4xx_hal.h"
#include "stdint.h"

/* =========================
 * DMA STATUS
 * ========================= */
typedef enum {

    DMA_OK = 0,

    DMA_ERROR_INIT,

    DMA_ERROR_BUSY

} DmaStatus_t;

/* =========================
 * DMA CONFIG
 * ========================= */
typedef struct {

    DMA_Channel_TypeDef *channel;

    uint32_t request;

    uint32_t direction;

    uint32_t periph_inc;

    uint32_t mem_inc;

    uint32_t periph_alignment;

    uint32_t mem_alignment;

    uint32_t mode;

    uint32_t priority;

} DmaConfig_t;

/* =========================
 * DMA HANDLE
 * ========================= */
typedef struct {

    DMA_HandleTypeDef handle;

    volatile uint8_t busy;

} Dma_t;

/* =========================
 * API
 * ========================= */

void dma_enable(DMA_Channel_TypeDef *channel);

DmaStatus_t dma_init(
    Dma_t *dma,
    DmaConfig_t *conf
);

void dma_wait(
    Dma_t *dma
);

const char *dma_error_str(
    DmaStatus_t status
);

#endif