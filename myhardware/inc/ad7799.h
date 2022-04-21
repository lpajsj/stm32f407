#ifndef _AD7799_H
#define _AD7799_H
#include "stm32f10x.h"
#include "ange_systick.h"

//��������AD7799�ķ�ʽ
#define Sofeware_SPI 0  
#define Hardware_SPI 1

/*-------------------���SPI��AD7799�궨��-----------------------------------------------*/	
#if Sofeware_SPI   
#define  AD_RCC				 RCC_APB2Periph_GPIOB//AD7799��GPIOʱ��
#define  AD_CS_PIN     GPIO_Pin_12 	//AD7799��Ƭѡ����
#define  AD_CS_GPIO    GPIOB

#define  AD_DI_PIN     GPIO_Pin_15  	//AD7799����������
#define  AD_DI_GPIO    GPIOB

#define  AD_SCK_PIN    GPIO_Pin_13	//AD7799��ʱ������
#define  AD_SCK_GPIO   GPIOB

#define  AD_DO_PIN     GPIO_Pin_14 	//AD7799���������
#define  AD_DO_GPIO    GPIOB
//#define  AD_CS_PIN     GPIO_Pin_14 	//AD7799��Ƭѡ����
//#define  AD_CS_GPIO    GPIOB

//#define  AD_DI_PIN     GPIO_Pin_13  	//AD7799����������
//#define  AD_DI_GPIO    GPIOB

//#define  AD_SCK_PIN    GPIO_Pin_15	//AD7799��ʱ������
//#define  AD_SCK_GPIO   GPIOB

//#define  AD_DO_PIN     GPIO_Pin_12 	//AD7799���������
//#define  AD_DO_GPIO    GPIOB

#define  AD_CS_0()	 GPIO_ResetBits(AD_CS_GPIO, AD_CS_PIN) 			 
#define  AD_CS_1()	 GPIO_SetBits(AD_CS_GPIO, AD_CS_PIN) 

#define  AD_DI_0()	 GPIO_ResetBits(AD_DI_GPIO, AD_DI_PIN) 			 
#define  AD_DI_1()	 GPIO_SetBits(AD_DI_GPIO, AD_DI_PIN) 

#define  AD_SCK_0()	 GPIO_ResetBits(AD_SCK_GPIO, AD_SCK_PIN) 			 
#define  AD_SCK_1()	 GPIO_SetBits(AD_SCK_GPIO, AD_SCK_PIN) 

#define  AD_DO     (GPIO_ReadInputDataBit(AD_DO_GPIO, AD_DO_PIN))

#define AD7799_CS_LOW  AD_CS_0()
#define AD7799_CS_HIGH  AD_CS_1()
#define ADC_RDY_DAT (AD_DO)
#endif
/*-------------------Ӳ��SPI��AD7799�궨��-----------------------------------------------*/	
#if Hardware_SPI 
#define             AD7799_SPIx                               SPI2
#define             AD7799_SPI_APBxClock_FUN                  RCC_APB1PeriphClockCmd
#define             AD7799_SPI_CLK                            RCC_APB1Periph_SPI2
#define             AD7799_SPI_GPIO_APBxClock_FUN           	RCC_APB2PeriphClockCmd
#define							AD7799_SPI_GPIO_CLK												RCC_APB2Periph_GPIOB


#define             AD7799_SPI_SCK_PORT                       GPIOB   
#define             AD7799_SPI_SCK_PIN                        GPIO_Pin_13

#define             AD7799_SPI_MOSI_PORT                      GPIOB 
#define             AD7799_SPI_MOSI_PIN                       GPIO_Pin_15

#define             AD7799_SPI_MISO_PORT                      GPIOB 
#define             AD7799_SPI_MISO_PIN                       GPIO_Pin_14

#define             AD7799_SPI_CS_PORT                       	GPIOB
#define             AD7799_SPI_CS_PIN                        	GPIO_Pin_12

#define  AD_CS_0()	 GPIO_ResetBits(AD7799_SPI_CS_PORT, AD7799_SPI_CS_PIN) 			 
#define  AD_CS_1()	 GPIO_SetBits(AD7799_SPI_CS_PORT, AD7799_SPI_CS_PIN) 
#define  AD_DO     (GPIO_ReadInputDataBit(AD7799_SPI_MISO_PORT, AD7799_SPI_MISO_PIN))

#define AD7799_CS_LOW  AD_CS_0()
#define AD7799_CS_HIGH  AD_CS_1()
#endif

/*-------------------��Ӳ��ͨ�õļĴ�����ַ-----------------------------------------------*/	
/*AD7799 Registers*/  //�Ĵ�����ַ
#define AD7799_REG_COMM		0 /* Communications Register(WO, 8-bit) */ 
#define AD7799_REG_STAT	    0 /* Status Register	    (RO, 8-bit) */
#define AD7799_REG_MODE	    1 /* Mode Register	     	(RW, 16-bit */
#define AD7799_REG_CONF	    2 /* Configuration Register (RW, 16-bit)*/ //���üĴ����ĵ�ַ
#define AD7799_REG_DATA	    3 /* Data Register	     	(RO, 16-/24-bit) */
#define AD7799_REG_ID	    4 /* ID Register	     	(RO, 8-bit) */
#define AD7799_REG_IO	    5 /* IO Register	     	(RO, 8-bit) */  //����IO�Ĵ�����ַ
#define AD7799_REG_OFFSET   6 /* Offset Register	    (RW, 24-bit */
#define AD7799_REG_FULLSALE	7 /* Full-Scale Register	(RW, 24-bit */

/* Communications Register Bit Designations (AD7799_REG_COMM) */ //ͨ�żĴ���ֵ
#define AD7799_COMM_WEN		(1 << 7) 			/* Write Enable */
#define AD7799_COMM_WRITE	(0 << 6) 			/* Write Operation *///дʹ��
#define AD7799_COMM_READ    (1 << 6) 			/* Read Operation */ //��ʹ��    				//����ַ���ڵ���λ������ ����6λ
#define AD7799_COMM_ADDR(x)	(((x) & 0x7) << 3)	/* Register Address */  	//�Ĵ���ѡ���ַΪ3-5Ϊ������111����3λ
#define AD7799_COMM_CREAD	(1 << 2) 			/* Continuous Read of Data Register */ //������

/* Status Register Bit Designations (AD7799_REG_STAT) *///״̬�Ĵ���
#define AD7799_STAT_RDY		(1 << 7) /* Ready */  //ת�����
#define AD7799_STAT_ERR		(1 << 6) /* Error (Overrange, Underrange) */
#define AD7799_STAT_CH3		(1 << 2) /* Channel 3 */
#define AD7799_STAT_CH2		(1 << 1) /* Channel 2 */
#define AD7799_STAT_CH1		(1 << 0) /* Channel 1 */

/* Mode Register Bit Designations (AD7799_REG_MODE) */ 
#define AD7799_MODE_SEL(x)		(((x) & 0x7) << 13)	/* Operation Mode Select */ //AD7799��ģʽѡ��λ��13-15λ��
#define AD7799_MODE_PSW		(1 << 12)			/* Power Switch Control Bit */	
#define AD7799_MODE_RATE(x)		((x) & 0xF) 		/* Filter Update Rate Select *///��������

/* AD7799_MODE_SEL(x) options */  ///AD7799��ģʽ
#define AD7799_MODE_CONT		 0 /* Continuous Conversion Mode *///����ת��ģʽ
#define AD7799_MODE_SINGLE		1 /* Single Conversion Mode *///����ת��ģʽ
#define AD7799_MODE_IDLE		 2 /* Idle Mode */ //����ģʽ
#define AD7799_MODE_PWRDN		 3 /* Power-Down Mode *///�µ�ģʽ
#define AD7799_MODE_CAL_INT_ZERO 4 /* Internal Zero-Scale Calibration *///У׼
#define AD7799_MODE_CAL_INT_FULL 5 /* Internal Full-Scale Calibration */
#define AD7799_MODE_CAL_SYS_ZERO 6 /* System Zero-Scale Calibration */
#define AD7799_MODE_CAL_SYS_FULL 7 /* System Full-Scale Calibration */

/* Configuration Register Bit Designations (AD7799_REG_CONF) */
#define AD7799_CONF_BO_EN	  (1 << 13) 			/* Burnout Current Enable */
#define AD7799_CONF_UNIPOLAR(x)  ((x&0x1 )<< 12) 			/* Unipolar/Bipolar Enable *///��˫����ѡ��1Ϊ������
#define AD7799_CONF_GAIN(x)	  (((x) & 0x7) << 8) 	/* Gain Select */  //����ѡ��λ�����üĴ�����8-10λ
#define AD7799_CONF_REFDET(x) (((x) & 0x1) << 5) 	/* Reference detect function */ //�ο�����ʹ��λΪ���üĴ�����5λ
#define AD7799_CONF_BUF		  (1 << 4) 				/* Buffered Mode Enable */ 
#define AD7799_CONF_CHAN(x)	  ((x) & 0x7) 			/* Channel select */ //ͨ��ѡ��λΪ���üĴ���0-2λ

/* AD7799_CONF_GAIN(x) options */
#define AD7799_GAIN_1       0
#define AD7799_GAIN_2       1
#define AD7799_GAIN_4       2
#define AD7799_GAIN_8       3
#define AD7799_GAIN_16      4
#define AD7799_GAIN_32      5
#define AD7799_GAIN_64      6
#define AD7799_GAIN_128     7

/* AD7799_CONF_REFDET(x) options */
#define AD7799_REFDET_ENA   1	
#define AD7799_REFDET_DIS   0

/* AD7799_CONF_CHAN(x) options */ //ͨ��ѡ��
#define AD7799_CH_AIN1P_AIN1M	0 /* AIN1(+) - AIN1(-) */
#define AD7799_CH_AIN2P_AIN2M	1 /* AIN2(+) - AIN2(-) */
#define AD7799_CH_AIN3P_AIN3M	2 /* AIN3(+) - AIN3(-) */
#define AD7799_CH_AIN1M_AIN1M	3 /* AIN1(-) - AIN1(-) */
#define AD7799_CH_AVDD_MONITOR	7 /* AVDD Monitor */

/* ID Register Bit Designations (AD7799_REG_ID) */
#define AD7799_ID			0x9
#define AD7799_ID_MASK		0xF  

/* IO (Excitation Current Sources) Register Bit Designations (AD7799_REG_IO) */
#define AD7799_IOEN			(1 << 6)
#define AD7799_IO1(x)		(((x) & 0x1) << 4)
#define AD7799_IO2(x)		(((x) & 0x1) << 5)

void AD7799_GPIO_Init(void);//AD7799���ų�ʼ��
#if Hardware_SPI
void AD7799_DMA(void);
#endif
#if Sofeware_SPI   
void spi_ad7799_init(void);//ʹAD7799�ĹܽŴ���Ĭ��״̬,���ģ��ʹ��
#endif
void AD7799_Write(uint8_t *buf,uint8_t num);//��AD7799д����
void AD7799_Read(uint8_t *buf,uint8_t num);//��AD7799����
void AD7799_SetRegisterValue(uint8_t regAddress,uint32_t regValue,uint8_t size);//дAD7799�Ĵ���
uint32_t AD7799_GetRegisterValue(uint8_t regAddress, uint8_t size);   //��AD7799�Ĵ���
uint8_t AD7799_Init(void);//��AD7799��ID
void AD7799_Reset(void);//��λAD7799
uint8_t AD7799_Ready(void);//��״̬�Ĵ����е�RDYλ
void AD7799_SetMode(uint16_t mode);//����AD7799��ģʽ
void AD7799_SetChannel(uint16_t channel);//��ѡAD7799��ͨ��λ
void AD7799_SetGain(uint16_t gain);//����AD7799����
void AD7799_SetReference(uint16_t state);//��������òο���������
void AD7799_Calibrate(u8 t);//ͨ��У׼
void AD7799_Speed(u8 x); //�ٶ�����
void AD7799_CReadMode(uint8_t CH);//����������ģʽ
uint16_t AD7799_CRead(void);//������ģʽ
void AD7799_TUIRead(void);//�˳�������ģʽ�����ǲ�����

uint32_t AD7799_SRead(void);//����ת����ģʽ�Ķ�ȡ
void AD7799_REG_Init(uint8_t CH); //AD7799���ܳ�ʼ��

uint32_t readad1(void);//���ζ�AD7799����

u16 readad16(void);//AD779916���˲�����,16λ������


//ƽ���˲�ȫ�ֱ���
extern u8 average_b1;
extern double average_zhi1;
extern u8 average_b2;
extern double average_zhi2;
extern u8 average_b3;
extern double average_zhi3;
void average_lvbo(double x,u8 t);
//�ҵ�fir
extern u8 fir_b1;
extern u8 fir_b2;
extern u8 fir_b3;
double fir_lvbo(uint32_t,u8 t);
//�ҵ�iir
double iir_lvbo(double x);
//�ҵ�ƽ���˲���fir
extern u8 average_fir_fb;
extern double average_fir_zhi;
void average_fir_lvbo(double x);
///////////////////
void Non_Filter(uint32_t *AD);//���˲�
void Average_Filter(uint32_t *AD);//�Ĵ�ƽ���˲�
void FIR_Filter(uint32_t *AD);//FIRʮ���˲�
void IIR_Filter(uint32_t *AD);//IIR�����˲�

#endif
