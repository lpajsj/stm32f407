#include "chuankouping.h"
#include "stm32f10x.h"
#include "stdio.h"
#include "ange_usart.h"
#include "ange_systick.h"
#define USARTx ange_USARTx
///
/// ckpqx(1,0,100);
void ckpqx(u8 id,u8 t,u8 s) //���������߲����ֱ��� ID ͨ�� ����0-255
{
	char fs[20];
	sprintf(fs,"add %d,%d,%d",id,t,s);
	printf("%s",fs);
	ckpjieshu();
}
//�����������ַ����緢�� page y2
//ckpfasong("page y2") 
void ckpfasong(char x[]) 
{
	printf("%s",x);
	ckpjieshu();
}
//�ؼ���ֵ �縳ֵt0��txt�ı�     �����ַ�
//ckpxianshis("t0.txt","ʵ����") Ҳ����t0.txt="ʵ����"
//����t0��ʾʵ����
void ckpxianshis(char obj[],char shuju[])
{
	char fs[30];
		sprintf(fs,"%s=\"%s\"",obj,shuju);
	  printf("%s",fs);
	ckpjieshu();
}
//�ؼ���ֵ �縳ֵt0��txt�ı���   ����������
//ckpxianshids("t0.txt",123) Ҳ����t0.txt="123"
//����t0��ʾ123
void ckpxianshids(char obj[],u32 shuju)
{
	char fs[30];
		sprintf(fs,"%s=\"%d\"",obj,shuju);
	  printf("%s",fs);
		ckpjieshu();
}
//�ؼ���ֵ �������� ��ı�ؼ���ɫ   ��������
//ckpxianshid("bj.bc0",63488) Ҳ����bj.bco=63488
//����t0��ʾ123
void ckpxianshid(char obj[],u32 shuju)
{
	char fs[30];
		sprintf(fs,"%s=%d",obj,shuju);
	  printf("%s",fs);
		ckpjieshu();
}
//�ı���ʾ��t1��ʾ33.333333    ������С��
//ckpxianshifs(t1.txt,33.333333)   ��ʾС��
//����t1��ʾ33.333333
void ckpxianshifs(char obj[],double shuju)
{
	char fs[30];
		sprintf(fs,"%s=\"%.6f\"",obj,shuju);
	  printf("%s",fs);
		ckpjieshu();
}
void ckpjieshu(void)
{
	USART_SendData(USARTx,0xff);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
	USART_SendData(USARTx,0xff);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
	USART_SendData(USARTx,0xff);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
}
//void baudtz(u32 x) //����������������Ϊ��ǰ��������
//{
//		USART_Cmd(ange_USARTx,DISABLE);
//	ange_USART_init(9600);
//	ckpxianshid("baud",x);//��Ҫ�������������Ҫ����ʱ
//   SysTick_delayms(1);  ///////////��ʱһ��Ҫ���ϲ�Ȼ����һ��0xff��
//	USART_Cmd(ange_USARTx,DISABLE);
//	ange_USART_init(x);
//}

