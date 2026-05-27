#include "cubeless/uart.h"
#include "string.h"

/* =========================
 * UART INIT
 * ========================= */
UartStatus_t uart_init(
    Uart_t *uart,
    UartConfig_t *conf
)
{
    uart->busy = 0;

    uart->handle.Instance = conf->instance;

    uart->handle.Init.BaudRate =
        conf->baudrate;

    uart->handle.Init.WordLength =
        conf->word_length;

    uart->handle.Init.StopBits =
        conf->stop_bits;

    uart->handle.Init.Parity =
        conf->parity;

    uart->handle.Init.Mode =
        conf->mode;

    uart->handle.Init.HwFlowCtl =
        conf->hw_flow_ctl;

    uart->handle.Init.OverSampling =
        conf->oversampling;

    GPIO_InitTypeDef gpio_uart = {0};

    /* =========================
    * TX
    * ========================= */
    gpio_uart.Pin =
        conf->tx.pin;

    gpio_uart.Mode =
        GPIO_MODE_AF_PP;

    gpio_uart.Pull =
        conf->tx.pull;

    gpio_uart.Speed =
        conf->tx.speed;

    gpio_uart.Alternate =
        conf->tx.alternate;

    HAL_GPIO_Init(
        conf->tx.port,
        &gpio_uart
    );

    /* =========================
    * RX
    * ========================= */
    gpio_uart.Pin =
        conf->rx.pin;

    gpio_uart.Pull =
        conf->rx.pull;

    gpio_uart.Speed =
        conf->rx.speed;

    gpio_uart.Alternate =
        conf->rx.alternate;

    HAL_GPIO_Init(
        conf->rx.port,
        &gpio_uart
    );

    HAL_GPIO_Init(
        conf->rx.port,
        &gpio_uart
    );

    
    if (HAL_UART_Init(&uart->handle) != HAL_OK)
    {
        return UART_ERROR_INIT;
    }

    return UART_OK;
}


/* =========================
 * GPIO UART
 * ========================= */



/* =========================
 * UART WRITE
 * ========================= */
UartStatus_t uart_write(
    Uart_t *uart,
    uint8_t *data,
    uint16_t size,
    uint32_t timeout
)
{
    uart_wait(uart);

    uart->busy = 1;

    HAL_StatusTypeDef status =
        HAL_UART_Transmit(
            &uart->handle,
            data,
            size,
            timeout
        );

    uart->busy = 0;

    if (status != HAL_OK)
    {
        return UART_ERROR_TIMEOUT;
    }

    return UART_OK;
}

/* =========================
 * UART WRITE STRING
 * ========================= */
UartStatus_t uart_write_string(
    Uart_t *uart,
    const char *str,
    uint32_t timeout
)
{
    return uart_write(
        uart,
        (uint8_t*)str,
        strlen(str),
        timeout
    );
}


/* =========================
 * UART ENABLE
 * ========================= */
void uart_enable(USART_TypeDef *uart){
    if(uart == USART1) __HAL_RCC_USART1_CLK_ENABLE();
    else if(uart == USART2) __HAL_RCC_USART2_CLK_ENABLE();
    else if(uart == USART3) __HAL_RCC_USART3_CLK_ENABLE();
    else if(uart == UART4) __HAL_RCC_UART4_CLK_ENABLE();
    else if(uart == UART5) __HAL_RCC_UART5_CLK_ENABLE();
}

/* =========================
 * UART WAIT
 * ========================= */
void uart_wait(Uart_t *uart)
{
    while (uart->busy);
}

/* =========================
 * UART ERROR STRING
 * ========================= */
const char *uart_error_str(
    UartStatus_t status
)
{
    switch (status)
    {
        case UART_OK:
            return "UART_OK";

        case UART_ERROR_INIT:
            return "UART_ERROR_INIT";

        case UART_ERROR_TIMEOUT:
            return "UART_ERROR_TIMEOUT";

        case UART_ERROR_BUSY:
            return "UART_ERROR_BUSY";

        default:
            return "UART_UNKNOWN_ERROR";
    }
}