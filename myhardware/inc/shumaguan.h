#ifndef __SHUMAGUAN_H
#define __SHUMAGUAN_H
#include "ange_systick.h"


//��Ҫ������Ҫ�޸�IO��
#define SHUMAGUANPORT GPIOB  	//����IO�ӿ�
#define DATA_595 GPIO_Pin_12	//����LED1��IO�ӿ�
#define STCP_595 GPIO_Pin_10	//����LED2��IO�ӿ�
#define SHCP_595 GPIO_Pin_11	//����LED2��IO�ӿ�

void ShuMaGuan_Init(void);	//����ܳ�ʼ��
void display(u8 a,u8 b,u8 c,u8 d,u8 e,u8 f);
/*�������*/
#define ange_DATA595_GPIO_CLK   RCC_APB2Periph_GPIOB
#define ange_DATA595_GPIO_PORT  GPIOB
#define ange_DATA595_GPIO_Pin   GPIO_Pin_11
#define data595       PBout(11)
#define ange_STCP595_GPIO_CLK   RCC_APB2Periph_GPIOB
#define ange_STCP595_GPIO_PORT  GPIOB
#define ange_STCP595_GPIO_Pin   GPIO_Pin_13
#define stcp595       PBout(13)
#define ange_SHCP595_GPIO_CLK   RCC_APB2Periph_GPIOB
#define ange_SHCP595_GPIO_PORT  GPIOB
#define ange_SHCP595_GPIO_Pin   GPIO_Pin_15
#define shcp595       PBout(15)
void ange_595_GPIO_init(void);
void ange_595_xianshi(void);
extern u8 shuma595[];

#endif


//595�ܽ�--->����ܹܽ�
//a->c
//b->h
//c->f
//d->a
//e->b
//f->d
//g->e
//h->g


//��·���ϵ��¹ܽ� VCC GND DS GND���ɲ����� STCP SHCP
