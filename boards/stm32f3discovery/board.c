/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_stm32f3discovery
 * @{
 *
 * @file
 * @brief       Board specific implementations for the STM32F3Discovery evaluation board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include "board.h"
#include "periph/gpio.h"


void board_init(void)
{
    /* initialize the boards LEDs */
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init(LED1_PIN, GPIO_OUT);
    gpio_init(LED2_PIN, GPIO_OUT);
    gpio_init(LED3_PIN, GPIO_OUT);
    gpio_init(LED4_PIN, GPIO_OUT);
    gpio_init(LED5_PIN, GPIO_OUT);
    gpio_init(LED6_PIN, GPIO_OUT);
    gpio_init(LED7_PIN, GPIO_OUT);
	/*
	* Author: Norbert Danisik
	*
	* Following block of code was added as an part of bachelor thesis.
	*/
    gpio_init(BTN_B1_PIN, GPIO_IN);
    gpio_irq_enable(BTN_B1_PIN);

    /* initialize the CPU */
    cpu_init();
}
