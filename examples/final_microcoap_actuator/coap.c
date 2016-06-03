/*
 * Copyright (C) 2015 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
 
 

#include <coap.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.c"
#include "board.h"
#include "periph/gpio.h"
#include "xtimer.h"

#define MAX_RESPONSE_LEN 500
static uint8_t response[MAX_RESPONSE_LEN] = { 0 };

static int handle_get_well_known_core(coap_rw_buffer_t *scratch,
                                      const coap_packet_t *inpkt,
                                      coap_packet_t *outpkt,
                                      uint8_t id_hi, uint8_t id_lo);
/*
 * Author: Norbert Danisik
 *
 * Following block of code was added as an part of bachelor thesis.
 */
static int handle_get_riot_board(coap_rw_buffer_t *scratch,
                                 const coap_packet_t *inpkt,
                                 coap_packet_t *outpkt,
                                 uint8_t id_hi, uint8_t id_lo);

/*
 * Author: Norbert Danisik
 *
 * Following block of code was added as an part of bachelor thesis.
 */
static int handle_set_riot_state(coap_rw_buffer_t *scratch,
                                 const coap_packet_t *inpkt,
                                 coap_packet_t *outpkt,
                                 uint8_t id_hi, uint8_t id_lo);

static const coap_endpoint_path_t path_well_known_core =
        { 2, { ".well-known", "core" } };

static const coap_endpoint_path_t path_riot_board =
        { 2, { "riot", "board" } };
		
/*
 * Author: Norbert Danisik
 *
 * Following block of code was added as an part of bachelor thesis.
 */
static const coap_endpoint_path_t path_riot_state =
        { 2, { "riot", "state" } };

/*
 * Author: Norbert Danisik
 *
 * Following block of code was modified as an part of bachelor thesis.
 */		
const coap_endpoint_t endpoints[] =
{
    { COAP_METHOD_GET,	handle_get_well_known_core,
        &path_well_known_core, "ct=40" },
    { COAP_METHOD_PUT,	handle_set_riot_state,
        &path_riot_state, "ct=0" },
    { COAP_METHOD_GET,	handle_get_riot_board,
        &path_riot_board, "ct=0" },
    /* marks the end of the endpoints array: */
    { (coap_method_t)0, NULL, NULL, NULL }
};

static int handle_get_well_known_core(coap_rw_buffer_t *scratch,
        const coap_packet_t *inpkt, coap_packet_t *outpkt,
        uint8_t id_hi, uint8_t id_lo)
{
    char *rsp = (char *)response;
    int len = sizeof(response);
    const coap_endpoint_t *ep = endpoints;
    int i;

    len--; // Null-terminated string

    while (NULL != ep->handler) {
        if (NULL == ep->core_attr) {
            ep++;
            continue;
        }

        if (0 < strlen(rsp)) {
            strncat(rsp, ",", len);
            len--;
        }

        strncat(rsp, "<", len);
        len--;

        for (i = 0; i < ep->path->count; i++) {
            strncat(rsp, "/", len);
            len--;

            strncat(rsp, ep->path->elems[i], len);
            len -= strlen(ep->path->elems[i]);
        }

        strncat(rsp, ">;", len);
        len -= 2;

        strncat(rsp, ep->core_attr, len);
        len -= strlen(ep->core_attr);

        ep++;
    }

    return coap_make_response(scratch, outpkt, (const uint8_t *)rsp,
                              strlen(rsp), id_hi, id_lo, &inpkt->tok,
                              COAP_RSPCODE_CONTENT,
                              COAP_CONTENTTYPE_APPLICATION_LINKFORMAT);
}


static int handle_get_riot_board(coap_rw_buffer_t *scratch,
        const coap_packet_t *inpkt, coap_packet_t *outpkt,
        uint8_t id_hi, uint8_t id_lo)
{
    const char *riot_name = RIOT_BOARD;
    int len = strlen(RIOT_BOARD);

    memcpy(response, riot_name, len);

    return coap_make_response(scratch, outpkt, (const uint8_t *)response, len,
                              id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT,
                              COAP_CONTENTTYPE_TEXT_PLAIN);
}

/*
 * Author: Norbert Danisik
 *
 * Following block of code was added as an part of bachelor thesis.
 */
static int handle_set_riot_state(coap_rw_buffer_t *scratch,
        const coap_packet_t *inpkt, coap_packet_t *outpkt,
        uint8_t id_hi, uint8_t id_lo)
{
     if (inpkt->payload.len == 0)
	{
	puts("Error: Empty payload!");
        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok,  		 					COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN); 
	}
     
    char *str_on =  "light_on";
    char *str_off = "light_off";
    char *str_payload = (char*)inpkt->payload.p ;
    uint32_t last = xtimer_now();
    if ( strcmp(str_on,str_payload) == 0)
    {
	LED0_ON;xtimer_usleep_until(&last, 50000);
	LED1_ON;xtimer_usleep_until(&last, 50000);	
	LED3_ON;xtimer_usleep_until(&last, 50000);	
	LED5_ON;xtimer_usleep_until(&last, 50000);	
	LED7_ON;xtimer_usleep_until(&last, 50000);	
	LED6_ON;xtimer_usleep_until(&last, 50000);	
	LED4_ON;xtimer_usleep_until(&last, 50000);	
	LED2_ON;xtimer_usleep_until(&last, 50000);	
	LED0_OFF;xtimer_usleep_until(&last, 50000);	
	LED1_OFF;xtimer_usleep_until(&last, 50000);	
	LED3_OFF;xtimer_usleep_until(&last, 50000);	
	LED5_OFF;xtimer_usleep_until(&last, 50000);	
	LED7_OFF;xtimer_usleep_until(&last, 50000);
	LED6_OFF;xtimer_usleep_until(&last, 50000);	
	LED4_OFF;xtimer_usleep_until(&last, 50000);	
	LED2_OFF;xtimer_usleep_until(&last, 50000); 	
	LED0_ON;		
    }
    if ( strcmp(str_off,str_payload) == 0 )
	LED0_OFF;	
    if ( inpkt->payload.len > 8 )	    
	str_payload[8] = '\0';
    return coap_make_response(scratch, outpkt, (const uint8_t *)response, 1, id_hi, id_lo, &inpkt->tok,  					COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN); 
}
