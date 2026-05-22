#include "cubeless/clock.h"

#include "stm32g4xx_hal.h"

/* =========================
 * LED CONFIG
 * ========================= */
#define LED_PORT        GPIOA
#define LED_PIN         GPIO_PIN_5

#define LED_DELAY_MS    500

/* =========================
 * CLOCK CONFIG
 * ========================= */
ClockConfig_t clock_conf = {
    .source = CLOCK_SRC_PLL,
    .target_freq = 80000000
};

/* =========================
 * PRIVATE FUNCTIONS
 * ========================= */
static void led_init(void);

/* =========================
 * MAIN
 * ========================= */
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

    /* =========================
     * SYSTEM CLOCK
     * ========================= */
    clock_init(&clock_conf);

    SystemCoreClockUpdate();

    /* =========================
     * LED INIT
     * ========================= */
    led_init();

    while (1)
    {
        HAL_GPIO_TogglePin(
            LED_PORT,
            LED_PIN
        );

        HAL_Delay(LED_DELAY_MS);
    }
}

/* =========================
 * LED INIT
 * ========================= */
static void led_init(void)
{
    GPIO_InitTypeDef led_conf = {0};

    led_conf.Pin = LED_PIN;

    led_conf.Mode =
        GPIO_MODE_OUTPUT_PP;

    led_conf.Pull =
        GPIO_NOPULL;

    led_conf.Speed =
        GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(
        LED_PORT,
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