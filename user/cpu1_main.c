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
* �ļ�����          cpu1_main
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
#pragma section all "cpu1_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU1��RAM��


// ���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
// ����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
// Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
// һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

// ����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ�� enableInterrupts(); �������ж�Ƕ��
// �򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ������� disableInterrupts(); ���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ����� enableInterrupts(); �������жϵ���Ӧ��


// **************************** �������� ****************************
/*
#define UART_INDEX              (DEBUG_UART_INDEX   )                           // Ĭ�� UART_0
#define UART_BAUDRATE           (DEBUG_UART_BAUDRATE)                           // Ĭ�� 115200

//���ߴ���
#define UART_TX_PIN_YOU             UART0_TX_P14_0                          // Ĭ�� UART0_TX_P14_0
#define UART_RX_PIN_YOU             UART0_RX_P14_1                         // Ĭ�� UART0_RX_P14_1


uint8 MOTOR_STOP=0;
uint8 key=0;
*/
void core1_main(void)
{
    disable_Watchdog();                     // �رտ��Ź�
    interrupt_global_enable(0);             // ��ȫ���ж�
    // �˴���д�û����� ���������ʼ�������
/*
          //  /*���ߴ��ڳ�ʼ��(��)
     fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // ��ʼ�� fifo ���ػ�����
     uart_init(UART_0, UART_BAUDRATE, UART_TX_PIN_YOU, UART_RX_PIN_YOU);             // ��ʼ������
     uart_rx_interrupt(UART_0, 1);                                           // ���� UART_INDEX �Ľ����ж�


 //  adc_collection_init();//��ʼ��adcͨ����adc���ڲɼ���Դ��ѹ��ĸ�ߵ����������

     key_init(10);//������ʼ��

     tft180_init ();//��Ļ��ʼ��
     tft180_set_font(TFT180_8X16_FONT);

     menu();

     gpio_init (P33_13,GPI, 0, GPI_PULL_DOWN);//ң������ʼ��
     gpio_init (P33_12,GPI, 0, GPI_PULL_DOWN);//ң������ʼ��

     HALL_init();//������ʼ��

     move_filter_init(&speed_filter);//����ƽ���˲���ʼ��

    //  motor_out_init();//��ʼ������ٶ��뷽����Ϣ������

   //  pwm_input_init();  //�����źŲ����ʼ��

     motor_init();   //�����ʼ��

     pit_init (CCU60_CH1,50);//��ʼ��pit_ch1,50us
     pit_init (CCU60_CH0,5000);//��ʼ��pit_ch0,5ms
     pit_ms_init(CCU61_CH0,200);//��ʼ��pit_ch0,200ms

**/
    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();                 // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
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



       //ң�������ƹر�
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

        //ң�������ƿ���
        if(gpio_get_level(P33_12))
        {
            pit_start (CCU60_CH0);
            pit_start (CCU60_CH1);
            pit_start (CCU61_CH0);
            // duty_finish=0;
             MOTOR_STOP=0;
        }

*/
        // �˴���д��Ҫѭ��ִ�еĴ���
    }

}


#pragma section all restore
