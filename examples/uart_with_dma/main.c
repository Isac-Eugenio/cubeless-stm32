#include "cubeless/clock.h"
#include "cubeless/uart.h"
#include "stm32g4xx_hal.h"
#include "cubeless/dma.h"

#include "string.h"

static void led_init(void);

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
 * DMA CONFIG
 * ========================= */
DmaConfig_t uart2_tx_dma_conf = {

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
};
/* =========================
 * UART HANDLE
 * ========================= */
Uart_t uart2;

/* =========================
 * DMA HANDLE
 * ========================= */
Dma_t uart2_tx_dma;

/* =========================
 * TX BUFFER
 * ========================= */
uint8_t tx_buffer[] =
    "uart dma example\r\n";

int main(void)
{
    HAL_Init();

    /* =========================
     * CLOCK ENABLE
     * ========================= */
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_DMA1_CLK_ENABLE();

    __HAL_RCC_DMAMUX1_CLK_ENABLE();

    HAL_PWREx_ControlVoltageScaling(
        PWR_REGULATOR_VOLTAGE_SCALE1
    );

    /* =========================
     * SYSTEM CLOCK
     * ========================= */
    clock_init(&clock_conf);

    SystemCoreClockUpdate();

    /* =========================
     * INIT
     * ========================= */

    led_init();

    dma_init(&uart2_tx_dma, &uart2_tx_dma_conf);

    __HAL_LINKDMA(
        &uart2.handle,
        hdmatx,
        uart2_tx_dma.handle
    );

    uart_init(&uart2, &uart2_config);

    /* =========================
    * DMA IRQ
    * ========================= */
    HAL_NVIC_SetPriority(
        DMA1_Channel2_IRQn,
        0,
        0
    );

    HAL_NVIC_EnableIRQ(
        DMA1_Channel2_IRQn
    );

    /* =========================
    * USART IRQ
    * ========================= */
    HAL_NVIC_SetPriority(
        USART2_IRQn,
        0,
        0
    );

    HAL_NVIC_EnableIRQ(
        USART2_IRQn
    );

    while (1)
    {
        if (HAL_UART_GetState(&uart2.handle)
            == HAL_UART_STATE_READY)
        {
            HAL_UART_Transmit_DMA(
                &uart2.handle,
                tx_buffer,
                strlen((char*)tx_buffer)
            );
        }

        HAL_Delay(1000);
    }
}

static void led_init(void)
{
    GPIO_InitTypeDef led_conf = {0};

    led_conf.Pin = GPIO_PIN_5;

    led_conf.Mode =
        GPIO_MODE_OUTPUT_PP;

    led_conf.Pull =
        GPIO_NOPULL;

    led_conf.Speed =
        GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(
        GPIOA,
        &led_conf
    );
}
 
/* =========================
 * DMA IRQ HANDLER
 * ========================= */
void DMA1_Channel2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(
        &uart2_tx_dma.handle
    );
}

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(
        &uart2.handle
    );
}

/* =========================
 * SYSTICK
 * ========================= */
void SysTick_Handler(void)
{
    HAL_IncTick();
}