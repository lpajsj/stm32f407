#include "QMC5883.h"
#include "ange_USART.h"
#define delay_us SysTick_delayus		
void qmc5883_gpio_init()
{
	GPIO_InitTypeDef gpioinit;
	RCC_AHB1PeriphClockCmd(QMC_SCL_GPIO_CLK|QMC_SDA_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_OUT;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_UP;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=QMC_SCL_GPIO_Pin;
	GPIO_Init(QMC_SCL_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=QMC_SDA_GPIO_Pin;
	GPIO_Init(QMC_SDA_GPIO_PORT,&gpioinit);
	QMC_IIC_SCL=1;
	QMC_IIC_SDA=1;
}
//���IIC

//����IIC��ʼ�ź�
void QMC_IIC_Start(void)
{
	QMC_SDA_OUT();     //sda�����
	QMC_IIC_SDA=1;	  	  
	QMC_IIC_SCL=1;
	delay_us(4);
 	QMC_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	QMC_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void QMC_IIC_Stop(void)
{
	QMC_SDA_OUT();//sda�����
	QMC_IIC_SCL=0;
	QMC_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	QMC_IIC_SCL=1; 
	QMC_IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 QMC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	QMC_SDA_IN();      //SDA����Ϊ����  
	QMC_IIC_SDA=1;delay_us(1);	   
	QMC_IIC_SCL=1;delay_us(1);	 
	while(QMC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			QMC_IIC_Stop();
			return 1;
		}
	}
	QMC_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void QMC_IIC_Ack(void)
{
	QMC_IIC_SCL=0;
	QMC_SDA_OUT();
	QMC_IIC_SDA=0;
	delay_us(2);
	QMC_IIC_SCL=1;
	delay_us(2);
	QMC_IIC_SCL=0;
}
//������ACKӦ��		    
void QMC_IIC_NAck(void)
{
	QMC_IIC_SCL=0;
	QMC_SDA_OUT();
	QMC_IIC_SDA=1;
	delay_us(2);
	QMC_IIC_SCL=1;
	delay_us(2);
	QMC_IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void QMC_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	QMC_SDA_OUT(); 	    
    QMC_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        QMC_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		QMC_IIC_SCL=1;
		delay_us(2); 
		QMC_IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 QMC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	QMC_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        QMC_IIC_SCL=0; 
        delay_us(2);
		QMC_IIC_SCL=1;
        receive<<=1;
        if(QMC_READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        QMC_IIC_NAck();//����nACK
    else
        QMC_IIC_Ack(); //����ACK   
    return receive;
}


//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 QMC_IIC_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(QMC_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		QMC_IIC_Stop();		 
		return 1;		
	}
    QMC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    QMC_IIC_Wait_Ack();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		QMC_IIC_Send_Byte(buf[i]);	//��������
		if(QMC_IIC_Wait_Ack())		//�ȴ�ACK
		{
			QMC_IIC_Stop();	 
			return 1;		 
		}		
	}    
    QMC_IIC_Stop();	 
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 QMC_IIC_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(QMC_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		QMC_IIC_Stop();		 
		return 1;		
	}
    QMC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    QMC_IIC_Wait_Ack();		//�ȴ�Ӧ��
    QMC_IIC_Start();
	QMC_IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
    QMC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=QMC_IIC_Read_Byte(0);//������,����nACK 
		else *buf=QMC_IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    QMC_IIC_Stop();	//����һ��ֹͣ���� 
	return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 QMC_IIC_Write_Byte(u8 addr,u8 reg,u8 data) 				 
{ 
    QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(QMC_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		QMC_IIC_Stop();		 
		return 1;		
	}
    QMC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    QMC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	QMC_IIC_Send_Byte(data);//��������
	if(QMC_IIC_Wait_Ack())	//�ȴ�ACK
	{
		QMC_IIC_Stop();	 
		return 1;		 
	}		 
    QMC_IIC_Stop();	 
	return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 QMC_IIC_Read_RES_Byte(u8 addr,u8 reg)
{
	u8 res;
    QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	QMC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    QMC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    QMC_IIC_Wait_Ack();		//�ȴ�Ӧ��
    QMC_IIC_Start();
	QMC_IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
    QMC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	res=QMC_IIC_Read_Byte(0);//��ȡ����,����nACK 
    QMC_IIC_Stop();			//����һ��ֹͣ���� 
	return res;		
}

void qmc5883_init()
{
	u8 x;
	qmc_delayms(50);
	qmc5883_gpio_init();
	x=0x80;
	QMC_IIC_Write_Len(QMC5883_ADDR,0x0a,1,&x);
	x=0x01;
	QMC_IIC_Write_Len(QMC5883_ADDR,0x0B,1,&x);
	x=0x1d;
	QMC_IIC_Write_Len(QMC5883_ADDR,0x09,1,&x);
}
void qmc5883_get_raw_data(float *x,float *y,float *z,float *t)
{
	u8 q;
	u8 shuju[9];
	QMC_IIC_Read_Len(QMC5883_ADDR,0x06,1,&q);
	
	if(q&0x01)
	{
		QMC_IIC_Read_Len(QMC5883_ADDR,0x00,9,shuju);
		*x=(((int16_t)shuju[1]*256)+((int16_t)shuju[0]));
		*y=(((int16_t)shuju[3]*256)+((int16_t)shuju[2]));
		*z=(((int16_t)shuju[5]*256)+((int16_t)shuju[4]));
		*t=(((int16_t)shuju[8]*256)+((int16_t)shuju[7]));
	}
	QMC_IIC_Read_Len(QMC5883_ADDR,0x0d,1,&q);
	printf("%d\n",q);
}




























