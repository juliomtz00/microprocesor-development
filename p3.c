// LCD module connections
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;
// End LCD module connections

char txt1[] = "C:";
char txt2[] = "P:";
char txt3[] = "V:";

char i;                              // Loop variable
int adc_value;
float volt;
float pres;
float pwm;
char lcd_adc[8];
char lcd_volt[8];
char lcd_pres[15];

void main(){
  ANSEL  = 0x04;;                        // Configure AN pins as digital I/O
  ANSELH = 0;
  C1ON_bit = 0;                      // Disable comparators
  C2ON_bit = 0;
  
  TRISA  = 0xFF;              // PORTA is input
  PORTC = 0;                          // set PORTC to 0
  TRISC = 0;                          // designate PORTC pins as output
  PWM1_Init(5000);                    // Initialize PWM1 module at 5KHz
  

  Lcd_Init();                        // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  
  PWM1_Start();                       // start PWM1
  PWM1_Set_Duty(0);        // Set current duty for PWM1

  while(1) {                         // Endless loop

    adc_value = ADC_Read(2);   // Get 10-bit results of AD conversion
    Delay_ms(100);
    
    volt = (5.0/1023.0) * adc_value;
    pres = (700.0/1023.0) * adc_value;
    pwm = (255.0/1023.0) * adc_value;
    PWM1_Set_Duty(pwm);
    
    IntToStr(adc_value,lcd_adc);
    FloatToStr(volt,lcd_volt);
    FloatToStr(pres,lcd_pres);
    
    Lcd_Out(1,1,"C:" );                 // Write text in first row
    Lcd_Out(1,3,lcd_adc);                 // Write text in second row
    
    Lcd_Out(2,1,"P:" );                 // Write text in first row
    Lcd_Out(2,3,lcd_pres);                 // Write text in second row
    
    Delay_ms(700);
    Lcd_Cmd(_LCD_CLEAR);               // Clear display
    Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off

    Lcd_Out(1,1,"V:");                 // Write text in first row
    Lcd_Out(2,1,lcd_volt);                 // Write text in second row
    Delay_ms(700);
    Lcd_Cmd(_LCD_CLEAR);               // Clear display
    Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  }
}