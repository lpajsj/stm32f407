#include "ange_iic_24c02.h"
#include "ange_USART.H"
#define ange_iic_timeout  0x1000
#define ange_iic_longtimeout  0x1000*10
void ange_I2C_GPIO_Config()
{
	GPIO_InitTypeDef gpioinit;
	ange_I2C_GPIO_APBxClock(ange_I2C_GPIO_CLK,ENABLE); //����I2C��Ӧ�˿�ʱ��
	ange_I2C_APBxClock(ange_I2C_CLK,ENABLE);  //����I2Cʱ��
	gpioinit.GPIO_Mode=GPIO_Mode_AF;      //Ҫѡ��©���
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_OType=GPIO_OType_OD;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpioinit.GPIO_Pin=ange_I2C_SCL_Pin;      //
	GPIO_Init(ange_I2C_SCL_PORT,&gpioinit);
	gpioinit.GPIO_Pin=ange_I2C_SDA_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_I2C_SDA_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_I2C_SCL_PORT,ange_I2C_SCL_PinSource,ange_I2C_GPIO_AF);
	GPIO_PinAFConfig(ange_I2C_SDA_PORT,ange_I2C_SDA_PinSource,ange_I2C_GPIO_AF);
}
void ange_I2C_Config()
{
	I2C_InitTypeDef i2cinit;
	i2cinit.I2C_Mode=I2C_Mode_I2C;   //I2Cģʽ��#define I2C_Mode_I2C    I2C_Mode_SMBusDevice  I2C_Mode_SMBusHost   
	i2cinit.I2C_DutyCycle=I2C_DutyCycle_2;  //ռ�ձ� ��/��
	i2cinit.I2C_OwnAddress1=ange_I2C_OwnAddress;  //������ַ1
	i2cinit.I2C_Ack=I2C_Ack_Enable;    //Ӧ��ʹ��
	i2cinit.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit; //Ѱַ��ʽ
	i2cinit.I2C_ClockSpeed=ange_I2C_Speed;  //I2C�ٶ� ҪС��400000
	I2C_Init(ange_I2Cx,&i2cinit);   //I2C��ʼ��
	I2C_Cmd(ange_I2Cx,ENABLE);   //ʹ��
}
void ange_I2C_init()
{
	ange_I2C_GPIO_Config(); //gpio��ʼ��
	ange_I2C_Config();   //I2C��ʼ��
}
void ange_I2C_EE_ERROR(u8 x)
{
	printf("IIc�¼�����%d",x);
}
///�ֽ�д��
void ange_I2C_bytewrite(u8 d,u8 s)  //////////�ֽ�д��
{
	__IO u32 x=ange_iic_timeout;
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //������ʼ�ź�
			///EV5�� SBλ0����SR1�Ĵ���Ȼ�󽫵�ַд��DR�Ĵ�����������¼���0��δ������ʼ������1����ʼ�����ѷ��͡�
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((x--)==0)
 {ange_I2C_EE_ERROR(5); return;}
	}
	//���͵�ַ
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Transmitter);
	//ADDR=1����SR1Ȼ���SR2��������¼�(�¼�6)��   7λ��ַģʽʱ�����յ���ַ��ACK���λ���á�1����
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(6); return;}
	}
	//�������ݵ�ַ
	I2C_SendData(ange_I2Cx,d);
	x=ange_iic_timeout;
	//����¼�8
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(8); return;}
	}
	I2C_SendData(ange_I2Cx,s);
	/////////////////////��⵽�¼��������¼�
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(8); return;}
	}
	I2C_GenerateSTOP(ange_I2Cx,ENABLE);
	return;
}
////ҳд��
void ange_I2C_pagewrite(u8 d,u16 n,u8 *data)
{
	__IO u32 x=ange_iic_timeout*10;
	while(I2C_GetFlagStatus(ange_I2Cx,I2C_FLAG_BUSY)==SET)
	{
		if((x--)==0)
		{
			ange_I2C_EE_ERROR(24);
			return;
		}
	}
		x=ange_iic_timeout;
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //������ʼ�ź�
			///EV5�� SBλ0����SR1�Ĵ���Ȼ�󽫵�ַд��DR�Ĵ�����������¼���0��δ������ʼ������1����ʼ�����ѷ��͡�
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((x--)==0)
 {ange_I2C_EE_ERROR(25); return;}
	}
	//���͵�ַ
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Transmitter);
	//ADDR=1����SR1Ȼ���SR2��������¼�(�¼�6)��   7λ��ַģʽʱ�����յ���ַ��ACK���λ���á�1����
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(26); return;}
	}
	//�������ݵ�ַ
	I2C_SendData(ange_I2Cx,d);
	x=ange_iic_timeout;
	//����¼�8
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(28); return;}
	}
	while(n--)
	{
	I2C_SendData(ange_I2Cx,*data);
	/////////////////////��⵽�¼��������¼�
	data++;
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(28); return;}
	}
 }
	I2C_GenerateSTOP(ange_I2Cx,ENABLE);
	return;
}
////////////
void ange_I2C_datawrite(u8 d,u16 n,u8 *data)
{
	u8 ps,pj,py,pd;
	pd=d%eeprom_pagesize;  //��ַ����ҳ�ĵڼ�����ַ
	ps=eeprom_pagesize-pd;  //��ַ����ҳ���м�����ַ
	pj=n/eeprom_pagesize;   //����������д��ҳ
	py=n%eeprom_pagesize;//�����������м�������һҳ
	if(pd==0)  //�����ҳ��ַ��0�ſ�ʼ
	{
		if(pj==0)   //�ж��Ƿ�һҳ������һҳ�Ļ�
		{
			ange_I2C_pagewrite(d,n,data); //ֱ��д
			ange_I2C_waitbusy(eeprom_address);
		}
		else
		{
			while(pj--)
			{
			ange_I2C_pagewrite(d,eeprom_pagesize,data); //����ҳд�����
				ange_I2C_waitbusy(eeprom_address); //��æ
				d+=eeprom_pagesize;  //��ַ�����ݵ�ַ��ҳ�Ĵ�С
				data+=eeprom_pagesize;
			}
			if(py!=0)//�����һҳ��д��
			{
				ange_I2C_pagewrite(d,py,data);
				ange_I2C_waitbusy(eeprom_address);
			}
		}
	}
	else    //���д���ҳ��ַδ����
	{
		if(pj==0)  //����һҳ
		{
			if(ps>=n) //�����ҳʣ���ַ����д�����
			{
				ange_I2C_pagewrite(d,n,data);
				ange_I2C_waitbusy(eeprom_address);
			}
			else  //�����ҳʣ���ַ����д��
			{
				ange_I2C_pagewrite(d,ps,data);  //�Ƚ���ҳд�����
				ange_I2C_waitbusy(eeprom_address);
				py=n-ps;
				d+=ps;
				data+=ps;
				ange_I2C_pagewrite(d,py,data); //��ʣ�������һҳд��
				ange_I2C_waitbusy(eeprom_address);
			}
		}
		else  //����һҳ
		{
			pj=(n-ps)/eeprom_pagesize;  //����һҳ�����Ҫд�뼸ҳ
			py=(n-ps)%eeprom_pagesize;  //����ʣ����
			ange_I2C_pagewrite(d,ps,data);  //����һҳд��
			ange_I2C_waitbusy(eeprom_address); 
			d+=ps;
			data+=ps; //�ӵ�ַ
			while(pj--)  //дҳ
			{
			ange_I2C_pagewrite(d,eeprom_pagesize,data);
			ange_I2C_waitbusy(eeprom_address);
				d+=eeprom_pagesize;
				data+=eeprom_pagesize;
			}
			if(py!=0)  //дʣ����
			{
			ange_I2C_pagewrite(d,py,data);
			ange_I2C_waitbusy(eeprom_address);
			}
		}
	}
	return;
}
/////////////���ݶ���
void ange_I2C_dataread(u8 d,u16 n,u8 *data)  //�ֽڶ�ȡ
{
	__IO u32 t=ange_iic_timeout*10;
	  while(I2C_GetFlagStatus(ange_I2Cx, I2C_FLAG_BUSY))
  {
    if((t--) == 0)
			{ange_I2C_EE_ERROR(0xff); return;}
   }
	t=ange_iic_timeout;
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //������ʼ�ź�
			///EV5�� SBλ0����SR1�Ĵ���Ȼ�󽫵�ַд��DR�Ĵ�����������¼���0��δ������ʼ������1����ʼ�����ѷ��͡�
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(15); return;}
	}
	//����������ַ
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Transmitter);
	//ADDR=1����SR1Ȼ���SR2��������¼�(�¼�6)��   7λ��ַģʽʱ�����յ���ַ��ACK���λ���á�1����
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(16); return;}
	}
//	I2C_Cmd(ange_I2Cx,ENABLE);
	I2C_SendData(ange_I2Cx,d);  //д�����ݵ�ַ
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))  //�ȴ����ݷ���
	{
		if((t--)==0) {ange_I2C_EE_ERROR(18); return;}
	}
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //������ʼ�ź�
			///EV5�� SBλ0����SR1�Ĵ���Ȼ�󽫵�ַд��DR�Ĵ�����������¼���0��δ������ʼ������1����ʼ�����ѷ��͡�
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(15); return;}
	}
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Receiver); //����������
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(16); return;}
	}
	while(n)////////////n������
	{
		if(n==1)
		{
			I2C_AcknowledgeConfig(ange_I2Cx,DISABLE);
			I2C_GenerateSTOP(ange_I2Cx,ENABLE);  //�ڼ����������һ������ʱ��ʧ��Ӧ��
		}
	t=ange_iic_timeout*10;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED))  //�ȴ����ݱ�����
	{
		if((t--)==0) {ange_I2C_EE_ERROR(17); return;}
	}
	*data=I2C_ReceiveData(ange_I2Cx);
	data++;
	n--;
 }
	I2C_AcknowledgeConfig(ange_I2Cx,ENABLE);  //ʹ��Ӧ�𷽱��´δ���
	return;
}
////////////
void ange_I2C_waitbusy(u8 d)
{
	u16 t=ange_iic_timeout*10;
	do{
		///��ʼ�ź�
	I2C_GenerateSTART(ange_I2Cx,ENABLE);
//		///���Ĵ���������δ֪
	I2C_ReadRegister(ange_I2Cx,I2C_Register_SR1);
		//���͵�ַ
		I2C_Send7bitAddress(ange_I2Cx,d,I2C_Direction_Transmitter);
		t--;
	}
	//���addrλ��
	while(I2C_GetFlagStatus(ange_I2Cx,I2C_FLAG_ADDR)==RESET&&t!=0);  //�Ҿ���Ӧ�ü��������־λ
	///�������ʧ�ܱ�־λ
	I2C_ClearFlag(ange_I2Cx,I2C_FLAG_AF);
	///
//	I2C_Cmd(ange_I2Cx,ENABLE);
	I2C_GenerateSTOP(ange_I2Cx,ENABLE);
	return;
}
