/*
 * HALL.h
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */



#ifndef _HALL_H_
#define _HALL_H_

#include "zf_common_headfile.h"


//霍尔引脚定义
#define HALL_A  P10_1
#define HALL_B  P10_2
#define HALL_C  P10_3

void HALL_init(void);//霍尔初始化
inline void speed_calc(void);//转速计算
void read_hall(void);//霍尔读取
void scan_hall(void);//霍尔扫描

typedef enum
{
    motor_fwd=1,
    motor_rev=-1,
}motor_dir;


extern int8 hall_now;//当前霍尔值
extern int8 hall_last;//上一次霍尔值
extern int8 hall_next;//下一次霍尔值
extern int8 hall_index;//霍尔表下标
extern unsigned long time_sum;//换想总时间
extern int time_once;//本次换相时间
extern unsigned long time_delay;//延时换相时间
extern uint8 motor_state;

void HALL_init(void);//霍尔初始化
void read_hall(void);//霍尔读取
void scan_hall(void);//霍尔扫描



#endif /* CODE_HALL_H_ */
