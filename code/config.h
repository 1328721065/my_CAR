/*
 * config.h
 *
 *  Created on: 2023��1��1��
 *      Author: koubayaxi
 */

#ifndef CODE_CONFIG_H_
#define CODE_CONFIG_H_

#include "zf_common_headfile.h"

//0��������ɲ������     1������
#define BLDC_BRAKE_ENABLE       1

#define motor_go   1
#define motor_stop  0

#define PWM_PIT_NUM      60*FPWM

#define commutation_time 10000//���λ���ʱ����ֵ

#define DELAY_MAX   20  //��ʱ�������ʱ��

#define POLEPAIRS  2//���������



#define FCY             ((uint32)200000000)     //ϵͳʱ��
#define FPWM            ((uint16)20000)         //PWMƵ��
#define PWM_PRIOD_LOAD  (uint16)(FCY/FPWM/2)    //PWM����װ��ֵ
#define DEADTIME_LOAD   (50)                    //����װ��ֵ



extern uint8 user_control;


#define PID_swtich  1  //�ջ����ƿ��ء�0���رգ�1������

extern float  battery_voltage;
extern uint8 i;
extern uint16 duty_fin;
extern uint32 MAX_SPEED;
extern uint16 duty;//PWM�趨ֵ
extern float PID_err_now,PID_KP,PID_KI,Iout;
extern uint16 duty_copy;

#endif /* CODE_CONFIG_H_ */
