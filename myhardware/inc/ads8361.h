#ifndef __ads8361_H
#define __ads8361_H	
#include "stm32f10x.h"
#include "ange_systick.h"
#define ADS8361_Sofeware_SPI 0
#define ADS8361_Hardware_SPI 1
#if ADS8361_Sofeware_SPI
#define ads8361_OUTA_GPIO_CLK     RCC_APB2Periph_GPIOC //a�����������
#define ads8361_OUTA_GPIO_PORT    GPIOC
#define ads8361_OUTA_GPIO_Pin   	GPIO_Pin_0
#define ADATA PCin(0)//

#define ads8361_OUTB_GPIO_CLK     RCC_APB2Periph_GPIOA //b�����������
#define ads8361_OUTB_GPIO_PORT    GPIOA
#define ads8361_OUTB_GPIO_Pin     GPIO_Pin_6
#define BDATA    PAin(6)

#define ads8361_CLOCK_GPIO_CLK    RCC_APB2Periph_GPIOA  //ads8361ʱ������
#define ads8361_CLOCK_GPIO_PORT   GPIOA
#define ads8361_CLOCK_GPIO_Pin  	GPIO_Pin_5
#define CLOCK PAout(5)//

#define ads8361_CS_GPIO_CLK       RCC_APB2Periph_GPIOA //Ƭѡ
#define ads8361_CS_GPIO_PORT      GPIOA  
#define ads8361_CS_GPIO_Pin     	GPIO_Pin_0
#define AD8361_CS    PAout(0)

#define ads8361_RD_GPIO_CLK       RCC_APB2Periph_GPIOA  //ת������
#define ads8361_RD_GPIO_PORT     	GPIOA
#define ads8361_RD_GPIO_Pin    	 	GPIO_Pin_7
#define RD    PAout(7)//

#define ads8361_A0_GPIO_CLK       RCC_APB2Periph_GPIOA //A0 ��������
#define ads8361_A0_GPIO_PORT    	GPIOA
#define ads8361_A0_GPIO_Pin     	GPIO_Pin_3
#define A0    PAout(3)//

#define ads8361_M0_GPIO_CLK       RCC_APB2Periph_GPIOB  //ת������
#define ads8361_M0_GPIO_PORT     	GPIOB
#define ads8361_M0_GPIO_Pin     	GPIO_Pin_10
#define M0    PBout(10)//

#define ads8361_M1_GPIO_CLK       RCC_APB2Periph_GPIOB  //ת������
#define ads8361_M1_GPIO_PORT     	GPIOB
#define ads8361_M1_GPIO_Pin     	GPIO_Pin_1
#define M1    PBout(1)//
////////////////////////////////////////////////////////////////////////////////////////////////////
//#define ads8361_OUTA_GPIO_CLK     RCC_APB2Periph_GPIOB //a�����������
//#define ads8361_OUTA_GPIO_PORT    GPIOB
//#define ads8361_OUTA_GPIO_Pin   	GPIO_Pin_15
//#define ADATA PBin(15)//

//#define ads8361_OUTB_GPIO_CLK     RCC_APB2Periph_GPIOC //b�����������
//#define ads8361_OUTB_GPIO_PORT    GPIOC
//#define ads8361_OUTB_GPIO_Pin     GPIO_Pin_7
//#define BDATA    PCin(7)

//#define ads8361_CLOCK_GPIO_CLK    RCC_APB2Periph_GPIOC  //ads8361ʱ������
//#define ads8361_CLOCK_GPIO_PORT   GPIOC
//#define ads8361_CLOCK_GPIO_Pin  	GPIO_Pin_9
//#define CLOCK PCout(9)//

//#define ads8361_CS_GPIO_CLK       RCC_APB2Periph_GPIOA //Ƭѡ
//#define ads8361_CS_GPIO_PORT      GPIOA  
//#define ads8361_CS_GPIO_Pin     	GPIO_Pin_12
//#define AD8361_CS    PAout(12)

//#define ads8361_RD_GPIO_CLK       RCC_APB2Periph_GPIOC //ת������
//#define ads8361_RD_GPIO_PORT     	GPIOC
//#define ads8361_RD_GPIO_Pin    	 	GPIO_Pin_10
//#define RD    PCout(10)//

//#define ads8361_A0_GPIO_CLK       RCC_APB2Periph_GPIOA //A0 ��������
//#define ads8361_A0_GPIO_PORT    	GPIOA
//#define ads8361_A0_GPIO_Pin     	GPIO_Pin_11
//#define A0    PAout(11)//

//#define ads8361_M0_GPIO_CLK       RCC_APB2Periph_GPIOC  //ת������
//#define ads8361_M0_GPIO_PORT     	GPIOC
//#define ads8361_M0_GPIO_Pin     	GPIO_Pin_11
//#define M0    PCout(11)//

//#define ads8361_M1_GPIO_CLK       RCC_APB2Periph_GPIOD  //ת������
//#define ads8361_M1_GPIO_PORT     	GPIOD
//#define ads8361_M1_GPIO_Pin     	GPIO_Pin_2
//#define M1    PDout(2)//
#endif
#if ADS8361_Hardware_SPI
#define		ADS8361_SPIx                              SPI1
#define		ADS8361_SPI_APBxClock_FUN                 RCC_APB2PeriphClockCmd
#define		ADS8361_SPI_CLK                           RCC_APB2Periph_SPI1

#define   ADS8361_SPI_SCK_PORT                      GPIOA   
#define   ADS8361_SPI_SCK_PIN                       GPIO_Pin_5
#define 	AD8361_SCK    PAout(5)

#define   ADS8361_SPI_MOSI_PORT                     GPIOA 
#define   ADS8361_SPI_MOSI_PIN                      GPIO_Pin_7

#define   ADS8361_SPI_MISO_PORT                     GPIOA 
#define   ADS8361_SPI_MISO_PIN                      GPIO_Pin_6


#define 	ads8361_CS_GPIO_CLK       								RCC_APB2Periph_GPIOA //Ƭѡ
#define 	ads8361_CS_GPIO_PORT      								GPIOA  
#define 	ads8361_CS_GPIO_Pin     									GPIO_Pin_0
#define 	AD8361_CS    PAout(0)

#define 	ads8361_A0_GPIO_CLK       								RCC_APB2Periph_GPIOA //A0 ��������
#define 	ads8361_A0_GPIO_PORT    									GPIOA
#define 	ads8361_A0_GPIO_Pin     									GPIO_Pin_3
#define 	A0    PAout(3)//

#define 	ads8361_M0_GPIO_CLK       								RCC_APB2Periph_GPIOB  //ת������
#define 	ads8361_M0_GPIO_PORT     									GPIOB
#define 	ads8361_M0_GPIO_Pin     									GPIO_Pin_10
#define 	M0    PBout(10)//

#define 	ads8361_M1_GPIO_CLK       								RCC_APB2Periph_GPIOB  //ת������
#define 	ads8361_M1_GPIO_PORT     									GPIOB
#define 	ads8361_M1_GPIO_Pin     									GPIO_Pin_1
#define 	M1    PBout(1)//


#endif
#if ADS8361_Sofeware_SPI
void ads8361_init(void);
u32 ads8361_readb(void);
u32 ads8361_reada(void);

void ads8361_read00(u8 a);  //˫ͨ����ȡCA1 CB1  ab����ͬʱ���  180Hz���Զ�256��
void ads8361_read01(u8 a); //˫ͨ����ȡCA1 CB1  ֻ��a�������  130Hz���Զ�256��
void ads8361_read10(void); //��ͨ�� abͬʱ���  100Hz���Զ�256��
void ads8361_read11(void); //��ͨ�� a���   70Hz���Զ�256��
void ads8361_read00a1(void);  //˫ͨ����ʽ ����ֻ��ȡa1   250hz���Զ�256��
void ads8361_read00b1(void); //˫ͨ����ʽ ��ֻ��b1  250hz���Զ�256��
void ads8361_read00a0(void); //
void ads8361_read00b0(void); //
/////
void ADS8361_Read_01_OUTA(uint32_t CH,uint32_t *data_a_01,uint32_t *data_b_01);//��M0M1=01�£���ȡAͨ��������
#endif

#if ADS8361_Hardware_SPI
void ads8361_init(void);  //���Ӳ���
u32 ADS8361_SPI_Read(void);
#endif


extern float ads8361a0,ads8361a1,ads8361b0,ads8361b1;

#endif
