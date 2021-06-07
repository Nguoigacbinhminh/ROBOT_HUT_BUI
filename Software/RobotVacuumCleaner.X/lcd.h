#define LCD_TRIS TRISD
#define LCD_RS RD0                       
#define LCD_RW RD1
#define LCD_EN RD2
#define LCD_D4 RD4
#define LCD_D5 RD5
#define LCD_D6 RD6
#define LCD_D7 RD7

#include <xc.h>

void LCD_Send4Bit(unsigned char data) {
    LCD_D4 = data & 0x01;
    LCD_D5 = (data >> 1) & 0x01;
    LCD_D6 = (data >> 2) & 0x01;
    LCD_D7 = (data >> 3) & 0x01;
    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;
    __delay_us(40);
}

void LCD_SendCommand(unsigned char command) {
    LCD_Send4Bit(command >> 4);
    LCD_Send4Bit(command);
}

void LCD_Init(void) {
    LCD_TRIS = 0x00;
    LCD_RS = 0;
    LCD_RW = 0;
    __delay_ms(20);
    LCD_Send4Bit(0x03);
    __delay_ms(10);
    LCD_Send4Bit(0x03);
    __delay_ms(10);
    LCD_Send4Bit(0x03);
    __delay_ms(10);
    LCD_Send4Bit(0x02);
    __delay_ms(10);
    
    LCD_SendCommand(0x28);      // Function Set: 4-bit, 2 Line, 5×7 Dots
    LCD_SendCommand(0x0C);      // Display on Cursor OFF
    LCD_SendCommand(0x06);      // Tang ID, khong dich khung hinh  Entry Mode
    LCD_SendCommand(0x01);      // Clear Display (also clear DDRAM content)
}

void LCD_PutChar(unsigned char data) {
    LCD_RS = 1;
    LCD_SendCommand(data);
    LCD_RS = 0;
}

void LCD_PutString(char *str) {
   while(*str) {        // String end when char is null - '\0'
      LCD_PutChar(*str);
      str++;
   }
}

void LCD_Clear() {
  LCD_SendCommand(0x01);  
  __delay_ms(5);
}

void LCD_Gotoxy(unsigned char row, unsigned char column) {
    unsigned char address;
    if(!row)
        address = (0x80 + column);
    else
        address = (0xC0 + column);
    LCD_SendCommand(address);
    __delay_us(50);
}
