/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu0_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.8.0
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
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
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��


// ���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
// ����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
// Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
// һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

// ����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ�� interrupt_global_enable(0); �������ж�Ƕ��
// �򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ������� interrupt_global_disable(); ���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ����� interrupt_global_enable(0); �������жϵ���Ӧ��

// �������ǿ�Դ����ֲ�ÿչ���
// �������ǿ�Դ����ֲ�ÿչ���
// �������ǿ�Դ����ֲ�ÿչ���

// **************************** �������� ****************************

#define UART_INDEX              (DEBUG_UART_INDEX   )                           // Ĭ�� UART_0
#define UART_BAUDRATE           (DEBUG_UART_BAUDRATE)                           // Ĭ�� 115200

//���ߴ���
#define UART_TX_PIN_YOU              UART0_TX_P14_0                         // Ĭ�� UART0_TX_P14_0
#define UART_RX_PIN_YOU              UART0_RX_P14_1                          // Ĭ�� UART0_RX_P14_1

////���ߴ���
//#define UART_TX_PIN_YOU               UART1_TX_P20_10                         // Ĭ�� UART0_TX_P14_0
//#define UART_RX_PIN_YOU               UART1_RX_P20_9                         // Ĭ�� UART0_RX_P14_1



uint8 MOTOR_STOP=0;
uint8 key=0;

int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������

   /*���ߴ��ڳ�ʼ��(��)*/
    fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // ��ʼ�� fifo ���ػ�����
    uart_init(UART_0, UART_BAUDRATE, UART_TX_PIN_YOU, UART_RX_PIN_YOU);             // ��ʼ������
    uart_rx_interrupt(UART_0,1);                                           // ���� UART_INDEX �Ľ����ж�

    adc_collection_init();//��ѹ����ʼ��

    key_init(10);//������ʼ��

    tft180_init ();//��Ļ��ʼ��
    tft180_set_font(TFT180_8X16_FONT);

    menu();

    gpio_init (P33_13,GPI, 0, GPI_PULL_DOWN);//ң������ʼ��
    gpio_init (P33_12,GPI, 0, GPI_PULL_DOWN);//ң������ʼ��

    HALL_init();//������ʼ��

    move_filter_init(&speed_filter);//����ƽ���˲���ʼ��

  //  pwm_input_init();  //�����źŲ����ʼ��

    motor_init();   //�����ʼ��

    pit_init (CCU60_CH1,50);//��ʼ��pit_ch1,50us
    pit_init (CCU60_CH0,5000);//��ʼ��pit_ch0,5ms
    pit_ms_init(CCU61_CH0,100);//��ʼ��pit_ch0,200ms

    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        key=key_choose();

        if(key==2)
        {
            duty_copy-=100;
            key=0;
        }
        if(key==4)
        {
            duty_copy+=100;
            key=0;
        }
        if(key==7)        {duty_copy=0;key=0;}
            if(key==5)
            {
                menu();
            }
       //ң�������ƹر�
        if(gpio_get_level(P33_13))
        {
             pit_close (CCU60_CH0);
             pit_close (CCU60_CH1);
             pit_close (CCU61_CH0);
           //  duty=0;
             MOTOR_STOP=1;
        }
        if(MOTOR_STOP)
        {
            motor_close();
          //  pit_close (CCU61_CH0);
        }
        //ң�������ƿ���
        if(gpio_get_level(P33_12))
        {
            pit_start (CCU60_CH0);
            pit_start (CCU60_CH1);
            pit_start (CCU61_CH0);
          //  duty=0;
             MOTOR_STOP=0;
        }
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}


IFX_INTERRUPT(uart0_rx_isr, 0, UART0_RX_INT_PRIO)
{
    interrupt_global_enable(0);                     // �����ж�Ƕ��
    IfxAsclin_Asc_isrReceive(&uart0_handle);
                  // ���ڽ��մ���
    uart_rx_interrupt_handler();
   // wireless_module_uart_handler();                 // ����ģ��ͳһ�ص�����
}




#pragma section all restore
// **************************** �������� ****************************

