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
 * nfc_sensors.h
 *
 *  Created on: Oct 17, 2023
 *      Author: fil
 */

#ifndef NFC_SENSORS_H_
#define NFC_SENSORS_H_

extern	I2C_HandleTypeDef 	hi2c1;
extern	I2C_HandleTypeDef 	hi2c3;

#define	SENSORS_I2C_BUS		hi2c1
#define	ST25_I2C_BUS		hi2c3

#define	SCAN_TRY				1
#define	SCAN_I2C_TIMEOUT		500
#define	NFC_SENSORS_I2C_TIMEOUT	(SCAN_I2C_TIMEOUT)
#define	SPI_MAX_LEN				8
#define	RFAL_MSG_SIZE			255
#define	PASSWORD_SIZE			17

#define	SMARTAG1_PWD_MSB		0x00000000
#define	SMARTAG1_PWD_LSB		0x00000000
#define	SMARTAG1_WRONG_PWD_MSB	~(SMARTAG1_PWD_MSB)
#define	SMARTAG1_WRONG_PWD_LSB	~(SMARTAG1_PWD_LSB)
#define	IRQ_MODE_ON_WAKEUP		0
#define	IRQ_MODE_ON_FTH			1
#define	NUM_FIFO_LOCATIONS		16
#define	LIS_QUEUE_LEN			64
#define	MAG_LEN					6
#define	HIGRO_LEN				6
#define	PRESSURE_P_LEN			3
#define	PRESSURE_T_LEN			2
#define	TEMPERATURE_LEN			2
#define	MAG_LEN_BUFFER_LEN		(MAG_LEN * 1024)

#define	RFAL_NUM_ACCDATA	8
#define	RFAL_PKT_SIZE		(RFAL_NUM_ACCDATA*MAG_LEN)

typedef struct _SystemTypeDef
{
	uint8_t			system_flags;
	uint8_t			tick_flags;
	uint32_t		tick_cntr;
	uint8_t			devices_state;
	uint8_t			sht40_status;
	uint8_t			sht40_data[HIGRO_LEN];
	uint8_t			lis_who_am_i;
	uint8_t			lis_state;
	uint8_t			lis_id;
	uint8_t			lis_status;
	uint8_t			lis_full_scale_acc;
	uint8_t			lis_wake_source;
	uint8_t			lis_fifo_samples_reg;
	uint8_t			lis_fifo_samples_num;
	uint8_t			lis_ie;
	uint16_t		lis_counter;
	uint8_t			lps22df_who_am_i;
	uint8_t			lps22df_status;
	uint8_t			lps22df_p_data[PRESSURE_P_LEN];
	uint8_t			lps22df_t_data[PRESSURE_T_LEN];
	uint8_t			stts22h_who_am_i;
	uint8_t			stts22h_status;
	uint8_t			stts22h_t_data[TEMPERATURE_LEN];
	uint8_t			spi_txbuf[SPI_MAX_LEN];
	uint8_t			spi_rxbuf[SPI_MAX_LEN];
	uint8_t			axis_regs[MAG_LEN_BUFFER_LEN];
	uint32_t		axis_regs_index_insertion;
	uint32_t		axis_regs_index_extraction;
	uint8_t			tx_rfal_message[RFAL_MSG_SIZE];
	uint8_t			tx_rfal_message_len;
	uint8_t			tx_rfal_message_cntr;
	uint8_t			rx_rfal_message[RFAL_MSG_SIZE];
	uint8_t			rx_rfal_message_len;
	uint8_t			st25dv_whoami;
	uint8_t			st25dv_status;
	uint8_t			st25_password[PASSWORD_SIZE];
	/*
	float			lis_offset[3];
	float 			aRes;
	float 			ax,ay,az;
	*/
}SystemTypeDef;
/* system_flags */
#define	SYSTEM_LIS_SAMPLES_READY	0x80
#define	SYSTEM_LIS_IRQ1				0x40
#define	SYSTEM_LIS_32				0x20
#define	SYSTEM_LIS_SEND_DATA		0x10
#define	SYSTEM_STTS22_IRQ			0x08
#define	SYSTEM_LPS22DF_IRQ			0x04
#define	SYSTEM_ST25DV_IRQ			0x02
#define	SYSTEM_ST25DV_FIELD			0x01
/* tick_flags */
#define	TICK_1MSEC					0x01
#define	TICK_LISIRQSTATE			0x02
extern	SystemTypeDef 				System;
/* devices_state */
#define	DEV_ST25DV64				0x80	/* 0xa6 */
#define	DEV_LPS22DF					0x08	/* 0xb8 */
#define	DEV_LIS2DW12				0x04	/* 0x30 */
#define	DEV_STTS22					0x02	/* 0x7e */
#define	DEV_SHT40					0x01	/* 0x88 */
/* sht40_status */
#define	SHT40_ACQUIRE_DATA			0x01
/* lps22df_status */
#define	LPS22DF_ACQUIRE_DATA		0x01
/* stts22h_status */
#define	STTS22H_ACQUIRE_DATA		0x01
/* st25dv_status */
#define	ST25DV_FOUND				0x01
#define	ST25DV_I2CSSO				0x02
#define	ST25DV_RFSSO				0x04

#define	ST25DV_ADDR					0xa6
#define	LPS22DF_ADDR				0xb8
#define	LIS2DW12_ADDR				0x32
#define	STTS22_ADDR					0x7e
#define	SHT40_ADDR					0x88

extern	void nfc_sensors_init(void);
extern	void nfc_sensors_loop(void);


extern	void enable_LIS12_IRQ1(void);
extern	void enable_LIS12_IRQ2(void);
extern	void enable_st25dw_GPO_IRQ14(void);
extern	void disable_external_irqs(void);


#endif /* NFC_SENSORS_H_ */
