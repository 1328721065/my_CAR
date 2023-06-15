/*
 * key.c
 *
 *  Created on: 2023年3月16日
 *      Author: koubayaxi
 */

#include "zf_common_headfile.h"
#include "key.h"
#include "config.h"
#include "flash_save.h"
#include "adc.h"

uint8 choose_out=0;     //位置
uint8 key_control=0; //选择

uint8 key_choose(void)
{
    uint8 i=0;
    if(!gpio_get_level(KEY_left))    { system_delay_ms(10);while(!gpio_get_level(KEY_left)); i=1;}
    if(!gpio_get_level(KEY_up))      { system_delay_ms(10);while(!gpio_get_level(KEY_up)); i=2;}
    if(!gpio_get_level(KEY_right))   { system_delay_ms(10);while(!gpio_get_level(KEY_right));i=3;}
    if(!gpio_get_level(KEY_down))    { system_delay_ms(10);while(!gpio_get_level(KEY_down)); i=4;}
    if(!gpio_get_level(KEY_press))   { system_delay_ms(10);while(!gpio_get_level(KEY_press)); i=5;}
    if(!gpio_get_level(SWITCH1))     { system_delay_ms(10);while(!gpio_get_level(SWITCH1)); i=6;}
    if(!gpio_get_level(SWITCH2))     { system_delay_ms(10);while(!gpio_get_level(SWITCH2)); i=7;}
    return i;
}

void menu(void)
{
    tft180_clear();
    while(1)
    {
        adc_read();
        tft180_show_char (0, choose_out, '>');
        tft180_show_string (10, 0, "KP:");
        tft180_show_string (10, 20, "KI:");
        tft180_show_string (10,40, "duty:");
        tft180_show_string (10,60, "bat:");
        tft180_show_string (10, 80, "SAVE");
        tft180_show_string (10, 100, "READ");
        tft180_show_string (10, 120, "PID_con:");
        tft180_show_float (50, 0,PID_KP,2,2);
        tft180_show_float (50, 20,PID_KI,2,2);
        tft180_show_uint(50,40,duty,6);
        tft180_show_float (50,60,battery_voltage,2,1);
        tft180_show_uint(80,120,user_control,3);
        key_control=key_choose();
        if(key_control==2)
        {
            tft180_show_string(0,choose_out," ");
            if(choose_out>0) choose_out-=20;
            tft180_show_char (0, choose_out, '>');
        }
        else if(key_control==4)
        {
            tft180_show_string(0,choose_out," ");
            if(choose_out<120) choose_out+=20;
            tft180_show_char (0, choose_out, '>');
        }
        if(key_control==1)
        {
            if(choose_out==0)
            {
                PID_KP-=0.1;
                tft180_show_float (50,0,PID_KP,2,2);
            }
            else if(choose_out==20)
            {
               PID_KI-=0.1;
               tft180_show_float (50,20,PID_KI,2,2);
            }
            else if(choose_out==40)
            {
               duty-=100;
               tft180_show_uint (50,40,duty,8);
            }
            else if(choose_out==120)
            {
                if(user_control>0)
                  user_control-=1;
               tft180_show_uint(80,120,user_control,3);
            }
        }
        if(key_control==3)
        {
            if(choose_out==0)
            {
                PID_KP+=0.1;
                tft180_show_float (50,0,PID_KP,2,2);
            }
            else if(choose_out==20)
            {
               PID_KI+=0.1;
               tft180_show_float(50,20,PID_KI,2,2);
            }
            else if(choose_out==40)
            {
               duty+=100;
               tft180_show_uint (50,40,duty,8);
            }
            else if(choose_out==120)
            {
                if(user_control<1)
                user_control+=1;
               tft180_show_uint(80,120,user_control,3);
            }
        }
        if(key_control==5&&choose_out==80)
        {
            key_control=0;
            flash_write();
            tft180_show_float (50, 0,PID_KP,2 , 2);
            tft180_show_float (50, 20,PID_KI,2 , 2);
            tft180_show_uint(50,40,duty,6);
            tft180_show_string (60, 80, "ok");
        }
        if(key_control==5&&choose_out==100)
        {
            key_control=0;
            flash_read();
            tft180_show_float (50, 0,PID_KP,2,2);
            tft180_show_float (50, 20,PID_KI,2,2);
            tft180_show_uint(50,40,duty,6);
            tft180_show_string (60, 100, "ok");
        }
        if(key_control==6)
        {
            tft180_clear();
            duty_copy=duty;
            break;
        }
    }
}
