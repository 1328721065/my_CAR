/*
 * config.c
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */


#include "config.h"
#include "zf_common_headfile.h"
#include "stdlib.h"

uint8 i=0;
uint32 MAX_SPEED=8000;
uint16 duty=1800;//PWM接收值
uint16 duty_copy=0;
uint16 duty_fin=1800;

//PID_control

float PID_err_now=0,PID_KP=2.6,PID_KI=0.4,Iout=0;

float  battery_voltage=0.0;

uint8 user_control=0;


