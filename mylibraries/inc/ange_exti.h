#ifndef __ange_exti_H
#define __ange_exti_H
#include "stm32f4xx.h"
#define ange_EXTI_GPIO_PORT   GPIOB         //
#define ange_EXTI_SYSCFG_CLK     RCC_APB2Periph_SYSCFG   //ʹ���ⲿ�ж���ҲҪ��SYSCFGʱ��
#define ange_EXTI_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define ange_EXTI_GPIO_Pin    GPIO_Pin_6
#define ange_EXTI_PortSource  EXTI_PortSourceGPIOB //void GPIO_EXTILineConfig(u8 GPIO_PortSource, u8 GPIO_PinSource)  0123456��Ӧabcdefg
#define ange_EXTI_PinSource   EXTI_PinSource6  //ѡ�� GPIO �ܽ������ⲿ�ж���·�Ĳ���  0-15
#define ange_EXTI_Line        EXTI_Line6      //�ж��¼���  1<<n
#define ange_EXTI_IRQn        EXTI9_5_IRQn      //�ж�Դ
#define ange_EXTI9_5_IRQHandler           EXTI9_5_IRQHandler  ///�жϺ���
void ange_extinvicinit(void);
void ange_extiinit(void);
#endif
/*
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
���� EXTI_InitStruct ��ָ���Ĳ�����ʼ������ EXTI �Ĵ���
typedef struct
{
u32 EXTI_Line;
EXTIMode_TypeDef EXTI_Mode;
EXTIrigger_TypeDef EXTI_Trigger;
FunctionalState EXTI_LineCmd;
} EXTI_InitTypeDef;
typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;
typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;
*/
