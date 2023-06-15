/*
 * config.h
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */

#ifndef CODE_CONFIG_H_
#define CODE_CONFIG_H_

#include "zf_common_headfile.h"

//0：不开启刹车功能     1：开启
#define BLDC_BRAKE_ENABLE       1

#define motor_go   1
#define motor_stop  0

#define PWM_PIT_NUM      60*FPWM

#define commutation_time 10000//本次换向时间阈值

#define DELAY_MAX   20  //延时换相最大时长

#define POLEPAIRS  2//电机极对数



#define FCY             ((uint32)200000000)     //系统时钟
#define FPWM            ((uint16)20000)         //PWM频率
#define PWM_PRIOD_LOAD  (uint16)(FCY/FPWM/2)    //PWM周期装载值
#define DEADTIME_LOAD   (50)                    //死区装载值



extern uint8 user_control;


#define PID_swtich  1  //闭环控制开关。0：关闭，1：开启

extern float  battery_voltage;
extern uint8 i;
extern uint16 duty_fin;
extern uint32 MAX_SPEED;
extern uint16 duty;//PWM设定值
extern float PID_err_now,PID_KP,PID_KI,Iout;
extern uint16 duty_copy;

#endif /* CODE_CONFIG_H_ */
