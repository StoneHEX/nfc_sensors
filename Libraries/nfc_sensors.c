/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : nfc_sensors 
*/
/*
 * nfc_sensors.c
 *
 *  Created on: Oct 17, 2023
 *      Author: fil
 */

#include "main.h"
#include "irqs.h"
#include "nfc_sensors.h"
#include "Components/st25dvxxkc_driver/st25dvxxkc.h"
#include "Components/sht40_driver/sht40.h"
#include "Components/lis2dw12_driver/lis2dw12.h"
#include "Components/lps22df_driver/lps22df.h"
#include "Components/stts22h_driver/stts22h.h"

#include <stdio.h>
#include <string.h>

SystemTypeDef 				System;


void st25dv_power_on(void)
{
	HAL_GPIO_WritePin(ST25_POWER_GPIO_Port, ST25_POWER_Pin, GPIO_PIN_SET);
}

void st25dv_power_off(void)
{
	HAL_GPIO_WritePin(ST25_POWER_GPIO_Port, ST25_POWER_Pin, GPIO_PIN_RESET);
}

void sensors_power_on(void)
{
	HAL_GPIO_WritePin(SENSORS_POWER_GPIO_Port, SENSORS_POWER_Pin, GPIO_PIN_SET);
}

void sensors_power_off(void)
{
	HAL_GPIO_WritePin(SENSORS_POWER_GPIO_Port, SENSORS_POWER_Pin, GPIO_PIN_RESET);
}

void scan_for_i2cdev(void)
{
	System.devices_state = 0;
	if ( HAL_I2C_IsDeviceReady(&hi2c3, ST25DV_ADDR, SCAN_TRY, SCAN_I2C_TIMEOUT) == 0 )
		System.devices_state |= DEV_ST25DV64;

	if ( HAL_I2C_IsDeviceReady(&hi2c1, SHT40_ADDR, SCAN_TRY, SCAN_I2C_TIMEOUT) == 0 )
		System.devices_state |= DEV_SHT40;
	if ( HAL_I2C_IsDeviceReady(&hi2c1, STTS22_ADDR, SCAN_TRY, SCAN_I2C_TIMEOUT) == 0 )
		System.devices_state |= DEV_STTS22;
	if ( HAL_I2C_IsDeviceReady(&hi2c1, LIS2DW12_ADDR, SCAN_TRY, SCAN_I2C_TIMEOUT) == 0 )
		System.devices_state |= DEV_LIS2DW12;
	if ( HAL_I2C_IsDeviceReady(&hi2c1, LPS22DF_ADDR, SCAN_TRY, SCAN_I2C_TIMEOUT) == 0 )
		System.devices_state |= DEV_LPS22DF;
}

uint8_t lis2dw12_initialize(void)
{
	LIS2DW12_SetCTRL_2_Reg();
	LIS2DW12_GetStatusReg();
	System.lis_who_am_i = LIS2DW12_GetWhoAmI();
	if ( System.lis_who_am_i  != LIS2DW12_ID )
		return 1;
	return LIS2DW12_Init(IRQ_MODE_ON_FTH,NUM_FIFO_LOCATIONS,&System.lis_id,&System.lis_status,&System.lis_ie);
}

uint32_t lps22d_Initialize(void)
{
	System.lps22df_who_am_i = LPS22DF_GetWhoAmI();
	if ( System.lps22df_who_am_i  != LPS22DF_ID )
		return 0x80000000 ;
	return LPS22DF_Init();
}

uint32_t stts22h_Initialize(void)
{
	System.stts22h_who_am_i = STTS22H_GetWhoAmI();
	if ( System.stts22h_who_am_i  != STTS22H_ID )
		return 0x80000000 ;
	return STTS22H_Init();
}


void sht40_Initialize(void)
{
	SHT40_StartAcquisition();
}

void set_st25_password(void)
{
uint8_t	i;
	for(i=0;i<PASSWORD_SIZE;i++)
		System.st25_password[i] = 0;
	System.st25_password[8] = 0x09;

}

void nfc_sensors_init(void)
{
	disable_LIS12_irq1();
	System.axis_regs_index_insertion = System.axis_regs_index_extraction = System.tick_cntr = 0;
	st25dv_power_on();
	sensors_power_on();
	HAL_Delay(500);
	scan_for_i2cdev();
	lps22d_Initialize();
	sht40_Initialize();
	stts22h_Initialize();
	set_st25_password();
	st25dv_Initialize(&System.st25dv_whoami,&System.st25dv_status,System.st25_password);
	lis2dw12_initialize();
	enable_LIS12_irq1();
}

void sht40_get_data(void)
{
	if (( System.sht40_status & SHT40_ACQUIRE_DATA ) == SHT40_ACQUIRE_DATA )
	{
		SHT40_ReadData(System.sht40_data);
		System.sht40_status &= ~SHT40_ACQUIRE_DATA;
		SHT40_StartAcquisition();
	}
	else
		System.sht40_status |= SHT40_ACQUIRE_DATA;
}

void shtts22_get_data(void)
{
	if (( System.stts22h_status & STTS22H_ACQUIRE_DATA ) == STTS22H_ACQUIRE_DATA )
	{
		STTS22H_Read_T_Data(System.stts22h_t_data);
		System.stts22h_status &= ~STTS22H_ACQUIRE_DATA;
		STTS22H_Start_Acquisition();
	}
	else
		System.stts22h_status |= STTS22H_ACQUIRE_DATA;
}

uint8_t lis2dw12_get_data(uint8_t index)
{
uint8_t	i,k;
	__disable_irq();

	for(i=0,k=index*MAG_LEN;i<NUM_FIFO_LOCATIONS;i++,k+=MAG_LEN)
	{
		LIS2DW12_ReadAccRegs(&System.axis_regs[k]);
	}
	__enable_irq();
	return 32;
}

uint8_t	tmpstr[256];

void prepare_TPH_Data(void)
{
uint8_t	header_len = 55;
	sprintf((char *)System.tx_rfal_message,"<%d*%03d!PP:%02x,%02x,%02x",
			System.tx_rfal_message_cntr,
			header_len,
			System.lps22df_p_data[0],System.lps22df_p_data[1],System.lps22df_p_data[2]);
	sprintf((char *)tmpstr,"PT:%02x,%02x",System.lps22df_t_data[0],System.lps22df_t_data[1]);
	strcat((char *)System.tx_rfal_message,(char *)tmpstr);
	sprintf((char *)tmpstr,"T:%02x,%02x",System.stts22h_t_data[0],System.stts22h_t_data[1]);
	strcat((char *)System.tx_rfal_message,(char *)tmpstr);
	sprintf((char *)tmpstr,"H:%02x,%02x,%02x,%02x,%02x,%02x>\n\r",
			System.sht40_data[0],System.sht40_data[1],System.sht40_data[2],
			System.sht40_data[3],System.sht40_data[4],System.sht40_data[5]);
	strcat((char *)System.tx_rfal_message,(char *)tmpstr);
	System.tx_rfal_message_len = strlen((char *)System.tx_rfal_message);
}

void prepare_ACC_Data(uint8_t num_samples)
{
uint8_t	i;
uint8_t	data_len = 100;
	sprintf((char *)tmpstr,"<%d*%03d#A:",data_len,MAG_LEN*num_samples);
	data_len = strlen((char *)tmpstr) + MAG_LEN*num_samples;
	sprintf((char *)System.tx_rfal_message,"<%d*%03d#A:",System.tx_rfal_message_cntr,data_len);
	System.tx_rfal_message_len = strlen((char *)System.tx_rfal_message);
	for(i=0;i<MAG_LEN*num_samples;i++)
	{
		System.tx_rfal_message[System.tx_rfal_message_len+i] = System.axis_regs[i];
	}
	System.tx_rfal_message_len +=MAG_LEN*num_samples;
	System.tx_rfal_message[System.tx_rfal_message_len] = '$';
	System.tx_rfal_message_len++;
	System.tx_rfal_message[System.tx_rfal_message_len] = '\n';
	System.tx_rfal_message_len++;
}

#define	LOW_POWER	1
void wait_st25i2c_ready(void)
{
#ifdef LOW_POWER
	uint8_t	max_retry = 75;
	while ( HAL_I2C_IsDeviceReady(&ST25_I2C_BUS, ST25DV_ADDR, SCAN_TRY, SCAN_I2C_TIMEOUT))
	{
		max_retry--;
		if ( max_retry == 0 )
			return;
		HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON,PWR_SLEEPENTRY_WFE);
	}
#else
	while ( HAL_I2C_IsDeviceReady(&ST25_I2C_BUS, ST25DV_ADDR, SCAN_TRY, SCAN_I2C_TIMEOUT));
#endif
}

void async_st25dv_Send_Sensors_Data(void)
{
	disable_LIS12_irq1();
	wait_st25i2c_ready();
	ST25DV_ReSetMB_en_Ctrl_Dyn();
	ST25DV_SetMB_en_Ctrl_Dyn();
	ST25DV_WriteMailboxData(System.tx_rfal_message,  System.tx_rfal_message_len);
	enable_LIS12_irq1();
	System.tx_rfal_message_cntr++;
}

void nfc_sensors_loop(void)
{
	if ( (System.tick_flags & TICK_1MSEC ) == TICK_1MSEC)
	{
		if ( System.tick_cntr > NFC_SENSORS_I2C_TIMEOUT*8 )
		{
			lis2dw12_get_data(0);
			System.tick_cntr=0;
			System.system_flags |= SYSTEM_LIS_IRQ1;
		}
		System.tick_flags &= ~TICK_1MSEC;
	}
	if (( System.system_flags & SYSTEM_LIS_IRQ1) == SYSTEM_LIS_IRQ1 )
	{
		if (( System.system_flags & SYSTEM_LIS_32) == 0 )
		{
			lis2dw12_get_data(0);
			LPS22DF_Read_P_Data(System.lps22df_p_data);
			LPS22DF_Read_T_Data(System.lps22df_t_data);
			STTS22H_Read_T_Data(System.stts22h_t_data);
			SHT40_ReadData(System.sht40_data);
			prepare_TPH_Data();
			async_st25dv_Send_Sensors_Data();
			SHT40_StartAcquisition();
			System.system_flags |= SYSTEM_LIS_32;
		}
		else
		{
			lis2dw12_get_data(NUM_FIFO_LOCATIONS);
			prepare_ACC_Data(NUM_FIFO_LOCATIONS*2);
			async_st25dv_Send_Sensors_Data();
			LPS22DF_Start_Acquisition();
			System.system_flags &= ~SYSTEM_LIS_32;
		}
		System.tick_cntr=0;
		System.system_flags &= ~SYSTEM_LIS_IRQ1;
	}
	HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON,PWR_SLEEPENTRY_WFE);

}

