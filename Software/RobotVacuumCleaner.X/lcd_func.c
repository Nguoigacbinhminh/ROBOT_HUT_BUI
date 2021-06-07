#include <xc.h>
#include "main_config.h"
#include "lcd.h"

void LCD_Enable(void) {
    LCD_EN = 1;
    __delay_us(3);
    LCD_EN = 0;
    __delay_us(50);
}

void LCD_Send4Bit(unsigned char data) {
    LCD_D4 = data & 0x01;
    LCD_D5 = (data >> 1) & 1;
    LCD_D6 = (data >> 2) & 1;
    LCD_D7 = (data >> 3) & 1;
}

void LCD_SendCommand(unsigned char command) {
    LCD_Send4Bit(command >> 4); /* Gui 4 bit cao */
    LCD_Enable() ;
    LCD_Send4Bit(command);      /* Gui 4 bit thap*/
    LCD_Enable();
}

void LCD_Init(void) {
    TRISD = 0x00;
    LCD_RS = 0;
    LCD_RW = 0;
    __delay_ms(20);
    LCD_Send4Bit(0x03);
    LCD_Enable();
    __delay_ms(10);
    LCD_Send4Bit(0x03);
    LCD_Enable();
    __delay_ms(10);
    LCD_Send4Bit(0x03);
    LCD_Enable();
    __delay_ms(10);
    LCD_Send4Bit(0x02);
    LCD_Enable();
    __delay_ms(10);
    LCD_SendCommand(0x28);      // giao thuc 4 bit, hien thi 2 hang, ki tu 5×8  
                                //Function Set: 8-bit, 1 Line, 5×7 Dots   0x30
                                //Function Set: 8-bit, 2 Line, 5×7 Dots   0x38
                                //Function Set: 4-bit, 1 Line, 5×7 Dots   0x20
                                //Function Set: 4-bit, 2 Line, 5×7 Dots   0x28
    LCD_SendCommand(0x0C);      //Display on Cursor on: 0x0E   0x0F
                                //Display on Cursor off: 0x0C
                                //Display on Cursor blinking: 0x0F
    LCD_SendCommand(0x06);      //tang ID, khong dich khung hinh  Entry Mode
    LCD_SendCommand(0x01);      // Clear Display  (also clear DDRAM content)
}

void LCD_PutChar(unsigned char data) {
    LCD_RS = 1;
    LCD_SendCommand(data);
    LCD_RS = 0;
}

void LCD_Puts(char *str) {
   while(*str) {
      LCD_PutChar(*str);
      str++;
   }
}

void LCD_Clear() {
  LCD_SendCommand(0x01);  
  __delay_ms(10);
}

void LCD_Gotoxy(unsigned char row, unsigned char column) {
    unsigned char address;
    if(!row)
        address = (0x80 + column);
    else
        address = (0xC0 + column);
    __delay_us(500);
    LCD_SendCommand(address);
    __delay_us(50);
}
