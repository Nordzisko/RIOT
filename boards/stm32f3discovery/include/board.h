/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @defgroup    boards_stm32f3discovery STM32F3Discovery
 * @ingroup     boards
 * @brief       Board specific files for the STM32F3Discovery board
 * @{
 *
 * @file
 * @brief       Board specific definitions for the STM32F3Discovery evaluation board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Author: Norbert Danisik
 *
 * Following block of code was added as an part of bachelor thesis.
 */
/**
 * @name AT86RF233 configuration
 *
 * {spi bus, spi speed, cs pin, int pin, reset pin, sleep pin}
 */
#define AT86RF2XX_PARAMS_BOARD      {.spi = SPI_0, \
                                     .spi_speed = SPI_SPEED_5MHZ, \
                                     .cs_pin = GPIO_PIN(PORT_A, 4), \
                                     .int_pin = GPIO_PIN(PORT_B, 0), \
                                     .sleep_pin = GPIO_PIN(PORT_A, 1), \
                                     .reset_pin = GPIO_PIN(PORT_A, 2)}


/**
 * @name Macros for controlling the on-board LEDs.
 * @{
 */
#define LED0_PIN            GPIO_PIN(PORT_E, 9)
#define LED1_PIN            GPIO_PIN(PORT_E, 8)
#define LED2_PIN            GPIO_PIN(PORT_E, 10)
#define LED3_PIN            GPIO_PIN(PORT_E, 15)
#define LED4_PIN            GPIO_PIN(PORT_E, 11)
#define LED5_PIN            GPIO_PIN(PORT_E, 14)
#define LED6_PIN            GPIO_PIN(PORT_E, 12)
#define LED7_PIN            GPIO_PIN(PORT_E, 13)

#define LED_PORT            GPIOE
#define LED0_MASK           (1 << 9)
#define LED1_MASK           (1 << 8)
#define LED2_MASK           (1 << 10)
#define LED3_MASK           (1 << 15)
#define LED4_MASK           (1 << 11)
#define LED5_MASK           (1 << 14)
#define LED6_MASK           (1 << 12)
#define LED7_MASK           (1 << 13)

#define LED0_ON             (LED_PORT->BSRRL = LED0_MASK)
#define LED0_OFF            (LED_PORT->BSRRH = LED0_MASK)
#define LED0_TOGGLE         (LED_PORT->ODR  ^= LED0_MASK)

#define LED1_ON             (LED_PORT->BSRRL = LED1_MASK)
#define LED1_OFF            (LED_PORT->BSRRH = LED1_MASK)
#define LED1_TOGGLE         (LED_PORT->ODR  ^= LED1_MASK)

#define LED2_ON             (LED_PORT->BSRRL = LED2_MASK)
#define LED2_OFF            (LED_PORT->BSRRH = LED2_MASK)
#define LED2_TOGGLE         (LED_PORT->ODR  ^= LED2_MASK)

#define LED3_ON             (LED_PORT->BSRRL = LED3_MASK)
#define LED3_OFF            (LED_PORT->BSRRH = LED3_MASK)
#define LED3_TOGGLE         (LED_PORT->ODR  ^= LED3_MASK)

#define LED4_ON             (LED_PORT->BSRRL = LED4_MASK)
#define LED4_OFF            (LED_PORT->BSRRH = LED4_MASK)
#define LED4_TOGGLE         (LED_PORT->ODR  ^= LED4_MASK)

#define LED5_ON             (LED_PORT->BSRRL = LED5_MASK)
#define LED5_OFF            (LED_PORT->BSRRH = LED5_MASK)
#define LED5_TOGGLE         (LED_PORT->ODR  ^= LED5_MASK)

#define LED6_ON             (LED_PORT->BSRRL = LED6_MASK)
#define LED6_OFF            (LED_PORT->BSRRH = LED6_MASK)
#define LED6_TOGGLE         (LED_PORT->ODR  ^= LED6_MASK)

#define LED7_ON             (LED_PORT->BSRRL = LED7_MASK)
#define LED7_OFF            (LED_PORT->BSRRH = LED7_MASK)
#define LED7_TOGGLE         (LED_PORT->ODR  ^= LED7_MASK)
/** @} */

/**
 * @brief User button
 */
#define BTN_B1_PIN          GPIO_PIN(PORT_A, 0)

/**
 * @brief Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
/** @} */
