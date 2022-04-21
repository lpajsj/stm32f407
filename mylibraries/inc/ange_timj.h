#ifndef _ange_timj_h
#define _ange_timj_h
#include "stm32f4xx.h"
//���ļ��еĶ�ʱ����ֻ����򵥼���
#define ange_tim6 1
#define ange_tim7 0
#define ange_tim4 0
void ange_TIMj_init(void);

#if  ange_tim6
#define ange_TIMjx TIM6
#define ange_TIMj_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMj_CLK       RCC_APB1Periph_TIM6
#define ange_TIMj_IRQ       TIM6_DAC_IRQn
#define ange_TIMj_IRQHandler  TIM6_DAC_IRQHandler
#endif

#if  ange_tim7
#define ange_TIMjx TIM7
#define ange_TIMj_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMj_CLK       RCC_APB1Periph_TIM7
#define ange_TIMj_IRQ       TIM7_IRQn
#define ange_TIMj_IRQHandler  TIM7_IRQHandler
#endif

#if  ange_tim4
#define ange_TIMjx TIM4
#define ange_TIMj_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMj_CLK       RCC_APB1Periph_TIM4
#define ange_TIMj_IRQ       TIM4_IRQn
#define ange_TIMj_IRQHandler  TIM4_IRQHandler
#endif
//TIM��������ʱ
#define micros() TIM5->CNT
#define timcnt() TIM5->CNT				

#define TIM5_delay(x) timcnt=0; x+=timcnt; while(timcnt<x);
void Initial_System_Timer5(void);



#endif



