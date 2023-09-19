bit led1;//Evita los rebotes de los botones
int i=0;    //Variable del contador
float duty = 0;

void main() {
 ANSEL = 0;  //I/O digitales
 ANSELH = 0;
 PORTC = 0;    //Puerto B se pone en "0" y se configura como salidas
 TRISC = 0x00;
 PORTD = 0;
 TRISD = 0x00;
 PORTA = 0;     //Puerto A se pone en "0" y se configura como entrada
 TRISA = 0xFF;
 led1 = 0;   //Inicializa variables
 PWM1_Init(1000);
 PWM1_Start();
do {
    if (led1 == 0 && Button(&PORTA, 0, 1, 1)) {               // Detect logical one del Botón
         PORTD.F2 = 1;
         led1 = 1;
         for(i = 0;i<=5;i++){
             duty = 51*i;
             PWM1_Set_Duty(duty);
             PORTD.F3 = 1;
             delay_ms(100);
             PORTD.F3 = 0;
             delay_ms(900);
         }
    }else if (led1 == 1 && Button(&PORTA, 0, 1, 1)) {   // Detect one-to-zero transition
         PORTD.F2 = 0;
         led1 = 0;
         for(i = 0;i<=10;i++){
             duty = 255-25.5*i;
             PWM1_Set_Duty(duty);
             PORTD.F3 = 1;
             delay_ms(100);
             PORTD.F3 = 0;
             delay_ms(900);
         }                              // Invert PORTB.F0
    }

  } while(1);
}
