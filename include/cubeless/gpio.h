#ifndef GPIO_H
#define GPIO_H

#include "stm32g4xx_hal.h"

/* =====================================
 * CONFIG MODE
 * ===================================== */
typedef enum {

    GPIO_CONFIG_BASIC = 0,

    GPIO_CONFIG_ADVANCED

} GpioConfigMode_t;

/* =====================================
 * PULL MODE
 * ===================================== */
typedef enum {

    GPIO_NO_PULL = 0,

    GPIO_PULL_UP,

    GPIO_PULL_DOWN

} GpioPullMode_t;

/* =====================================
 * GPIO PRESETS
 * ===================================== */
typedef enum {

    /* =========================
     * DIGITAL
     * ========================= */
    GPIO_INPUT_DEFAULT = 0,

    GPIO_OUTPUT_DEFAULT,

    GPIO_OUTPUT_OD_DEFAULT,

    /* =========================
     * ANALOG
     * ========================= */
    GPIO_ANALOG,

    /* =========================
     * UART
     * ========================= */
    GPIO_UART_TX_DEFAULT,

    GPIO_UART_RX_DEFAULT,

    /* =========================
     * I2C
     * ========================= */
    GPIO_I2C_SCL_DEFAULT,

    GPIO_I2C_SDA_DEFAULT,

    /* =========================
     * SPI
     * ========================= */
    GPIO_SPI_SCK_DEFAULT,

    GPIO_SPI_MISO_DEFAULT,

    GPIO_SPI_MOSI_DEFAULT,

    GPIO_SPI_CS_DEFAULT,

    /* =========================
     * PWM / TIMER
     * ========================= */
    GPIO_PWM_DEFAULT,

    /* =========================
     * EXTI
     * ========================= */
    GPIO_EXTI_RISING_DEFAULT,

    GPIO_EXTI_FALLING_DEFAULT,

    GPIO_EXTI_RISING_FALLING_DEFAULT,

    /* =========================
     * ADVANCED
     * ========================= */
    GPIO_INPUT_ADVANCED,

    GPIO_OUTPUT_ADVANCED,

    GPIO_AF_ADVANCED,

    GPIO_ANALOG_ADVANCED

} GpioPreset_t;

/* =====================================
 * ADVANCED CONFIG
 * ===================================== */
typedef struct {

    uint32_t mode;

    GpioPullMode_t pull;

    uint32_t speed;

    uint32_t alternate;

} GpioAdvancedConfig_t;

/* =====================================
 * GPIO CONFIG
 * ===================================== */
typedef struct {

    GPIO_TypeDef *port;

    uint16_t pin;

    GpioPreset_t preset;

    GpioConfigMode_t config_mode;

    GpioAdvancedConfig_t advanced;

} GpioConfig_t;

void gpio_init(GpioConfig_t *conf);

#endif