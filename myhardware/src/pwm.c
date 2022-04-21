#include "pwm.h"
#include "ange_usart.h"
#include "ange_systick.h"
#if PWM_xiangwei
//�ǲ��񰡣�Ϊ��λ����************************************************************/ 
void PWMqh_TIMt_IC_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(PWMqh_TIMt_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=PWMqh_TIMt_CH1_Pin;
	GPIO_Init(PWMqh_TIMt_CH1_PORT,&gpioinit);
	//ͨ��2gpio��ʼ��
	RCC_APB2PeriphClockCmd(PWMqh_TIMt_CH2_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=PWMqh_TIMt_CH2_Pin;
	GPIO_Init(PWMqh_TIMt_CH2_PORT,&gpioinit);
}
void PWMqh_TIMt_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=PWMqh_TIMt_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=0;
	nvicinit.NVIC_IRQChannelSubPriority=2;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}

void PWMqh_TIMt_IC_Config()
{
	PWMqh_TIMt_APBxClock(PWMqh_TIMt_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Prescaler=PWMqh_TIMt_Prescaler;
	timinit.TIM_Period=PWMqh_TIMt_Period;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(PWMqh_TIMtx,&timinit);
	///����ṹ��
	TIM_ICInitTypeDef timinit2;
	//��һ��ͨ������****************
	timinit2.TIM_Channel=PWMqh_TIMt_Channelx1;
	///�˲���ϵ����0-f֮��
	timinit2.TIM_ICFilter=0;
	//Ԥ��Ƶ
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//����
	timinit2.TIM_ICPolarity=PWMqh_TIMt_Channel_Polarity1;
	//ͨ��ѡ��
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(PWMqh_TIMtx,&timinit2);
	//�ڶ���ͨ������**********
	timinit2.TIM_Channel=PWMqh_TIMt_Channelx2;
	///�˲���ϵ����0-f֮��
	timinit2.TIM_ICFilter=0;
	//Ԥ��Ƶ
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//����
	timinit2.TIM_ICPolarity=PWMqh_TIMt_Channel_Polarity1;
	//ͨ��ѡ��
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(PWMqh_TIMtx,&timinit2);
	//***************
	TIM_ClearFlag(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1);  //ֻ��ͨ��1�ж�
	TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1,ENABLE);
	TIM_Cmd(PWMqh_TIMtx,ENABLE);
}
/**************************************************************************************
***************************************************************************************/
PWMqh_TIMt_ICValue_TypeDef PWMqh_TIMt_IC_Value;  //���岶��ֵ�ṹ��
void PWMqh_TIMt_IRQHandler() //�޸���2021-8-1������nice
{
	if(TIM_GetFlagStatus(PWMqh_TIMtx,TIM_FLAG_CC1)==SET)  //ֻ��ͨ��1�ж�
	{
		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_FLAG_CC1); //����жϱ�־λ
		if(PWMqh_TIMt_IC_Value.Capture_finish==0)  //�ж��Ƿ��ȡ������
		{
		if((PWMqh_TIMt_IC_Value.Capture_ci==0)&&(PWMqh_TIMt_IC_Value.Capture_finish==0))
		{
			TIM_SetCounter(PWMqh_TIMtx,0);    //��ȡͨ��1�����غ��������㣬
			PWMqh_TIMt_IC_Value.Capture_ci=1;		//1.48us +0.15	
			
		}
		else if((PWMqh_TIMt_IC_Value.Capture_ci==1)&&(PWMqh_TIMt_IC_Value.Capture_finish==0)) //�ڶ���ֱ�ӽ�ͨ��һ��ͨ�����Ĳ�����ֵһ�����
		{
			PWMqh_TIMt_IC_Value.Capture_value2=TIM_GetCapture2(PWMqh_TIMtx);
			PWMqh_TIMt_IC_Value.Capture_value1=TIM_GetCapture1(PWMqh_TIMtx);
			PWMqh_TIMt_IC_Value.Capture_finish=1;
			PWMqh_TIMt_IC_Value.Capture_ci=0;
		}
	  }
		
	}
//	if(TIM_GetFlagStatus(PWMqh_TIMtx,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_IT_Update);
//	}

}
void PWMqh_TIMt_IC_init()
{
	PWMqh_TIMt_IC_GPIO_Config();
	PWMqh_TIMt_NVIC_Config();
	PWMqh_TIMt_IC_Config();
}
//*********************************************/
void PWMqh_TIMt_panduan()
{
		if(PWMqh_TIMt_IC_Value.Capture_finish)
		{
			PWMqh_TIMt_IC_Value.t1=(double)((PWMqh_TIMt_IC_Value.Capture_value1+1))/72; //�ó���΢��Ϊ��λ
			PWMqh_TIMt_IC_Value.t2=(double)((PWMqh_TIMt_IC_Value.Capture_value2+1))/72;
			PWMqh_TIMt_IC_Value.t1+=1.48+0.15;       //���ϲ���ֵ
			PWMqh_TIMt_IC_Value.t2+=1.48+0.15;       //��һ�������ص��ж��аѼ�ʱ�������ʱ��
			if(PWMqh_TIMt_IC_Value.t2>PWMqh_TIMt_IC_Value.t1) //���ͨ��2�������ؾ���ͨ��һ�������ص�ʱ��̫�̣��ܿ���ͨ�����Ĳ���ֵ����һ������
				PWMqh_TIMt_IC_Value.t2-=PWMqh_TIMt_IC_Value.t1;
			PWMqh_TIMt_IC_Value.xiangwei=PWMqh_TIMt_IC_Value.t2/PWMqh_TIMt_IC_Value.t1*360; //�������λ
			if(PWMqh_TIMt_IC_Value.xiangwei>180)
				PWMqh_TIMt_IC_Value.xiangwei-=360;  //����������
			PWMqh_TIMt_IC_Value.pinlv=1000000/PWMqh_TIMt_IC_Value.t1;  //���Ƶ��
			SysTick_delayms(100);  //��ʱ
			PWMqh_TIMt_IC_Value.Capture_finish=0;	 //���ת����ɱ�־λ
		}
}
#endif
