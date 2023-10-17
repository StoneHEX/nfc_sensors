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
 * Project : Rollon_Sensors_L431 
*/
/*
 * irqs.c
 *
 *  Created on: Sep 22, 2023
 *      Author: fil
 */

#include "main.h"
#include "nfc_sensors.h"

void disable_external_irqs(void)
{
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}
void enable_external_irqs(void)
{
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void enable_LIS12_irq1(void)
{
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void disable_LIS12_irq1(void)
{
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if ( GPIO_Pin == LIS12_IRQ1_Pin)
		System.system_flags |= SYSTEM_LIS_IRQ1;
	if ( GPIO_Pin == LPS22DF_IRQ_Pin)
		System.system_flags |= SYSTEM_LPS22DF_IRQ;
	if ( GPIO_Pin == STTS22_IRQ_Pin)
		System.system_flags |= SYSTEM_STTS22_IRQ;
	if ( GPIO_Pin == GPO_Pin)
		System.system_flags |= SYSTEM_ST25DV_IRQ;
}

void HAL_IncTick(void)
{
	uwTick += (uint32_t)uwTickFreq;
	System.tick_flags |= TICK_1MSEC;
	if ( HAL_GPIO_ReadPin(LIS12_IRQ1_GPIO_Port, LIS12_IRQ1_Pin) )
		System.tick_cntr++;

}
