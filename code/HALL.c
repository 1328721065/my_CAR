/*
 * HALL.c
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */



#include "HALL.h"
#include "config.h"
#include "zf_common_headfile.h"
#include "zf_driver_gpio.h"
#include "motor.h"
#include "motor_filter.h"

int16 speed_ahead_limit=4000;//转速阈值
/*
uint8 hall_steps_normal[2][8] =
{
    //数据中的0并没有作用，只是用于占位
    {0,2, 4, 3, 6, 1, 5,0},  //正转的时候霍尔顺序
    {0,5,3,1,6,4,2,0},  //反转的时候霍尔顺序
};


*/
uint8 control_hall[6]={6,2,3,1,5,4};
//#define BLDC_HALL_ABC
uint8 hall_steps_normal[2][8]={             //正常转动的霍尔时序
      // {0,4,2,3,6,5,1,0},
       {0,5,6,1,2,3,4,0},
       {0,4,5,6,1,2,3,0},
};  //  {0,6,1,4,3,5,2,0},   // {0,6,1,4,3,5,2,0},                 //0仅用于占位 无作用

uint8 hall_steps_advance[2][8]={            //超前1相换向的霍尔时序
        {0,6,1,2,3,4,5,0},                 //0仅用于占位 无作用
        {0,5,6,1,2,3,4,0},
};

uint8 motor_state;

int8 hall_now=0;
int8 hall_last=0;
int8 hall_next=0;
int8 hall_index=0;
unsigned int time_save[6]={commutation_time,commutation_time,commutation_time,commutation_time,commutation_time,commutation_time};
unsigned long time_sum=0;//六次换相时间总和
int time_once=0;//统计本次换相所需时间
unsigned long time_delay=commutation_time;//延迟换相延时时间



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

    if(motor_control.dir==1)//电机反转的时候需要对速度取反
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
    time_once++;//看定时器设置( commutation_time_sum是统计电机换相6次会进入多少次T12周期中断, T12周期中断周期中断的频率为20KHz,50us)

    //换相超时保护
   //如果换相超过了250ms则认为出现堵转，应该及时将速度设置为0
    if(time_once>commutation_time)
    {
        time_once=commutation_time;
        time_save[0]=commutation_time;
        time_save[1]=commutation_time;
        time_save[2]=commutation_time;
        time_save[3]=commutation_time;
        time_save[4]=commutation_time;
        time_save[5]=commutation_time;
    //滑动平均滤波初始化
    move_filter_init(&speed_filter);
    //停车
    motor_state=motor_stop;
    }
    else
    {
        motor_state=motor_go;
    }
    if(hall_now==7||hall_now==0)//霍尔数据读取错误 不执行换相部分
    {
        return;
    }
    if(((hall_now!=hall_last)&&(!time_delay))||!hall_next)//能继续下去的条件,开始换相
    {

            hall_index++;
            if(hall_index>=6)
            {
                hall_index=0;
            }
        time_save[hall_index]=time_once;//本次换向所需时间
        time_once=0;
        speed_calc();//转子速度计算
 //     motor_set_dir();//设置旋转方向并输出方向

 // if((speed_filter.data_average>speed_ahead_limit)||(speed_filter.data_average<-1*speed_ahead_limit))//速度高于阈值，霍尔传感器有误差，提前换相
 //   {
  //     hall_next=hall_steps_advance[motor_control.dir][hall_now];//速度大于一定的时候，霍尔延迟较大,因此采用超前换相加延时的方式去匹配最佳的换相点
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
