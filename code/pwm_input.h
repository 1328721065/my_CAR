/*
 * pwm_input.h
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */

#ifndef CODE_PWM_INPUT_H_
#define CODE_PWM_INPUT_H_

#include "ifxGtm_Tim.h"
#include "IFXGTM_TIM_IN.h"
#include "zf_common_headfile.h"


#define GTM_PWM_IN_PRIORITY 80          //输入捕获中断优先级

#define MOTOR_DIR_IN_PIN    P20_13//输入捕获方向引脚
#define MOTOR_PWM_IN_PIN    P20_14//输入捕获脉宽引脚

#define PWM_CONVERT   200
#define DUTY_IN_MAX   9000
#define PWM_MAX  (PWM_CONVERT*DUTY_IN_MAX)


extern uint32 pwm_in_duty;
extern IfxGtm_Tim_In driver;

void pwm_input_init(void);




#endif /* CODE_PWM_INPUT_H_ */
