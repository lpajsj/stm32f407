#include "ange_USART.h"
#include "ange_dma.h"
void ange_usartnvicinit()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_USART_IRQ;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
void ange_USART_init(u32 BaudRate)  //���ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	USART_InitTypeDef usartinit;
	ange_USART_GPIO_AHBxClkCmd(ange_USART_GPIO_CLK,ENABLE);
	ange_USART_APBxClkCmd(ange_USART_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AF;  //����
	gpioinit.GPIO_Pin=ange_USART_TX_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(ange_USART_TX_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Mode=GPIO_Mode_AF; //RX����ģʽ
	gpioinit.GPIO_Pin=ange_USART_RX_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_USART_RX_GPIO_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_USART_TX_GPIO_PORT,ange_USART_TX_AF_Pinsource,ange_USART_TX_AF);  //����
	GPIO_PinAFConfig(ange_USART_TX_GPIO_PORT,ange_USART_RX_AF_Pinsource,ange_USART_RX_AF);
	usartinit.USART_BaudRate=BaudRate;   //������
//	usartinit.USART_BaudRate=ange_USART_BaudRate;   //������
	usartinit.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //Ӳ��������
	usartinit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //����ģʽ
	usartinit.USART_Parity=USART_Parity_No;  //У��λ
	usartinit.USART_StopBits=USART_StopBits_1; //ֹͣλ
	usartinit.USART_WordLength=USART_WordLength_8b; //����λ�������У��λѡ��9λ
	USART_Init(ange_USARTx,&usartinit);

	ange_usartnvicinit();  //�ж�ʱʹ��
	USART_ITConfig(ange_USARTx,USART_IT_TC,ENABLE);
//USART_IT_PE ��ż������
//USART_IT_TXE �����ж�
//USART_IT_TC ���������
//USART_IT_RXNE �����ж�
//USART_IT_IDLE ����������
//USART_IT_LBD LIN �жϼ�
//USART_IT_CTS CTS �ж�
//USART_IT_ERR �����ж�
	USART_Cmd(ange_USARTx,ENABLE);
//	USART_DMACmd(ange_USARTx,USART_DMAReq_Rx,ENABLE);  //Ӧ��ֻ��dma��usart��ͨ�����
}
void ange_usart_sendbyte(USART_TypeDef *USARTx,u8 x)
{
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
	USART_SendData(USARTx,x);
	
//USART_FLAG_CTS CTS ��־λ
//USART_FLAG_LBD LIN �жϼ���־λ
//USART_FLAG_TXE �������ݼĴ����ձ�־λ
//USART_FLAG_TC ������ɱ�־λ
//USART_FLAG_RXNE �������ݼĴ����ǿձ�־λ
//USART_FLAG_IDLE �������߱�־λ
//USART_FLAG_ORE ��������־λ
//USART_FLAG_NE ���������־λ
//USART_FLAG_FE ֡�����־λ
//USART_FLAG_PE ��ż�����־λ
}
void ange_usart_sendstring(USART_TypeDef *USARTx,u8 *str)
{
	u32 n=0;
	while(str[n]!='\0')
	{
		ange_usart_sendbyte(USARTx,str[n]);
		n++;
	}
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
}
void ange_usart_sendnumstr(USART_TypeDef *usartx,u8 *str,u16 n)
{
	while(n--)
	{
	ange_usart_sendbyte(usartx,*str);
		str++;
	}
}
//u8 jieshouzu[ange_DMA_WC_BufferSize];
//void ange_USART_IRQHandler() //dma����
//{
//	u8 x;
//	if(USART_GetITStatus(ange_USARTx,USART_IT_IDLE)!=RESET)
//	{
//		DMA_Cmd(ange_DMA_WC_Stream,DISABLE);  //Ҫ�ر�dma��USART_DMACmd�����ԣ�
//		x=DMA_GetCurrDataCounter(ange_DMA_WC_Stream);
//		DMA_SetCurrDataCounter(ange_DMA_WC_Stream,ange_DMA_WC_BufferSize);  
//		ange_usart_sendnumstr(ange_USARTx,jieshouzu,ange_DMA_WC_BufferSize-x);
//		DMA_Cmd(ange_DMA_WC_Stream,ENABLE);
//		USART_ReceiveData(ange_USARTx);//��Ҫ����һ�����ݲ�Ȼ��һֱ���ж�
//		USART_ClearFlag(ange_USARTx,USART_FLAG_IDLE);
//	}
//}

//void ange_USART_IRQHandler()   //����
//{
//	u8 x;
//	if(USART_GetITStatus(ange_USARTx,USART_IT_RXNE)!=RESET)
//	{
//		x=USART_ReceiveData(ange_USARTx);
//		ange_usart_sendbyte(ange_USARTx,x+1);
//	}
//}
u8 jishu=0;
u8 jishu1=0;
void ange_USART_IRQHandler()   //����
{
	u8 x;
	if(USART_GetITStatus(ange_USARTx,USART_IT_TC)!=RESET)
	{
		jishu++;
		USART_ClearITPendingBit(ange_USARTx,USART_IT_TC);
//		while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_TXE)==0); //RESET
//		  USART1->DR=jishu1;
//		jishu++;
//		jishu1++;
		if(jishu==255)
		{
//			USART_Cmd(ange_USARTx,DISABLE);
//			USART_ITConfig(ange_USARTx,USART_IT_TXE,DISABLE);
//			USART_Cmd(ange_USARTx,ENABLE);
		}
//		x=USART_ReceiveData(ange_USARTx);
//		ange_usart_sendbyte(ange_USARTx,x+1);
		
	}
}
#if 1
int fputc(int ch,FILE *f)
{
	ange_usart_sendbyte(ange_USARTx,(u8)ch);
	return ch;
}
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_RXNE)==RESET);
	return (int)USART_ReceiveData(ange_USARTx);
}
#endif

#if 0
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
