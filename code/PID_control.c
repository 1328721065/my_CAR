/*
 * PID_control.c
 *
 *  Created on: 2023年1月1日
 *      Author: koubayaxi
 */

#include "zf_common_headfile.h"
#include "config.h"
#include "motor.h"

//float FLT_EPSILON=5000;
//
//typedef struct lowpassFilter2p{    // 历史采样数据
//        float _delay_element1;
//        float _delay_element2;    // 权重系数
//        float _a1;
//        float _a2;
//        float _b0;
//        float _b1;
//        float _b2;    // 截至频率
//        float _cutoff_freq;    // 采样频率
//        float _sample_freq;
//         } lowpassFilter2p_t;

int16 incre_ve_loop(float err)
{
    int16 next_duty;
    PID_err_now=err;
    Iout+=PID_err_now;
    if(Iout>6000)
    {
        Iout=6000;
    }
    if(Iout<-6000)
    {
        Iout=-6000;
    }
    next_duty=(int16)(PID_KP*PID_err_now+PID_KI*Iout);
    next_duty=(int16)func_limit_ab(next_duty,motor_control.speed_min, motor_control.speed_max);
    return next_duty;
}

//void iir_pid(float duty_next)
//{
//
//    const float fr=sample_freq/_cutoff_freq;
//    const float
//}


//void lp2p_init(lowpassFilter2p_t *lp, float sample_freq, float cutoff_freq)
//{
//    lp2p_set_cutoff_frequency(lp, sample_freq, cutoff_freq);
//}
//
//
//float lp2p_reset(lowpassFilter2p_t *lp, float sample)
//{    const float input = isfinite(sample) ? sample : 0.0f;
//      if (fabsf(1 + lp->_a1 + lp->_a2) > FLT_EPSILON)
//      {
//          lp->_delay_element1 = lp->_delay_element2 = input / (1 + lp->_a1 + lp->_a2);
//          if (!isfinite(lp->_delay_element1) || !isfinite(lp->_delay_element2))
//          {
//              lp->_delay_element1 = lp->_delay_element2 = input;
//          }
//      }
//      else
//           {
//                lp->_delay_element1 = lp->_delay_element2 = input;
//           }
//      return lp2p_apply(lp, input);
//}
//void lp2p_disable(lowpassFilter2p_t *lp)
//{    lp->_sample_freq = 0.f;
//     lp->_cutoff_freq = 0.f;
//     lp->_delay_element1 = 0.0f;
//     lp->_delay_element2 = 0.0f;
//     lp->_b0 = 1.f;
//     lp->_b1 = 0.f;
//     lp->_b2 = 0.f;
//     lp->_a1 = 0.f;
//     lp->_a2 = 0.f;
//}
//void lp2p_set_cutoff_frequency(lowpassFilter2p_t *lp, float sample_freq,float cutoff_freq)
//{    if ((sample_freq <= 0.f)||(cutoff_freq <= 0.f)||(cutoff_freq >= sample_freq / 2)||!isfinite(sample_freq)||!isfinite(cutoff_freq))
//      {
//            lp2p_disable(lp);
//                 return;
//      }    // reset delay elements on filter change
//     lp->_delay_element1 = 0;
//     lp->_delay_element2 = 0;
//     lp->_cutoff_freq = constrain_float(cutoff_freq,1.f,sample_freq / 2); // TODO: min based on actual numerical limit
//     lp->_sample_freq = sample_freq;
//     const float fr = lp->_sample_freq / lp->_cutoff_freq;
//     const float ohm = tanf(PI/ fr);
//     const float c = 1.f + 2.f * cosf(PI / 4.f) * ohm + ohm * ohm;
//     lp->_b0 = ohm * ohm / c;
//     lp->_b1 = 2.f * lp->_b0;
//     lp->_b2 = lp->_b0;
//     lp->_a1 = 2.f * (ohm * ohm - 1.f) / c;
//     lp->_a2 = (1.f - 2.f * cosf(PI / 4.f) * ohm + ohm * ohm) / c;
//     if (!isfinite(lp->_b0) || !isfinite(lp->_b1) || !isfinite(lp->_b2) ||!isfinite(lp->_a1) || !isfinite(lp->_a2))
//     {
//         lp2p_disable(lp);
//     }
//}
//
//float lp2p_apply(lowpassFilter2p_t *lp, float sample)
//{    float delay_element_0 = sample - lp->_delay_element1 * lp->_a1 - lp->_delay_element2 * lp->_a2;
//     const float output = delay_element_0 * lp->_b0 +lp->_delay_element1 * lp->_b1 +lp->_delay_element2 * lp->_b2;lp->_delay_element2 = lp->_delay_element1;
//     lp->_delay_element1 = delay_element_0;
//     return output;
//}
//

