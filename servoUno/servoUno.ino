#include <Servo.h>
 
Servo servo;

int pinServo = 3 ;
int pinDetectorTapadera = 7;
int pinLedAzul = 6;
int pinLedRojo = 5;
int pinDetectorLleno = 4;

int vel = 0;
bool estadoAC = false;
bool ocupadoAC ;
int detectorAC ;
int detectorLleno;

unsigned long tiempoAbierto,tiempoInicio,tiempoDelta;

void inicializacion();
bool aperturaCierre(int inicio, int fin, bool modo);

void setup() {
  pinMode(pinDetectorTapadera, INPUT);
  pinMode(pinDetectorLleno, INPUT);
  pinMode(pinLedRojo, OUTPUT);
  pinMode(pinLedAzul, OUTPUT);


  servo.attach(pinServo);
  inicializacion();
}

void loop() {
  
  //detectorAC = digitalRead(pinDetectorTapadera);
  //detectorLleno = digitalRead(pinDetectorLleno);

  if (digitalRead(pinDetectorLleno) == LOW && ocupadoAC==false) {//Bote lleno
    while(digitalRead(pinDetectorLleno) == LOW){
      digitalWrite(pinLedRojo, HIGH);
      delay(100);
      digitalWrite(pinLedRojo, LOW);
      delay(100);
      }
  } else 
  if(digitalRead(pinDetectorTapadera) == LOW){
    
    while (digitalRead(pinDetectorTapadera) == LOW) {//Bote Vacio
             
        if (estadoAC != true && vel ==180 ) {
          ocupadoAC = true;
          estadoAC = true;
          digitalWrite(pinLedAzul, HIGH);
          aperturaCierre(180,90,true);
        }else if(90<vel<180 && estadoAC!=true){
          estadoAC=true;
          aperturaCierre(vel,90,true);
          }

        delay(5000);      
      }
        
    if (estadoAC != false) {
      estadoAC = false;
      if(aperturaCierre(90,180,false)!=false){
          ocupadoAC=false;
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
  aperturaCierre(180,90,true);
  delay(800);
  aperturaCierre(90,180,false);
}
