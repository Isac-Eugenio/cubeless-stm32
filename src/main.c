#include "cubeless/serial.h"
#include "cubeless/clock.h"
#include "stm32g4xx_hal.h"

#include "stdio.h"

static void led_init(void);

/* =========================
 * CLOCK CONFIG
 * ========================= */
ClockConfig_t clock_conf = {
    .source = CLOCK_SRC_PLL,
    .target_freq = 80000000
};


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

    serial_init();

    while (1)
    {
       printf("ola mundo \r\n");
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
 * SYSTICK
 * ========================= */
void SysTick_Handler(void)
{
    HAL_IncTick();
}