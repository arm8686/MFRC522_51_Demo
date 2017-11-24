#include <intrins.h>
#include "lpcreg.h"
#include "1602.h"
#define uchar unsigned char
#define uint unsigned int

extern unsigned char g_ucTempbuf[20]; 
unsigned char code table1[]="Welcome to Card";
unsigned char code table2[]="Thank you!";
unsigned char code table3[]="Card ID:";

unsigned char code table4[]="UltraLight";
unsigned char code table5[]="M1(S50)";
unsigned char code table6[]="M1(S70)";
unsigned char code table7[]="Pro(X)";
unsigned char code table8[]="DESFire";
unsigned char code table9[]="Type:";



void delay(unsigned int z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}



////////////写命令////////////////////////////
void write_com(unsigned char com)
{
	
    lcdrs=0;
    RW =0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
//////////////////////////////////////////////

////////////写数据////////////////////////////
void write_data(unsigned char date)
{
	lcdrs=1;
    RW =0;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
//////////////////////////////////////////////

//////////数值的转换格式  \ 显示数值 ////////////////

void LCD_Data(unsigned char LCDbyte )
{
	 unsigned char count;
	 count=(LCDbyte&0xf0)>>4;
	 if (count>0x9) write_data(count%9+0x40);
	 else write_data(count+0x30);
	 count=LCDbyte&0x0f;
	 if (count>9) write_data(count%9+0x40);
	 else write_data(count+0x30);
}
/////////////////////////////////////////////////////




////////////初始化////////////////////////////
void init()
{
	lcden=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);

}
///////////////////////////////////////////////


void display_welcome()
{
	unsigned char num;
	write_com(0x80);//显示的起始地址
	for(num=0;num<15;num++)
	{
		write_data(table1[num]);

	}
	write_com(0x80+0x40);//显示的起始地址
	for(num=0;num<10;num++)
	{
		write_data(table2[num]);

	}



}


void display_cardnum()
{
	unsigned char num;

	write_com(0x80);//显示的起始地址
	for(num=0;num<8;num++)//第一行要显示的11个字符
	{
		write_data(table3[num]);

	}

	//write_com(0x80+0x08);//显示的起始地址
	for(num=0;num<4;num++)//第一行要显示的11个字符
	{
		LCD_Data(g_ucTempbuf[num]);

	}
}

void display_type()
{
		unsigned char num;
	//	write_com(0x1);			//清屏
		write_com(0x80+0x40);	//第二行显示的起始地址	
		for(num=0;num<5;num++)	
		{
			write_data(table9[num]);
		}

		if((g_ucTempbuf[0]==0x44)&&(g_ucTempbuf[1]==0))//Mifare_UltraLight
		{

				for(num=0;num<4;num++)//第一行要显示的11个字符
				{
					write_data(table4[num]);
			
				}
		}
		else if((g_ucTempbuf[0]==0x04)&&(g_ucTempbuf[1]==0))//Mifare_One(S50)
		{

				for(num=0;num<7;num++)//第一行要显示的11个字符
				{
					write_data(table5[num]);
			
				}
		}
		else if((g_ucTempbuf[0]==0x02)&&(g_ucTempbuf[1]==0))//Mifare_One(S70)
		{

				for(num=0;num<7;num++)//第一行要显示的11个字符
				{
					write_data(table6[num]);
			
				}
		}
		else if((g_ucTempbuf[0]==0x08)&&(g_ucTempbuf[1]==0))//Pro(X)
		{

				for(num=0;num<6;num++)//第一行要显示的11个字符
				{
					write_data(table7[num]);
			
				}
		}
		else if((g_ucTempbuf[0]==0x44)&&(g_ucTempbuf[1]==0x03))//DESFire
		{

				for(num=0;num<7;num++)//第一行要显示的11个字符
				{
					write_data(table8[num]);
			
				}
		}

}
