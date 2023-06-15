/*
 * motor_filter.h
 *
 *  Created on: 2023��1��1��
 *      Author: koubayaxi
 */

#ifndef _MOTOR_FILTER_H_
#define _MOTOR_FILTER_H_

#include "zf_common_headfile.h"

#define MOVE_AVERAGE_SIZE   5  //���建������С

typedef struct
{
    uint8 index;            //�±�
    uint8 buffer_size;      //buffer��С
    int32 data_buffer[MOVE_AVERAGE_SIZE];  //������
    int32 data_sum;         //���ݺ�
    int32 data_average;     //����ƽ��ֵ
}move_filter_struct;

extern move_filter_struct speed_filter;


void move_filter_init(move_filter_struct *move_average);
void move_filter_calc(move_filter_struct *move_average, int32 new_data);



#endif /* CODE_MOTOR_FILTER_H_ */
