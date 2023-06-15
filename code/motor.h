/*
 * motor.h
 *
 *  Created on: 2023��1��1��
 *      Author: koubayaxi
 */

#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "zf_common_headfile.h"

#define MOTOR_SPEED_OUT_PIN ATOM2_CH1_P33_5 //����ٶ��������
#define MOTOR_DIR_OUT_PIN   P33_11          //������з����������
#define MOTOR_SWITCH        P11_6           //���ʹ�ܿ���
typedef struct
{
       uint8 brake_flag;   //ָʾ��ǰɲ���Ƿ���Ч    1������ɲ��  0����������
       uint8 dir;//����ѡ��0:��ǰ;1:���;
       int32 speed_set;
       int32 speed_max;
       int32 speed_min;
}motor_struct;

extern motor_struct motor_control;

void motor_init(void);//�����ʼ��
void motor_set_dir(void);//��ȡ����������ŵ�ƽ���л���Ӧ����
void motor_commutation(uint8 hall_value,uint16 duty_finish);//����ʵ�ʲ���
void motor_close(void);



#endif /* _MOTOR_H_ */
