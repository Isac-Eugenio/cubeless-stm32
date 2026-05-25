#include "cubeless/clock.h"
#include "cubeless/gpio.h"
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
 * LED CONFIG
 * ========================= */

GpioConfig_t led = {
    .config_mode = GPIO_CONFIG_BASIC,
    .preset = GPIO_OUTPUT_DEFAULT,
    .port = GPIOA,
    .pin = GPIO_PIN_5
};


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

    gpio_init(&led);

    while (1)
    {   
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

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