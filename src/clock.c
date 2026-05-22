#include "cubeless/clock.h"

ClockStatus_t clock_init(ClockConfig_t *conf)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    switch(conf->source)
    {
        case CLOCK_SRC_HSI:

            osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
            osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
            osc.PLL.PLLState = RCC_PLL_OFF;
            osc.HSIState = RCC_HSI_ON;

            if(HAL_RCC_OscConfig(&osc) != HAL_OK)
            {
                return CLOCK_ERROR_OSC;
            }

            clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;

            break;

        case CLOCK_SRC_PLL: {

            uint32_t pll_n;

            pll_n = (conf->target_freq * 2) / 16000000;

            if(pll_n < 8 || pll_n > 127)
            {
                return CLOCK_ERROR_PLL_INVALID;
            }

            osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
            osc.HSIState = RCC_HSI_ON;
            osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

            osc.PLL.PLLSource = RCC_PLLSOURCE_HSI;
            osc.PLL.PLLState = RCC_PLL_ON;

            osc.PLL.PLLM = RCC_PLLM_DIV1;
            osc.PLL.PLLR = RCC_PLLR_DIV2;
            osc.PLL.PLLQ = RCC_PLLQ_DIV2;
            osc.PLL.PLLP = RCC_PLLP_DIV2;
            osc.PLL.PLLN = pll_n;

            if(HAL_RCC_OscConfig(&osc) != HAL_OK)
            {
                return CLOCK_ERROR_OSC;
            }

            RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;

            clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

            break;
        }
    }

    clk.ClockType =
          RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_HCLK
        | RCC_CLOCKTYPE_PCLK1
        | RCC_CLOCKTYPE_PCLK2;

    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_4) != HAL_OK)
    {
        return CLOCK_ERROR_CLOCK;
    }

    return CLOCK_OK;
}

const char *clock_error_str(ClockStatus_t status)
{
    switch(status)
    {
        case CLOCK_OK:
            return "CLOCK_OK";

        case CLOCK_ERROR_OSC:
            return "CLOCK_ERROR_OSC";

        case CLOCK_ERROR_CLOCK:
            return "CLOCK_ERROR_CLOCK";

        case CLOCK_ERROR_PLL_INVALID:
            return "CLOCK_ERROR_PLL_INVALID";

        default:
            return "UNKNOWN";
    }
}
