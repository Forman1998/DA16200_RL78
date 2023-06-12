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
}sensor_callback_status_t;


static volatile sensor_callback_status_t hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static volatile sensor_callback_status_t hs300x_oneshot_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static rm_hs300x_data_t hs300x_data;

static volatile sensor_read_state_t sensor_read_state = SENSOR_WAITING;

/** @brief function to handle/log errors in sensor code*/
static void Demo_err(void);
uint16_t get_humidity(void);
uint16_t get_temp(void);
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

bool Sensor_read(/*sensor_data_t * const sense_data_arg*/)
{
	static rm_hs300x_raw_data_t hs300x_raw_data;

	fsp_err_t err = FSP_SUCCESS;
	bool readings_completed = false;

	switch(sensor_read_state)
	{

	case SENSOR_START_MEASURMENT:
	{
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
		while(SENSOR_CALLBACK_STATUS_WAIT == hs300x_i2c_callback_status)
		{
			HALT();
		}

		//Hw_start_oneshot(); /* Wait for oneshot to elapse before reading HS300X*/
		R_Config_TAU0_5_Start();
		sensor_read_state = SENSOR_WAIT_TO_READ;
	}
	break;

	case SENSOR_WAIT_TO_READ:
	{
		/* Only read and process data if the sensors are ready*/
		if( (SENSOR_CALLBACK_STATUS_SUCCESS == hs300x_oneshot_callback_status))
		{
			hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

			/* Read data */
			err = g_hs300x_sensor0.p_api->read(g_hs300x_sensor0.p_ctrl, &hs300x_raw_data);
			if (FSP_SUCCESS != err)
			{
				Demo_err();
			}

			/* Wait for IIC to finish*/
			while(SENSOR_CALLBACK_STATUS_WAIT == hs300x_i2c_callback_status)
			{
				HALT();
			}

			/* Calculate data */
			err = g_hs300x_sensor0.p_api->dataCalculate(g_hs300x_sensor0.p_ctrl, &hs300x_raw_data, &hs300x_data);
			if (FSP_SUCCESS == err)
			{

				//sense_data_arg->temperature_int = hs300x_data.temperature.integer_part;
				//sense_data_arg->humidity_int = hs300x_data.humidity.integer_part;
			}

			hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
			hs300x_oneshot_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

			sensor_read_state = SENSOR_WAITING;
			readings_completed = true;
		}
	}
	break;

	default:
		/* Do Nothing*/
		break;
	}

	return readings_completed;
}
/* END OF FUNCTION*/
uint16_t get_temp()
{
	return hs300x_data.temperature.integer_part;
}

uint16_t get_humidity()
{
	return hs300x_data.humidity.integer_part;
}

bool Sensor_stop_safe(void)
{
	return (SENSOR_WAITING == sensor_read_state) ||
			((SENSOR_WAIT_TO_READ == sensor_read_state) &&
			 (SENSOR_CALLBACK_STATUS_SUCCESS == hs300x_oneshot_callback_status));
}
/* END OF FUNCTION*/

bool Sensor_state_machine_ready(void)
{
	return (SENSOR_START_MEASURMENT == sensor_read_state) ||
			((SENSOR_WAIT_TO_READ == sensor_read_state) &&
			 (SENSOR_CALLBACK_STATUS_SUCCESS == hs300x_oneshot_callback_status));
}
/* END OF FUNCTION*/

void Sensor_try_trigger_read(void)
{
	if(SENSOR_WAITING == sensor_read_state)
	{
		sensor_read_state = SENSOR_START_MEASURMENT;
	}
}
/* END OF FUNCTION*/

void Sensor_oneshot_callback(void)
{
	hs300x_oneshot_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
}
/* END OF FUNCTION*/
void hs300x_callback(rm_hs300x_callback_args_t * p_args)
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
	while(1)
	{
		// nothing
	}
}
