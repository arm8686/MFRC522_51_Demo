#include "lpcreg.h"
#include <intrins.h>	
#include <12864.h>
extern unsigned char g_ucTempbuf[20]; 
uchar code dis1[] = {"�����ӿƼ�"};
uchar code dis2[] = {"RFIDˢ��ϵͳ"};
uchar code dis3[] = {"����оƬRC522 "};
uchar code dis4[] = {"����ˢ���ϳ��� "};
uchar code table3[]={"����:"};
uchar code table4[]={"������:"};
uchar code table5[]={"����:"};
uchar code table6[]={"���:"};
uchar code table7[]={"Ԫ:"};

/*******************************************************************/
/*                                                                 */
/*  ��ʱ����                                                       */
/*                                                                 */
/*******************************************************************/
void delay(int ms)
{
    while(ms--)
	{
      uchar i;
	  for(i=0;i<250;i++)  
	   {
	    _nop_();			   
		_nop_();
		_nop_();
		_nop_();
	   }
	}
}		
/*******************************************************************/
/*                                                                 */
/*���LCDæ״̬                                                    */
/*lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ�      */
/*                                                                 */
/*******************************************************************/
bit lcd_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }
/*******************************************************************/
/*                                                                 */
/*дָ�����ݵ�LCD                                                  */
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣                             */
/*                                                                 */
/*******************************************************************/
void lcd_wcmd(uchar cmd)
{                          
   while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;//�½���д��
    delayNOP();
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*д��ʾ���ݵ�LCD                                                  */
/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�                               */
/*                                                                 */
/*******************************************************************/
void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}
/*******************************************************************/
/*                                                                 */
/*  LCD��ʼ���趨                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD_PSB = 1;         //���ڷ�ʽ
    
    lcd_wcmd(0x34);      //����ָ�����
    delay(5);
    lcd_wcmd(0x30);      //����ָ�����
    delay(5);
    lcd_wcmd(0x0C);      //��ʾ�����ع��
    delay(5);
    lcd_wcmd(0x01);      //���LCD����ʾ����
    delay(5);
}

void display_welcome2()
{
	uchar i;
    delay(10);                 //��ʱ
    //wela=0;
	//dula=0;         
  
    lcd_pos(0,0);             //������ʾλ��Ϊ��һ�еĵ�1���ַ�
     i = 0;
    while(dis1[i] != '\0')
     {                         //��ʾ�ַ�
       lcd_wdat(dis1[i]);
       i++;
     }
    lcd_pos(1,0);             //������ʾλ��Ϊ�ڶ��еĵ�1���ַ�
     i = 0;
    while(dis2[i] != '\0')
     {
       lcd_wdat(dis2[i]);      //��ʾ�ַ�
       i++;
     }
 	 lcd_pos(2,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
     i = 0;
    while(dis3[i] != '\0')
     {
       lcd_wdat(dis3[i]);      //��ʾ�ַ�
       i++;
     }
	 lcd_pos(3,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
     i = 0;
    while(dis4[i] != '\0')
     {
       lcd_wdat(dis4[i]);      //��ʾ�ַ�
       i++;
     }
  //while(1);


}
/*********************************************************/
/*														 */
/* ��ʱx*0.14ms�ӳ���									 */
/*                                                       */
/*********************************************************/

/*void delay0(uchar x)    //x*0.14MS
{
  uchar i;
  while(x--)
 {
  for (i = 0; i<13; i++) {}
 }
}*/
/*********************************************************/
/*                                                       */
/* �趨��ʾλ��                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   lcd_wcmd(pos);     //��ʾ��ַ
}

void LCD_Data(unsigned char LCDbyte )
{
	 unsigned char count;
	 count=(LCDbyte&0xf0)>>4;
	 if (count>0x9) lcd_wdat(count%9+0x40);
	 else lcd_wdat(count+0x30);
	 count=LCDbyte&0x0f;
	 if (count>9) lcd_wdat(count%9+0x40);
	 else lcd_wdat(count+0x30);
}

void display_type()//Ѱ��������ʾ���ÿ�������
{
	unsigned char num;
    lcd_wcmd(0x01);      //���LCD����ʾ����
    delay(5);
    lcd_pos(0,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
	for(num=0;num<8;num++)    //��һ��Ҫ��ʾ��11���ַ�
	{
	lcd_wdat(table4[num]);	
	}

	for(num=0;num<2;num++)//��һ��Ҫ��ʾ��11���ַ�
	{
		lcd_pos(0,num+4);
		LCD_Data(g_ucTempbuf[num]);//д����
	}
}

void display_cardnum()
{
	unsigned char num;
    //lcd_wcmd(0x01);      //���LCD����ʾ����
    delay(5);
    lcd_pos(1,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
	for(num=0;num<6;num++)    //��һ��Ҫ��ʾ��11���ַ�
	{
	lcd_wdat(table3[num]);	
	}

	for(num=0;num<4;num++)//��һ��Ҫ��ʾ��11���ַ�
	{
		lcd_pos(1,num+3);
		LCD_Data(g_ucTempbuf[num]);//д����
	}
}
void display_xiaofeicarddat()//����
{
    unsigned char num;
	lcd_pos(2,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
	for(num=0;num<6;num++)    //��һ��Ҫ��ʾ��11���ַ�
	{
	lcd_wdat(table5[num]);	
	}
    lcd_pos(2,7);             //������ʾλ��Ϊ�����еĵ�1���ַ�
	for(num=0;num<2;num++)    //��һ��Ҫ��ʾ��11���ַ�
	{
	lcd_wdat(table7[num]);	
	}

	for(num=0;num<1;num++)//��һ��Ҫ��ʾ��11���ַ�
	{
		lcd_pos(2,num+3);
		LCD_Data(0x01);//����
	}
}

void display_carddat()    //���
{
	unsigned char num;

    lcd_pos(3,0);     
	for(num=0;num<6;num++)    //��һ��Ҫ��ʾ��11���ַ�
	{
	lcd_wdat(table6[num]);	
	}
    lcd_pos(3,7);             //������ʾλ��Ϊ�����еĵ�1���ַ�
	for(num=0;num<2;num++)    //��һ��Ҫ��ʾ��11���ַ�
	{
	lcd_wdat(table7[num]);	
	}
           //������ʾλ��Ϊ�����еĵ�1���ַ�
	
        lcd_pos(3,3);
		LCD_Data(g_ucTempbuf[3]);//д����,���

    /*for(num=0;num<4;num++)//��һ��Ҫ��ʾ��11���ַ�
	{
        lcd_pos(3,num+3);
		LCD_Data(g_ucTempbuf[3]);//д����,���
	}*/
   /*lcd_pos(3,0);
    for(num=8;num<16;num++)//��һ��Ҫ��ʾ��11���ַ�
	{
		LCD_Data(g_ucTempbuf[num]);//д����
	}*/
}
