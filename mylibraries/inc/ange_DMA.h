#ifndef __ange_DMA_H_
#define __ange_DMA_H_
#include "stm32f4xx.h"
#define ange_DMA_CC 1
#define ange_DMA_CW 1
#define ange_DMA_WC 1
#if ange_DMA_CC
#define ange_DMA_CC_Stream     DMA2_Stream0  //ѡ��������
#define ange_DMA_CC_Channel    DMA_Channel_6  //ͨ��
#define ange_DMA_CC_Clock      RCC_AHB1Periph_DMA2  //DMAʱ��

#define ange_DMA_CC_TCIF    DMA_FLAG_TCIF0 //���ݴ�����

#define ange_DMA_CC_BufferSize 32
void ange_DMA_CC_Config( u32* y,u32 *m,u32 n);//�洢�������洢��
#endif


#if ange_DMA_CW
//�ڴ浽����
#define ange_DMA_CW_Stream   DMA2_Stream7
#define ange_DMA_CW_Channel  DMA_Channel_4
#define ange_DMA_CW_mudi     (u32)&USART1->DR
#define ange_DMA_CW_Clock      RCC_AHB1Periph_DMA2  //DMAʱ��

#define ange_DMA_CW_BufferSize 32
void ange_DMA_CW_USARTConfig(u8* y);//�洢��������
#endif


#if ange_DMA_WC
#define ange_DMA_WC_Stream   DMA2_Stream5
#define ange_DMA_WC_yuan (u32)&USART1->DR  //����
#define ange_DMA_WC_Channel  DMA_Channel_4
#define ange_DMA_WC_BufferSize 30
//#define ange_DMA_WC_Stream   DMA2_Stream0
//#define ange_DMA_WC_yuan   (u32)&(ADC1->DR)
//#define ange_DMA_WC_Channel  DMA_Channel_0
//#define ange_DMA_WC_BufferSize 5
#define ange_DMA_WC_Clock      RCC_AHB1Periph_DMA2
void ange_DMA_WC_USARTConfig(u8* m);
void ange_DMA_WC_ADCConfig(u16* m);
#endif


#if 0
#endif
#endif


