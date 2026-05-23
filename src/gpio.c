#include "cubeless/gpio.h"

/* =====================================
 * PRIVATE
 * ===================================== */
static void _define_preset(
    GPIO_InitTypeDef *gpio,
    GpioPreset_t preset
);

/* =====================================
 * GPIO INIT
 * ===================================== */
void gpio_init(
    GpioConfig_t *conf
)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = conf->pin;

    switch (conf->config_mode)
    {
        /* =========================
         * BASIC CONFIG
         * ========================= */
        case GPIO_CONFIG_BASIC:

            _define_preset(
                &gpio,
                conf->preset
            );

            break;

        /* =========================
         * ADVANCED CONFIG
         * ========================= */
        case GPIO_CONFIG_ADVANCED:

            gpio.Mode =
                conf->advanced.mode;

            gpio.Pull =
                conf->advanced.pull;

            gpio.Speed =
                conf->advanced.speed;

            gpio.Alternate =
                conf->advanced.alternate;

            break;
    }

    HAL_GPIO_Init(
        conf->port,
        &gpio
    );
}

/* =====================================
 * DEFINE PRESET
 * ===================================== */
static void _define_preset(
    GPIO_InitTypeDef *gpio,
    GpioPreset_t preset
)
{
    switch (preset)
    {
        /* =========================
         * OUTPUT
         * ========================= */
        case GPIO_OUTPUT_DEFAULT:

            gpio->Mode =
                GPIO_MODE_OUTPUT_PP;

            gpio->Pull =
                GPIO_NOPULL;

            gpio->Speed =
                GPIO_SPEED_FREQ_LOW;

            break;

        case GPIO_OUTPUT_OD_DEFAULT:

            gpio->Mode =
                GPIO_MODE_OUTPUT_OD;

            gpio->Pull =
                GPIO_NOPULL;

            gpio->Speed =
                GPIO_SPEED_FREQ_LOW;

            break;

        /* =========================
         * INPUT
         * ========================= */
        case GPIO_INPUT_DEFAULT:

            gpio->Mode =
                GPIO_MODE_INPUT;

            gpio->Pull =
                GPIO_NOPULL;

            break;

        /* =========================
         * ANALOG
         * ========================= */
        case GPIO_ANALOG:

            gpio->Mode =
                GPIO_MODE_ANALOG;

            gpio->Pull =
                GPIO_NOPULL;

            break;

        /* =========================
         * UART
         * ========================= */
        case GPIO_UART_TX_DEFAULT:

            gpio->Mode =
                GPIO_MODE_AF_PP;

            gpio->Pull =
                GPIO_NOPULL;

            gpio->Speed =
                GPIO_SPEED_FREQ_VERY_HIGH;

            break;

        case GPIO_UART_RX_DEFAULT:

            gpio->Mode =
                GPIO_MODE_AF_PP;

            gpio->Pull =
                GPIO_NOPULL;

            gpio->Speed =
                GPIO_SPEED_FREQ_VERY_HIGH;

            break;

        default:
            break;
    }
}