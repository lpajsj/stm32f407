#include "ange_timj.h"
#include "main.h"

static void ange_TIMj_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_TIMj_IRQ;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvicinit);
}
static void ange_TIMj_Config()
{
	TIM_TimeBaseInitTypeDef timinit;    
	ange_TIMj_APBxClock(ange_TIMj_CLK,ENABLE);     //timʱ����apb1
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;   //ckint,�������������Լ������˲�������ʱ��Ƶ�ʷ�Ƶ�� ������ʱ����
	timinit.TIM_Prescaler=168-1;  //ck_psc��Ƶ
	timinit.TIM_CounterMode=TIM_CounterMode_Up;  //��ʱ��������ʽ��������ʱ��ֻ������ģʽ
	timinit.TIM_Period=1000-1;     //��������װֵ
	timinit.TIM_RepetitionCounter=0;  //�ظ���������ֻ���ڸ߼���ʱ��
	TIM_TimeBaseInit(ange_TIMjx,&timinit);//��ʱ��������ʼ��
	TIM_ClearFlag(ange_TIMjx,TIM_FLAG_Update); //��������־
	TIM_ITConfig(ange_TIMjx,TIM_IT_Update,ENABLE); //ʹ������ж�
	TIM_Cmd(ange_TIMjx,ENABLE);  //ʹ��TIM

}

void ange_TIMj_init()
{
	ange_TIMj_NVIC_Config();
	ange_TIMj_Config();
}
void ange_TIMj_IRQHandler()
{
	if(TIM_GetITStatus(ange_TIMjx,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(ange_TIMjx,TIM_IT_Update);
	}
	
}


//tim5��ʱ��ʼ��
void Initial_System_Timer5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFFFFFF; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;       //��ʱ����Ƶ 1us
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //�����ж�
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��3
}

