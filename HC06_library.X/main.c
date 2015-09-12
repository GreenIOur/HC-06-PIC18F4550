/* 
 * File:   main.c
 * Author: GreenIOur
 *
 * Created on 10 septembre 2015, 19:09
 */
// PIC18F4550 Configuration Bit Settings
// 'C' source line config statements
#include <xc.h>
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
// CONFIG1L
#pragma config PLLDIV = 1 // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1 // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)
// CONFIG1H
#pragma config FOSC = INTOSC_HS // Oscillator Selection bits (Internal oscillator, HS oscillator used by USB (INTHS))
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
// CONFIG2L
#pragma config PWRT = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3 // Brown-out Reset Voltage bits (Minimum setting)
#pragma config VREGEN = OFF // USB Voltage Regulator Enable bit (USB voltage regulator disabled)
// CONFIG2H
#pragma config WDT = ON // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768 // Watchdog Timer Postscale Select bits (1:32768)
// CONFIG3H
#pragma config CCP2MX = ON // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
// CONFIG4L
#pragma config STVREN = ON // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
// CONFIG5L
#pragma config CP0 = OFF // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)
// CONFIG5H
#pragma config CPB = OFF // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)
// CONFIG6L
#pragma config WRT0 = OFF // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)
// CONFIG6H
#pragma config WRTC = OFF // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)
// CONFIG7L
#pragma config EBTR0 = OFF // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)
// CONFIG7H
#pragma config EBTRB = OFF // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)




#include <stdio.h>
#include <stdlib.h>
/*
#include <plib/usart.h>
#include "UART.h"

#define _XTAL_FREQ 8000000
*/
/*
 * 
 */

#define _XTAL_FREQ 8000000 //The speed of your internal(or)external oscillator
#define USE_AND_MASKS
#include <xc.h>
#include <plib/usart.h>

#define LED PORTDbits.RD1
int i = 0;
unsigned char UART1Config = 0, baud = 0;
unsigned char MsgFromPIC[] = "PIC Rocks\r";

void SetupClock(void);
void Delay1Second(void);

void main(int argc, char** argv) {

    SetupClock(); // Internal Clock to 8MHz

    TRISDbits.RD1 = 0;
    TRISCbits.RC6 = 0; //TX pin set as output
    TRISCbits.RC7 = 1; //RX pin set as input

    UART1Config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_HIGH ;
    baud = 51;
    OpenUSART(UART1Config,baud);

   
    while(1) //infinite loop
    {
        
      // putsUSART(MsgFromPIC);
      // Delay1Second();
       char a = getcUSART();
    if (a == '1')
    {
        
      LED = 1;
      putsUSART ("LED on");
    }
    if (a == '2')
    {
        LED = 0;
      putsUSART("LED off");
    }
    if (a == '?')
    {
      putsUSART("Send '1' to turn LED on");
      putsUSART("Send '2' to turn LED on");
    } 
    }
}

void SetupClock()
{
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
}

void Delay1Second()
{
    for(i=0;i<100;i++)
    {
         __delay_ms(10);
    }
}

/*
int main(int argc, char** argv) {
    
    OSCCONbits.IRCF = 1;
    
    
    //TEST liaison BT
#define LED RD1
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

  // set digital pin to control as an output
  TRISDbits.RD1 = 0;
  // set the data rate for the SoftwareSerial port
  init_uart();
  // Send test message to other device
  putsUSART("Hello from Arduino");

char a; // stores incoming character from other device
while(1){
    putsUSART("Hello from Arduino \r\n");
    while(!DataRdyUSART());
    a = getcUSART();
    if (a == '1')
    {
        
      LED = 1;
      putsUSART ("LED on");
    }
    if (a == '2')
    {
        LED = 0;
      putsUSART("LED off");
    }
    if (a == '?')
    {
      putsUSART("Send '1' to turn LED on");
      putsUSART("Send '2' to turn LED on");
    }   
    // you can add more "if" statements with other characters to add more commands
  }

    

    return (EXIT_SUCCESS);
}
*/
