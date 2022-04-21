/*********************************************************************************************
�ײ�����������ܵײ�����
ģ��������
��������		STM32ͨ��ģ��-LJX
��д�ˣ�		���ѫ
��дʱ�䣺2021��07��07��
Ӳ��֧�֣�STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��
�޸���־����
˵������
*********************************************************************************************/
#include "shumaguan.h"

u8 numtable[] = {0x82,0xee,0x07,0x46,0x6A,0x52,0x12,0xE6,0x02,0x42,0x22,0x02,0x93,0x82,0x13,0x33,0x2A,0x9b,0x2a,0x23};
/////////////////0000,1111,2222,3333,4444,5555,6666,7777,8888,9999,AAAA,BBBB,CCCC,DDDD,EEEE,FFFF,HHHH,LLLL,UUUU,PPPP//�����Ӧ����
/////////////////0000,1111,2222,3333,4444,5555,6666,7777,8888,9999,1010,1111,1212,1313,1414,1515,1616,1717,1818,1919//�������ж�Ӧλ��

u8 numtable_pot[] = {0x80,0xec,0x05,0x44,0x68,0x50,0x10,0xE4,0x00,0x40};
/////////////////////0.0.,1.1.,2.2.,3.3.,4.4.,5.5.,6.6.,7.7.,8.8.,9.9.//���ּӵ���ʾ


void ShuMaGuan_Init(void)	//����ܳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);//����ʱ��
	GPIO_InitStructure.GPIO_Pin = DATA_595 | STCP_595 | SHCP_595;																			//ѡ��˿ں�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;																									//ѡ��IO�ڹ���ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;																									//ѡ��IO�ڽӿ��ٶ�
	GPIO_Init(SHUMAGUANPORT,&GPIO_InitStructure);																											//����������д��IO��
}


//�������ʾ����������  F E D C B A��д������˳��Ϊ A B C D E F
void display(u8 a,u8 b,u8 c,u8 d,u8 e,u8 f)
{
	u8 i,num,n;
	GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
	GPIO_WriteBit(SHUMAGUANPORT,STCP_595,(BitAction)(0));
////////////////////////Aλ//////////////////////////////////////
	num = numtable[a];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));//SH_CPһ��������
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////Bλ//////////////////////////////////////
	num = numtable[b];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////Cλ//////////////////////////////////////
	num = numtable[c];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////Dλ//////////////////////////////////////
	num = numtable[d];
		for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////Eλ//////////////////////////////////////
	num = numtable[e];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////Fλ//////////////////////////////////////
	num = numtable[f];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}

	GPIO_WriteBit(SHUMAGUANPORT,STCP_595,(BitAction)(1));//����ȫ��д�꣬��STCPһ��������
  SysTick_delayus(1);
	GPIO_WriteBit(SHUMAGUANPORT,STCP_595,(BitAction)(0));
}
/*������Ӻ���*/
void ange_595_GPIO_init()
{
	GPIO_InitTypeDef gpioinit;
	RCC_APB2PeriphClockCmd(ange_DATA595_GPIO_CLK|ange_STCP595_GPIO_CLK|ange_SHCP595_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_Out_OD;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_DATA595_GPIO_Pin;
	GPIO_Init(ange_DATA595_GPIO_PORT,&gpioinit);
	
	gpioinit.GPIO_Pin=ange_STCP595_GPIO_Pin;
	GPIO_Init(ange_STCP595_GPIO_PORT,&gpioinit);
	
	gpioinit.GPIO_Pin=ange_SHCP595_GPIO_Pin;
	GPIO_Init(ange_SHCP595_GPIO_PORT,&gpioinit);
}
#define shumanum 6
u8 shuma595[shumanum]={1,2,3,4,5,6};

//ѧ����
//static u8 duanma[]={0x28,0xBD,0x58,0x19,0x8D,0x0B,0x0A,0xB9,0x08,0x09,0xff,0x88,0x0E,0x6A,0x1C,0x4A,0xCA,0xdf};//��Ϊf7

//��ѫ����
//static u8 duanma[]={0x82,0xee,0x07,0x46,0x6A,0x52,0x12,0xE6,0x02,0x42,0x22,0x02,0x93,0x82,0x13,0x33,0x2A,0x9b,0x2a,0x23};

//ѧ�ܴ�� a-a bb cc dd ee ff gg hh  ����0-9 Ϩ�� a-f -
static u8 duanma[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xff,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xbf}; //dianΪ7f  ��ʾ��Ϊ��һ��

//extern s32   doppler_speed_s32;//�������ٶ������ж��ٶ��Ƿ�Ϊ��
void ange_595_xianshi()
{
	u8 i,j,x;
	data595=0;
	shcp595=0;
	stcp595=0;
	for(i=0;i<shumanum;i++)
	{
//	x=shuma595[shumanum-i];
//		x=shuma595[5-i];
		x=shuma595[i];
		x=duanma[x];
		for(j=0;j<8;j++)
		{
			if(x&0x80)
			{
				data595=1;
			}
			else
			{
				data595=0;
			}
			shcp595=1;
			SysTick_delayus(1);
			shcp595=0;
			x<<=1;
		}
	}
	stcp595=1;
	SysTick_delayus(1);
	stcp595=0;
}



/* GPIO �⺯��			PDF���Ӱ�122/368ҳ
**************************************************************************************************************************
GPIO_DeInit  			������ GPIOx �Ĵ�������Ϊȱʡֵ
GPIO_AFIODeInit  	�����ù��ܣ���ӳ���¼����ƺ� EXTI ���ã�����Ϊȱʡֵ
GPIO_Init  				���� GPIO_InitStruct ��ָ���Ĳ�����ʼ������ GPIOx �Ĵ���
GPIO_StructInit  	�� GPIO_InitStruct �е�ÿһ��������ȱʡֵ����
GPIO_ReadInputDataBit  	��ȡָ���˿ڹܽŵ�����
GPIO_ReadInputData  		��ȡָ���� GPIO �˿�����
GPIO_ReadOutputDataBit  ��ȡָ���˿ڹܽŵ����
GPIO_ReadOutputData  		��ȡָ���� GPIO �˿����
GPIO_SetBits  					����ָ�������ݶ˿�λ
GPIO_ResetBits  				���ָ�������ݶ˿�λ
GPIO_WriteBit  					���û������ָ�������ݶ˿�λ
GPIO_Write  						��ָ�� GPIO ���ݶ˿�д������
GPIO_PinLockConfig  		���� GPIO �ܽ����üĴ���
GPIO_EventOutputConfig  ѡ�� GPIO �ܽ������¼����
GPIO_EventOutputCmd  		ʹ�ܻ���ʧ���¼����
GPIO_PinRemapConfig  		�ı�ָ���ܽŵ�ӳ��
GPIO_EXTILineConfig  		ѡ�� GPIO �ܽ������ⲿ�ж���·
**************************************************************************************************************************/

/*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/

/*GPIO_Speed�ɹ�ѡ���ֵ
typedef enum
{

  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz,
  GPIO_Speed_50MHz

}GPIOSpeed_TypeDef;
*/
