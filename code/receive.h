/*
 * receive.h
 *
 *  Created on: 2023��3��7��
 *      Author: koubayaxi
 */

#ifndef CODE_RECEIVE_H_
#define CODE_RECEIVE_H_

#include "zf_common_headfile.h"

extern uint16 duty;
extern uint8  get_data;
extern uint8 uart_get_data[64];                                                        // ���ڽ������ݻ�����
extern fifo_struct uart_data_fifo;

void uart_rx_interrupt_handler(void);




#endif /* CODE_RECEIVE_H_ */
