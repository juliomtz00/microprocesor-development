unsigned short kp, cnt, oldstate = 0;
char value[16];
char txt[16];
float result;
float nmr;
char dig;
short clr_cnt;
short first;
char flag;

// Keypad module connections
char  keypadPort at PORTD;
// End Keypad module connections

// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End LCD module connections

void print_display(value){
  Lcd_Cmd(_LCD_CLEAR);                     // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);                // Cursor off
  Lcd_Out(1, 1, value);                   // Display counter value on LCD
}

void main() {
  cnt = 0;                                 // Reset counter
  clr_cnt = 0;
  value[16] = "";
  result = 0;
  Keypad_Init();                           // Initialize Keypad
  ANSEL  = 0;                              // Configure AN pins as digital I/O
  ANSELH = 0;
  Lcd_Init();                              // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);                     // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);                // Cursor off
  Lcd_Out(1, 1, "0");                 // Write message text on LCD


  do {
    kp = 0;                                // Reset key code variable
    first = 0;
    // Wait for key to be pressed and released
    do
      // kp = Keypad_Key_Press();          // Store key code in kp variable
      kp = Keypad_Key_Click();             // Store key code in kp variable
    while (!kp);
   // Prepare value for output, transform key to it's ASCII value
    switch (kp) {
      //case 10: kp = 42; break;  // '*'   // Uncomment this block for keypad4x3
      //case 11: kp = 48; break;  // '0'
      //case 12: kp = 35; break;  // '#'
      //default: kp += 48;

      case  1: dig = '1'; strcat(value, "1"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 1        // Uncomment this block for keypad4x4
      case  2: dig = '2'; strcat(value, "2"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 2
      case  3: dig = '3'; strcat(value, "3"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 3
      case  4: dig = '/'; flag = '/';Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, "/"); clr_cnt = 0; strcpy(value,"");
            if(first == 0){
            result = nmr;
            first = 1;
            }
        break; // A DIVISION
      case  5: dig = '4'; strcat(value, "4"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 4
      case  6: dig = '5'; strcat(value, "5"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 5
      case  7: dig = '6'; strcat(value, "6"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 6
      case  8: dig = 'X'; flag = 'X'; Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, "x"); clr_cnt = 0; strcpy(value,"");
            if(first == 0){
            result = nmr;
            first = 1;
            }
        break; // B MULTIPLICATION
      case  9: dig = '7'; strcat(value, "7"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 7
      case 10: dig = '8'; strcat(value, "8"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 8
      case 11: dig = '9'; strcat(value, "9"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atof(value); clr_cnt = 0;
        break; // 9
      case 12: dig = '-'; flag = '-'; Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, "-"); clr_cnt = 0; strcpy(value,"");
           if(first == 0){
            result = nmr;
            first = 1;
            }

        break; // C SUBTRACT
      case 13: dig = 'C'; strcpy(value,""); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, "0");
        if (clr_cnt == 1){
          result = 0;
          first = 0;
        }
        clr_cnt = 1;
        break; // * DELETE / ERASE
      case 14: dig = '0'; strcat(value, "0"); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, value); nmr = atoi(value); clr_cnt = 0;
        break; // 0
      case 15: dig = '=';
           switch(flag){
                        case '/': result = result/nmr; break;
                        case 'X': result = result*nmr; break;
                        case '-': result = result-nmr; break;
                        case '+': result = result+nmr; break;
           }
           FloatToStr(result,txt); Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, txt); clr_cnt = 0; strcpy(value,"");
        break; // # EQUAL
      case 16: dig = '+'; flag = '+'; Lcd_Cmd(_LCD_CLEAR); Lcd_Cmd(_LCD_CURSOR_OFF); Lcd_Out(1, 1, "+"); clr_cnt = 0; strcpy(value,"");
           if(first == 0){
            result = nmr;
            first = 1;
            }
        break; // D ADD

    }

    if (kp != oldstate) {                  // Pressed key differs from previous
      cnt = 1;
      oldstate = kp;
      }
    else {                                 // Pressed key is same as previous
      cnt++;
      }



  } while (1);
}