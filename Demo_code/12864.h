
#define uchar unsigned char
#define uint  unsigned int
/*TS12864A-3 端口定义*/
#define LCD_data  P0             //数据口
sbit LCD_RS  =  P2^0;            //寄存器选择输入 
sbit LCD_RW  =  P2^1;            //液晶读/写控制
sbit LCD_EN  =  P2^2;            //液晶使能控制
sbit LCD_PSB =  P2^3;            //串/并方式控制
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;

#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
//uchar IRDIS[2];
//uchar IRCOM[4];
//void delay0(uchar x);  //x*0.14MS
//void beep();
void  dataconv();
void lcd_pos(uchar X,uchar Y);  //确定显示位置
bit lcd_busy();
void lcd_wcmd(uchar cmd);
void lcd_wdat(uchar dat);
void lcd_init();
void display_welcome2();
void display_cardnum();
