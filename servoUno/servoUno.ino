//Autor: Omar Damian
//Basurero automático
//1/2022
#include <Servo.h>
 
Servo servo;

int pinServo = 3 ;
int pinDetectorTapadera = 2;
int pinLedAzul = 14;
int pinLedRojo = 16;
int pinDetectorLleno = 10 ;

int vel = 0;
bool estadoAC = false;
bool noAC = true;

void inicializacion();
bool aperturaCierre(int inicio, int fin, bool modo);
void blinkled(){
  digitalWrite(pinLedAzul,LOW);
  delay(50);
  digitalWrite(pinLedAzul,HIGH);
  delay(50);
  digitalWrite(pinLedAzul,LOW);
  delay(50);
  digitalWrite(pinLedAzul,HIGH);
  delay(50);
  }
void setup() {
  pinMode(pinDetectorTapadera, INPUT);
  pinMode(pinDetectorLleno, INPUT);
  pinMode(pinLedRojo, OUTPUT);
  pinMode(pinLedAzul, OUTPUT);
  Serial.begin(9600);
  delay(200);

  servo.attach(pinServo);
  inicializacion();
}

void loop() {
  if (digitalRead(pinDetectorLleno) == LOW && noAC==true) {//Bote lleno
    while(digitalRead(pinDetectorLleno)==LOW){
      digitalWrite(pinLedRojo, HIGH);
      delay(100);
      digitalWrite(pinLedRojo, LOW);
      delay(100);
      }
  } else if(digitalRead(pinDetectorTapadera) == LOW){
    while (digitalRead(pinDetectorTapadera) == LOW) {//Bote Vacio
             
        if (estadoAC != true && vel ==180 ) {
          estadoAC = true;
          noAC=false;
          digitalWrite(pinLedAzul, HIGH);
          aperturaCierre(180,85,true);
        }else if(85<vel<180 && estadoAC!=true){
          estadoAC=true;
          noAC=false;
          digitalWrite(pinLedAzul, HIGH);
          aperturaCierre(vel,85,true);
          }
        delay(3000);        
        blinkled();
      }
        
    if (estadoAC != false) {
      estadoAC = false;
      if(aperturaCierre(85,180,false)!=false){
          noAC=true;
          digitalWrite(pinLedAzul, LOW);
        }
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool aperturaCierre(int inicio, int fin, bool modo) { //Funcion para abrir y cerrar la puerta
  if (modo == true) {
    for (vel = inicio; vel > fin; vel--) { //apertura
      servo.write(vel);
      delay(15);
    }
    return true;
  }
  else {
    for (vel = inicio; vel < fin; vel++) { //cierre
      servo.write(vel);
      if(digitalRead(pinDetectorTapadera)==LOW){
        return false;
        }
      delay(15);
    }
    return true;
  }
}

void inicializacion() { //Funcion de inicializacion
  aperturaCierre(180,175,true);
  Serial.println("1");
  aperturaCierre(175,180,false);
  Serial.println("2");
  digitalWrite(pinLedAzul,HIGH);
  digitalWrite(pinLedRojo,HIGH);
  delay(50);
  digitalWrite(pinLedAzul,LOW);
  digitalWrite(pinLedRojo,LOW);
  delay(50);
  digitalWrite(pinLedAzul,HIGH);
  digitalWrite(pinLedRojo,HIGH);
  delay(50);
  digitalWrite(pinLedAzul,LOW);
  digitalWrite(pinLedRojo,LOW);
  delay(50);
  
}
