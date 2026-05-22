#include "cubeless/dma.h"

/* =========================
 * DMA INIT
 * ========================= */
DmaStatus_t dma_init(
    Dma_t *dma,
    DmaConfig_t *conf
)
{
    dma->busy = 0;

    dma->handle.Instance =
        conf->channel;

    dma->handle.Init.Request =
        conf->request;

    dma->handle.Init.Direction =
        conf->direction;

    dma->handle.Init.PeriphInc =
        conf->periph_inc;

    dma->handle.Init.MemInc =
        conf->mem_inc;

    dma->handle.Init.PeriphDataAlignment =
        conf->periph_alignment;

    dma->handle.Init.MemDataAlignment =
        conf->mem_alignment;

    dma->handle.Init.Mode =
        conf->mode;

    dma->handle.Init.Priority =
        conf->priority;

    if (HAL_DMA_Init(
            &dma->handle
        ) != HAL_OK)
    {
        return DMA_ERROR_INIT;
    }

    return DMA_OK;
}

/* =========================
 * DMA WAIT
 * ========================= */
void dma_wait(
    Dma_t *dma
)
{
    while (dma->busy);
}

/* =========================
 * DMA ERROR STRING
 * ========================= */
const char *dma_error_str(
    DmaStatus_t status
)
{
    switch (status)
    {
        case DMA_OK:
            return "DMA_OK";

        case DMA_ERROR_INIT:
            return "DMA_ERROR_INIT";

        case DMA_ERROR_BUSY:
            return "DMA_ERROR_BUSY";

        default:
            return "DMA_UNKNOWN_ERROR";
    }
}