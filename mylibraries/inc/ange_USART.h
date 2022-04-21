#ifndef __ange_USART_H
#define __ange_USART_H
#include "stm32f4xx.h"
#include <stdio.h>
#define chuankou1  1
//����
#if chuankou1
#define ange_USARTx     						USART1           //�Ĵ�����Ҫ�ĵ�
#define ange_USART_CLK  						RCC_APB2Periph_USART1    //�Ĵ�����Ҫ�ĵ�
#define ange_USART_APBxClkCmd				RCC_APB2PeriphClockCmd   //�Ĵ�����Ҫ�ĵ�
//#define ange_USART_BaudRate  9600

#define ange_USART_IRQ 							USART1_IRQn       //�Ĵ�����Ҫ�ĵ�
#define ange_USART_IRQHandler 			USART1_IRQHandler  //�Ĵ�����Ҫ�ĵ�
//GPIO
#define ange_USART_GPIO_CLK 				RCC_AHB1Periph_GPIOA
#define ange_USART_GPIO_AHBxClkCmd 	RCC_AHB1PeriphClockCmd  //����
#define ange_USART_TX_GPIO_PORT 		GPIOA        //�Ĵ�����Ҫ�ĵ�
#define ange_USART_TX_GPIO_Pin  		GPIO_Pin_9   //�Ĵ�����Ҫ�ĵ�
#define ange_USART_TX_AF            GPIO_AF_USART1
#define ange_USART_TX_AF_Pinsource  GPIO_PinSource9

#define ange_USART_RX_GPIO_PORT 		GPIOA        //�Ĵ�����Ҫ�ĵ�
#define ange_USART_RX_GPIO_Pin  		GPIO_Pin_10   //�Ĵ�����Ҫ�ĵ�
#define ange_USART_RX_AF_Pinsource   GPIO_PinSource10
#define ange_USART_RX_AF            GPIO_AF_USART1
#else
#define ange_USARTx     						USART2           //�Ĵ�����Ҫ�ĵ�
#define ange_USART_CLK  						RCC_APB1Periph_USART2    //�Ĵ�����Ҫ�ĵ�
#define ange_USART_APBxClkCmd				RCC_APB1PeriphClockCmd   //�Ĵ�����Ҫ�ĵ�
//#define ange_USART_BaudRate  9600

#define ange_USART_IRQ 							USART2_IRQn       //�Ĵ�����Ҫ�ĵ�
#define ange_USART_IRQHandler 			USART2_IRQHandler  //�Ĵ�����Ҫ�ĵ�
//GPIO
#define ange_USART_GPIO_CLK 				RCC_APB2Periph_GPIOA
#define ange_USART_GPIO_APBxClkCmd 	RCC_APB2PeriphClockCmd  //����
#define ange_USART_TX_GPIO_PORT 		GPIOA        //�Ĵ�����Ҫ�ĵ�
#define ange_USART_TX_GPIO_Pin  		GPIO_Pin_2   //�Ĵ�����Ҫ�ĵ�
#define ange_USART_RX_GPIO_PORT 		GPIOA        //�Ĵ�����Ҫ�ĵ�
#define ange_USART_RX_GPIO_Pin  		GPIO_Pin_3   //�Ĵ�����Ҫ�ĵ�
#endif
void ange_usartnvicinit(void);
void ange_USART_init(u32 BaudRate);  //���ڳ�ʼ��
//void ange_USART_init(void);
void ange_usart_sendbyte(USART_TypeDef *USARTx,u8 x);
void ange_usart_sendstring(USART_TypeDef *USARTx,u8 *str);
//////
int fputc(int ch,FILE *f);
int fgetc(FILE *f);
#endif
#if 0
typedef struct
{
vu16 SR;
u16 RESERVED1;
vu16 DR;
u16 RESERVED2;
vu16 BRR;
u16 RESERVED3;
vu16 CR1;
u16 RESERVED4;
vu16 CR2;
u16 RESERVED5;
vu16 CR3;
u16 RESERVED6;
vu16 GTPR;
u16 RESERVED7;
} USART_TypeDef;

SR USART ״̬�Ĵ���
DR USART ���ݼĴ���
BRR USART �����ʼĴ���
CR1 USART ���ƼĴ��� 1
CR2 USART ���ƼĴ��� 2
CR3 USART ���ƼĴ��� 3
GTPR USART ����ʱ���Ԥ��Ƶ�Ĵ���

typedef struct
{
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

  uint16_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  uint16_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint16_t USART_Parity;                                                                 /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  uint16_t USART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;
#endif
