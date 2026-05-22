#include "cubeless/clock.h"
#include "cubeless/uart.h"

#include "stm32g4xx_hal.h"
#include "stdio.h"

/* =========================
 * CLOCK CONFIG
 * ========================= */
ClockConfig_t clock_conf = {
    .source = CLOCK_SRC_PLL,
    .target_freq = 80000000
};

/* =========================
 * UART CONFIG
 * ========================= */
UartConfig_t uart2_config = {

    .instance = USART2,

    .baudrate = 115200,

    .word_length = UART_WORDLENGTH_8B,

    .stop_bits = UART_STOPBITS_1,

    .parity = UART_PARITY_NONE,

    .mode = UART_MODE_TX_RX,

    .hw_flow_ctl = UART_HWCONTROL_NONE,

    .oversampling = UART_OVERSAMPLING_16,

    .tx = {
        .port = GPIOA,
        .pin = GPIO_PIN_2,
        .alternate = GPIO_AF7_USART2,
        .pull = GPIO_NOPULL,
        .speed = GPIO_SPEED_FREQ_VERY_HIGH
    },

    .rx = {
        .port = GPIOA,
        .pin = GPIO_PIN_3,
        .alternate = GPIO_AF7_USART2,
        .pull = GPIO_NOPULL,
        .speed = GPIO_SPEED_FREQ_VERY_HIGH
    }
};

/* =========================
 * UART HANDLE
 * ========================= */
Uart_t uart2;

/* =========================
 * printf redirect
 * ========================= */
int _write(int file, char *ptr, int len)
{
    uart_write(
        &uart2,
        (uint8_t*)ptr,
        len,
        HAL_MAX_DELAY
    );

    return len;
}

int main(void)
{
    HAL_Init();

    /* =========================
     * CLOCK ENABLE
     * ========================= */
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    __HAL_RCC_USART2_CLK_ENABLE();

    HAL_PWREx_ControlVoltageScaling(
        PWR_REGULATOR_VOLTAGE_SCALE1
    );

    /* =========================
     * SYSTEM CLOCK
     * ========================= */
    clock_init(&clock_conf);

    SystemCoreClockUpdate();

    /* =========================
     * UART INIT
     * ========================= */
    if (uart_init(
            &uart2,
            &uart2_config
        ) != UART_OK)
    {
        while (1);
    }

    printf("cubeless uart printf example\r\n");

    uint32_t counter = 0;

    while (1)
    {
        printf(
            "counter: %lu\r\n",
            counter++
        );

        HAL_Delay(1000);
    }
}

/* =========================
 * SYSTICK
 * ========================= */
void SysTick_Handler(void)
{
    HAL_IncTick();
}