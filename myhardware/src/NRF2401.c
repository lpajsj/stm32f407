/**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   2.4g����ģ��/nrf24l01+/������� Ӧ��bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103 ָ���߿�����  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "NRF2401.h"
#include "ange_usart.h"

 u8 RX_BUF[RX_PLOAD_WIDTH];		//�������ݻ���
 u8 TX_BUF[TX_PLOAD_WIDTH];		//�������ݻ���
 u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  // ����һ����̬���͵�ַ
 u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};
 u8 RX_ADDRESS1[RX_ADR_WIDTH] = {0x01};
void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  SPI�� I/O����
  * @param  ��
  * @retval ��
  */
void SPI_NRF_Init(void)
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /*������ӦIO�˿ڵ�ʱ��*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                         |NRF_CSN_GPIO_CLK
                         |NRF_CE_GPIO_CLK
                         |NRF_IRQ_GPIO_CLK,ENABLE);

  /*����SPI_NRF_SPI��CE����,��SPI_NRF_SPI�� CSN ����*/
   GPIO_InitStructure.GPIO_Pin = NRF_CSN_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(NRF_CSN_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = NRF_CE_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(NRF_CE_GPIO_PORT, &GPIO_InitStructure);
   /*����SPI_NRF_SPI��IRQ����*/
  GPIO_InitStructure.GPIO_Pin = NRF_IRQ_GPIO_CLK;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //��������
  GPIO_Init(NRF_IRQ_GPIO_PORT, &GPIO_InitStructure); 		  
  /* �����Զ���ĺ꣬��������csn���ţ�NRF�������״̬ */
  NRF_CSN_HIGH(); 
 #if NRF_hardware
 SPI_InitTypeDef  SPI_InitStructure;
   /*���� SPI_NRF_SPI�� SCK,MISO,MOSI���ţ�GPIOA^5,GPIOA^6,GPIOA^7 */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù���
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 					           //��ģʽ
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	 				         //���ݴ�С8λ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		 			               //ʱ�Ӽ��ԣ�����ʱΪ��
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						           //��1��������Ч��������Ϊ����ʱ��
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		   					           //NSS�ź����������
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //8��Ƶ��9MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  				       //��λ��ǰ
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
#endif
 #if NRF_software
 
  GPIO_InitStructure.GPIO_Pin = NRF_soft_clk_GPIO_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(NRF_soft_clk_GPIO_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = NRF_soft_mosi_GPIO_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(NRF_soft_mosi_GPIO_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = NRF_soft_miso_GPIO_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(NRF_soft_miso_GPIO_PORT, &GPIO_InitStructure); 
	
#endif
  /* Enable SPI1  */
  
}

/**
  * @brief   ������NRF��/дһ�ֽ�����
  * @param   д�������
  *		@arg dat 
  * @retval  ��ȡ�õ�����
  */
#if NRF_hardware
u8 SPI_NRF_RW(u8 dat)
{  	
	
   /* �� SPI���ͻ������ǿ�ʱ�ȴ� */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  
   /* ͨ�� SPI2����һ�ֽ����� */
  SPI_I2S_SendData(SPI1, dat);		
 
   /* ��SPI���ջ�����Ϊ��ʱ�ȴ� */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
}
#endif
#if NRF_software
u8 SPI_NRF_RW(u8 dat)
{
	u8 i,x=0;
	for(i=0;i<8;i++)
	{
	NRF_soft_clk=0;
	__nop();
	dat&0x80?(NRF_soft_mosi=1):(NRF_soft_mosi=0);
		dat<<=1;
	NRF_soft_clk=1;
		x<<=1;
	NRF_soft_miso?(x|=0x01):x;
	__nop();
	
	}
	NRF_soft_clk=0;
	return x;
}
#endif
/**
  * @brief   ������NRF�ض��ļĴ���д������
  * @param   
  *		@arg reg:NRF������+�Ĵ�����ַ
  *		@arg dat:��Ҫ��Ĵ���д�������
  * @retval  NRF��status�Ĵ�����״̬
  */
u8 SPI_NRF_WriteReg(u8 reg,u8 dat)
{
 	u8 status;
	 NRF_CE_LOW();
	/*�õ�CSN��ʹ��SPI����*/
    NRF_CSN_LOW();
				
	/*��������Ĵ����� */
	status = SPI_NRF_RW(reg);
		 
	 /*��Ĵ���д������*/
    SPI_NRF_RW(dat); 
	          
	/*CSN���ߣ����*/	   
  	NRF_CSN_HIGH();	
		
	/*����״̬�Ĵ�����ֵ*/
   	return(status);
}

/**
  * @brief   ���ڴ�NRF�ض��ļĴ�����������
  * @param   
  *		@arg reg:NRF������+�Ĵ�����ַ
  * @retval  �Ĵ����е�����
  */
u8 SPI_NRF_ReadReg(u8 reg)
{
 	u8 reg_val;

	NRF_CE_LOW();
	/*�õ�CSN��ʹ��SPI����*/
 	NRF_CSN_LOW();
				
  	 /*���ͼĴ�����*/
	SPI_NRF_RW(reg); 

	 /*��ȡ�Ĵ�����ֵ */
	reg_val = SPI_NRF_RW(NOP);
	            
   	/*CSN���ߣ����*/
	NRF_CSN_HIGH();		
   	
	return reg_val;
}	

/**
  * @brief   ������NRF�ļĴ�����д��һ������
  * @param   
  *		@arg reg : NRF������+�Ĵ�����ַ
  *		@arg pBuf�����ڴ洢���������ļĴ������ݵ����飬�ⲿ����
  * 	@arg bytes: pBuf�����ݳ���
  * @retval  NRF��status�Ĵ�����״̬
  */
u8 SPI_NRF_ReadBuf(u8 reg,u8 *pBuf,u8 bytes)
{
 	u8 status, byte_cnt;

	  NRF_CE_LOW();
	/*�õ�CSN��ʹ��SPI����*/
	NRF_CSN_LOW();
		
	/*���ͼĴ�����*/		
	status = SPI_NRF_RW(reg); 

 	/*��ȡ����������*/
	 for(byte_cnt=0;byte_cnt<bytes;byte_cnt++)		  
	   pBuf[byte_cnt] = SPI_NRF_RW(NOP); //��NRF24L01��ȡ����  

	 /*CSN���ߣ����*/
	NRF_CSN_HIGH();	
		
 	return status;		//���ؼĴ���״ֵ̬
}

/**
  * @brief   ������NRF�ļĴ�����д��һ������
  * @param   
  *		@arg reg : NRF������+�Ĵ�����ַ
  *		@arg pBuf���洢�˽�Ҫд��д�Ĵ������ݵ����飬�ⲿ����
  * 	@arg bytes: pBuf�����ݳ���
  * @retval  NRF��status�Ĵ�����״̬
  */
u8 SPI_NRF_WriteBuf(u8 reg ,u8 *pBuf,u8 bytes)
{
	 u8 status,byte_cnt;
	 NRF_CE_LOW();
   	 /*�õ�CSN��ʹ��SPI����*/
	 NRF_CSN_LOW();			

	 /*���ͼĴ�����*/	
  	 status = SPI_NRF_RW(reg); 
 	
  	  /*�򻺳���д������*/
	 for(byte_cnt=0;byte_cnt<bytes;byte_cnt++)
		SPI_NRF_RW(*pBuf++);	//д���ݵ������� 	 
	  	   
	/*CSN���ߣ����*/
	NRF_CSN_HIGH();			
  
  	return (status);	//����NRF24L01��״̬ 		
}

/**
  * @brief  ���ò��������ģʽ
  * @param  ��
  * @retval ��
  */
void NRF_RX_Mode(void)

{
	NRF_CE_LOW();	

   SPI_NRF_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ

   SPI_NRF_WriteReg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    

   SPI_NRF_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ    

   SPI_NRF_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);      //����RFͨ��Ƶ��    

   SPI_NRF_WriteReg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��      

   SPI_NRF_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��   

   SPI_NRF_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 

/*CE���ߣ��������ģʽ*/	
  NRF_CE_HIGH();

}    
//ʵ��ͨ��������
//void NRF_RX_Mode(void)

//{
//	NRF_CE_LOW();	

//   SPI_NRF_WriteBuf(NRF_WRITE_REG+RX_ADDR_P1,RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
//	 SPI_NRF_WriteBuf(NRF_WRITE_REG+RX_ADDR_P2,RX_ADDRESS1,1);//дRX�ڵ��ַ

//   SPI_NRF_WriteReg(NRF_WRITE_REG+EN_AA,0x06);    //ʹ��ͨ��0���Զ�Ӧ��    
//	

//   SPI_NRF_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x06);//ʹ��ͨ��0�Ľ��յ�ַ    

//   SPI_NRF_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);      //����RFͨ��Ƶ��    

// SPI_NRF_WriteReg(NRF_WRITE_REG+RX_PW_P2,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��
// SPI_NRF_WriteReg(NRF_WRITE_REG+RX_PW_P1,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��      	

//   SPI_NRF_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��   

//   SPI_NRF_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 

///*CE���ߣ��������ģʽ*/	
//  NRF_CE_HIGH();

//}  
/**
  * @brief  ���÷���ģʽ
  * @param  ��
  * @retval ��
  */
void NRF_TX_Mode(void)
{  
	NRF_CE_LOW();		

   SPI_NRF_WriteBuf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);    //дTX�ڵ��ַ 

   SPI_NRF_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK   

   SPI_NRF_WriteReg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    

   SPI_NRF_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  

   SPI_NRF_WriteReg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��

   SPI_NRF_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);       //����RFͨ��ΪCHANAL

   SPI_NRF_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	
   SPI_NRF_WriteReg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�

/*CE���ߣ����뷢��ģʽ*/	
  NRF_CE_HIGH();
    Delay(0xffff); //CEҪ����һ��ʱ��Ž��뷢��ģʽ
}


/**
  * @brief  ��Ҫ����NRF��MCU�Ƿ���������
  * @param  ��
  * @retval SUCCESS/ERROR ��������/����ʧ��
  */
u8 NRF_Check(void)
{
	u8 buf[5]={0xC2,0xC2,0xC2,0xC2,0xC2};
	u8 buf1[5];
	u8 i; 
	 
	/*д��5���ֽڵĵ�ַ.  */  
	SPI_NRF_WriteBuf(NRF_WRITE_REG+TX_ADDR,buf,5);

	/*����д��ĵ�ַ */
	SPI_NRF_ReadBuf(TX_ADDR,buf1,5); 
	 
	/*�Ƚ�*/               
	for(i=0;i<5;i++)
	{
		if(buf1[i]!=0xC2)
		break;
	} 
	       
	if(i==5)
		return SUCCESS ;        //MCU��NRF�ɹ����� 
	else
		return ERROR ;        //MCU��NRF����������
}

/**
  * @brief   ������NRF�ķ��ͻ�������д������
  * @param   
  *		@arg txBuf���洢�˽�Ҫ���͵����ݵ����飬�ⲿ����	
  * @retval  ���ͽ�����ɹ�����TXDS,ʧ�ܷ���MAXRT��ERROR
  */
u8 NRF_Tx_Dat(u8 *txbuf)
{
	u8 state;  

	 /*ceΪ�ͣ��������ģʽ1*/
	NRF_CE_LOW();

	/*д���ݵ�TX BUF ��� 32���ֽ�*/						
   SPI_NRF_WriteBuf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);

      /*CEΪ�ߣ�txbuf�ǿգ��������ݰ� */   
 	 NRF_CE_HIGH();
	  	
	  /*�ȴ���������ж� */                            
	while(NRF_Read_IRQ()!=0); 	
	
	/*��ȡ״̬�Ĵ�����ֵ */                              
	state = SPI_NRF_ReadReg(STATUS);

	 /*���TX_DS��MAX_RT�жϱ�־*/                  
	SPI_NRF_WriteReg(NRF_WRITE_REG+STATUS,state); 	

	SPI_NRF_WriteReg(FLUSH_TX,NOP);    //���TX FIFO�Ĵ��� 

	 /*�ж��ж�����*/    
	if(state&MAX_RT)                     //�ﵽ����ط�����
			 return MAX_RT; 

	else if(state&TX_DS)                  //�������
		 	return TX_DS;
	 else						  
			return ERROR;                 //����ԭ����ʧ��
} 

/**
  * @brief   ���ڴ�NRF�Ľ��ջ������ж�������
  * @param   
  *		@arg rxBuf �����ڽ��ո����ݵ����飬�ⲿ����	
  * @retval 
  *		@arg ���ս��
  */
u8 NRF_Rx_Dat(u8 *rxbuf)
{
	u8 state; 
	NRF_CE_HIGH();	 //�������״̬
	 /*�ȴ������ж�*/
	while(NRF_Read_IRQ()==0)
  {
    NRF_CE_LOW();  	 //�������״̬
    /*��ȡstatus�Ĵ�����ֵ  */               
    state=SPI_NRF_ReadReg(STATUS);
     
    /* ����жϱ�־*/      
    SPI_NRF_WriteReg(NRF_WRITE_REG+STATUS,state);

    /*�ж��Ƿ���յ�����*/
    if(state&RX_DR)                                 //���յ�����
    {
      SPI_NRF_ReadBuf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
         SPI_NRF_WriteReg(FLUSH_RX,NOP);          //���RX FIFO�Ĵ���
      return RX_DR; 
    }
    else    
      return ERROR;                    //û�յ��κ�����
  }
  
  return ERROR;                    //û�յ��κ�����
}
void NRF_Rx_nvicinit()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=NRF_Rx_IRQn;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvicinit);
}
void NRF_Rx_extiinit()
{
	GPIO_InitTypeDef gpioinit;
	EXTI_InitTypeDef extiinit;
	NRF_Rx_nvicinit();
	RCC_APB2PeriphClockCmd(NRF_IRQ_GPIO_CLK|RCC_APB2Periph_AFIO,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_IPU;
	gpioinit.GPIO_Pin=NRF_IRQ_PIN;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(NRF_IRQ_GPIO_PORT,&gpioinit);
	GPIO_EXTILineConfig(NRF_EXTI_PortSource,NRF_EXTI_PinSource);
	extiinit.EXTI_Line=NRF_EXTI_Line;
	extiinit.EXTI_LineCmd=ENABLE;
	extiinit.EXTI_Mode=EXTI_Mode_Interrupt;
	extiinit.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&extiinit);
	
}

u8 nrfrx_data[32];
u8 nrfrx_chx;
void NRF_Rx_IRQHandler()
{
	u32 i;
	if(EXTI_GetITStatus(NRF_EXTI_Line)==SET)
	{
	u8 state; 
	EXTI_ClearITPendingBit(NRF_EXTI_Line);
	 /*�ȴ������ж�*/
    NRF_CE_LOW();  	 //�������״̬
    /*��ȡstatus�Ĵ�����ֵ  */               
    state=SPI_NRF_ReadReg(STATUS);
     nrfrx_chx=STATUS&0x07;
		printf("%d\n",nrfrx_chx);
    /* ����жϱ�־*/      
    SPI_NRF_WriteReg(NRF_WRITE_REG+STATUS,state);

    /*�ж��Ƿ���յ�����*/
    if(state&RX_DR)                                 //���յ�����
    {
      SPI_NRF_ReadBuf(RD_RX_PLOAD,nrfrx_data,RX_PLOAD_WIDTH);//��ȡ����
      SPI_NRF_WriteReg(FLUSH_RX,NOP);          //���RX FIFO�Ĵ���
    }
		NRF_CE_HIGH();	 //�������״̬
	}
	for(i=0;i<32;i++)
	{
		printf("%d,",nrfrx_data[i]);
	}
	printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////����������������������������������������������������������SPI2
/**
  * @brief  SPI�� I/O����
  * @param  ��
  * @retval ��
  */
void SPI_NRF2_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /*������ӦIO�˿ڵ�ʱ��*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
                         |NRF2_CSN_GPIO_CLK
                         |NRF2_CE_GPIO_CLK
                         |NRF2_IRQ_GPIO_CLK,ENABLE);

 /*ʹ��SPI2ʱ��*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

   /*���� SPI_NRF_SPI�� SCK,MISO,MOSI���ţ�GPIOA^13,GPIOA^14,GPIOA^15 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù���
  GPIO_Init(GPIOB, &GPIO_InitStructure);  

  /*����SPI_NRF_SPI��CE����,��SPI_NRF_SPI�� CSN ����*/
   GPIO_InitStructure.GPIO_Pin = NRF2_CSN_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(NRF2_CSN_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = NRF2_CE_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(NRF2_CE_GPIO_PORT, &GPIO_InitStructure);

  /*����SPI_NRF_SPI��IRQ����*/
  GPIO_InitStructure.GPIO_Pin = NRF2_IRQ_GPIO_CLK;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //��������
  GPIO_Init(NRF2_IRQ_GPIO_PORT, &GPIO_InitStructure);
		  
  /* �����Զ���ĺ꣬��������csn���ţ�NRF�������״̬ */
  NRF2_CSN_HIGH(); 
 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 					//��ģʽ
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	 				//���ݴ�С8λ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		 				//ʱ�Ӽ��ԣ�����ʱΪ��
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						//��1��������Ч��������Ϊ����ʱ��
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		   					//NSS�ź����������
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //8��Ƶ��9MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  				//��λ��ǰ
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* Enable SPI2  */
  SPI_Cmd(SPI2, ENABLE);
}




/**
  * @brief   ������NRF��/дһ�ֽ�����
  * @param   д�������
  *		@arg dat 
  * @retval  ��ȡ�õ�����
  */
u8 SPI_NRF2_RW(u8 dat)
{  	
   /* �� SPI���ͻ������ǿ�ʱ�ȴ� */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  
   /* ͨ�� SPI2����һ�ֽ����� */
  SPI_I2S_SendData(SPI2, dat);		
 
   /* ��SPI���ջ�����Ϊ��ʱ�ȴ� */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI2);
}

/**
  * @brief   ������NRF�ض��ļĴ���д������
  * @param   
  *		@arg reg:NRF������+�Ĵ�����ַ
  *		@arg dat:��Ҫ��Ĵ���д�������
  * @retval  NRF��status�Ĵ�����״̬
  */
u8 SPI_NRF2_WriteReg(u8 reg,u8 dat)
{
 	u8 status;
	 NRF2_CE_LOW();
	/*�õ�CSN��ʹ��SPI����*/
    NRF2_CSN_LOW();
				
	/*��������Ĵ����� */
	status = SPI_NRF2_RW(reg);
		 
	 /*��Ĵ���д������*/
    SPI_NRF2_RW(dat); 
	          
	/*CSN���ߣ����*/	   
  	NRF2_CSN_HIGH();	
		
	/*����״̬�Ĵ�����ֵ*/
   	return(status);
}

/**
  * @brief   ���ڴ�NRF�ض��ļĴ�����������
  * @param   
  *		@arg reg:NRF������+�Ĵ�����ַ
  * @retval  �Ĵ����е�����
  */
u8 SPI_NRF2_ReadReg(u8 reg)
{
 	u8 reg_val;

	NRF2_CE_LOW();
	/*�õ�CSN��ʹ��SPI����*/
 	NRF2_CSN_LOW();
				
  	 /*���ͼĴ�����*/
	SPI_NRF2_RW(reg); 

	 /*��ȡ�Ĵ�����ֵ */
	reg_val = SPI_NRF2_RW(NOP);
	            
   	/*CSN���ߣ����*/
	NRF2_CSN_HIGH();		
   	
	return reg_val;
}	

/**
  * @brief   ������NRF�ļĴ�����д��һ������
  * @param   
  *		@arg reg : NRF������+�Ĵ�����ַ
  *		@arg pBuf�����ڴ洢���������ļĴ������ݵ����飬�ⲿ����
  * 	@arg bytes: pBuf�����ݳ���
  * @retval  NRF��status�Ĵ�����״̬
  */
u8 SPI_NRF2_ReadBuf(u8 reg,u8 *pBuf,u8 bytes)
{
 	u8 status, byte_cnt;

	  NRF2_CE_LOW();
	/*�õ�CSN��ʹ��SPI����*/
	NRF2_CSN_LOW();
		
	/*���ͼĴ�����*/		
	status = SPI_NRF2_RW(reg); 

 	/*��ȡ����������*/
	 for(byte_cnt=0;byte_cnt<bytes;byte_cnt++)		  
	   pBuf[byte_cnt] = SPI_NRF2_RW(NOP); //��NRF24L01��ȡ����  

	 /*CSN���ߣ����*/
	NRF2_CSN_HIGH();	
		
 	return status;		//���ؼĴ���״ֵ̬
}

/**
  * @brief   ������NRF�ļĴ�����д��һ������
  * @param   
  *		@arg reg : NRF������+�Ĵ�����ַ
  *		@arg pBuf���洢�˽�Ҫд��д�Ĵ������ݵ����飬�ⲿ����
  * 	@arg bytes: pBuf�����ݳ���
  * @retval  NRF��status�Ĵ�����״̬
  */
u8 SPI_NRF2_WriteBuf(u8 reg ,u8 *pBuf,u8 bytes)
{
	 u8 status,byte_cnt;
	 NRF2_CE_LOW();
   	 /*�õ�CSN��ʹ��SPI����*/
	 NRF2_CSN_LOW();			

	 /*���ͼĴ�����*/	
  	 status = SPI_NRF2_RW(reg); 
 	
  	  /*�򻺳���д������*/
	 for(byte_cnt=0;byte_cnt<bytes;byte_cnt++)
		SPI_NRF2_RW(*pBuf++);	//д���ݵ������� 	 
	  	   
	/*CSN���ߣ����*/
	NRF2_CSN_HIGH();			
  
  	return (status);	//����NRF24L01��״̬ 		
}

/**
  * @brief  ���ò��������ģʽ
  * @param  ��
  * @retval ��
  */
void NRF2_RX_Mode(void)

{
	NRF2_CE_LOW();	

   SPI_NRF2_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ

   SPI_NRF2_WriteReg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    

   SPI_NRF2_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ    

   SPI_NRF2_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);      //����RFͨ��Ƶ��    

   SPI_NRF2_WriteReg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��      

   SPI_NRF2_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��   

   SPI_NRF2_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 

/*CE���ߣ��������ģʽ*/	
  NRF2_CE_HIGH();

}    

/**
  * @brief  ���÷���ģʽ
  * @param  ��
  * @retval ��
  */
void NRF2_TX_Mode(void)
{  
	NRF2_CE_LOW();		

   SPI_NRF2_WriteBuf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);    //дTX�ڵ��ַ 

   SPI_NRF2_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK   

   SPI_NRF2_WriteReg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    

   SPI_NRF2_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  

   SPI_NRF2_WriteReg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��

   SPI_NRF2_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);       //����RFͨ��ΪCHANAL

   SPI_NRF2_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	
   SPI_NRF2_WriteReg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�

/*CE���ߣ����뷢��ģʽ*/	
  NRF2_CE_HIGH();
    Delay(0xffff); //CEҪ����һ��ʱ��Ž��뷢��ģʽ
}
//ʵ����򣬺���
//void NRF2_TX_Mode(void)
//{  
//	NRF2_CE_LOW();		

//   SPI_NRF2_WriteBuf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);    //дTX�ڵ��ַ 

//   SPI_NRF2_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,TX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK   
//   SPI_NRF2_WriteReg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    

//   SPI_NRF2_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  

//   SPI_NRF2_WriteReg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��

//   SPI_NRF2_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);       //����RFͨ��ΪCHANAL

//   SPI_NRF2_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
//	
//   SPI_NRF2_WriteReg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�

///*CE���ߣ����뷢��ģʽ*/	
//  NRF2_CE_HIGH();
//    Delay(0xffff); //CEҪ����һ��ʱ��Ž��뷢��ģʽ
//}
/**
  * @brief  ��Ҫ����NRF��MCU�Ƿ���������
  * @param  ��
  * @retval SUCCESS/ERROR ��������/����ʧ��
  */
u8 NRF2_Check(void)
{
	u8 buf[5]={0xC2,0xC2,0xC2,0xC2,0xC2};
	u8 buf1[5];
	u8 i; 
	 
	/*д��5���ֽڵĵ�ַ.  */  
	SPI_NRF2_WriteBuf(NRF_WRITE_REG+TX_ADDR,buf,5);

	/*����д��ĵ�ַ */
	SPI_NRF2_ReadBuf(TX_ADDR,buf1,5); 
	 
	/*�Ƚ�*/               
	for(i=0;i<5;i++)
	{
		if(buf1[i]!=0xC2)
		break;
	} 
	       
	if(i==5)
		return SUCCESS ;        //MCU��NRF�ɹ����� 
	else
		return ERROR ;        //MCU��NRF����������
}

/**
  * @brief   ������NRF�ķ��ͻ�������д������
  * @param   
  *		@arg txBuf���洢�˽�Ҫ���͵����ݵ����飬�ⲿ����	
  * @retval  ���ͽ�����ɹ�����TXDS,ʧ�ܷ���MAXRT��ERROR
  */
u8 NRF2_Tx_Dat(u8 *txbuf)
{
	u8 state;  

	 /*ceΪ�ͣ��������ģʽ1*/
	NRF2_CE_LOW();

	/*д���ݵ�TX BUF ��� 32���ֽ�*/						
   SPI_NRF2_WriteBuf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);

      /*CEΪ�ߣ�txbuf�ǿգ��������ݰ� */   
 	 NRF2_CE_HIGH();
	  	
	  /*�ȴ���������ж� */                            
	while(NRF2_Read_IRQ()!=0); 	
	
	/*��ȡ״̬�Ĵ�����ֵ */                              
	state = SPI_NRF2_ReadReg(STATUS);

	 /*���TX_DS��MAX_RT�жϱ�־*/                  
	SPI_NRF2_WriteReg(NRF_WRITE_REG+STATUS,state); 	

	SPI_NRF2_WriteReg(FLUSH_TX,NOP);    //���TX FIFO�Ĵ��� 

	 /*�ж��ж�����*/    
	if(state&MAX_RT)                     //�ﵽ����ط�����
			 return MAX_RT; 

	else if(state&TX_DS)                  //�������
		 	return TX_DS;
	 else						  
			return ERROR;                 //����ԭ����ʧ��
} 

/**
  * @brief   ���ڴ�NRF�Ľ��ջ������ж�������
  * @param   
  *		@arg rxBuf �����ڽ��ո����ݵ����飬�ⲿ����	
  * @retval 
  *		@arg ���ս��
  */
u8 NRF2_Rx_Dat(u8 *rxbuf)
{
	u8 state; 
	NRF2_CE_HIGH();	 //�������״̬
	 /*�ȴ������ж�*/
	while(NRF2_Read_IRQ()==0) 
	{
    NRF2_CE_LOW();  	 //�������״̬
    /*��ȡstatus�Ĵ�����ֵ  */               
    state=SPI_NRF2_ReadReg(STATUS);
     
    /* ����жϱ�־*/      
    SPI_NRF2_WriteReg(NRF_WRITE_REG+STATUS,state);

    /*�ж��Ƿ���յ�����*/
    if(state&RX_DR)                                 //���յ�����
    {
      SPI_NRF2_ReadBuf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
         SPI_NRF2_WriteReg(FLUSH_RX,NOP);          //���RX FIFO�Ĵ���
      return RX_DR; 
    }
    else    
      return ERROR;                    //û�յ��κ�����
  }
  return ERROR;                    //û�յ��κ�����
}


/*********************************************END OF FILE**********************/
