/*
 * adc.c
 *
 *  Created on: 2022年11月26日
 *      Author: koubayaxi
 */
#include "adc.h"
#include "zf_common_headfile.h"
#include "config.h"

uint16 battery_phase=0;

void adc_collection_init(void)
{
   // adc_init(BOARD_POTENTIOMET_PORT, ADC_12BIT);   //板载电位器
    adc_init(ADC0_CH0_A0, ADC_12BIT); //电压检测
}
/*
在中断内主要是获取母线电流、相电流、板载电位器电压。母线电流在之后做电流环的时候需要使用到，也可以用于做故障检测，
当检测到电流过大的时候，及时关闭输出以保护硬件，相电流可以用于之后做FOC驱动方案的时候提供支持。
*/
void adc_read(void)
{
    battery_phase=adc_convert (ADC0_CH0_A0);
    battery_voltage=(float) battery_phase / 4096 * 3.3 *  5 ;
}

