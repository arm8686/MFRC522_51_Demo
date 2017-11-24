#include "lpcreg.h"
#include <intrins.h>	
#include <12864.h>
extern unsigned char g_ucTempbuf[20]; 
uchar code dis1[] = {"曙光电子科技"};
uchar code dis2[] = {"RFID刷卡系统"};
uchar code dis3[] = {"主控芯片RC522 "};
uchar code dis4[] = {"请您刷卡上车！ "};
uchar code table3[]={"卡号:"};
uchar code table4[]={"卡类型:"};
uchar code table5[]={"消费:"};
uchar code table6[]={"余额:"};
uchar code table7[]={"元:"};

/*******************************************************************/
/*                                                                 */
/*  延时函数                                                       */
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
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
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
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
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
    LCD_EN = 1;//下降沿写入
    delayNOP();
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
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
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD_PSB = 1;         //并口方式
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
}

void display_welcome2()
{
	uchar i;
    delay(10);                 //延时
    //wela=0;
	//dula=0;         
  
    lcd_pos(0,0);             //设置显示位置为第一行的第1个字符
     i = 0;
    while(dis1[i] != '\0')
     {                         //显示字符
       lcd_wdat(dis1[i]);
       i++;
     }
    lcd_pos(1,0);             //设置显示位置为第二行的第1个字符
     i = 0;
    while(dis2[i] != '\0')
     {
       lcd_wdat(dis2[i]);      //显示字符
       i++;
     }
 	 lcd_pos(2,0);             //设置显示位置为第三行的第1个字符
     i = 0;
    while(dis3[i] != '\0')
     {
       lcd_wdat(dis3[i]);      //显示字符
       i++;
     }
	 lcd_pos(3,0);             //设置显示位置为第四行的第1个字符
     i = 0;
    while(dis4[i] != '\0')
     {
       lcd_wdat(dis4[i]);      //显示字符
       i++;
     }
  //while(1);


}
/*********************************************************/
/*														 */
/* 延时x*0.14ms子程序									 */
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
/* 设定显示位置                                          */
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
   lcd_wcmd(pos);     //显示地址
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

void display_type()//寻到卡后显示出该卡的类型
{
	unsigned char num;
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
    lcd_pos(0,0);             //设置显示位置为第四行的第1个字符
	for(num=0;num<8;num++)    //第一行要显示的11个字符
	{
	lcd_wdat(table4[num]);	
	}

	for(num=0;num<2;num++)//第一行要显示的11个字符
	{
		lcd_pos(0,num+4);
		LCD_Data(g_ucTempbuf[num]);//写数字
	}
}

void display_cardnum()
{
	unsigned char num;
    //lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
    lcd_pos(1,0);             //设置显示位置为第四行的第1个字符
	for(num=0;num<6;num++)    //第一行要显示的11个字符
	{
	lcd_wdat(table3[num]);	
	}

	for(num=0;num<4;num++)//第一行要显示的11个字符
	{
		lcd_pos(1,num+3);
		LCD_Data(g_ucTempbuf[num]);//写数字
	}
}
void display_xiaofeicarddat()//消费
{
    unsigned char num;
	lcd_pos(2,0);             //设置显示位置为第四行的第1个字符
	for(num=0;num<6;num++)    //第一行要显示的11个字符
	{
	lcd_wdat(table5[num]);	
	}
    lcd_pos(2,7);             //设置显示位置为第四行的第1个字符
	for(num=0;num<2;num++)    //第一行要显示的11个字符
	{
	lcd_wdat(table7[num]);	
	}

	for(num=0;num<1;num++)//第一行要显示的11个字符
	{
		lcd_pos(2,num+3);
		LCD_Data(0x01);//消费
	}
}

void display_carddat()    //余额
{
	unsigned char num;

    lcd_pos(3,0);     
	for(num=0;num<6;num++)    //第一行要显示的11个字符
	{
	lcd_wdat(table6[num]);	
	}
    lcd_pos(3,7);             //设置显示位置为第四行的第1个字符
	for(num=0;num<2;num++)    //第一行要显示的11个字符
	{
	lcd_wdat(table7[num]);	
	}
           //设置显示位置为第四行的第1个字符
	
        lcd_pos(3,3);
		LCD_Data(g_ucTempbuf[3]);//写数字,余额

    /*for(num=0;num<4;num++)//第一行要显示的11个字符
	{
        lcd_pos(3,num+3);
		LCD_Data(g_ucTempbuf[3]);//写数字,余额
	}*/
   /*lcd_pos(3,0);
    for(num=8;num<16;num++)//第一行要显示的11个字符
	{
		LCD_Data(g_ucTempbuf[num]);//写数字
	}*/
}
