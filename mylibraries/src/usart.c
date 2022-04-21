#include "usart.h"
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//Ƕ�������жϿ�������ѡ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//����USARTΪ�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannel=DEBUG_USART_IRQ;
	//ʹ���ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	//������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	//���ô����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	//��ʼ������
	NVIC_Init(&NVIC_InitStructure);
}
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	//�򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd(DEBUG_USART_GPIO_CLK,ENABLE);
	//�򿪴��������ʱ��
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK,ENABLE);
	//��USART TX��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStruct.GPIO_Pin=DEBUG_USART_TX_GP1O_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitStruct);
	//��USART RX��GPIO����Ϊ��������ģʽ
	GPIO_InitStruct.GPIO_Pin=DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitStruct);
	//���ô��ڵĹ���ģʽ
	USART_InitStruct.USART_BaudRate=DEBUG_USART_BAUDRATE;//���ò�����
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//����֡�����ֳ�
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//����ֹͣλ
	USART_InitStruct.USART_Parity=USART_Parity_No;//����У��λ
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//����Ӳ��������
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//���ù���ģʽ���շ�һ��
	USART_Init(DEBUG_USARTx,&USART_InitStruct);//��ɴ��ڵĳ�ʼ������
	
	//ʹ�ܴ����ж����ȼ�����
//	NVIC_Configuration();
//	//ʹ�ܴ��ڽ����ж�
//	USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);
	//ʹ�ܴ��� UE
	USART_Cmd(DEBUG_USARTx,ENABLE);
}
////�ض���C�⺯��printf�����ڣ��ض����ʹ��printf����
//int fputc(int ch,FILE *f)
//{
//	/*����һ���ֽ����ݵ�����*/
//	USART_SendData(DEBUG_USARTx,(uint8_t)ch);
//	/*�ȴ��������*/
//	while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TXE)==RESET);	
//	return ch;
//}
