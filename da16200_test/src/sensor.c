/*
 * sensor.c
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#include "sensor.h"
#include "r_cg_macrodriver.h"
#include "r_hs300x_if.h"
#include "http_server.h"

/** callback status enumerated type*/
typedef enum
{
	SENSOR_CALLBACK_STATUS_WAIT = (0),
	SENSOR_CALLBACK_STATUS_SUCCESS,
	SENSOR_CALLBACK_STATUS_REPEAT,
} sensor_callback_status_t;

static volatile sensor_callback_status_t hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static rm_hs300x_data_t hs300x_data;

/** @brief function to handle/log errors in sensor code*/
static void Demo_err(void);

/**********************************************************************
 * Sensor API
 *********************************************************************/
void Sensor_init(void)
{
	fsp_err_t err = g_hs300x_sensor0.p_api->open(g_hs300x_sensor0.p_ctrl, g_hs300x_sensor0.p_cfg);

	if (FSP_SUCCESS != err)
	{
		Demo_err();
	}
}
/* END OF FUNCTION*/

void Sensor_read(void)
{
	static rm_hs300x_raw_data_t hs300x_raw_data;

	fsp_err_t err = FSP_SUCCESS;

	/**********************
	 * HS3001
	 *********************/
	/* Start measurement */
	err = g_hs300x_sensor0.p_api->measurementStart(g_hs300x_sensor0.p_ctrl);
	if (FSP_SUCCESS != err)
	{
		Demo_err();
	}

	/* Wait for IIC to finish*/
	while (SENSOR_CALLBACK_STATUS_WAIT == hs300x_i2c_callback_status)
	{
		HALT();
	}

	R_Config_TAU0_5_Blocking_Wait();

	hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

	/* Read data */
	err = g_hs300x_sensor0.p_api->read(g_hs300x_sensor0.p_ctrl, &hs300x_raw_data);
	if (FSP_SUCCESS != err)
	{
		Demo_err();
	}

	/* Wait for IIC to finish*/
	while (SENSOR_CALLBACK_STATUS_WAIT == hs300x_i2c_callback_status)
	{
		HALT();
	}

	/* Calculate data */
	(void)g_hs300x_sensor0.p_api->dataCalculate(g_hs300x_sensor0.p_ctrl, &hs300x_raw_data, &hs300x_data);

	hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

	sensor_read_state = SENSOR_WAITING;
}
/* END OF FUNCTION*/

uint16_t Sensor_get_temp()
{
	return hs300x_data.temperature.integer_part;
}

uint16_t Sensor_get_humidity()
{
	return hs300x_data.humidity.integer_part;
}

void hs300x_callback(rm_hs300x_callback_args_t *p_args)
{
	if (RM_HS300X_EVENT_SUCCESS == p_args->event)
	{
		hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
	}
	else
	{
		hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_REPEAT;
	}
}

/**********************************************************************
 * General
 *********************************************************************/

static void Demo_err(void)
{
	while (1)
	{
		// nothing
	}
}
