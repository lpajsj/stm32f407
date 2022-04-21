#include "ads8361.h"
#include "ange_systick.h"
#include "ange_usart.h"
float ads8361a0,ads8361a1,ads8361b0,ads8361b1;
#if ADS8361_Sofeware_SPI
void ads8361_init()   //���Ӳ���
{
	GPIO_InitTypeDef gpioinit;
	
	RCC_APB2PeriphClockCmd(ads8361_OUTA_GPIO_CLK|ads8361_OUTB_GPIO_CLK|ads8361_M0_GPIO_CLK|ads8361_RD_GPIO_CLK|ads8361_CLOCK_GPIO_CLK|ads8361_RD_GPIO_CLK|ads8361_M1_GPIO_CLK|
ads8361_CS_GPIO_CLK|ads8361_A0_GPIO_CLK,ENABLE);//ʹ��PORTA,PORTEʱ��
	//RD
	gpioinit.GPIO_Pin  = ads8361_RD_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
 	GPIO_Init(ads8361_RD_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
	//CS
		gpioinit.GPIO_Pin  = ads8361_CS_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
 	GPIO_Init(ads8361_CS_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
	//clk
	gpioinit.GPIO_Pin  = ads8361_CLOCK_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
 	GPIO_Init(ads8361_CLOCK_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
  //A0
	gpioinit.GPIO_Pin  = ads8361_A0_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
 	GPIO_Init(ads8361_A0_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
	//outa��
	gpioinit.GPIO_Pin  = ads8361_OUTA_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���óɸ�������
 	GPIO_Init(ads8361_OUTA_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
	//////outb
	gpioinit.GPIO_Pin  = ads8361_OUTB_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���óɸ�������
 	GPIO_Init(ads8361_OUTB_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
	////MO 
	gpioinit.GPIO_Pin  = ads8361_M0_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���óɸ�������
 	GPIO_Init(ads8361_M0_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
	//M1
  gpioinit.GPIO_Pin  = ads8361_M1_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���óɸ�������
 	GPIO_Init(ads8361_M1_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4
//	M0=0;M1=0;A0=0; //ģʽһ  A0,B0˫ͨ��  A��B���  δ�ɹ�
	M0=0;M1=0;A0=0; //ģʽһ  A1,B1˫ͨ��  A��B���
//	MO=0;M1=1;A0=0; //ģʽ��  A0,B0˫ͨ��  A���
//	MO=0;M1=1;A0=1; //ģʽ��  A1,B1˫ͨ��  A���
//	MO=1;M1=0;A0=0; //ģʽ��  A0,A1,B0,B1��ͨ��  A��B���
//	M0=1;M1=1;A0=1; //ģʽ��  A0,A1,B0,B1��ͨ��  A���(˳��ΪA0,B0,A1,B1)

}
#endif
#if ADS8361_Hardware_SPI
void ads8361_init(void)   //���Ӳ���
{
	RCC_APB2PeriphClockCmd(ads8361_CS_GPIO_CLK|ads8361_A0_GPIO_CLK|ads8361_M0_GPIO_CLK,ENABLE);//ʹ��PORTA,PORTEʱ��	
	ADS8361_SPI_APBxClock_FUN(ADS8361_SPI_CLK,ENABLE);//��ʼ��SPI��ʱ��
/*-------------------GPIO��ʼ��-----------------------------------------------*/	
	//32��SPIʱ�ӣ�����Ϊ�����������
	GPIO_InitTypeDef ADS8361_GPIO_InitStructure;
	ADS8361_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	ADS8361_GPIO_InitStructure.GPIO_Pin=ADS8361_SPI_SCK_PIN;
	ADS8361_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ADS8361_SPI_SCK_PORT,&ADS8361_GPIO_InitStructure);
	//32��SPI������ţ�SOMI��������Ϊ�����������
	ADS8361_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	ADS8361_GPIO_InitStructure.GPIO_Pin=ADS8361_SPI_MOSI_PIN;
	ADS8361_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ADS8361_SPI_MOSI_PORT,&ADS8361_GPIO_InitStructure);	
	//32��SPI�������ţ�SOMO��������Ϊ��������
	ADS8361_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	ADS8361_GPIO_InitStructure.GPIO_Pin=ADS8361_SPI_MISO_PIN;
	GPIO_Init(ADS8361_SPI_MISO_PORT,&ADS8361_GPIO_InitStructure);	
	
	//CS
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Pin  = ads8361_CS_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
 	GPIO_Init(ads8361_CS_GPIO_PORT, &gpioinit);//
 //A0
	gpioinit.GPIO_Pin  = ads8361_A0_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
 	GPIO_Init(ads8361_A0_GPIO_PORT, &gpioinit);//
	////MO 
	gpioinit.GPIO_Pin  = ads8361_M0_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //
 	GPIO_Init(ads8361_M0_GPIO_PORT, &gpioinit);//
	//M1
  gpioinit.GPIO_Pin  = ads8361_M1_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //
 	GPIO_Init(ads8361_M1_GPIO_PORT, &gpioinit);//��ʼ��GPIOE2,3,4	
	A0=0;
	M0=0;
	M1=0;	
	
/*-------------------SPI��ʼ��-----------------------------------------------*/			
	SPI_InitTypeDef  ADS8361_SPI_InitStructure;
	ADS8361_SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;//�����ʵķ�Ƶ�������ʱ��ΪAPB2�ķ�Ƶ
	ADS8361_SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;//�ڶ������ز���
	ADS8361_SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;//����ʱSCKΪ�͵�ƽ
	ADS8361_SPI_InitStructure.SPI_CRCPolynomial=0;//��ʹ��CRC���ܣ���ֵ���д
	ADS8361_SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b ;//����λΪ8λ
	ADS8361_SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//˫��ȫ˫��
	ADS8361_SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//��λ����
	ADS8361_SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//��ģʽ
	ADS8361_SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//CSλ���������
	SPI_Init(ADS8361_SPIx,&ADS8361_SPI_InitStructure);//д�����õ��Ĵ���
	SPI_Cmd(ADS8361_SPIx,ENABLE);//ʹ��SPI	
}
uint32_t ADS8361_SPI_Read(void)
{
	uint32_t data=0;
	AD8361_CS=1;
	AD8361_CS=0;
	while(SPI_I2S_GetFlagStatus(ADS8361_SPIx,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(ADS8361_SPIx,0x80); //��Ҫ���ڷ���RD��convst����
	while(SPI_I2S_GetFlagStatus(ADS8361_SPIx,SPI_I2S_FLAG_RXNE)==RESET);
	data=SPI_I2S_ReceiveData(ADS8361_SPIx);		
	data*=256;
	while(SPI_I2S_GetFlagStatus(ADS8361_SPIx,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(ADS8361_SPIx,0x00);
	while(SPI_I2S_GetFlagStatus(ADS8361_SPIx,SPI_I2S_FLAG_RXNE)==RESET);
	data|=SPI_I2S_ReceiveData(ADS8361_SPIx);	//�������ݾ���ǰ16��ʱ�����ڵ�����	
//	data<<=8;
	while(SPI_I2S_GetFlagStatus(ADS8361_SPIx,SPI_I2S_FLAG_TXE)==RESET); //�������ֽڵ����ݴ�����Ϊ����ADS8361���ת�����ﵽ20��ʱ�����ڡ�������spi������ֻ�ܷ��������ֽڹ�24��ʱ������
	SPI_I2S_SendData(ADS8361_SPIx,0x00);
	while(SPI_I2S_GetFlagStatus(ADS8361_SPIx,SPI_I2S_FLAG_RXNE)==RESET);
  SPI_I2S_ReceiveData(ADS8361_SPIx);		
	AD8361_CS=1;
//	data=data>>5;
//	data&=0xffff;
	return data;
}

#endif
#if ADS8361_Sofeware_SPI
//int flag=0;
u32 ads8361_reada(void)
{
	unsigned char i;
	u32 A_Data = 0;
	
	AD8361_CS=0;
	RD = 1;
	CLOCK = 1;

	CLOCK = 0;

	RD = 0;
	
	for(i = 0;i < 18;i ++) //��ȡ16λADת�����ֵ����λ��ǰ������ÿ��һλ������
	{
			A_Data <<= 1;
			CLOCK = 1;
			A_Data|=ADATA;
//			if(ADATA)
//			{A_Data |= 0x01;}
			CLOCK = 0;

	}
	
	CLOCK = 1;

	CLOCK = 0;
//	SysTick_delayus(1);
	return A_Data;
}

u32 ads8361_readb(void)
{
	unsigned char i;
	u32 bdata = 0;
	
	AD8361_CS=0;
	RD = 1;
	CLOCK = 1;

	CLOCK = 0;

	RD = 0;
	
	for(i = 0;i < 18;i ++) //��ȡ16λADת�����ֵ����λ��ǰ������ÿ��һλ������
	{
			bdata<<=1;
			CLOCK = 1;
			{bdata |= BDATA;}
//			if(BDATA)
//			{bdata |= 0x01;}
			CLOCK = 0;

	}
	
	CLOCK = 1;

	CLOCK = 0;
AD8361_CS=1;
	return bdata;
}
uint64_t ads8361_readab(void)
{
	unsigned char i;
	u32 b = 0,a=0;
	uint64_t x=0;
	AD8361_CS=0;
	RD = 1;
	CLOCK = 1;
	CLOCK = 0;
	RD = 0;
	for(i = 0;i < 18;i ++) //��ȡ16λADת�����ֵ����λ��ǰ������ÿ��һλ������
	{
			b <<= 1;
		  a<<=1;
			CLOCK = 1;
			if(BDATA)
			{b |= 0x01;}
			if(ADATA)
			{
				a|=0x01;
			}
			CLOCK = 0;
	}
	
	CLOCK = 1;
	CLOCK = 0;
	x=a; //adata<<32������
	x<<=32;
	x+=b; //
	return x;
}
//���������ȡ��ʽ�Ѿ����������Ŵ������
void ads8361_read00a0() //
{
	 s32 ch1;
	M0=0;
	M1=0;
	A0=0;
		ch1=ads8361_reada();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361a0=ch1;
//			printf("%x ",ch1);
}
void ads8361_read00b0() //
{
	M0=0;
	M1=0;
	 s32 ch1;
	A0=0;
		ch1=ads8361_readb();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361b0=ch1;
	
}
void ads8361_read00a1() //
{
	 s32 ch1;
	A0=1;
	M0=0;
	M1=0;
		ch1=ads8361_reada();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361a1=ch1;
//					printf("%x ",ch1);
}
void ads8361_read00b1() //
{

	 s32 ch1;
	A0=1;
	M0=0;
	M1=0;
		ch1=ads8361_readb();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361b1=ch1;
}
//	M0=0;M1=0;A0=0; //ģʽһ  A0,B0˫ͨ��  A��B��� 
//	MO=0;M1=0;A0=1; //ģʽһ  A1,B1˫ͨ��  A��B���
void ads8361_read00(u8 a) //�������Ϊ A0״̬
{
	M0=0;
	M1=0;
	uint64_t ch;
	 s32 ch1,ch2;
	if(a==0)
	{
	A0=0;
	}
	else
	{
	A0=1;
	}
		ch=ads8361_readab();
			ch1=ch>>32;
			ch2=ch&0xfffff;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			if(a==0)
			{
				ads8361a0=ch1;  
		  }
			else
			{
				ads8361a1=ch1;
			}
			ch2&=0xffff;
			if(ch2&0x8000)
			{
				ch2&=0x7fff;
				ch2=0x7fff-ch2;
				ch2=-ch2;
			}
			if(a==0)
			{
				ads8361b0=ch2;  
		  }
			else
			{
				ads8361b1=ch2;
			}
}
//	MO=0;M1=1;A0=0; //ģʽ��  A0,B0˫ͨ��  A���
//	MO=0;M1=1;A0=1; //ģʽ��  A1,B1˫ͨ��  A���
void ads8361_read01(u8 a) //�������ΪA0״̬
{
	u8 i,x;
	s32 ch1;
	M0=0;
	M1=1;
	if(a==0)
	{
		A0=0;
	}
	else
	{
		A0=1;
	}
		for(i=0;i<2;i++)
		{

			ch1=ads8361_reada();

//			if(i==1)
//			{
//				A0=0;
//			}
			x=ch1>>16;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			if(a==0)
			{

				if(x==0)
				ads8361a0=ch1; 
				else
				ads8361b0=ch1;

			}				
			else
			{
				if(x==0)
				ads8361a1=ch1;
				else if(x==1)
				ads8361b1=ch1;
			}
		}
}
//	MO=1;M1=0;A0=0; //ģʽ��  A0,A1,B0,B1��ͨ��  A��B���
void ads8361_read10() //4ͨ���� ab��� nice
{
	u8 i,x;
	uint64_t ch;
	s32 ch1,ch2;
	M0=1;
	M1=0;
A0=1;
		for(i=0;i<2;i++)
		{
			ch=ads8361_readab();
			ch1=ch>>32;
			ch2=ch&0xfffff;
			x=ch1>>16;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			if(x==0)
				ads8361a0=ch1;
			else
				ads8361a1=ch1;
			x=ch2>>16;
			ch2&=0xffff;
			if(ch2&0x8000)
			{
				ch2&=0x7fff;
				ch2=0x7fff-ch2;
				ch2=-ch2;
			}
			if(x==0)
				ads8361b0=ch2;
			else
				ads8361b1=ch2;
			
		}
}
//	M0=1;M1=1;A0=1; //ģʽ��  A0,A1,B0,B1��ͨ��  A���(˳��ΪA0,B0,A1,B1)
void ads8361_read11() //��ͨ�� a��� nice
{
	u8 i;
	s32 ch1,x;
	M0=1;M1=1;
	A0=1;
		for(i=0;i<4;i++)
		{
			ch1=ads8361_reada();
//			if(i==3)
//			{
//				AD8361_CS=1;
//			}
			x=ch1>>16;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			switch(x)
			{
				
				case 0:
					ads8361a0=ch1;  
				break;
				case 1:
					ads8361b0=ch1;  
				break;
				case 2:
					ads8361a1=ch1;  
				break;
				case 3:
					ads8361b1=ch1; 
				break;
				default: break;					
			}
		}
}
/////////////���صĸİ�
void ADS8361_Read_01_OUTA(uint32_t CH,uint32_t *data_a_01,uint32_t *data_b_01)//��M0M1=01�£���ȡAͨ��������
{
	M0=0;
	M1=1;
	uint32_t dat=0,temp=0;
	uint32_t i;
	CLOCK=0;//
  AD8361_CS=0;
	RD=1;
	CLOCK = 1;
	if(CH==0)
		A0=0;
	else
		A0=1;	
	CLOCK=0;//
	CLOCK = 1;
	RD=0;//RDҪ����ѭ��ǰ������ѭ����CH1��������
	for(i=0;i<18;i++)
	{
		dat<<=1;
	CLOCK=0;//
		temp=ADATA;
		if(temp==1)
			dat|=1;
CLOCK = 1;
	}
	CLOCK=0;//
	CLOCK = 1;
	CLOCK=0;//
	dat=0;//��һ�ζ�������û�õ�����,ֱ�Ӳ�Ҫ
	
	RD=1;
	CLOCK = 1;
	CLOCK=0;//
	CLOCK = 1;
	RD=0;
	for(i=0;i<18;i++)
	{
		dat<<=1;
	CLOCK=0;//
		temp=ADATA;
		if(temp==1)
			dat|=1;
	CLOCK = 1;
	}
	CLOCK=0;//
	CLOCK = 1;
	CLOCK=0;//
	if((dat&0x30000)==0x00000)//�����־λ��Aͨ���ģ������ݸ�A
	{*data_a_01=dat;dat=0;}
	else if((dat&0x30000)==0x10000)//�����־λ��Bͨ���ģ������ݸ�B
	{*data_b_01=dat;dat=0;}
	else
		dat=0;
		
	RD=1;
	CLOCK = 1;
	CLOCK=0;//
	CLOCK = 1;
	RD=0;
	for(i=0;i<18;i++)
	{
		dat<<=1;
	CLOCK=0;//
		temp=ADATA;
		if(temp==1)
			dat|=1;
	CLOCK = 1;
	}
	CLOCK=0;//
	CLOCK = 1;
	CLOCK=0;//
	if((dat&0x30000)==0x00000)//�����־λ��Aͨ���ģ������ݸ�A
	{*data_a_01=dat;dat=0;}
	else if((dat&0x30000)==0x10000)//�����־λ��Bͨ���ģ������ݸ�B
	{*data_b_01=dat;dat=0;}
	else
		dat=0;				
	AD8361_CS=1;
}
#endif
