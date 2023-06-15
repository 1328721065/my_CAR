/*
 * motor.c
 *
 *  Created on: 2023��1��1��
 *      Author: koubayaxi
 */


#include "config.h"
#include "zf_common_headfile.h"
#include "zf_driver_gpio.h"
#include "motor.h"
#include "motor_filter.h"
#include "pwm_input.h"
motor_struct motor_control;

void motor_init(void)
{
    if (BLDC_BRAKE_ENABLE==1)
    {
    motor_control.brake_flag = 1;
    }
    motor_control.dir=0;//0Ϊ������1Ϊ������
    motor_control.speed_set=duty_copy;
    motor_control.speed_max=MAX_SPEED;
    motor_control.speed_min=0;

    pwm_init (ATOM0_CH1_P00_1, 20000, 0);
    pwm_init (ATOM0_CH2_P00_3, 20000, 0);
    pwm_init (ATOM0_CH4_P00_5, 20000, 0);

    gpio_init(P00_2, GPO, 0, GPO_PUSH_PULL);
    gpio_init(P00_4, GPO, 0, GPO_PUSH_PULL);
    gpio_init(P00_6, GPO, 0, GPO_PUSH_PULL);
}



void motor_set_dir(void)//��ȡ����������ŵ�ƽ���л���Ӧ����
{
    if(gpio_get_level(MOTOR_DIR_IN_PIN))
    {
     motor_control.dir=0;
    }
    else
    {
        motor_control.dir = 1;
    }

}

void motor_close(void)
{
    pwm_set_duty (ATOM0_CH1_P00_1, 0);
    gpio_set_level (P00_2, 1);

    pwm_set_duty (ATOM0_CH2_P00_3, 0);
    gpio_set_level (P00_4, 1);

    pwm_set_duty (ATOM0_CH4_P00_5, 0);
    gpio_set_level (P00_6, 1);
}
//UVW
//362514

//246135
// BC AB AC CA BA CB
// 6 2 1 4 5 3
// 2 4 3 6 1 5
void motor_commutation(uint8 hall_value,uint16 duty_finish)
{
    if(duty_finish>0)
    {
    switch(hall_value)
    {
        case 1:     //����A�����ţ�C������

            pwm_set_duty (ATOM0_CH1_P00_1, duty_finish);
            gpio_set_level (P00_2, 0);

            pwm_set_duty (ATOM0_CH2_P00_3, 0);
            gpio_set_level (P00_4, 0);

            pwm_set_duty (ATOM0_CH4_P00_5, 0);
            gpio_set_level (P00_6, 1);

            break;
        case 2:   //����A�����ţ�B������

            pwm_set_duty (ATOM0_CH1_P00_1, duty_finish);
            gpio_set_level (P00_2, 0);

            pwm_set_duty (ATOM0_CH2_P00_3, 0);
            gpio_set_level (P00_4, 1);

            pwm_set_duty (ATOM0_CH4_P00_5, 0);
            gpio_set_level (P00_6, 0);
            break;
        case 3:  //����C�����ţ�B������


            pwm_set_duty (ATOM0_CH1_P00_1, 0);
            gpio_set_level (P00_2, 0);

            pwm_set_duty (ATOM0_CH2_P00_3, 0);
            gpio_set_level (P00_4, 1);

            pwm_set_duty (ATOM0_CH4_P00_5, duty_finish);
            gpio_set_level (P00_6, 0);
            break;
        case 4: //����C�����ţ�A������

            pwm_set_duty (ATOM0_CH1_P00_1, 0);
            gpio_set_level (P00_2, 1);

            pwm_set_duty (ATOM0_CH2_P00_3, 0);
            gpio_set_level (P00_4, 0);

            pwm_set_duty (ATOM0_CH4_P00_5, duty_finish);
            gpio_set_level (P00_6, 0);

            break;
        case 5:   //����B�����ţ�A������


            pwm_set_duty (ATOM0_CH1_P00_1, 0);
            gpio_set_level (P00_2, 1);

            pwm_set_duty (ATOM0_CH2_P00_3, duty_finish);
            gpio_set_level (P00_4, 0);

            pwm_set_duty (ATOM0_CH4_P00_5, 0);
            gpio_set_level (P00_6, 0);

            break;
        case 6:  //����B�����ţ�C������

            pwm_set_duty (ATOM0_CH1_P00_1, 0);
            gpio_set_level (P00_2, 0);

            pwm_set_duty (ATOM0_CH2_P00_3, duty_finish);
            gpio_set_level (P00_4, 0);

            pwm_set_duty (ATOM0_CH4_P00_5, 0);
            gpio_set_level (P00_6, 1);
            break;
        default:

            motor_close();

            break;
        }
    }
    else
    {
        motor_close();
    }
}

