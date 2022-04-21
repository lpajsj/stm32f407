#include "DDS_API.h"

extern uchar cfr2[4]; //cfr2������
extern uchar cfr1[4]; //cfr1������
/*
���ĵ�ѹ��500MV
����1�����ֵ����λMV
����2��Ƶ��
*/
void sine(u32 volt,u32 frequence)  //
{
	
	cfr1[0] = 0x00;		 //RAM ʧ��
	cfr2[1] = 0x00;		 //DRG ʧ��
	Txcfr();			 //����cfrx������
	Amp_convert(volt);	//д����(��λmV)�����뷶Χ��1-650 mV
	Freq_convert(frequence); //дƵ��(��λHz)�����뷶Χ��1-400 000 000Hz
	
}

void sweep2(u32 volt,u32 startFreq,u32 endFreq,u32 sweepDianShu,u32 totalTime)
{
	cfr1[0] = 0x00;		 //RAM ʧ��
	cfr2[1] = 0x00;		 //DRG ʧ��
	Txcfr();			 //����cfrx������
	Amp_convert(volt);			//д���ȣ����뷶Χ��1-650 mV
	
	u32	freq = startFreq;
	u32 DianShu = sweepDianShu;		
	u32 buJinPinLv = (endFreq - startFreq)/(sweepDianShu - 1);
	u32 buJinShiJian = totalTime / sweepDianShu;
	
	Freq_convert(freq);
	SysTick_delayms(buJinShiJian/2);SysTick_delayms(buJinShiJian/2);
	DianShu--;
	
	while(DianShu--!=1)
	{
		freq+=buJinPinLv;
		Freq_convert(freq);
		SysTick_delayms(buJinShiJian/2);SysTick_delayms(buJinShiJian/2);
	}
	
	Freq_convert(endFreq);
	SysTick_delayms(buJinShiJian/2);SysTick_delayms(buJinShiJian/2);

	
}

void sweep1(u32 volt,u32 startFreq,u32 endFreq,u32 buJinFreq,u32 buJinTime)
{
	Amp_convert(volt);			//д���ȣ����뷶Χ��1-650 mV
	//ɨƵ������Ƶ�ʣ�����Ƶ�ʣ�Ƶ�ʲ�������λ��Hz��������ʱ��������λ��us��
	SweepFre(startFreq, endFreq, buJinFreq, buJinTime); //����ʱ�䷶Χ����0~262143ns
}

