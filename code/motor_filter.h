/*
 * motor_filter.h
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */

#ifndef _MOTOR_FILTER_H_
#define _MOTOR_FILTER_H_

#include "zf_common_headfile.h"

#define MOVE_AVERAGE_SIZE   5  //定义缓冲区大小

typedef struct
{
    uint8 index;            //下标
    uint8 buffer_size;      //buffer大小
    int32 data_buffer[MOVE_AVERAGE_SIZE];  //缓冲区
    int32 data_sum;         //数据和
    int32 data_average;     //数据平均值
}move_filter_struct;

extern move_filter_struct speed_filter;


void move_filter_init(move_filter_struct *move_average);
void move_filter_calc(move_filter_struct *move_average, int32 new_data);



#endif /* CODE_MOTOR_FILTER_H_ */
