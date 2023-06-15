/*
 * key.h
 *
 *  Created on: 2023Äê3ÔÂ16ÈÕ
 *      Author: koubayaxi
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_

#include "zf_common_headfile.h"

uint8 key_choose(void);
void menu(void);


#define KEY_left                    (P11_10)
#define KEY_right                   (P11_11)
#define KEY_press                   (P11_12)
#define KEY_down                    (P11_9)
#define KEY_up                      (P11_6)
#define SWITCH1                     (P11_2)
#define SWITCH2                     (P11_3)

#endif /* CODE_KEY_H_ */
