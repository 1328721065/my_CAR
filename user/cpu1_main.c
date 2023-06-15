/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu1_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.8.0
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "zf_driver_pit.h"
#include "motor_filter.h"
#include "HALL.h"
#include "motor.h"
#include "zf_common_headfile.h"
#include "adc.h"
#include "config.h"
#include "receive.h"
#include "pwm_input.h"
#include "isr_config.h"
#include "key.h"
#pragma section all "cpu1_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中


// 工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
// 工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
// 然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
// 一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

// 对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用 enableInterrupts(); 来开启中断嵌套
// 简单点说实际上进入中断后TC系列的硬件自动调用了 disableInterrupts(); 来拒绝响应任何的中断，因此需要我们自己手动调用 enableInterrupts(); 来开启中断的响应。


// **************************** 代码区域 ****************************
/*
#define UART_INDEX              (DEBUG_UART_INDEX   )                           // 默认 UART_0
#define UART_BAUDRATE           (DEBUG_UART_BAUDRATE)                           // 默认 115200

//有线串口
#define UART_TX_PIN_YOU             UART0_TX_P14_0                          // 默认 UART0_TX_P14_0
#define UART_RX_PIN_YOU             UART0_RX_P14_1                         // 默认 UART0_RX_P14_1


uint8 MOTOR_STOP=0;
uint8 key=0;
*/
void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    // 此处编写用户代码 例如外设初始化代码等
/*
          //  /*有线串口初始化(接)
     fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // 初始化 fifo 挂载缓冲区
     uart_init(UART_0, UART_BAUDRATE, UART_TX_PIN_YOU, UART_RX_PIN_YOU);             // 初始化串口
     uart_rx_interrupt(UART_0, 1);                                           // 开启 UART_INDEX 的接收中断


 //  adc_collection_init();//初始化adc通道，adc用于采集电源电压、母线电流、相电流

     key_init(10);//按键初始化

     tft180_init ();//屏幕初始化
     tft180_set_font(TFT180_8X16_FONT);

     menu();

     gpio_init (P33_13,GPI, 0, GPI_PULL_DOWN);//遥控器初始化
     gpio_init (P33_12,GPI, 0, GPI_PULL_DOWN);//遥控器初始化

     HALL_init();//霍尔初始化

     move_filter_init(&speed_filter);//滑动平均滤波初始化

    //  motor_out_init();//初始化输出速度与方向信息的引脚

   //  pwm_input_init();  //输入信号捕获初始化

     motor_init();   //电机初始化

     pit_init (CCU60_CH1,50);//初始化pit_ch1,50us
     pit_init (CCU60_CH0,5000);//初始化pit_ch0,5ms
     pit_ms_init(CCU61_CH0,200);//初始化pit_ch0,200ms

**/
    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕
    while (TRUE)
    {
        // 此处编写需要循环执行的代码
/*
        tft180_show_int (10,0,duty_fin,5);
    //    printf("sp:%d\r\n",speed_filter.data_average);
    //    printf("mo:%d\r\n",motor_state);
        key=key_choose();
        if(key==6)
        {
            duty+=100;
            key=0;
        }
        if(key==7)
        {
            duty-=100;
            key=0;
        }



       //遥控器控制关闭
        if(gpio_get_level(P33_13))
        {
             pit_close (CCU60_CH0);
             pit_close (CCU60_CH1);
             pit_close (CCU61_CH0);
            // duty_finish=0;
             MOTOR_STOP=1;
        }
        if(MOTOR_STOP)
        {
            motor_close();
        }

        //遥控器控制开启
        if(gpio_get_level(P33_12))
        {
            pit_start (CCU60_CH0);
            pit_start (CCU60_CH1);
            pit_start (CCU61_CH0);
            // duty_finish=0;
             MOTOR_STOP=0;
        }

*/
        // 此处编写需要循环执行的代码
    }

}


#pragma section all restore
