/*
 * receive.c
 *
 *  Created on: 2023��3��7��
 *      Author: koubayaxi
 */



#include "zf_common_headfile.h"
#include "config.h"


void uart_rx_interrupt_handler (void);

uint8 uart_get_data[64];


uint8  get_data = 0;                                                     // �������ݱ���
uint32 fifo_data_count = 0;                                                     // fifo ���ݸ���

fifo_struct uart_data_fifo;


struct Receive_Struct
{
     uint8 receive_start;                             //���ݽ��տ�ʼ��־
     uint8 receive_buff[15];                          //��ʱ����������
     uint8 receive_buff_finished[15];                 //У�����������
} receive_struct;

//&&!receive_struct.receive_start&&receive_struct.receive_buff[4]==0x06
void data_receive(void)
{
     if(receive_struct.receive_buff[0]==0x42&&!receive_struct.receive_start&&receive_struct.receive_buff[4]==0x06)
     {
         receive_struct.receive_start=true;
     }
     if(receive_struct.receive_start)
     {
                 memcpy(receive_struct.receive_buff_finished,receive_struct.receive_buff,sizeof(receive_struct.receive_buff));
              //   duty_copy=(uint16)receive_struct.receive_buff_finished[3]*256+(uint16)receive_struct.receive_buff_finished[2];
                 duty_copy=(uint16)receive_struct.receive_buff_finished[3]*256+(uint16)receive_struct.receive_buff_finished[2];
                 receive_struct.receive_start=false;
     }
}

void uart_rx_interrupt_handler(void)
{
    uart_query_byte(UART_0, &get_data);                                     // �������� ��ѯʽ �����ݻ᷵�� TRUE û�����ݻ᷵�� FALSE
    fifo_write_buffer(&uart_data_fifo, &get_data, 1);                           // ������д�� fifo ��

    fifo_data_count = fifo_used(&uart_data_fifo);                           // �鿴 fifo �Ƿ�������
    if(fifo_data_count == 6)                                                 //����ָ����Ŀ��ʼ����
        {
            fifo_read_buffer(&uart_data_fifo, receive_struct.receive_buff, &fifo_data_count, FIFO_READ_AND_CLEAN);  // �� fifo �����ݶ�������� fifo ���صĻ���
        }


    data_receive();
}

