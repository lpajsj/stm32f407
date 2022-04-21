#ifndef __OLED12864_H
#define __OLED12864_H
//--------------OLED��������---------------------��ͷ�ļ��ж������鲻�ܱ���������
#include "stm32f10x.h"

#define PAGE_SIZE    8
#define XLevelL		0x00
#define XLevelH		0x10
#define YLevel       0xB0
#define	Brightness	 0xFF 
#define WIDTH 	     128
#define HEIGHT 	     64	

//-------------д��������ݶ���-------------------
#define OLED_CMD     0	//д����
#define OLED_DATA    1	//д���� 
   						  
//-----------------OLED�˿ڶ���----------------
#define OLED_CS   GPIO_Pin_11   //Ƭѡ�ź�           PB11
#define OLED_DC   GPIO_Pin_10   //����/��������ź�  PB10
#define OLED_RST  GPIO_Pin_12   //��λ�ź�           PB12

//-----------------OLED�˿ڲ�������---------------- 
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,OLED_CS)
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,OLED_CS)

#define OLED_DC_Clr()  GPIO_ResetBits(GPIOB,OLED_DC)
#define OLED_DC_Set()  GPIO_SetBits(GPIOB,OLED_DC)
 					   
#define OLED_RST_Clr()  GPIO_ResetBits(GPIOB,OLED_RST)
#define OLED_RST_Set()  GPIO_SetBits(GPIOB,OLED_RST)
						 

//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);     //д�����������
void OLED_Set_Pos(unsigned char x, unsigned char y);  //��λ����
void OLED_Display_On(void);                           //����ʾ
void OLED_Display_Off(void);                           //�ر���ʾ //
void OLED_Reset(void);                                //OLED��λ
void OLED_Init_GPIO(void);	   							   		    //
void OLED_Init(void);
void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color);  //�ı���ʾ�����ֵ
void OLED_Display(void);                                  //������ֵ��ʾ
void OLED_Clear(unsigned dat);                   //�����ʾ



void GUI_DrawPoint(u8 x, u8 y, u8 color);       //����
void GUI_Fill(u8 sx,u8 sy,u8 ex,u8 ey,u8 color);  //���
void GUI_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2,u8 color); //����
void GUI_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color); //������
void GUI_FillRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color);  //ʵ�ķ���
void GUI_DrawCircle(u8 xc, u8 yc, u8 color, u8 r);          //Բ
void GUI_FillCircle(u8 xc, u8 yc, u8 color, u8 r);         //ʵ��Բ
void GUI_DrawTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color);  //������
void GUI_FillTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color);  //ʵ��������

void GUI_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 mode);        //�ַ���ʾ
void GUI_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 Size,u8 mode);    //��ʾ����
void GUI_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size,u8 mode);  //�ַ�����ʾ
void GUI_ShowFont16(u8 x,u8 y,u8 *s,u8 mode);           
void GUI_ShowFont24(u8 x,u8 y,u8 *s,u8 mode);
void GUI_ShowFont32(u8 x,u8 y,u8 *s,u8 mode);
void GUI_ShowCHinese(u8 x,u8 y,u8 hsize,u8 *str,u8 mode);
void GUI_DrawBMP(u8 x,u8 y,u8 width, u8 height, u8 BMP[], u8 mode); 




void TEST_MainPage(void);
void Test_Color(void);
void Test_Rectangular(void);
void Test_Circle(void);
void Test_Triangle(void);
void TEST_English(void);
void TEST_Number_Character(void);
void TEST_Chinese(void);
void TEST_BMP(void);
void TEST_Menu1(void);
void TEST_Menu2(void);
extern  unsigned char gImage_123[1024];
#endif


