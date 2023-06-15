/*
 * HALL.c
 *
 *  Created on: 2023��1��1��
 *      Author: koubayaxi
 */



#include "HALL.h"
#include "config.h"
#include "zf_common_headfile.h"
#include "zf_driver_gpio.h"
#include "motor.h"
#include "motor_filter.h"

int16 speed_ahead_limit=4000;//ת����ֵ
/*
uint8 hall_steps_normal[2][8] =
{
    //�����е�0��û�����ã�ֻ������ռλ
    {0,2, 4, 3, 6, 1, 5,0},  //��ת��ʱ�����˳��
    {0,5,3,1,6,4,2,0},  //��ת��ʱ�����˳��
};


*/
uint8 control_hall[6]={6,2,3,1,5,4};
//#define BLDC_HALL_ABC
uint8 hall_steps_normal[2][8]={             //����ת���Ļ���ʱ��
      // {0,4,2,3,6,5,1,0},
       {0,5,6,1,2,3,4,0},
       {0,4,5,6,1,2,3,0},
};  //  {0,6,1,4,3,5,2,0},   // {0,6,1,4,3,5,2,0},                 //0������ռλ ������

uint8 hall_steps_advance[2][8]={            //��ǰ1�໻��Ļ���ʱ��
        {0,6,1,2,3,4,5,0},                 //0������ռλ ������
        {0,5,6,1,2,3,4,0},
};

uint8 motor_state;

int8 hall_now=0;
int8 hall_last=0;
int8 hall_next=0;
int8 hall_index=0;
unsigned int time_save[6]={commutation_time,commutation_time,commutation_time,commutation_time,commutation_time,commutation_time};
unsigned long time_sum=0;//���λ���ʱ���ܺ�
int time_once=0;//ͳ�Ʊ��λ�������ʱ��
unsigned long time_delay=commutation_time;//�ӳٻ�����ʱʱ��



void HALL_init(void)
{
     gpio_init(HALL_A,GPI,0,GPI_PULL_UP );
     gpio_init(HALL_B,GPI,0,GPI_PULL_UP );
     gpio_init(HALL_C,GPI,0,GPI_PULL_UP );
  //   read_hall();
}

inline void speed_calc(void)
{
    uint8 i;
    int32 speed;
    time_sum=0;
    for(i=0;i<6;i++)
    {
        time_sum+=time_save[i];
    }
    speed = PWM_PIT_NUM/POLEPAIRS/time_sum;

    if(motor_control.dir==1)//�����ת��ʱ����Ҫ���ٶ�ȡ��
    {
        speed = -speed;
    }
    move_filter_calc(&speed_filter, speed);
}


void read_hall(void)
{
      uint8 A_active=0,B_active=0,C_active=0,i=0;
      A_active = gpio_get_level(HALL_A);
      B_active = gpio_get_level(HALL_B);
      C_active = gpio_get_level(HALL_C);

      hall_now=C_active*4+B_active*2+A_active;


      for(i=0;i<6;i++)
      {
          if(hall_now==control_hall[i])
          {
              hall_now=i+1;
              break;
          }
      }

}

void scan_hall(void)
{
    read_hall();
    time_once++;//����ʱ������( commutation_time_sum��ͳ�Ƶ������6�λ������ٴ�T12�����ж�, T12�����ж������жϵ�Ƶ��Ϊ20KHz,50us)

    //���೬ʱ����
   //������೬����250ms����Ϊ���ֶ�ת��Ӧ�ü�ʱ���ٶ�����Ϊ0
    if(time_once>commutation_time)
    {
        time_once=commutation_time;
        time_save[0]=commutation_time;
        time_save[1]=commutation_time;
        time_save[2]=commutation_time;
        time_save[3]=commutation_time;
        time_save[4]=commutation_time;
        time_save[5]=commutation_time;
    //����ƽ���˲���ʼ��
    move_filter_init(&speed_filter);
    //ͣ��
    motor_state=motor_stop;
    }
    else
    {
        motor_state=motor_go;
    }
    if(hall_now==7||hall_now==0)//�������ݶ�ȡ���� ��ִ�л��ಿ��
    {
        return;
    }
    if(((hall_now!=hall_last)&&(!time_delay))||!hall_next)//�ܼ�����ȥ������,��ʼ����
    {

            hall_index++;
            if(hall_index>=6)
            {
                hall_index=0;
            }
        time_save[hall_index]=time_once;//���λ�������ʱ��
        time_once=0;
        speed_calc();//ת���ٶȼ���
 //     motor_set_dir();//������ת�����������

 // if((speed_filter.data_average>speed_ahead_limit)||(speed_filter.data_average<-1*speed_ahead_limit))//�ٶȸ�����ֵ������������������ǰ����
 //   {
  //     hall_next=hall_steps_advance[motor_control.dir][hall_now];//�ٶȴ���һ����ʱ�򣬻����ӳٽϴ�,��˲��ó�ǰ�������ʱ�ķ�ʽȥƥ����ѵĻ����
  //     time_delay = func_limit_ab(time_save[hall_index]/2,0,DELAY_MAX);
  //  }
  //  else
  //  {

      hall_next=hall_steps_normal[motor_control.dir][hall_now];
      time_delay=0;
      motor_commutation(hall_next,duty_fin);
  //  }
    }
     hall_last=hall_now;
}
