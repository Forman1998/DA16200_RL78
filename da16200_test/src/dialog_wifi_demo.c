/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/
#include "dialog_wifi_demo.h"
#include "da16200_AT.h"
#include "http_server.h"
#include "sensor.h"
#include <string.h>

static uint8_t http_ip_port[500];

/************************************************************************************
 * Name:       dialog_wifi_demo
 * Function:   run dialog wifi demo
 * Parameters: none
 * Return:     none
 ************************************************************************************/
void dialog_wifi_demo(void)
{
	http_receive_status http_status;

	wifi_init();
	wifi_set();
	Sensor_try_trigger_read();
	while(1)
	{
		Sensor_try_trigger_read();
		Sensor_read();
		memset(http_ip_port, 0, 500);
		http_status = HTTP_ERROR;
		/* Wi-Fi server data receive */
		http_status = http_server_receive(http_ip_port);
		switch(http_status)
		{
		/* HTTP GET command received */
		case HTTP_GET:
			http_update(http_ip_port);
			break;
			/* HTTP LED ON command received */
		case HTTP_LED_ON:
			http_update(http_ip_port);
			break;
			/* HTTP LED OFF command received */
		case HTTP_LED_OFF:
			http_update(http_ip_port);
			break;
			/* HTTP LED BLINK command received */
		case HTTP_LED_BLINK:
			http_update(http_ip_port);
			break;
			/* HTTP OHTER command received */
		case HTTP_OTHERS:
			http_update(http_ip_port);
			break;

		default:

			break;
		}


	}
}

