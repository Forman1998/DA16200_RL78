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
* Copyright (C) 2021, 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_uarta_common.c
* Version          : 1.0.12
* Device(s)        : R7F100GFNxFP
* Description      : None
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_UARTA0.h"
#include "r_cg_uarta_common.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_UARTA_Create
* Description  : This function enables UARTA0/UARTA1 input clock supply and initializes UARTA0/UARTA1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTA_Create(void)
{
    UTAEN = 1U;    /* supply UARTA0/UARTA1 clock */
    /* Set UARTA0/UARTA1 settings */
    R_Config_UARTA0_Create();
}

/***********************************************************************************************************************
* Function Name: R_UARTA_Set_PowerOn
* Description  : This function starts the clock supply for UARTA0/UARTA1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTA_Set_PowerOn(void)
{
    UTAEN = 1U;    /* supply UARTA0,UARTA1 clock */
}

/***********************************************************************************************************************
* Function Name: R_UARTA_Set_PowerOff
* Description  : This function stops the clock supply for UARTA0/UARTA1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTA_Set_PowerOff(void)
{
    UTAEN = 0U;    /* stop UARTA0,UARTA1 clock */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
