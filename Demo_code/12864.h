
#define uchar unsigned char
#define uint  unsigned int
/*TS12864A-3 �˿ڶ���*/
#define LCD_data  P0             //���ݿ�
sbit LCD_RS  =  P2^0;            //�Ĵ���ѡ������ 
sbit LCD_RW  =  P2^1;            //Һ����/д����
sbit LCD_EN  =  P2^2;            //Һ��ʹ�ܿ���
sbit LCD_PSB =  P2^3;            //��/����ʽ����
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;

#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
//uchar IRDIS[2];
//uchar IRCOM[4];
//void delay0(uchar x);  //x*0.14MS
//void beep();
void  dataconv();
void lcd_pos(uchar X,uchar Y);  //ȷ����ʾλ��
bit lcd_busy();
void lcd_wcmd(uchar cmd);
void lcd_wdat(uchar dat);
void lcd_init();
void display_welcome2();
void display_cardnum();
