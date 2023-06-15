/*
 * adc.c
 *
 *  Created on: 2022��11��26��
 *      Author: koubayaxi
 */
#include "adc.h"
#include "zf_common_headfile.h"
#include "config.h"

uint16 battery_phase=0;

void adc_collection_init(void)
{
   // adc_init(BOARD_POTENTIOMET_PORT, ADC_12BIT);   //���ص�λ��
    adc_init(ADC0_CH0_A0, ADC_12BIT); //��ѹ���
}
/*
���ж�����Ҫ�ǻ�ȡĸ�ߵ���������������ص�λ����ѹ��ĸ�ߵ�����֮������������ʱ����Ҫʹ�õ���Ҳ�������������ϼ�⣬
����⵽���������ʱ�򣬼�ʱ�ر�����Ա���Ӳ�����������������֮����FOC����������ʱ���ṩ֧�֡�
*/
void adc_read(void)
{
    battery_phase=adc_convert (ADC0_CH0_A0);
    battery_voltage=(float) battery_phase / 4096 * 3.3 *  5 ;
}

