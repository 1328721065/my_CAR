/*
 * pwm_input.c
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */

#include "config.h"
#include "zf_driver_gpio.h"
#include "pwm_input.h"

uint32 pwm_in_duty;

IfxGtm_Tim_In driver;

//输入捕获初始化
void pwm_input_init(void)
{
    IfxGtm_enable(&MODULE_GTM);
    if(!(MODULE_GTM.CMU.CLK_EN.U & 0x2))
    {
        IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, 100000000);
        IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);
    }

    IfxGtm_Tim_In_Config config;
    IfxGtm_Tim_In_initConfig(&config, &MODULE_GTM);
    config.timIndex                     = IfxGtm_Tim_1;
    config.channelIndex                 = IfxGtm_Tim_Ch_2;
    config.isrPriority                  = GTM_PWM_IN_PRIORITY;
    config.capture.irqOnNewVal          = TRUE;
    config.capture.irqOnCntOverflow     = TRUE;
    config.timeout.clock                = IfxGtm_Cmu_Clk_0;
    config.filter.inputPin              = &IfxGtm_TIM1_2_TIN70_P20_14_IN;
    config.filter.inputPinMode          = IfxPort_InputMode_pullDown;


    IfxGtm_Tim_In_init(&driver, &config);
    driver.periodTick = PWM_MAX;


    gpio_init(MOTOR_DIR_IN_PIN, GPI, 0,GPI_PULL_DOWN);      //初始化方向设置引脚
}


