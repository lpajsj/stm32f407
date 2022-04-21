#ifndef _DDS_API_H
#define _DDS_API_H
#include "stm32f10x.h"
#include "stdio.h"
#include "AD9910.h"
#include "ange_SysTick.h"

/*
	��Ƶ����0~650mV��0~400,000,000Hz
	void sine(u32 volt,u32 frequence);
	
	ɨƵ��ʽ1�����Ʋ�������
				���ֵmV,	����Ƶ��Hz������Ƶ��Hz,	  Ƶ�ʲ���Hz,  ����ʱ����us
	void sweep1(u32 volt,u32 startFreq,u32 endFreq,u32 buJinFreq, u32 buJinTime);
	
	ɨƵ��ʽ2������ɨƵ��������ʱ��
				���ֵmV,	����Ƶ��Hz������Ƶ��Hz,		   ɨƵ������ɨƵ��ʱ��mS
	void sweep2(u32 volt,u32 startFreq,u32 endFreq,u32 sweepDianShu, u32 totalTime);
*/
void sine(u32 volt,u32 frequence);
void sweep1(u32 volt,u32 startFreq,u32 endFreq,u32 buJinFreq,u32 buJinTime);
void sweep2(u32 volt,u32 startFreq,u32 endFreq,u32 sweepDianShu,u32 totalTime);

#endif





