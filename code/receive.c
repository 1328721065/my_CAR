/*
 * receive.c
 *
 *  Created on: 2023年3月7日
 *      Author: koubayaxi
 */



#include "zf_common_headfile.h"
#include "config.h"


void uart_rx_interrupt_handler (void);

uint8 uart_get_data[64];


uint8  get_data = 0;                                                     // 接收数据变量
uint32 fifo_data_count = 0;                                                     // fifo 数据个数

fifo_struct uart_data_fifo;


struct Receive_Struct
{
     uint8 receive_start;                             //数据接收开始标志
     uint8 receive_buff[15];                          //临时接收数据区
     uint8 receive_buff_finished[15];                 //校验完成数据区
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
    uart_query_byte(UART_0, &get_data);                                     // 接收数据 查询式 有数据会返回 TRUE 没有数据会返回 FALSE
    fifo_write_buffer(&uart_data_fifo, &get_data, 1);                           // 将数据写入 fifo 中

    fifo_data_count = fifo_used(&uart_data_fifo);                           // 查看 fifo 是否有数据
    if(fifo_data_count == 6)                                                 //读到指定数目后开始解析
        {
            fifo_read_buffer(&uart_data_fifo, receive_struct.receive_buff, &fifo_data_count, FIFO_READ_AND_CLEAN);  // 将 fifo 中数据读出并清空 fifo 挂载的缓冲
        }


    data_receive();
}

