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
#include "http_server.h"
#include "da16200_AT.h"
#include "string.h"
#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int16_t temperature_int; /**< integer portion of the temperature*/
	int16_t humidity_int; /**< integer portion of the humidity*/
}sensor_data_t;
static sensor_data_t sensor_data = {0, 0};
static char my_get_contents_updated[] =
		"<html style= \"font-family: Arial, sans-serif\">"
		"<head>"
		"<meta http-equiv=\"refresh\" content=\"10\">"
		"<style>"
		".hide {display: none;}"
		".margin{margin: 25px;}"
		".semi-donut{"
		"--percentage: 0; --fill: #ff0;width: 450px; height: 225px; position: relative; text-align: center; color: #fff; font-size: 22px; font-weight: 600; border-radius: 225px 225px 0 0; overflow: hidden; color: black; display: flex; align-items: flex-end; justify-content: center; box-sizing : border-box; "
		"&:before, &:after{content: '';width: 450px; height: 225px; border:50px solid var(--fill); border-top: none; position: absolute; transform-origin :50%%  0%% 0; border-radius: 0 0 300px 300px ; box-sizing : border-box;left: 0;top: 100%%;}"
		"&:before {border-color:rgba(0,0,0,.15);transform: rotate(180deg);}"
		"&:after{z-index: 3;animation : 1s fillGraphAnimation ease-in;transform:rotate(calc(1deg*(var(--percentage)*1.8)));}"
		"&:hover{&:after{opacity: .8; cursor: pointer;}}"
		"}"
		".semi-donut:hover +.hide{ display: block; color: var(--fill);}"
		//"@keyframes fillGraphAnimation{0%%{transform: rotate(0deg);}50%%{transform: rotate(180deg);}}"
		"</style>"
		"<title>RL78/G23 Indoor Air Quality Training - Low Power</title>"
		"</head>"
		"<body style= \"margin: 0; background-color:=#fcfcfd\">"
		//
		"<header style=\"height: 80px; color: #fcfcfd; background-color: #29289D; text-align: center;font-size: x-large;\">"
		"<h2 style=\"float: left;  max-width:1000px;  margin-left: 100px;  margin-top: 30px;  font-size: x-large;\"> RL78/G23 - DA16200 WiFi Diagnostic Demo </h2>"
		//data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD//gAfQ29tcHJlc3NlZCBieSBqcGVnLXJlY29tcHJlc3P/2wCEAA0NDQ0ODQ4QEA4UFhMWFB4bGRkbHi0gIiAiIC1EKjIqKjIqRDxJOzc7STxsVUtLVWx9aWNpfZeHh5e+tb75+f8BDQ0NDQ4NDhAQDhQWExYUHhsZGRseLSAiICIgLUQqMioqMipEPEk7NztJPGxVS0tVbH1pY2l9l4eHl761vvn5///CABEIAIMC+wMBIgACEQEDEQH/xAAVAAEBAAAAAAAAAAAAAAAAAAAAB//aAAgBAQAAAACnAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/8QAFAEBAAAAAAAAAAAAAAAAAAAAAP/aAAgBAhAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD/xAAUAQEAAAAAAAAAAAAAAAAAAAAA/9oACAEDEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP/EABQQAQAAAAAAAAAAAAAAAAAAAKD/2gAIAQEAAT8ATB//xAAUEQEAAAAAAAAAAAAAAAAAAACA/9oACAECAQE/AFh//8QAFBEBAAAAAAAAAAAAAAAAAAAAgP/aAAgBAwEBPwBYf//Z
		//"<img style = \"height: 80px; width: 800px;  float: right;  margin-top: 20px;  margin-right: 20px;\" src=\"data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD//gAfQ29tcHJlc3NlZCBieSBqcGVnLXJlY29tcHJlc3P/2wCEAA0NDQ0ODQ4QEA4UFhMWFB4bGRkbHi0gIiAiIC1EKjIqKjIqRDxJOzc7STxsVUtLVWx9aWNpfZeHh5e+tb75+f8BDQ0NDQ4NDhAQDhQWExYUHhsZGRseLSAiICIgLUQqMioqMipEPEk7NztJPGxVS0tVbH1pY2l9l4eHl761vvn5///CABEIAIMC+wMBIgACEQEDEQH/xAAVAAEBAAAAAAAAAAAAAAAAAAAAB//aAAgBAQAAAACnAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/8QAFAEBAAAAAAAAAAAAAAAAAAAAAP/aAAgBAhAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD/xAAUAQEAAAAAAAAAAAAAAAAAAAAA/9oACAEDEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP/EABQQAQAAAAAAAAAAAAAAAAAAAKD/2gAIAQEAAT8ATB//xAAUEQEAAAAAAAAAAAAAAAAAAACA/9oACAECAQE/AFh//8QAFBEBAAAAAAAAAAAAAAAAAAAAgP/aAAgBAwEBPwBYf//Z\"  />"
		"</header><br>"
		"<br>\r\n"
		"<br>\r\n"
		"<br>\r\n"

		"<table ALIGN=\"center\" width=\"1000\">\r\n"

		"<tr>"
		"<H1 ALIGN=\"center\"> "
		//"<td> Temperature </td>"
		"<td>"
		"<div class=\"semi-donut margin\" style=\"--percentage : %2d; --fill: #FF3D00 ;\">Temperature</div>"
		"<div class=\"hide\"> %2dC </div>"
		"</td>\r\n"
		"<td>"
		"<div class=\"semi-donut margin\" style=\"--percentage : %2d; --fill: #039BE5 ;\">Humidity</div>"
		"<div class=\"hide\"> %2d&#37</div>"
		"</td>\r\n"		"</H1>\r\n"
		"</tr>"

		//"<tr>"
		//"<h1 ALIGN=\"center\"> "
		//"<td style=\"height: 80px; width: 25px; text-align: center; font-size: large; border:none;\"> Temperature </td>"
		//"<td style=\"height: 80px; width: 30px; text-align: center; font-size: large; border:none;\"> Humidity </td>"
		//"<td style=\"height: 80px; text-align: center; font-size: large; border:none;\"><b> Humidity </b></td>"
		//"<td><meter style=\"height: 60px; width: 800px; text-align: center;\" value=\"%2d\" min=\"0\" max=\"100\" style=\"text-align:center\">\r\n"
		//"<td><input style=\"height: 80px; width: 30px; text-align: center; font-size: large; border:none;\" type=text value=\"%2d\" readonly=\"readonly\" style=\"text-align:center\"></td>\r\n"
		//"<td> &#37 </td>"
		//"</h1>\r\n"
		//"</tr>"

		"</table>\r\n"

		"<br>\r\n"

		"<H1 ALIGN=\"center\">"
		"  Powered By Renesas RL78 MCU Series "
		"</H1>\r\n"

		"<br><br>\r\n"
		"</font>"
		"</body>"
		"</html>";


static uint8_t http_buffer[2048];
static uint8_t temp_buffer[2048];
static uint8_t user_buffer[2048];
static uint8_t resp_buff[2048] = {0};

static void http_ippt_get(uint8_t * buffer, uint8_t *ippt);

/************************************************************************************
 * Name:       http_server_receive
 * Function:   receive data and process receive message
 * Parameters: http_ippt
 * Return:     http receive status
 ************************************************************************************/
http_receive_status http_server_receive( uint8_t * http_ippt)
{
	http_receive_status retval = HTTP_ERROR;
	uint16_t bytes_read = 2048U;
	memset(resp_buff, 0, 2048);
	wifi_serial_read(resp_buff, &bytes_read, 300);

	if(is_str_present((const char*)resp_buff, "/index.html") || is_str_present((const char*)resp_buff, "/"))
	{


		if(is_str_present((const char*)resp_buff, "GET")
				&& !is_str_present((const char*)resp_buff,"blink=ON")
				&& !is_str_present((const char*)resp_buff,"blink=OFF")
				&& !is_str_present((const char*)resp_buff,"blink=BLINK"))
		{
			http_ippt_get(resp_buff,http_ippt);
			return HTTP_GET;
		}
		else
		{
			if(is_str_present((const char*)resp_buff,"blink=ON"))
			{
				http_ippt_get(resp_buff,http_ippt);
				if(http_ippt[0] !='1')
				{
					return HTTP_ERROR;
				}
				return HTTP_LED_ON;
			}
			else if(is_str_present((const char*)resp_buff,"blink=OFF"))
			{
				http_ippt_get(resp_buff,http_ippt);
				if(http_ippt[0] !='1')
				{
					return HTTP_ERROR;
				}
				return HTTP_LED_OFF;
			}
			else if(is_str_present((const char*)resp_buff,"blink=BLINK"))
			{
				http_ippt_get(resp_buff,http_ippt);
				if(http_ippt[0] !='1')
				{
					return HTTP_ERROR;
				}
				return HTTP_LED_BLINK;
			}
			else
			{

			}
		}


	}
	return retval;

}

/************************************************************************************
 * Name:       http_server_send
 * Function:   send http data
 * Parameters: http_ippt, data, length
 * Return:     none
 ************************************************************************************/
void http_server_send(uint8_t * http_ippt,uint8_t * data, uint16_t length)
{
	uint16_t length_num;
	uint16_t length_len;
	uint16_t head_len;
	uint16_t data_len;
	char lenth_str[10];
	memset(lenth_str,0, 10);
	length_num = length;

	memset(http_buffer, 0, 2048);
	length_len = length_num;

	/* <ESC>S - data transmission command in 5.6.9.1 of um-wi-003-da16200*/
	sprintf((char *)http_buffer, "\x1BS0%d,",length_len);
	strcat((char *)http_buffer, (char *)http_ippt);
	head_len = (uint16_t)strlen((char *)http_buffer);
	strcpy((char *)(http_buffer+head_len), (char *)data);
	data_len = (uint16_t)strlen((char *)http_buffer);
	wifi_serial_write(http_buffer, data_len);
}

/************************************************************************************
 * Name:       http_ippt_get
 * Function:   get ip and port data
 * Parameters: buffer, ippt
 * Return:     none
 ************************************************************************************/
static void http_ippt_get(uint8_t * buffer, uint8_t *ippt)
{
	char * p;
	uint8_t ippt_count = 0;

	p = strstr((char *)buffer, "+TRDTS:0,");
	if(0U == p)
	{
		return ;
	}
	p = p + strlen("+TRDTS:0,");
	while(*p != ',')
	{
		*ippt =(uint8_t) *p;
		ippt++;
		p++;
		ippt_count++;
		if(ippt_count >= 30)
		{
			return;
		}
	}
	*ippt =(uint8_t) *p;
	ippt++;
	p++;
	while(*p != ',')
	{
		*ippt =(uint8_t) *p;
		ippt++;
		p++;
	}
	*ippt =(uint8_t) *p;
	ippt++;
	p++;
}

/************************************************************************************
 * Name:       http_update
 * Function:   update html page
 * Parameters: http_ippt
 * Return:     none
 ************************************************************************************/
void  http_update(uint8_t * http_ippt)
{
	uint16_t len;
	Sensor_read(/*&sensor_data*/);
	sensor_data.humidity_int = get_humidity();
	sensor_data.temperature_int = get_temp();
	memset(user_buffer, 0 , 2048);
	sprintf((char *)user_buffer,(char *)my_get_contents_updated,(uint16_t)(sensor_data.temperature_int*100/65),(uint16_t)sensor_data.temperature_int,(uint16_t)sensor_data.humidity_int,(uint16_t)sensor_data.humidity_int,0U);

	len = (uint16_t)strlen((char *)user_buffer);
	sprintf((char *)temp_buffer, "HTTP/1.1 200 \r\nContent-Length: %d\r\nContent-Type: text/html\r\n\r\n", len);

	http_server_send(http_ippt,temp_buffer, (uint16_t)strlen((char *)temp_buffer));
	http_server_send(http_ippt,user_buffer, len);
}
