/*
 * Copyright (C) 2015 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       CoAP example server application (using microcoap)
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @}
 */

#include <stdio.h>
#include "msg.h"
#include "thread.h"
#include "xtimer.h"
#include "board.h"
#include "periph/gpio.h"

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];
void microcoap_server_loop(void);


/* NA LEDKY */
volatile int flag_stav_2 = 0;

void cb(void *arg)
{
	if ( flag_stav_2 == 0 )	
	{
		LED5_ON;
		LED6_ON;	
		flag_stav_2 = 1;
	}
	else 
	{ 
		LED5_OFF;
		LED6_OFF;	
		flag_stav_2 = 0;
	}
}
    





/* import "ifconfig" shell command, used for printing addresses */
extern int _netif_config(int argc, char **argv);

int main(void)
{
    puts("RIOT microcoap example application");

	


    /* microcoap_server uses conn which uses gnrc which needs a msg queue */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    puts("Waiting for address autoconfiguration...");
    xtimer_sleep(3);

    /* print network addresses */
    puts("Configured network interfaces:");
    _netif_config(0, NULL);

/* BUTTON INTERRUPT INITIALIZATION */
   	gpio_init_int(BTN_B1_PIN, GPIO_IN, GPIO_RISING, cb, (void*) 0);
	//gpio_init_int(GPIO_PIN(PORT_C, 1), GPIO_IN, GPIO_RISING, cb, (void*) 0);




    /* start coap server loop */
    microcoap_server_loop();

    /* should be never reached */
    return 0;
}
