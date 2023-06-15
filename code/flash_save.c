/*
 * flash_save.c
 *
 *  Created on: 2023Äê3ÔÂ16ÈÕ
 *      Author: koubayaxi
 */

#define flash_select 0
#define flash_page 8

#include "config.h"
#include "zf_common_headfile.h"

void flash_relcheck(void)
{
    if(flash_check(flash_select,flash_page))
           flash_erase_page(flash_select,flash_page);
    flash_buffer_clear();
}

void flash_write(void)
{
    flash_relcheck();
    flash_union_buffer[0].float_type  = PID_KP;
    flash_union_buffer[1].float_type  = PID_KI;
    flash_union_buffer[2].uint16_type  = duty;
    flash_write_page_from_buffer(flash_select,flash_page);
    flash_buffer_clear();
}

void flash_read(void)
{
    flash_buffer_clear();

    flash_read_page_to_buffer(flash_select,flash_page);
    PID_KP=flash_union_buffer[0].float_type;
    PID_KI=flash_union_buffer[1].float_type;
    duty=flash_union_buffer[2].uint16_type;
    flash_buffer_clear();
}
