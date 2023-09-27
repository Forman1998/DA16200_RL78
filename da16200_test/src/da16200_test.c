/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
*  File Name    : Test.c
*  Description  : Main Program
*  Creation Date: 2023-09-05
*  This file was generated by Smart Configurator.
***********************************************************************************************************************/
#include "r_smc_entry.h"
#include "da16200_AT.h"
#include "http_server.h"
#include "sensor.h"
#include <string.h>

static uint8_t http_ip_port[500];
void main(void)
{
	http_receive_status http_status;
	EI();
	wifi_init();
	wifi_set();
	Sensor_read();
	while(1)
	{
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

			/* LED BLINK command received */
			case HTTP_LED_BLINK:
			CCS0 ^= 0x01U;
			break;

			/* HTTP OTHER command received */
			case HTTP_OTHERS:
			http_update(http_ip_port);
			break;

			default:
			break;
		}
	}
}
