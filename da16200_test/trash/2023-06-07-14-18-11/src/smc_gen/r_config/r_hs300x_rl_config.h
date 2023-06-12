/* Generated configuration header file - do not edit */
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
/***********************************************************************************************************************
* File Name    : r_hs300x_rl_config.h
* Device(s)    : RL78
* Description  : The file r_hs300x_rl_config.h is used to configure your HS300X. r_hs300x_rl_config.h should be included
*                somewhere in your package so that the r_bsp code has access to it. This file (r_bsp_config_reference.h)
*                is just a reference file that the user can use to make their own r_hs300x_rl_config.h file.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 30.09.2020 1.00    First Release
***********************************************************************************************************************/
/* Guards against multiple inclusion */
#ifndef R_HS300X_CONFIG_H
#define R_HS300X_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_HS300X_CFG_PARAM_CHECKING_ENABLE             (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF DEVICES */
#define RM_HS300X_CFG_DEVICE_NUM_MAX                    (1) /* Number (max.) of HS300x Sensors */

/* SPECIFY DATA TYPE */
#define RM_HS300X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE    (1) /* Getting data type of HS300x Sensors */

/* SPECIFY PROGRAMMING MODE ON/OFF */
#define RM_HS300X_CFG_PROGRAMMING_MODE                  (0) /* Enable to enter the programming mode for HS300x Sensor */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE0 */
#define RM_HS300X_CFG_DEVICE0_COMMS_INSTANCE            (g_comms_i2c_device0)

/* SPECIFY CALLBACK ENABLE FOR DEVICE 0 */
#define RM_HS300X_CFG_DEVICE0_CALLBACK_ENABLE           (1) /* Enable user callback for HS300x Sensor Device0 */

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 0 */
#define RM_HS300X_CFG_DEVICE0_CALLBACK                  (hs300x_callback) /* Enable user callback for HS300x Sensor Device0 */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE1 */
#define RM_HS300X_CFG_DEVICE1_COMMS_INSTANCE            (g_comms_i2c_device1)

/* SPECIFY CALLBACK ENABLE FOR DEVICE 1 */
#define RM_HS300X_CFG_DEVICE1_CALLBACK_ENABLE           (0) /* Enable user callback for HS300x Sensor Device0 */

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 1 */
#define RM_HS300X_CFG_DEVICE1_CALLBACK                  (hs300x_user_callback1) /* Enable user callback for HS300x Sensor Device0 */

#endif  /* R_HS300X_CONFIG_H */
