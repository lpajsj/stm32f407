#include "ad7799.h"
#include "ange_systick.h"
#include "stdio.h"

#if Sofeware_SPI
void AD7799_GPIO_Init(void)//AD7799���ų�ʼ��
{
	RCC_APB2PeriphClockCmd(AD_RCC,ENABLE);//����GPIO��ʱ��
	
	GPIO_InitTypeDef AD7799_GPIO_InitStruction;
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//����CSΪ�������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_CS_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_CS_GPIO,&AD7799_GPIO_InitStruction);
	
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//����DIΪ�������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_DI_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_DI_GPIO,&AD7799_GPIO_InitStruction);
	
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//����SCKΪ�������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_SCK_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_SCK_GPIO,&AD7799_GPIO_InitStruction);	

	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����DOΪ��������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_DO_PIN;
	GPIO_Init(AD_SCK_GPIO,&AD7799_GPIO_InitStruction);	
}
/*****************************************************************************************************
���ã�ʹAD7799�ĹܽŴ���Ĭ��״̬
˵����ʹ��AD7799ǰҪ��CS���㣬DI��1
*****************************************************************************************************/
void spi_ad7799_init(void)
{
	AD_CS_0();
	AD_DI_1();
	AD_SCK_1();
	SysTick_delayms(10);
}
/*****************************************************************************************************
���ã���AD7799д����
������*buf-Ҫд����������飬num-Ҫд������ݸ���
˵����AD7799һ�ν���һ�ֽڣ��ߵ�ƽ�������ݣ��͵�ƽҪ�������ȶ������ȷ��͸�λ
*****************************************************************************************************/
void AD7799_Write(uint8_t *buf,uint8_t num)
{
	uint8_t dat;
	uint8_t i,j;
	
	AD_SCK_1();
	__nop();
//	AD_CS_1();  ��д�����в���Ҫ��CS�Ĳ���
//	__nop();
//	AD_CS_0();
	__nop();
	
	for(j=0;j<num;j++)
	{
		dat=*(buf+j);
		for(i=0;i<8;i++)
		{
			AD_SCK_0();
			if(0x80 == (dat & 0x80))
			AD_DI_1();
			else
			AD_DI_0();
			__nop();
			AD_SCK_1();
			__nop();
			dat<<=1;
		}
	}
//	AD_CS_1();//�ر�Ƭѡ�������
}
/*****************************************************************************************************
���ã���AD7799����
������*buf-�������ݵĴ�����飬num-Ҫ�������ݸ���
˵����AD7799�͵�ƽ������ݣ��ߵ�ƽ�ȶ����ݣ��ȶ�ȡ��λ
*****************************************************************************************************/
void AD7799_Read(uint8_t *buf,uint8_t num)//��AD7799����
{
	uint8_t dat=0,temp=0;
	
	uint8_t i,j;	
	
	AD_SCK_1();
	__nop();
//	AD_CS_1();
//	__nop();
//	AD_CS_0();	
	
	for(j=0;j<num;j++)
	{
		for(i=0;i<8;i++)
		{
			AD_SCK_0();
			dat<<=1;//ע�����Ʒ�ǰ��
			temp=AD_DO;
			if(temp==1)
				dat|=1;			
			AD_SCK_1();
			__nop();
		}
		*(buf+j)=dat;
	}
//	AD_CS_1();	
}
#endif
#if Hardware_SPI
void AD7799_GPIO_Init(void)
{
	AD7799_SPI_GPIO_APBxClock_FUN(AD7799_SPI_GPIO_CLK,ENABLE);//��ʼ��SPI���ŵ�ʱ��	
	AD7799_SPI_APBxClock_FUN(RCC_APB1Periph_SPI2,ENABLE);//��ʼ��SPI��ʱ��
	
/*-------------------GPIO��ʼ��-----------------------------------------------*/		
	//32��SPIʱ�ӣ�����Ϊ�����������
	GPIO_InitTypeDef AD7799_GPIO_InitStructure;
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_SCK_PIN;
	AD7799_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD7799_SPI_SCK_PORT,&AD7799_GPIO_InitStructure);
	//32��SPI������ţ�SOMI��������Ϊ�����������
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_MOSI_PIN;
	AD7799_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD7799_SPI_MOSI_PORT,&AD7799_GPIO_InitStructure);	
	//32��SPI�������ţ�SOMO��������Ϊ��������
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_MISO_PIN;
	GPIO_Init(AD7799_SPI_MISO_PORT,&AD7799_GPIO_InitStructure);	

	//��ʼ��CS���ţ�ʹ��������ƣ�����ֱ�����ó��������
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_CS_PIN;
	GPIO_Init(AD7799_SPI_CS_PORT,&AD7799_GPIO_InitStructure);		

/*-------------------SPI��ʼ��-----------------------------------------------*/		
	SPI_InitTypeDef  AD7799_SPI_InitStructure;
	AD7799_SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;//�����ʵķ�Ƶ�������ʱ��ΪAPB1�����з�Ƶ��ʱ18M,�������4��Ƶ�ſ���
	AD7799_SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;//�ڶ������ز���
	AD7799_SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;//����ʱSCKΪ�ߵ�ƽ
	AD7799_SPI_InitStructure.SPI_CRCPolynomial=0;//��ʹ��CRC���ܣ���ֵ���д
	AD7799_SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//����λΪ8λ
	AD7799_SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//˫��ȫ˫��
	AD7799_SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//��λ����
	AD7799_SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//��ģʽ
	AD7799_SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//CSλ���������
	SPI_Init(AD7799_SPIx,&AD7799_SPI_InitStructure);//д�����õ��Ĵ���
	SPI_Cmd(AD7799_SPIx,ENABLE);//ʹ��SPI
}
uint8_t AD7799_Data[3]={0};
uint8_t AD7799_SendData[3]={0};
void AD7799_DMA(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//����DMA1��ʱ��
	/*-------------------����DMA��ʼ��-----------------------------------------------*/
	DMA_InitTypeDef ADC_DMA_InitStruction;
	ADC_DMA_InitStruction.DMA_BufferSize=3;//һ�δ���3��
	ADC_DMA_InitStruction.DMA_DIR=DMA_DIR_PeripheralSRC;//����ΪԴ
	ADC_DMA_InitStruction.DMA_M2M=DMA_M2M_Disable;//�رմ洢���洢
	ADC_DMA_InitStruction.DMA_MemoryBaseAddr=(uint32_t)AD7799_Data;//�洢���ĵ�ַ
	ADC_DMA_InitStruction.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;//8λ
	ADC_DMA_InitStruction.DMA_MemoryInc=DMA_MemoryInc_Enable;//��ַ����
	ADC_DMA_InitStruction.DMA_Mode=DMA_Mode_Circular;//����ѭ������
	ADC_DMA_InitStruction.DMA_PeripheralBaseAddr=(uint32_t)(&(SPI2->DR));//ADC���ݵ�ַ
	ADC_DMA_InitStruction.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//8λ
	ADC_DMA_InitStruction.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//�����ַ����
	ADC_DMA_InitStruction.DMA_Priority=DMA_Priority_High;//�����ȼ�
	DMA_Init(DMA1_Channel4,&ADC_DMA_InitStruction);
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
	/*-------------------����DMA��ʼ��-----------------------------------------------*/
	ADC_DMA_InitStruction.DMA_BufferSize=3;//һ�δ���3��
	ADC_DMA_InitStruction.DMA_DIR=DMA_DIR_PeripheralDST;//����ΪԴ
	ADC_DMA_InitStruction.DMA_M2M=DMA_M2M_Disable;//�رմ洢���洢
	ADC_DMA_InitStruction.DMA_MemoryBaseAddr=(uint32_t)AD7799_SendData;//�洢���ĵ�ַ
	ADC_DMA_InitStruction.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;//8λ
	ADC_DMA_InitStruction.DMA_MemoryInc=DMA_MemoryInc_Enable;//��ַ����
	ADC_DMA_InitStruction.DMA_Mode=DMA_Mode_Circular;//����ѭ������
	ADC_DMA_InitStruction.DMA_PeripheralBaseAddr=(uint32_t)(&(SPI2->DR));//ADC���ݵ�ַ
	ADC_DMA_InitStruction.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//8λ
	ADC_DMA_InitStruction.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//�����ַ����
	ADC_DMA_InitStruction.DMA_Priority=DMA_Priority_High;//�����ȼ�
	DMA_Init(DMA1_Channel5,&ADC_DMA_InitStruction);
	SPI_I2S_DMACmd(AD7799_SPIx,SPI_I2S_DMAReq_Tx|SPI_I2S_DMAReq_Rx,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);	
	
}
/*****************************************************************************************************
���ã���AD7799д����
������*buf-Ҫд����������飬num-Ҫд������ݸ���
˵����AD7799һ�ν���һ�ֽڣ��ߵ�ƽ�������ݣ��͵�ƽҪ�������ȶ������ȷ��͸�λ
*****************************************************************************************************/
static u8 SPIByte(u8 byte)
{
	while(SPI_I2S_GetFlagStatus(AD7799_SPIx,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(AD7799_SPIx,byte);
	
	while(SPI_I2S_GetFlagStatus(AD7799_SPIx,SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(AD7799_SPIx);
}
void AD7799_Write(u8 * buffer,u8 num)
{
	int i=0;
	for(i=0;i<num;i++)
	SPIByte(buffer[i]);
}
/*****************************************************************************************************
���ã���AD7799����
������*buf-�������ݵĴ�����飬num-Ҫ�������ݸ���
˵����AD7799�͵�ƽ������ݣ��ߵ�ƽ�ȶ����ݣ��ȶ�ȡ��λ
*****************************************************************************************************/
void AD7799_Read(u8 * buffer,u8 size)
{
	int i=0;
	for(i=0;i<size;i++)
	buffer[i]=SPIByte(0x00);
}
#endif
/*****************************************************************************************************
���ã�дAD7799�Ĵ���
������regAddress-�Ĵ�����ַ��regValue-д������ݣ�size-д������ݵ��ֽ���
˵������AD7799д�Ĵ���������Ҫ��дͨ�żĴ�����д��ͨ�żĴ��������ݾ���Ҫд��ļĴ���
*****************************************************************************************************/
void AD7799_SetRegisterValue(uint8_t regAddress,uint32_t regValue,uint8_t size)//дAD7799�Ĵ���
{
	uint8_t data[5]={0};//30
	data[0]=data[0] = AD7799_COMM_WRITE |  AD7799_COMM_ADDR(regAddress);//ͨ�żĴ���������
	if(size==1)
	{
		data[1] = (uint8_t)regValue;
	}
	else if(size == 2)
	{
		data[1] = (uint8_t)((regValue&0x00ff00)>>8);
		data[2] = (uint8_t)(regValue&0x0000ff);
	}
	else
	{
		data[1] = (uint8_t)((regValue & 0xFF0000) >> 16);	
		data[2] = (uint8_t)((regValue & 0x00FF00) >> 8);
    data[3] = (uint8_t)((regValue & 0x0000FF) >> 0);    	
	}
	AD_CS_1();
	AD_CS_0();
	AD7799_Write(data,size+1);//��ΪҪ��дͨ�żĴ���������д�������+1
	AD_CS_1();
}	
/*****************************************************************************************************
���ã���AD7799�Ĵ���
������regAddress-�Ĵ�����ַ��size-��ȡ�����ݵ��ֽ���
˵������AD7799д�Ĵ���������Ҫ��дͨ�żĴ�����д��ͨ�żĴ��������ݾ���Ҫ��ȡ�ļĴ���
*****************************************************************************************************/
uint32_t AD7799_GetRegisterValue(uint8_t regAddress, uint8_t size)   //��AD7799�Ĵ���
{
	uint8_t corresspond_data=0;//ͨ�żĴ�������
	uint8_t data[4]={0};//����������
	uint32_t receivedData = 0x00;//��󷵻ص�����
	corresspond_data = AD7799_COMM_READ |  AD7799_COMM_ADDR(regAddress);
	
	AD_CS_1();
	AD_CS_0();	
	AD7799_Write(&corresspond_data,1);//1.��дͨ�żĴ���
	AD7799_Read(data,size);//2.���Ĵ�����ֵ
	AD_CS_1();////////////////////////
	
	if(size == 1)
	{
		receivedData = data[0];
	}
	else if(size == 2)
	{
		receivedData |= (data[0] << 8);
		receivedData |= (data[1] << 0);
	}
	else
	{
		receivedData |= (data[0] << 16);
		receivedData |= (data[1] << 8);
		receivedData |= (data[2] << 0);
	}
	 return receivedData;
}
/*****************************************************************************************************
���ã���AD7799��ID
˵����AD7799��IDΪ0xx9
����ֵ�������0xx9���򷵻�success�����򷵻�ERROR
*****************************************************************************************************/
uint8_t AD7799_Init(void)//��AD7799��ID
{
	uint8_t status = 0x1;
	uint8_t ID;
	ID=AD7799_GetRegisterValue(AD7799_REG_ID,1);
	printf("%d\r\n",ID);
	if((ID&0x0f)!=AD7799_ID)
		status= 0x0;
	return status;
}
/*****************************************************************************************************
���ã���λAD7799
˵��������32λ��1��λAD7799
*****************************************************************************************************/
void AD7799_Reset(void)//��λAD7799
{
	uint8_t dataToSend[4] = {0xff, 0xff, 0xff, 0xff};
	AD_CS_1();
	AD_CS_0();		
	AD7799_Write(dataToSend,4);
	AD_CS_1();
}
/*****************************************************************************************************
���ã���״̬�Ĵ����е�RDYλ
˵�������RDYΪ1����ת��δ��ɣ�RDYΪ0����ת�����
����ֵ��ת�����-1��ת��δ���-0
*****************************************************************************************************/
uint8_t AD7799_Ready(void)//��״̬�Ĵ����е�RDYλ
{
	uint8_t rdy = 0;
	rdy=(AD7799_GetRegisterValue( AD7799_REG_STAT,1) & 0x80);   
	return(!rdy);
}
/*****************************************************************************************************
���ã�����AD7799��ģʽ
������mode-ģʽ�Ĵ�����MD2 MD1 MD0��13-15λ����ѡ��ģʽ
*****************************************************************************************************/
void AD7799_SetMode(uint16_t mode)//����AD7799��ģʽ
{
	uint16_t command;
	command = AD7799_GetRegisterValue(AD7799_REG_MODE,2);//��ȡԭ��ģʽ�Ĵ���������
	command &= ~AD7799_MODE_SEL(0xFF);//����13-15λ���㣬��λ���ֲ���
	command |= AD7799_MODE_SEL(mode);//����13-15λ��ΪҪд���ģʽ
  AD7799_SetRegisterValue(AD7799_REG_MODE, command,2);//д��ģʽ�Ĵ���	
}

/*****************************************************************************************************
���ã���ѡAD7799��ͨ��λ
������channel-���üĴ�����HD2 HD1 HD0��0-2λ��
*****************************************************************************************************/
void AD7799_SetChannel(uint16_t channel)//��ѡAD7799��ͨ��λ
{
   uint16_t command;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//��ȡ���üĴ����������ֽڵ�����
    command &= ~AD7799_CONF_CHAN(0xFF);//����0-2λ���㣬��λ���ֲ���
    command |= AD7799_CONF_CHAN(channel);////����0-2λ��ΪҪд���ͨ��
    AD7799_SetRegisterValue(AD7799_REG_CONF, command,2);//д�����üĴ���
}
/*****************************************************************************************************
���ã�����AD7799����
������gain-���üĴ�����G2 G1 G0��8-10λ��
˵������Ӧ�ķŴ����ο��ֲ�
*****************************************************************************************************/
void AD7799_SetGain(uint16_t gain)//����AD7799����
{
    uint16_t command;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//��ȡ���üĴ����������ֽڵ�����
    command &= ~AD7799_CONF_GAIN(0xFF);//����8-10λ������ѡ��λ�����㣬��λ���ֲ���
    command |= AD7799_CONF_GAIN(gain);//����8-10λ������ѡ��λ����ΪҪ�Ŵ������
    AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);//д�����üĴ��� 
}
/*****************************************************************************************************
���ã���������òο���������
������state-1-������state-0-�ر�
˵�������ο���ѹ��·����С��0.5Vʱ��״̬�Ĵ�����NOREF����ָʾ��
*****************************************************************************************************/
void AD7799_SetReference(uint16_t state)//��������òο���������
{
    uint16_t command = 0;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//��ȡ���üĴ����������ֽڵ�����
    command &= ~AD7799_CONF_REFDET(1);//����5λ���ο�����ʹ��λ�����㣬����λ���ֲ���
    command |= AD7799_CONF_REFDET(state);//����5λ���ο�����ʹ��λ����Ϊ�������ֹ״̬
    AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);//д�����üĴ���			
}


/*****************************************************************************************************
���ã�ͨ��У׼
������t-ͨ��
˵����
*****************************************************************************************************/
void AD7799_Calibrate(u8 t)//ͨ��У׼
{
	u16 command,x;
	x=AD7799_GetRegisterValue(AD7799_REG_MODE,2);
	SysTick_delayms(5);////////////////////
	AD7799_SetChannel(t);
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(4);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);SysTick_delayms(5);//�ڲ���̶�У��
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(5);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);SysTick_delayms(5);//�ڲ����̶�У��
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(6);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);SysTick_delayms(5);//ϵͳ��̶�У��
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(7);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);SysTick_delayms(5);//ϵͳ���̶�У��
	AD7799_SetRegisterValue(AD7799_REG_IO,0,1);//����ͨ��3 Ϊad����
}
/*****************************************************************************************************
���ã��ٶ�����
������x-���ٶȵĴ���
*****************************************************************************************************/
void AD7799_Speed(u8 x) //16.7hz��10
{
	u16 command;
	command=AD7799_GetRegisterValue(AD7799_REG_MODE,2);
	command&=~AD7799_MODE_RATE(0xff);
	command|=AD7799_MODE_RATE(x);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
}
/*****************************************************************************************************
���ã�������ģʽ����Ӧ����
������x-���ٶȵĴ���
˵��������������ģʽ�󣬲����ٸ�AD7799�����ݣ�ֻ��ֱ�Ӷ�����
��������ת��ֱ�ӵ����º�����ɳ�ʼ��
AD7799_CReadMode(0)

ת��ͨ�������´��룺
AD7799_CReadMode(0);
ad1=AD7799_CRead();

AD7799_CReadMode(1);
ad2=AD7799_CRead();
	
AD7799_CReadMode(2);
ad3=AD7799_CRead();
��ת��ֱ�Ӷ���
ad1=AD7799_CRead();
*****************************************************************************************************/
void AD7799_CReadMode(uint8_t CH)//����������ģʽ
{
	
	uint8_t corresspond_data=0;
	
	AD7799_REG_Init(CH);//��Ϊ����������ģʽ���˲��������Ըɴิλ��ʼ��
	
	AD_CS_1();
	AD_CS_0();	
	corresspond_data=0x5c;
	AD7799_Write(&corresspond_data,1);//������ģʽ
}
uint8_t AD7799_Date[3]={0};
uint16_t AD7799_CRead(void)//������ģʽ�Ķ�ȡAD7799
{
	uint8_t times=5;
	uint16_t ad=0;
	while(times--)
	{
		if(AD_DO==0)//���D0��Ϊ�͵�ƽ��ת�����
		{
			AD7799_Read(AD7799_Date,3);//��ȡ����
			ad=AD7799_Date[0];
			ad=ad*256;//�˱����ƿ���0.03us
			ad+=AD7799_Date[1];
			return ad;
		}
		SysTick_delayms(59);
	}	
	return 0;
}
void AD7799_TUIRead(void)//�˳�������ģʽ�����ǲ�����
{
	uint8_t corresspond_data=0x58;
	AD7799_Write(&corresspond_data,1);
}
/*****************************************************************************************************
���ã�����ת����ģʽ�Ķ�ȡ
������x-���ٶȵĴ���
*****************************************************************************************************/
uint32_t AD7799_SRead(void)//����ת����ģʽ�Ķ�ȡ
{
	uint32_t times=5,ad=0;
	u16 command=0x200a;//16.7HZ,����ת������
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
	while(times--)
	{
		if(AD7799_Ready())
		{
			ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
			return ad;
		}
		SysTick_delayms(60);
	}	
	return 0;
}
/*****************************************************************************************************
���ã�AD7799���ܳ�ʼ��
*****************************************************************************************************/
void AD7799_REG_Init(uint8_t CH) //���üĴ��������ջٵ��� ��˫���� ����ģʽ
{
	u16 command=0;
		////psw��һ����Դ
#if Sofeware_SPI	
	spi_ad7799_init();	
#endif	
	AD7799_Reset();
	command|=AD7799_MODE_PSW;
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
	command=AD7799_GetRegisterValue(AD7799_REG_CONF,2);
	//�����ԣ����屣��
	command&=~(AD7799_CONF_UNIPOLAR(1)|AD7799_CONF_BUF);
	command|=(AD7799_CONF_UNIPOLAR(1)|AD7799_CONF_BUF);
	AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);
	//�����ο���������
	AD7799_SetReference(1);
	 //�ɼ��ٶ�����
	AD7799_Speed(10);
	 //AD7799��������
	AD7799_SetGain(AD7799_GAIN_1); 
	 //AD7799ͨ��У׼
	AD7799_Calibrate(0);
	AD7799_Calibrate(1);
	AD7799_Calibrate(2);   
	AD7799_SetChannel(CH);
	//ģʽ���ã�����ת��ģʽ
	AD7799_SetMode(AD7799_MODE_CONT); 
}
/*****************************************************************************************************
���ã���ȡ����AD7799
����ֵ��16λ������
*****************************************************************************************************/
uint32_t readad1(void)//���ζ�AD7799����
{
	uint32_t times=10,ad=0;//������ڶ��������Ͳ�����
	while(times--)
	{
		if(AD7799_Ready())
		{
			ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
			ad=ad/256;
			return ad;
		}
		SysTick_delayms(60);//��ʱһ��ת������
	}
	AD7799_REG_Init(1);//���������������Ǿ��ǿ����ˣ����и�λ,ֻ�ܽ��һ��������
	times=10;
	while(times--)//�����������п��ܾͿ����ˣ����Ը�λ
	{
		if(AD7799_Ready())
		{
			ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
			ad=ad/256;
			return ad;
		}
		SysTick_delayms(60);
	}
	return 0;
}
/*****************************************************************************************************
���ã�16��ƽ���˲�����
����ֵ��16λ������
*****************************************************************************************************/
u16 readad16(void)//AD779916���˲�����
{
	uint32_t times=1000,i=0,ad;
	u32 sum=0;
	for(i=0;i<16;i++)
	{
		times=1000;
		while(times--)
		{
			if(AD7799_Ready())
			{
				ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
				ad>>=8;
				times=0;
				sum+=ad;
			}
			else
			{
			}
			SysTick_delayms(1);
		}	
	}
	sum=sum/16;
	return sum;
}


/********************
fir �˲�
����ֵ��Ϊ�˲�ֵ
���ڸտ�ʼ���ݸ����޷����㣬�����ñ�־λfir_b�ж�,�����ص�ǰ�յ�����ƽ��ֵ
		AD7799_SetChannel(0);
		while(!AD7799_Ready());
		AD=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
		AD7799_ProcessValue=fir_lvbo(AD,1);
		if(fir_b1==1)	
		{
			printf("ͨ��1��%lf  \n",AD7799_ProcessValue*5/16777215);
		} 
*****************/
#define fir_cishu 10
double fir_jilu1[fir_cishu];//1ͨ�����ݵ�����
u8 fir_jishu1=0;//1ͨ��������
u8 fir_b1=0;//1ͨ�����FIR�˲��ı�־
/////////
double fir_jilu2[fir_cishu];//2ͨ�����ݵ�����
u8 fir_jishu2=0;//2ͨ��������
u8 fir_b2=0;//2ͨ�����FIR�˲��ı�־
///////
double fir_jilu3[fir_cishu];//3ͨ�����ݵ�����
u8 fir_jishu3=0;//3ͨ��������
u8 fir_b3=0;//3ͨ�����FIR�˲��ı�־

double fir_lvbo(uint32_t x,u8 t)
{
	u8 i;
	double sum=0;
	if(t==1)  //ͨ��1��FIR�˲�
	{
		fir_jilu1[fir_jishu1]=x;//�������鸳ֵ
		fir_jishu1++;//�����Ӽ�
		if(fir_jishu1==fir_cishu)//�������Ϊ10����λ��־
		{
			fir_jishu1=0;
			fir_b1=1;
		}
		if(fir_b1==1)//�����������10
		{
			for(i=0;i<fir_cishu;i++)
			{
				sum+=fir_jilu1[i];
			}
			return sum/fir_cishu;//���FIR�˲����ֵ
		}
		else
		{
			for(i=0;i<fir_jishu1;i++)
			{
				sum+=fir_jilu1[i];
			}
			return sum/fir_jishu1;//���FIR�˲�ǰ��ֵ
		}
  }
	else if(t==2)
	{
		fir_jilu2[fir_jishu2]=x;
		fir_jishu2++;
		if(fir_jishu2==fir_cishu)
		{
			fir_jishu2=0;
			fir_b2=1;
		}
		if(fir_b2==1)
		{
			for(i=0;i<fir_cishu;i++)
			{
				sum+=fir_jilu2[i];
			}
			return sum/fir_cishu;
		}
		else
		{
			for(i=0;i<fir_jishu2;i++)
			{
				sum+=fir_jilu2[i];
			}
			return sum/fir_jishu2;
		}
  }
	else
	{
		fir_jilu3[fir_jishu3]=x;
		fir_jishu3++;
		if(fir_jishu3==fir_cishu)
		{
			fir_jishu3=0;
			fir_b3=1;
		}
		if(fir_b3==1)
		{
			for(i=0;i<fir_cishu;i++)
			{
				sum+=fir_jilu3[i];
			}
			return sum/fir_cishu;
		}
		else
		{
			for(i=0;i<fir_jishu3;i++)
			{
				sum+=fir_jilu3[i];
			}
			return sum/fir_jishu3;
		}
  }
}
/******************
iir�˲� ����ֵ�����˲����
****************/
double iir_jilu;
u8 iir_b=0;
double iir_lvbo(double x)
{
	if(iir_b==0)
	{
		iir_b=1;
	  iir_jilu=x;
		return x;
	}
	else
	{
		iir_jilu=iir_jilu/2+x/2;
		return iir_jilu;
	}
}
/*******************
ƽ���˲�+fir ʹ��ʱ
average_fir_lvbo(x);
if(average_fir_fb)
{
average_fir_fb=0;
//ȡֵ
y=average_fir_zhi;
}
*********************/
#define average_fir_acishu 16  //ƽ������
#define average_fir_fcishu 4  //fir����
double average_fir_asum=0;    //ƽ���ͱ���
double average_fir_fjilu[average_fir_fcishu]; //ÿ�ε�ƽ��ֵ��¼����Ϊfir�˲���ֵ
u8 average_fir_ab=0;  //��һ�����ݸ����ﵽ��־
u16 average_fir_ajishu=0; ///ƽ����������
u8 average_fir_fb=0;   //fir�����ﵽ��־������Ϊ�����жϱ�־
u16 average_fir_fjishu=0; //fir��������
double average_fir_zhi;  //����firֵ
void average_fir_lvbo(double x)
{
	u8 i;
	double sum=0;
	average_fir_asum+=x; //ƽ��ֵ���
	average_fir_ajishu++; //ƽ��������һ
	if(average_fir_ab==0)
	{
		if(average_fir_ajishu==average_fir_acishu) //����ƽ������
		{
			average_fir_ajishu=0;  //ƽ����������
			average_fir_fjilu[average_fir_fjishu]=average_fir_asum/average_fir_acishu; //��ƽ��ֵ��¼
			average_fir_fjishu++;  //fir���ݼ���+1  
			average_fir_asum=0;   //ƽ��������
			if(average_fir_fjishu==average_fir_fcishu)  //����fir���ݸ���
			{
				average_fir_fjishu=0;   //fir��������
				for(i=0;i<average_fir_fcishu;i++)
				{
					sum+=average_fir_fjilu[i];   //��fir����֮��
				}
				average_fir_zhi=sum/average_fir_fcishu;  //�����������
				average_fir_fb=1;  //��һ�������ݸ��±�־λ
				average_fir_ab=1;
			}
		}
  }
	else if(average_fir_ab==1)
	{
		if(average_fir_ajishu==average_fir_acishu) //����ƽ������
		{
			average_fir_ajishu=0;  //ƽ����������
			average_fir_fjilu[average_fir_fjishu]=average_fir_asum/average_fir_acishu; //��ƽ��ֵ��¼
			average_fir_fjishu++;  //fir���ݼ���+1  
			average_fir_asum=0;   //ƽ��������
			if(average_fir_fjishu==average_fir_fcishu)  //����fir���ݸ���
			{
				average_fir_fjishu=0;   //fir��������
			}
			for(i=0;i<average_fir_fcishu;i++)
			{
				sum+=average_fir_fjilu[i];   //��fir����֮��
			}
			average_fir_zhi=sum/average_fir_fcishu;  //�����������
			average_fir_fb=1;  //��һ�������ݸ��±�־λ
		}
	}
}
/**************************************************************************************
���ã����˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
***************************************************************************************/
void Non_Filter(uint32_t *AD)//���˲�
{
	static double ADD_AD=0;
	ADD_AD=*AD;
	ADD_AD=ADD_AD*5/16777215;
	printf("���˲�%.16f\n",ADD_AD);
}
/*****************************************************************************************************
���ã��Ĵ�ƽ���˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
*****************************************************************************************************/
void Average_Filter(uint32_t *AD)//�Ĵ�ƽ���˲�
{
	static uint8_t times=0;
	static double ADD_AD=0;
	times++;
	ADD_AD=ADD_AD+(*AD);
	if(times==4)
	{
		times=0;
		ADD_AD=ADD_AD*5/16777215/4;
		printf("ƽ���˲�%.16f\n",ADD_AD);
		ADD_AD=0;
	}
}
/**************************************************************************************
���ã�FIRʮ���˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
FIRFilter_Flag ��һ�ε�ʮ�����ݲ�������11�����ݿ�ʼ����ı�־λ
FIR_times ���մ���
�����������˳�FIR�˲���ǵ�����
***************************************************************************************/
FunctionalState FIRFilter_Flag=DISABLE;
uint8_t FIR_times=0;
void FIR_Filter(uint32_t *AD)//FIRʮ���˲�
{
	
	static uint32_t FIR_Buf[10]={0};
	static double ADD_AD=0;
	
	FIR_Buf[FIR_times]=*AD;
	FIR_times++;
	
	if((FIR_times==10)&&(FIRFilter_Flag==DISABLE))
	{
		FIR_times=0;
		FIRFilter_Flag=ENABLE;
	}
	else if(FIRFilter_Flag==ENABLE)
	{
		ADD_AD=FIR_Buf[0]+FIR_Buf[1]+FIR_Buf[2]+FIR_Buf[3]+FIR_Buf[4]+FIR_Buf[5]+FIR_Buf[6]+FIR_Buf[7]+FIR_Buf[8]+FIR_Buf[9];
		ADD_AD=ADD_AD*5/16777215/10;
		printf("FIR�˲�%.16f\n",ADD_AD);
		if(FIR_times==10)
			FIR_times=0;
	}
}
/**************************************************************************************
���ã�IIR�����˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
IIR_ADD_AD ��ȡ��ת��ֵ֮��
IIR_times ���մ���
�����������˳�IIR�˲���ǵ�����
***************************************************************************************/
double IIR_ADD_AD=0;
uint8_t IIR_times=0;
void IIR_Filter(uint32_t *AD)//IIR�����˲�
{
	static double ADToVolitage=0;
	if(IIR_times<2)
	{
		IIR_times++;
		IIR_ADD_AD=IIR_ADD_AD+(*AD);
	}
	else if(IIR_times==2)
	{
		IIR_times++;
		IIR_ADD_AD=IIR_ADD_AD/2;
		IIR_ADD_AD=(IIR_ADD_AD+(*AD))/2; //??????
		ADToVolitage=IIR_ADD_AD*5/16777215;
		printf("IIR�˲���%.16f\n",ADToVolitage);
	}
	else
	{
		IIR_ADD_AD=(IIR_ADD_AD+(*AD))/2;
		ADToVolitage=IIR_ADD_AD*5/16777215;
		printf("IIR�˲���%.16f\n",ADToVolitage);
	}
	
}
