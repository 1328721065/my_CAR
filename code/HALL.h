/*
 * HALL.h
 *
 *  Created on: 2023��1��1��
 *      Author: koubayaxi
 */



#ifndef _HALL_H_
#define _HALL_H_

#include "zf_common_headfile.h"


//�������Ŷ���
#define HALL_A  P10_1
#define HALL_B  P10_2
#define HALL_C  P10_3

void HALL_init(void);//������ʼ��
inline void speed_calc(void);//ת�ټ���
void read_hall(void);//������ȡ
void scan_hall(void);//����ɨ��

typedef enum
{
    motor_fwd=1,
    motor_rev=-1,
}motor_dir;


extern int8 hall_now;//��ǰ����ֵ
extern int8 hall_last;//��һ�λ���ֵ
extern int8 hall_next;//��һ�λ���ֵ
extern int8 hall_index;//�������±�
extern unsigned long time_sum;//������ʱ��
extern int time_once;//���λ���ʱ��
extern unsigned long time_delay;//��ʱ����ʱ��
extern uint8 motor_state;

void HALL_init(void);//������ʼ��
void read_hall(void);//������ȡ
void scan_hall(void);//����ɨ��



#endif /* CODE_HALL_H_ */
