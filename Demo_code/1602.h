
sbit lcden=P2^5;
sbit lcdrs=P1^0;
sbit RW = P1^1;

void delay(unsigned int z);
void write_com(unsigned char com);
void write_data(unsigned char date);
void LCD_Data(unsigned char LCDbyte );
void init();
void display_welcome();
void display_cardnum();
void display_type();
