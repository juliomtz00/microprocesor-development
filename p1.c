bit oldstate, oldstate1, oldstate2, oldstate3;//Evita los rebotes de los botones
int i=0;    //Variable del contador
int time=0;   //Nos permite almacenar el tiempo que ha transcurrido para restarlo
int time1=0;
void main() {
 ANSEL = 0;  //I/O digitales
 ANSELH= 0;
 PORTB= 0;    //Puerto B se pone en "0" y se configura como salidas
 TRISB= 0x00;
 PORTA= 0;     //Puerto A se pone en "0" y se configura como entrada
 TRISA= 0xFF;
 oldstate=0;   //Inicializa variables
 oldstate1=0;
 oldstate2=0;
  do {
    if (Button(&PORTA, 0, 1, 1)) {               // Detect logical one del Botón 1
      oldstate = 1;                              // Update flag
    }
    if (oldstate && Button(&PORTA, 0, 1, 0)) {   // Detect one-to-zero transition
      PORTB.F0 = ~PORTB.F0;                              // Invert PORTB.F0
      oldstate = 0;                              // Update flag
    }
    if(PORTB.F0==1){    //Si ya se presionó el botón 1, se puede elegir la temporización
      if (Button(&PORTA, 1, 1, 1)) {               // Detect logical one del Botón 2
      oldstate1 = 1;                              // Update flag
      }
      if (oldstate1 && Button(&PORTA, 1, 1, 0)) {   // Detect one-to-zero transition
      oldstate1 = 0;
      PORTB.F1=1;
        do{     //Primera opción de 1hora (10s)
        i++;
        time=i;
        delay_ms(1);
        if (Button(&PORTA, 1, 1, 1)) {               // Detect logical one del Botón 2 (2da presión)
           oldstate2 = 1;                              // Update flag
        }
        if (oldstate2 && Button(&PORTA, 1, 1, 0)) {   // Detect one-to-zero transition
           PORTB.F1=0;
           PORTB.F2=1;
           oldstate2=0;
           i=2000; // al realizar la segunda presión la cuenta se detiene, el ciclo termina
        }
        }while(i<2000); //Se cuenta hasta 2000, con esto se conseguió un tiempo similar a 10s
        PORTB.F1=0;
        if (time==2000){
        PORTB.F0=0;//Si pasa el tiempo completo el humidificador se apaga por completo
        }
        i=time;
        if (PORTB.F2==1){ //Segunda opción 2 horas (20s)
          do{
          i++;
          time1=i;
          delay_ms(1);
          if (Button(&PORTA, 1, 1, 1)) {   // Detect logical one del Botón 2 (3ra presión)
             oldstate3 = 1;                              // Update flag
          }
          if (oldstate3 && Button(&PORTA, 1, 1, 0)) {   // Detect one-to-zero transition
            PORTB.F1=0;
            PORTB.F2=0;
            oldstate3=0;
            i=4000; //al realizar la tercera presión la cuenta se detiene, el ciclo termina
          }
          }while(i<4000); //Se cuenta hasta 4000, con esto se conseguió un tiempo similar a 20s
      i=0;
      PORTB.F2=0; //
      if (time1==4000){
      PORTB.F0=0; //Si pasa el tiempo completo el humidificador se apaga por completo
      }
      }
      else{ //Si no se deja acabar el tiempo ambos leds se apagaran execeptuando el de "no temporizado"
          i=0;
          PORTB.F1=0;
          PORTB.F2=0;
      }
      }
    }
  } while(1);
}
