/*
 * Copyright (C) 2015 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <coap.h>
#include <string.h>
#include "main.c"
#include "board.h"
#include "periph/gpio.h"


#define MAX_RESPONSE_LEN 500
static uint8_t response[MAX_RESPONSE_LEN] = { 0 };

static int handle_get_well_known_core(coap_rw_buffer_t *scratch,
                                      const coap_packet_t *inpkt,
                                      coap_packet_t *outpkt,
                                      uint8_t id_hi, uint8_t id_lo);

static int handle_get_riot_board(coap_rw_buffer_t *scratch,
                                 const coap_packet_t *inpkt,
                                 coap_packet_t *outpkt,
                                 uint8_t id_hi, uint8_t id_lo);

static int handle_get_riot_stav(coap_rw_buffer_t *scratch,
                                 const coap_packet_t *inpkt,
                                 coap_packet_t *outpkt,
                                 uint8_t id_hi, uint8_t id_lo);

static int handle_get_riot_stav2(coap_rw_buffer_t *scratch,
                                 const coap_packet_t *inpkt,
                                 coap_packet_t *outpkt,
                                 uint8_t id_hi, uint8_t id_lo);

static const coap_endpoint_path_t path_well_known_core =
        { 2, { ".well-known", "core" } };

static const coap_endpoint_path_t path_riot_board =
        { 2, { "riot", "board" } };



static const coap_endpoint_path_t path_riot_stav =
        { 2, { "riot", "stav" } };

const coap_endpoint_t endpoints[] =
{
    { COAP_METHOD_GET,	handle_get_well_known_core,
        &path_well_known_core, "ct=40" },
    { COAP_METHOD_GET,	handle_get_riot_stav,
        &path_riot_stav, "ct=5" },
{ COAP_METHOD_PUT,	handle_get_riot_stav2,
        &path_riot_stav, "ct=6" },
    { COAP_METHOD_GET,	handle_get_riot_board,
        &path_riot_board,	   "ct=0"  },
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

static int handle_get_riot_stav(coap_rw_buffer_t *scratch,
        const coap_packet_t *inpkt, coap_packet_t *outpkt,
        uint8_t id_hi, uint8_t id_lo)
{
    const char *riot_name;
    if (flag_stav_2 == 1 )
	riot_name = "ano";
    else riot_name = "nie";
    
    int len = 3;

    memcpy(response, riot_name, len);

    return coap_make_response(scratch, outpkt, (const uint8_t *)response, len,
                              id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT,
                              COAP_CONTENTTYPE_TEXT_PLAIN);
}

static int handle_get_riot_stav2(coap_rw_buffer_t *scratch,
        const coap_packet_t *inpkt, coap_packet_t *outpkt,
        uint8_t id_hi, uint8_t id_lo)
{
     if (inpkt->payload.len == 0)
	{
	puts("Som neni tu");
        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok,  		 		COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN); 
	}
     if (inpkt->payload.p[0] == '1')
	{
		LED7_ON;
		//flag_stav_2 = 1;
	}
     if (inpkt->payload.p[0] == '0')
	{
		LED7_OFF;
	}		
    return coap_make_response(scratch, outpkt, (const uint8_t *)response, 1, id_hi, id_lo, &inpkt->tok,  			COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN); 
}
