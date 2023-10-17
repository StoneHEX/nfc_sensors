/*
 * lis2dw12.c
 *
 *  Created on: Jul 31, 2023
 *      Author: fil
 */

#include "main.h"
#include "lis2dw12.h"
//#include "sensors_bus.h"
#include "nfc_sensors.h"

#include <string.h>

static uint8_t	read_lis_reg(uint8_t address)
{
uint8_t	rreg;
	HAL_I2C_Mem_Read(&SENSORS_I2C_BUS, LIS2DW12_ADDR, (uint16_t )address, I2C_MEMADD_SIZE_8BIT,	&rreg, 1, 1000);
	return rreg;
}

static uint8_t	write_lis_reg(uint8_t address,uint8_t data)
{
	return HAL_I2C_Mem_Write(&SENSORS_I2C_BUS, LIS2DW12_ADDR, (uint16_t )address, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
}

uint8_t LIS2DW12_GetWhoAmI(void)
{
	read_lis_reg(LIS2DW12_WHO_AM_I);
	return read_lis_reg(LIS2DW12_WHO_AM_I);
}

uint8_t LIS2DW12_ReadAccRegs(uint8_t *axis_ptr)

{
	return HAL_I2C_Mem_Read(&SENSORS_I2C_BUS, LIS2DW12_ADDR, (uint16_t )LIS2DW12_OUT_X_L, I2C_MEMADD_SIZE_8BIT, axis_ptr, 6, 1000);
}

uint8_t LIS2DW12_GetStatusReg(void)
{
	return read_lis_reg(LIS2DW12_STATUS);
}

uint8_t LIS2DW12_SetCTRL_2_Reg(void)
{
	write_lis_reg(LIS2DW12_CTRL2,0x40);
	HAL_Delay(1);
	write_lis_reg(LIS2DW12_CTRL2,0x80);
	HAL_Delay(1);
	return write_lis_reg(LIS2DW12_CTRL2,0x14);
}

uint8_t LIS2DW12_GetWakeSource(void)
{
	return read_lis_reg(LIS2DW12_WAKE_UP_SRC);
}

uint8_t LIS2DW12_GetFifoSamples(void)
{
	return read_lis_reg(LIS2DW12_FIFO_SAMPLES) & 0x3f;
}

uint8_t LIS2DW12_GetFifoSamplesReg(void)
{
	return read_lis_reg(LIS2DW12_FIFO_SAMPLES);
}

void LIS2DW12_ConfigureFIFO(uint8_t FIFOMode, uint8_t FIFOThreshold)
{
	write_lis_reg(LIS2DW12_FIFO_CTRL, FIFOMode << 5 | (FIFOThreshold-1) );
}

uint8_t LIS2DW12_Reset(void)
{
uint8_t temp;
	temp = read_lis_reg(LIS2DW12_CTRL2);
	write_lis_reg(LIS2DW12_CTRL2, temp | 0x40); // software reset the LIS2DW12
	return read_lis_reg(LIS2DW12_STATUS);
}

//https://github.com/kriswiner/LIS2DW12/blob/main/LIS2DW12_Tap_OrientationDetect_Ladybug/LIS2DW12.cpp#L36

uint8_t LIS2DW12_GetTempReg(void)
{
	return read_lis_reg(LIS2DW12_OUT_T);
}

uint8_t LIS2DW12_Init(uint8_t irq_mode,uint8_t fifo_locations,uint8_t *id,uint8_t *status,uint8_t *ie)
{
	write_lis_reg( LIS2DW12_CTRL1 , LIS2DW12_LP_MODE_1 | LIS2DW12_MODE_HIGH_PERF | LIS2DW12_ODR_100Hz );
	write_lis_reg( LIS2DW12_CTRL6, LIS2DW12_BW_FILT_ODR20 | LIS2DW12_FS_16G);
	write_lis_reg( LIS2DW12_CTRL2 , LIS2DW12_BOOT | LIS2DW12_BDU | LIS2DW12_IF_ADD_INC);
	write_lis_reg( LIS2DW12_CTRL3 , 0x0);	// pulsed irq
	if ( irq_mode == IRQ_MODE_ON_WAKEUP )
		write_lis_reg( LIS2DW12_CTRL4_INT1_PAD_CTRL , LIS2DW12_INT1_WU);
	else
		write_lis_reg( LIS2DW12_CTRL4_INT1_PAD_CTRL , LIS2DW12_INT1_FTH);

	write_lis_reg( LIS2DW12_CTRL5_INT2_PAD_CTRL , 0);
	write_lis_reg( LIS2DW12_WAKE_UP_THS ,  LIS2DW12_SINGLE_DOUBLE_TAP | 16);
	write_lis_reg( LIS2DW12_WAKE_UP_DUR ,  0x10);
	write_lis_reg( LIS2DW12_CTRL_REG7, LIS2DW12_DRDY_PULSED | LIS2DW12_INTERRUPTS_ENABLE | LIS2DW12_INT2_ON_INT1);

	LIS2DW12_ConfigureFIFO(LISDW_FIFOMODE_BYPASS, fifo_locations);		// clear fifo
	LIS2DW12_ConfigureFIFO(LISDW_FIFOMODE_CONTINUOUS, fifo_locations);// restart fifo

	*ie = read_lis_reg(LIS2DW12_CTRL4_INT1_PAD_CTRL);
	*status = LIS2DW12_GetStatusReg();
	return 0;
}




