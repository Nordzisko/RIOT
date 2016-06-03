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


#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

void microcoap_server_loop(void);

/*
 * Author: Norbert Danisik
 *
 * Following block of code was added as an part of bachelor thesis.
 */
int flag_state;
const char *btn_handler = "button";
static char btn_handler_stack [THREAD_STACKSIZE_DEFAULT];	
static void *btn_handler_function (void *arg)
{
    uint32_t last = xtimer_now();
    int i;
    flag_state = 0;
    while (1)
    {
    	i = gpio_read(BTN_B1_PIN);
   	if (i != 0) {
		if ( flag_state == 0  )
			{
				LED6_ON;
				flag_state = 1;
				xtimer_usleep_until(&last, 1000000);
			}
		else {  
			LED6_OFF;
			flag_state = 0;
			xtimer_usleep_until(&last, 1000000);
			}		
		}
	xtimer_usleep_until(&last, 100000);
    }
    return NULL;
}
/* End of code of bachelor thesis outcome */




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


	/*
	* Author: Norbert Danisik
	*
	* Following block of code was added as an part of bachelor thesis.
	*/
    thread_create(btn_handler_stack, sizeof(btn_handler_stack),
    THREAD_PRIORITY_MAIN,
    THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
    btn_handler_function, NULL, btn_handler);




    /* start coap server loop */
    microcoap_server_loop();

    /* should be never reached */
    return 0;
}
