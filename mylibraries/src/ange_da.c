#include "ange_da.h"
# include "math.h"
#define ange_code_da 1
#if  ange_code_da
//Ŀǰ���빦�ܼ�ʹ�÷���
//��ǰ���ö�ʱ�������������Ҳ�64������30K���Ϸֱ��ʻ����½�����35K���ϴ��ֻ�����35K��36K��37.5K��38.5K��40K��41.5K��43K��45K��46.5K��48.5K��51K��53.5K��56K��59K��66K��70K��74.5K��80K
//ange_DA_init();//DA��ʼ��
//ange_DA_DMA_Config(da_shuju1);//DMA��ʼ��	
//dapinlv(1000); //�������ΪƵ�ʣ�������Ҳ�
//DA�������ʹ�ܺ����������Լ12MA���������169ŷ��δ����ʹ����������Լ12K
u16 da_shuju1[64]={620,681,741,800,857,912,965,1014,1059,1100,1136,1167,1193,1214,1228,1237,1240,1237,1228,1214,
	1193,1167,1136,1100,1059,1014,965,912,857,800,741,681,620,559,499,440,383,327,275,226,181,140,104,73,47,26,11,
2,0,2,11,26,47,73,104,140,181,226,275,327,383,440,499,559};
//u16 da_shuju2[64]={};
void ange_DA_GPIO_Config()  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	ange_DA_GPIO_APBxClock(ange_DA_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_DA1_GPIO_Pin  ;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(ange_DA_GPIO_PORT,&gpioinit);
	return;
}
u16 ange_DA_TIM_Period=1130;   //
u16 ange_DA_TIM_Prescaler=0;  //��Ƶ���Ե���0
void ange_DA_Config()
{
	DAC_InitTypeDef dacinit;
	ange_DA_APBxClock(ange_DA_CLK,ENABLE);
	//DAC_LFSRUnmask_Bit�൱����ѡ�м�λ�����ڲ�����DA�Ĵ�������Ϊ��Сֵ��0bit��һλ����DAC_TriangleAmplitude���ǲ��ķ�����DA����Ϊ��Сֵ��ÿ�δ�����һ
	dacinit.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	dacinit.DAC_OutputBuffer=DAC_OutputBuffer_Disable;            //������壬��С����迹
	dacinit.DAC_Trigger=DAC_Trigger_T4_TRGO;                      //�ⲿ����ʹ�ܺ����޸Ĵ�����ʽ�����������������
	dacinit.DAC_WaveGeneration=DAC_WaveGeneration_None;            //�� ���� ���ǲ�//
	DAC_Init(ange_DA_Channel1,&dacinit);
	DAC_Cmd(ange_DA_Channel1,ENABLE);
}
void ange_DA_DMA_Config(u16* y)
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DA_DMA_Clock,ENABLE);
	dmainit.DMA_Channel=ange_DA_DMA_Channel;
	
	dmainit.DMA_DIR=DMA_DIR_MemoryToPeripheral;  //SRC ���赽�洢�� DST �浽��
	dmainit.DMA_PeripheralBaseAddr=ange_DA_DMA_mudi;
	dmainit.DMA_Memory0BaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DA_DMA_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;
	dmainit.DMA_Priority=DMA_Priority_Medium;
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DA_DMA_Stream,&dmainit);
	DMA_Cmd(ange_DA_DMA_Stream,ENABLE);
	DAC_DMACmd(ange_DA_Channel1,ENABLE);
}
void ange_DA_TIM_Config()
{
	ange_DA_TIM_APBxClock(ange_DA_TIM_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=0;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Period=ange_DA_TIM_Period;
	timinit.TIM_Prescaler=ange_DA_TIM_Prescaler;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_DA_TIMx,&timinit);
	TIM_SelectOutputTrigger(ange_DA_TIMx,TIM_TRGOSource_Update);
	TIM_Cmd(ange_DA_TIMx,ENABLE);
}
void ange_DA_init()
{
	ange_DA_GPIO_Config();  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
	ange_DA_Config();
	ange_DA_TIM_Config();
}
void dapinlv(u32 i)//�������Ҳ�,�������ΪƵ��
{
	  double  x;
		uint32_t t;
		x=1125000/i;  //���HZ
		t=(u32)x-1;
		ange_DA_TIM_Period=t;
	 TIM_SetAutoreload(ange_DA_TIMx,ange_DA_TIM_Period);
//		ange_DA_TIM_Config();
}
void dafudu(u16 *x,u32 d,float max)
{
    int i;
    double s,a;
	max/=3.3f;
	max*=4095;
    a=max/2;
    s=2*3.1415926/d;
    for(i=0;i<d;i++)
    {
       *x= (int)(a*sin(s*i)+a);
			x++;
    }

    return;
}
/*���������,ʵ����򵥵��������*/
void ange_DA_easy_init()
{
	ange_DA_easy_GPIO_Config();  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
	ange_DA_easy_Config();

}
void ange_DA_easy_GPIO_Config()  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	ange_DA_EASY_GPIO_APBxClock(ange_DA_EASY_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_DA1_EASY_GPIO_Pin  ;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_DA_EASY_GPIO_PORT,&gpioinit);
	return;
}
void ange_DA_easy_Config()
{
	DAC_InitTypeDef dacinit;
	ange_DA_EASY_APBxClock(ange_DA_EASY_CLK,ENABLE);
	//DAC_LFSRUnmask_Bit�൱����ѡ�м�λ�����ڲ�����DA�Ĵ�������Ϊ��Сֵ��0bit��һλ����DAC_TriangleAmplitude���ǲ��ķ�����DA����Ϊ��Сֵ��ÿ�δ�����һ
	dacinit.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	dacinit.DAC_OutputBuffer=DAC_OutputBuffer_Enable;            //������壬��С����迹
	dacinit.DAC_Trigger=DAC_Trigger_Software;                      //�ⲿ����ʹ�ܺ����޸Ĵ�����ʽ�����������������
	dacinit.DAC_WaveGeneration=DAC_WaveGeneration_None;            //�� ���� ���ǲ�//
	DAC_Init(ange_DA_EASY_Channel1,&dacinit);
	DAC_Cmd(ange_DA_EASY_Channel1,ENABLE);
}
void ange_DA_easy_trigger(float x)
{
	x=(u16)(x/3.3f*4095);
	#if ange_DA_EASY_OUT1
		DAC_SetChannel1Data(DAC_Align_12b_R,x);
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	#endif
	#if ange_DA_EASY_OUT2
		DAC_SetChannel2Data(DAC_Align_12b_R,x);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
	#endif
}
#endif
