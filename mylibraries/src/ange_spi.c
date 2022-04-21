#include "ange_spi.h"
#include "ange_usart.h"
#define ange_SPI_timeout 1000
//ע�Ⲣδ������֤
void ange_SPI_GPIO_Congfig()
{
	GPIO_InitTypeDef gpioinit;
	//////����spi��ʱ��
	ange_SPI_APBxClock(ange_SPI_CLK,ENABLE);
	///����gpioʱ��
	ange_SPI_CS_APBxClock(ange_SPI_CS_CLK|ange_SPI_SCK_CLK|ange_SPI_MISO_CLK|ange_SPI_MOSI_CLK,ENABLE);
	///cs
	gpioinit.GPIO_Mode=GPIO_Mode_AF;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpioinit.GPIO_Pin=ange_SPI_CS_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_SPI_CS_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_CS_PORT,ange_SPI_CS_PinSource,GPIO_AF_SPI1);
	//
	gpioinit.GPIO_Mode=GPIO_Mode_AF;
	gpioinit.GPIO_Pin=ange_SPI_SCK_Pin;
	GPIO_Init(ange_SPI_SCK_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_SCK_PORT,ange_SPI_SCK_PinSource,GPIO_AF_SPI1);
	///
	gpioinit.GPIO_Pin=ange_SPI_MISO_Pin;
	GPIO_Init(ange_SPI_MISO_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_MISO_PORT,ange_SPI_MISO_PinSource,GPIO_AF_SPI1);
	//
	gpioinit.GPIO_Pin=ange_SPI_MOSI_Pin;
	GPIO_Init(ange_SPI_MOSI_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_MOSI_PORT,ange_SPI_MOSI_PinSource,GPIO_AF_SPI1);
}
void ange_SPI_Config()
{
	SPI_InitTypeDef spiinit;
	spiinit.SPI_Mode=SPI_Mode_Master;  //spi��ģʽ ��Ϊ��master ��slave
	spiinit.SPI_Direction=SPI_Direction_2Lines_FullDuplex; //���䷽��
	spiinit.SPI_DataSize=SPI_DataSize_8b;  //������ʽ 8bits ��16bits
	spiinit.SPI_CPOL=SPI_CPOL_High;    //sck���е�ƽ
	spiinit.SPI_CPHA=SPI_CPHA_2Edge;   //���ݲ������ڵ�һ�����ǵڶ����仯��ƽ
	spiinit.SPI_NSS=SPI_NSS_Soft;   //cs�������������Ӳ������
	spiinit.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;  //������Ԥ��Ƶ  spi1����APB2������
	spiinit.SPI_FirstBit=SPI_FirstBit_MSB;  //С��ģʽ���Ǵ��ģʽ
	spiinit.SPI_CRCPolynomial=7;   //crc 
	SPI_Init(ange_SPIx,&spiinit);
	SPI_Cmd(ange_SPIx,ENABLE);
}
void ange_SPI_ERROR(u8 x)
{
	printf("spi����%d",x);
}
u8 ange_SPI_sendbyte(u8 x)
{
	u16 t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(0);
			return 0xff;
		}
	}
	SPI_I2S_SendData(ange_SPIx,x);
	t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPIx);
	return x;
}
u16 ange_SPI_send2byte(u16 x)
{
	u16 t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(0);
			return 0xffff;
		}
	}
	SPI_I2S_SendData(ange_SPIx,x);
	t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPIx);
	return x;
}
///
#define ange_SPI2_timeout 1000
//ע�Ⲣδ������֤
void ange_SPI2_GPIO_Congfig()
{
	GPIO_InitTypeDef gpioinit;
	//////����spi��ʱ��
	ange_SPI2_APBxClock(ange_SPI2_CLK,ENABLE);
	///����gpioʱ��
	ange_SPI2_CS_APBxClock(ange_SPI2_CS_CLK|ange_SPI2_SCK_CLK|ange_SPI2_MISO_CLK|ange_SPI2_MOSI_CLK,ENABLE);
	///cs
	gpioinit.GPIO_Mode=GPIO_Mode_OUT;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpioinit.GPIO_Pin=ange_SPI2_CS_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(ange_SPI2_CS_PORT,&gpioinit);
//	GPIO_PinAFConfig(ange_SPI_CS_PORT,ange_SPI2_CS_PinSource,GPIO_AF_SPI2);
	//
	gpioinit.GPIO_Mode=GPIO_Mode_AF;
	gpioinit.GPIO_Pin=ange_SPI2_SCK_Pin;
	GPIO_Init(ange_SPI2_SCK_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI2_SCK_PORT,ange_SPI2_SCK_PinSource,GPIO_AF_SPI2);
	///
	gpioinit.GPIO_Pin=ange_SPI2_MISO_Pin;
	GPIO_Init(ange_SPI2_MISO_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI2_MISO_PORT,ange_SPI2_MISO_PinSource,GPIO_AF_SPI2);
	//
	gpioinit.GPIO_Pin=ange_SPI2_MOSI_Pin;
	GPIO_Init(ange_SPI2_MOSI_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI2_MOSI_PORT,ange_SPI2_MOSI_PinSource,GPIO_AF_SPI2);
}
void ange_SPI2_Config()
{
	SPI_InitTypeDef spiinit;
	spiinit.SPI_Mode=SPI_Mode_Master;  //spi��ģʽ ��Ϊ��master ��slave
	spiinit.SPI_Direction=SPI_Direction_2Lines_FullDuplex; //���䷽��
	spiinit.SPI_DataSize=SPI_DataSize_8b;  //������ʽ 8bits ��16bits
	spiinit.SPI_CPOL=SPI_CPOL_Low;    //MS5611��Ҫ
	spiinit.SPI_CPHA=SPI_CPHA_1Edge;   //MS5611��Ҫ
//	spiinit.SPI_CPOL=SPI_CPOL_High;    //sck���е�ƽ
//	spiinit.SPI_CPHA=SPI_CPHA_2Edge;   //���ݲ������ڵ�һ�����ǵڶ����仯��ƽ
	spiinit.SPI_NSS=SPI_NSS_Soft;   //cs�������������Ӳ������
	spiinit.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;  //������Ԥ��Ƶ  spi1����APB2������
	spiinit.SPI_FirstBit=SPI_FirstBit_MSB;  //С��ģʽ���Ǵ��ģʽ
	spiinit.SPI_CRCPolynomial=7;   //crc 
	SPI_Init(ange_SPI2x,&spiinit);
	SPI_Cmd(ange_SPI2x,ENABLE);
}
void ange_SPI2_ERROR(u8 x)
{
	printf("spi����%d",x);
}
u8 ange_SPI2_sendbyte(u8 x)
{
	u16 t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(0);
			return 0xff;
		}
	}
	SPI_I2S_SendData(ange_SPI2x,x);
	t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPI2x);
	return x;
}
u16 ange_SPI2_send2byte(u16 x)
{
	u16 t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(0);
			return 0xffff;
		}
	}
	SPI_I2S_SendData(ange_SPI2x,x);
	t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPI2x);
	return x;
}
///spi3����������

/*::::::::::::::::::::::::::::::::::::
** ��������: void SPI3_Init(void)
** ��������: SPI3��ʼ��
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void SPI3_Init(void)
{	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);//ʹ��SPI1ʱ��
 
  //GPIOFB3,4,5��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI3); //PB3����Ϊ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI3); //PB4����Ϊ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI3); //PB5����Ϊ SPI1
 
	//����ֻ���SPI�ڳ�ʼ��
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);//��λSPI1
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,DISABLE);//ֹͣ��λSPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI3, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI3, ENABLE); //ʹ��SPI����	
}   
/*::::::::::::::::::::::::::::::::::::
** ��������: void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
** ��������: ����SPI3�����ٶ�
** ���������� SPI_BaudRatePrescalerʱ�ӷ�Ƶϵ��
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI3->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI3->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI3,ENABLE); //ʹ��SPI1
} 
/*::::::::::::::::::::::::::::::::::::
** ��������: u8 SPI3_ReadWriteByte(u8 TxData)
** ��������: SPI3����һ���ֽ�
** ����������TxData�����ֽ�
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
u8 SPI3_ReadWriteByte(u8 TxData)
{		 			 

  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){;}//�ȴ���������  
	
	SPI_I2S_SendData(SPI3, TxData); //ͨ������SPIx����һ��byte  ����
		
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){;} //�ȴ�������һ��byte  
 
	return SPI_I2S_ReceiveData(SPI3); //����ͨ��SPIx������յ�����		    
}


