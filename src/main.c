#include "cubeless/board.h"
#include "cubeless/uart.h"
#include "cubeless/gpio.h"
#include "stm32g4xx_hal.h"

#include "stdio.h"

/* =========================
 * LED CONFIG
 * ========================= */

GpioConfig_t led = {
    .config_mode = GPIO_CONFIG_BASIC,
    .preset = GPIO_OUTPUT_DEFAULT,
    .port = GPIOA,
    .pin = GPIO_PIN_5
};

Uart_t uart2;
Dma_t uart2_tx_dma;

Board_t board = {
    .dma = &uart2_tx_dma,
    .uart = &uart2
};

BoardConfig_t config = {
    .clock  = {
        .source = CLOCK_SRC_PLL,
        .target_freq = 80000000
    },

    .uart  = {
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
    },

    .dma = {
        .channel =
        DMA1_Channel2,

    .request =
        DMA_REQUEST_USART2_TX,

    .direction =
        DMA_MEMORY_TO_PERIPH,

    .periph_inc =
        DMA_PINC_DISABLE,

    .mem_inc =
        DMA_MINC_ENABLE,

    .periph_alignment =
        DMA_PDATAALIGN_BYTE,

    .mem_alignment =
        DMA_MDATAALIGN_BYTE,

    .mode =
        DMA_NORMAL,

    .priority =
        DMA_PRIORITY_LOW
    },
    .enable = {
        .clock = true,
        .uart = true,
        .dma  = true
    }
};

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


    HAL_PWREx_ControlVoltageScaling(
        PWR_REGULATOR_VOLTAGE_SCALE1
    );

    BoardStatus_t t = board_init(&board, &config);

    gpio_init(&led);

    while (1)
    {   

        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);

        printf("%s %s %s\r\n", clock_error_str(t.clock), uart_error_str(t.uart), dma_error_str(t.dma));

        HAL_Delay(1000);
    }
}
