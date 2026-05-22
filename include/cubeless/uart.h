#ifndef UART_H
#define UART_H

#include "stm32g4xx_hal.h"
#include "stdint.h"

/* =========================
 * UART STATUS
 * ========================= */
typedef enum {

    UART_OK = 0,

    UART_ERROR_INIT,
    UART_ERROR_TIMEOUT,
    UART_ERROR_BUSY

} UartStatus_t;


/* =========================
 * GPIO UART CONFIG
 * ========================= */
typedef struct {

    GPIO_TypeDef *port;

    uint16_t pin;

    uint32_t alternate;

    uint32_t pull;

    uint32_t speed;

} GpioUartConfig_t;


/* =========================
 * UART CONFIG
 * ========================= */
typedef struct {

    USART_TypeDef *instance;

    uint32_t baudrate;

    uint32_t word_length;

    uint32_t stop_bits;

    uint32_t parity;

    uint32_t mode;

    uint32_t hw_flow_ctl;

    uint32_t oversampling;

    /* =========================
     * TX GPIO
     * ========================= */

    GpioUartConfig_t tx;

    /* =========================
     * RX GPIO
     * ========================= */
   
    GpioUartConfig_t rx;

} UartConfig_t;

/* =========================
 * UART HANDLE
 * ========================= */
typedef struct {

    UART_HandleTypeDef handle;

    volatile uint8_t busy;

} Uart_t;

/* =========================
 * API
 * ========================= */
UartStatus_t uart_init(
    Uart_t *uart,
    UartConfig_t *conf
);

UartStatus_t uart_write(
    Uart_t *uart,
    uint8_t *data,
    uint16_t size,
    uint32_t timeout
);

UartStatus_t uart_write_string(
    Uart_t *uart,
    const char *str,
    uint32_t timeout
);

/* =========================
 * FUTURE DMA SUPPORT
 * ========================= */
void uart_wait(Uart_t *uart);

const char *uart_error_str(
    UartStatus_t status
);

#endif