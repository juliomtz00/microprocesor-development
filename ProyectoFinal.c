char kp;
char password[5] = "1234";
char np[5] = "";
char entValue[5] = "";
char signs[5] = "";
char dig;
int time;
int timei;
char timestr[2] = "";
int i;
bit oldstate;
bit newstate;
bit activada;
int ressigns;
int resvalue;
bit cmp;
bit cpsw;
int j;

char keypadPort at PORTD;

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

void keypad_enter(){
     kp = 0; // Reset key code variable

    kp = Keypad_Key_Click();             // Store key code in kp variable

    switch (kp)
    {
     case  1: strcat(entValue, "1"); break; // 1
     case  2: strcat(entValue, "2"); break; // 2
     case  3: strcat(entValue, "3"); break; // 3
     case  4: strcpy(password,entValue); strcpy(entValue,""); cpsw = 1; break; // A
     case  5: strcat(entValue, "4"); break; // 4
     case  6: strcat(entValue, "5"); break; // 5
     case  7: strcat(entValue, "6"); break; // 6
     case  8: strcpy(np,""); cpsw = 1; break;
     case  9: strcat(entValue, "7"); break; // 7
     case 10: strcat(entValue, "8"); break; // 8
     case 11: strcat(entValue, "9"); break; // 9
     case 14: strcat(entValue, "0"); break; // 0
     default: break;
     }
     
     switch(strlen(entValue))
     {
      case 1: strcpy(signs,"#"); break;
      case 2: strcpy(signs,"##"); break;
      case 3: strcpy(signs,"###"); break;
      case 4: strcpy(signs,"####"); break;
      default: strcpy(signs,""); break;
     }

     Lcd_Out(3, 1, entValue);
}

void main()
{
 Keypad_Init();
 ANSEL = 0;
 ANSELH = 0;
 PORTA = 0;
 TRISA = 0xFF;
 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);

 Sound_Init(&PORTC, 3);

 do
 {
 
 if (PORTA.F0==0){ // caja abierta
      oldstate=1;
   }
   if(oldstate==1 && PORTA.F0==1){ // caja cerrada
      oldstate=0;
      newstate=1;
   }
   if(oldstate==0 && newstate==1 && PORTA.F0==0){
   newstate = 0;
   cmp = 0;
   cpsw = 0;
   Lcd_Cmd(_LCD_CLEAR);
   Delay_ms(100);
   time = 30000;
   timei = 60;
   //memset(entValue,'\0',sizeof(entValue));

   do
   {
    Lcd_Out(1, 1, "ACTIVADA:");
    keypad_enter();

     if(strlen(entValue) >= 4)
     {
      if(strcmp(entValue,password)==0){
      Lcd_Out(1, 1, "DESACTIVADA");
      Delay_ms(1000);
      strcpy(entValue,"");
      Lcd_Cmd(_LCD_CLEAR);
         do{

             Lcd_Out(1, 1, "A-SI B-NO");
             //Lcd_Out(2, 1, "A-SI B-NO");
            keypad_enter();
            
            if(cpsw==1){
            Delay_ms(1000);
            strcpy(entValue,"");
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Out(4, 1, "LISTO");
            break;}
         }while(1);


       break;
       }else
       {
        Delay_ms(100);
        strcpy(entValue,"");
        Lcd_Out(2, 1, "INCORRECTO");
        Sound_Play(500, 300);   // Frequency = 659Hz, duration = 250ms
        Lcd_Cmd(_LCD_CLEAR);
       }
       }

       IntToStr(timei, timestr);
       Lcd_Out(1, 10, timestr);
       time--;

       if(time%50==0)
       {
        timei--;
        Sound_Play(350, 200);
       }

       if(timei<=0)
       {
        cmp = 1;
        Lcd_Cmd(_LCD_CLEAR);
        Lcd_Out(3, 1, "BOOM");
        Sound_Play(880, 2000);   // Frequency = 659Hz, duration = 250ms
        Delay_ms(1000);
        break;
       }


       }while(1); //close do while
       
       activada = 0;
       }   //close if

    }while(1);     //close do while
} //close main