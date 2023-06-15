/*
 * motor.h
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */

#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "zf_common_headfile.h"

#define MOTOR_SPEED_OUT_PIN ATOM2_CH1_P33_5 //电机速度输出引脚
#define MOTOR_DIR_OUT_PIN   P33_11          //电机运行方向输出引脚
#define MOTOR_SWITCH        P11_6           //电机使能开关
typedef struct
{
       uint8 brake_flag;   //指示当前刹车是否有效    1：正在刹车  0：正常运行
       uint8 dir;//方向选择：0:向前;1:向后;
       int32 speed_set;
       int32 speed_max;
       int32 speed_min;
}motor_struct;

extern motor_struct motor_control;

void motor_init(void);//电机初始化
void motor_set_dir(void);//获取方向控制引脚电平并切换对应方向
void motor_commutation(uint8 hall_value,uint16 duty_finish);//换相实际操作
void motor_close(void);



#endif /* _MOTOR_H_ */
