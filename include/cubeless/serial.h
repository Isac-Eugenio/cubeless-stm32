#ifndef SERIAL_H
#define SERIAL_H

#include "cubeless/uart.h"
#include "cubeless/dma.h"
#include "stdint.h"
typedef enum {
    SERIAL_OK = 0,

    SERIAL_ERROR_UART,

    SERIAL_ERROR_DMA
} SerialStatus_t;

typedef struct {
    uint32_t baudrate;
} SerialConfig_t;

void serial_init(void);

#endif