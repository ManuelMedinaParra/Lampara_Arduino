// librerias para el lcd y el timer
#include <LiquidCrystal.h>
#include <TimerOne.h>

// initializacion lcd
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//pines pulsadores y luces
const int Pulsador1=2;
const int Pulsador2=3;
const int Pulsador3=4;
const int Luces=5;

bool P1;
bool P2;
bool P3;
bool pausa=0;
int opcion;
long tencendido;
int encendido;
const int salto = 300;
int queda;
char quedaTexto[17];
int quedaMenu=1800;
char quedaMenuTexto[17];


void setup() {
  pinMode(Pulsador1,INPUT_PULLUP);
  pinMode(Pulsador2,INPUT_PULLUP);
  pinMode(Pulsador3,INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Luces apagadas");
  lcd.setCursor(0, 1);
  lcd.print(0);
  lcd.print(" s");
  digitalWrite(LED_BUILTIN,LOW);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(tiempo);
  Serial.begin(9600);
}

void loop() {
  P1= digitalRead(Pulsador1);
  P2= digitalRead(Pulsador2);
  P3= digitalRead(Pulsador3);
  //pulsador subir tiempo
  if(!P1){
    opcion=1;
  }
  //pulsador bajar tiempo
  if(!P2){
    opcion=2;
  }
  //desactiva si ninguno esta pulsado y no ha acabado el secado
  if(P1&&P2&&opcion!=4){
    opcion=0;
  }
  //pulsador encender/pausa
  if(!P3){
    opcion=3;
  }
  
  
  switch(opcion){
    //aumenta el tiempo
    case 1:
      quedaMenu=quedaMenu+salto;
      //cancela el secado si se pulsa y esta pausado
      if(pausa){
        pausa=0;
        queda=0;
        lcd.setCursor(0, 0);
        lcd.write("Luces apagadas");
      }
    break;
    //disminuye el tiempo
    case 2:
      if(quedaMenu>salto){
        quedaMenu=quedaMenu-salto;
      }
    break;
    //inicia el secado o lo pausa
    case 3:
      noInterrupts();
      if(queda<=0){
        lcd.setCursor(0,0);
        queda=quedaMenu;
        lcd.print("Luces encendidas");
        digitalWrite(Luces,HIGH);
      }

      //implementacion pausa
      else{
        Serial.print(pausa);
        if(!pausa){
          pausa=1;
          lcd.setCursor(0,0);
          lcd.print("Secado pausado  ");
          digitalWrite(Luces,LOW);
        }
        else{
          pausa=0;
          lcd.setCursor(0,0);
          lcd.print("Luces encendidas");
          digitalWrite(Luces,HIGH);
        }
      }
      interrupts();
    break;
    //indica que el secado ha acabado
    case 4:
      lcd.setCursor(0, 0);
      lcd.write("Fin de secado   ");
      digitalWrite(Luces,LOW);
    break;
    
    default:
    break;
  }
  
  //actualizacion lcd
  if(queda<=0){
    noInterrupts();
    sprintf(quedaMenuTexto, "%d", quedaMenu/60);
    lcd.setCursor(0, 1);
    lcd.write(quedaMenuTexto);
    lcd.write(" min  ");
    sprintf(quedaMenuTexto, "%d", quedaMenu%60);
    lcd.write(quedaMenuTexto);
    lcd.write(" seg        ");
    interrupts();
  }
  else{
    if(pausa==0){
      sprintf(quedaTexto, "%d", queda/60);
      lcd.setCursor(0, 1);
      lcd.write(quedaTexto);
      lcd.write(" min  ");
      sprintf(quedaTexto, "%d", queda%60);
      lcd.write(quedaTexto);
      lcd.write(" seg        ");
    }
  }
  //esperamos hasta que el ciclo haga 250 ms
  delay(tencendido+250-millis());
  tencendido=millis();
}


void tiempo(void){
  //entra si queda tiempo y no esta pausado
  if (queda>0&&!pausa){
    queda=queda-1;
    lcd.setCursor ( 0, 1 );
    lcd.print(queda);
    //entra al terminar el tiempo
    if (queda<=0){
      opcion=4;
      }
  }
}
