/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
 #include "r_comms_i2c_if.h"
 #include "r_hs300x_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/
#if (1 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
void rm_hs300x_callback0(rm_comms_callback_args_t * p_args);
 #if (1 == RM_HS300X_CFG_DEVICE0_CALLBACK_ENABLE)
 void RM_HS300X_CFG_DEVICE0_CALLBACK(rm_hs300x_callback_args_t * p_args);
 #endif
#endif
#if (2 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
void rm_hs300x_callback1(rm_comms_callback_args_t * p_args);
 #if (1 == RM_HS300X_CFG_DEVICE1_CALLBACK_ENABLE)
 void RM_HS300X_CFG_DEVICE1_CALLBACK(rm_hs300x_callback_args_t * p_args);
 #endif
#endif

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
extern void rm_hs300x_callback (rm_comms_callback_args_t * p_args);
#if (1 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
rm_hs300x_instance_ctrl_t g_hs300x_sensor0_ctrl;
const rm_hs300x_cfg_t g_hs300x_sensor0_cfg =
{
    .p_instance = &(RM_HS300X_CFG_DEVICE0_COMMS_INSTANCE),
#if (1 == RM_HS300X_CFG_DEVICE0_CALLBACK_ENABLE)
    .p_callback = (void (*)(rm_hs300x_callback_args_t *))RM_HS300X_CFG_DEVICE0_CALLBACK,
#else
    .p_callback = NULL,
#endif
    .p_context  = NULL,
};
const rm_hs300x_instance_t g_hs300x_sensor0 =
{
    .p_ctrl = &g_hs300x_sensor0_ctrl,
    .p_cfg  = &g_hs300x_sensor0_cfg,
    .p_api  = &g_hs300x_on_hs300x,
};
void rm_hs300x_callback0(rm_comms_callback_args_t * p_args)
{
    p_args->p_context = (void *)&g_hs300x_sensor0_ctrl;
    rm_hs300x_callback(p_args);
}
#endif
#if (2 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
const rm_hs300x_cfg_t g_hs300x_sensor1_cfg =
{
	.p_instance = &(RM_HS300X_CFG_DEVICE1_COMMS_INSTANCE),
#if (1 == RM_HS300X_CFG_DEVICE1_CALLBACK_ENABLE)
    .p_callback = (void (*)(rm_hs300x_callback_args_t *))RM_HS300X_CFG_DEVICE1_CALLBACK,
#else
    .p_callback = NULL,
#endif
    .p_context  = NULL,
};
rm_hs300x_instance_ctrl_t g_hs300x_sensor1_ctrl;
const rm_hs300x_instance_t g_hs300x_sensor1 =
{
    .p_ctrl = &g_hs300x_sensor1_ctrl,
    .p_cfg  = &g_hs300x_sensor1_cfg,
    .p_api  = &g_hs300x_on_hs300x,
};
void rm_hs300x_callback1(rm_comms_callback_args_t * p_args)
{
    p_args->p_context = (void *)&g_hs300x_sensor1_ctrl;
    rm_hs300x_callback(p_args);
}
#endif
