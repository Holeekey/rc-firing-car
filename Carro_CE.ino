#include <Servo.h>

int ENAA=3;
int ENBB=5;
int ENAC=6;
int ENBD=9;

int IN1A=2;
int IN2A=10;
int IN3B=4;
int IN4B=11;
int IN1C=12;
int IN2C=7;
int IN3D=8;
int IN4D=13;

int cannonPin=A0;
int cannonDirPin=A1;
int aux=0;

Servo cannon;
Servo cannonDir;

byte datos[4];

/*

Motor A (Izquierdo Delantero) ENAA, IN1A, IN2A

Motor B (Derecho Delantero) ENBB, IN3B, IN4B

Motor C (Izquierdo Trasero) ENAC, IN1C,
IN2C

Motor D (Derecho Trasero) ENBD, IN3D, IN4D


*/

void velMotorA(int v){
  analogWrite(ENAA,v);
}

void dirMotorA(int INX,int INY){
  digitalWrite(IN1A,INX);
  digitalWrite(IN2A,INY);  
}

void velMotorB(int v){
  analogWrite(ENBB,v);
}

void dirMotorB(int INX,int INY){
  digitalWrite(IN3B,INX);
  digitalWrite(IN4B,INY);  
}

void velMotorC(int v){
  analogWrite(ENAC,v);
}

void dirMotorC(int INX,int INY){
  digitalWrite(IN1C,INX);
  digitalWrite(IN2C,INY);  
}

void velMotorD(int v){
  analogWrite(ENBD,v);
}

void dirMotorD(int INX,int INY){
  digitalWrite(IN3D,INX);
  digitalWrite(IN4D,INY);  
}

void vel(byte vel){
  
  velMotorA(vel);
  velMotorB(vel);
  velMotorC(vel);
  velMotorD(vel);
  
}

void avanzar(){
  
  dirMotorA(1,0);
  dirMotorB(1,0);
  dirMotorC(1,0);
  dirMotorD(1,0);
    
}

void retroceder(){
  
  dirMotorA(0,1);
  dirMotorB(0,1);
  dirMotorC(0,1);
  dirMotorD(0,1);
    
}

void derecha(){

  dirMotorA(1,0);
  dirMotorB(0,1);
  dirMotorC(1,0);
  dirMotorD(0,1);
    
}

void izquierda(){

  dirMotorA(0,1);
  dirMotorB(1,0);
  dirMotorC(0,1);
  dirMotorD(1,0);

}

void detener(){
  dirMotorA(0,0);
  dirMotorB(0,0);
  dirMotorC(0,0);
  dirMotorD(0,0);
}

void direccion(byte d){

  switch(d){
    case 0: detener();
      break;
    case 1: avanzar();
      break;
    case 2: izquierda();
      break;
    case 3: derecha();
      break;
    case 4: retroceder();
      break;
  }

}

void disparo(int shot){
  //att==1 => --
  //att==0 => servo se activa otra vez
  if(shot){

    cannon.attach(cannonPin);
    cannon.write(180);
    
  } else {
    cannon.detach();
  }
}

void apuntar(int grado){

  cannonDir.write(grado);
  
}

void setup (){
  pinMode(ENAA,OUTPUT);
  pinMode(IN1A,OUTPUT);
  pinMode(IN2A,OUTPUT);
  pinMode(ENBB,OUTPUT);
  pinMode(IN3B,OUTPUT);
  pinMode(IN4B,OUTPUT);
  pinMode(ENAC,OUTPUT);
  pinMode(IN1C,OUTPUT);
  pinMode(IN2C,OUTPUT);
  pinMode(ENBD,OUTPUT);
  pinMode(IN3D,OUTPUT);
  pinMode(IN4D,OUTPUT);
  pinMode(cannonPin,OUTPUT);
  pinMode(cannonDirPin,OUTPUT);
  cannonDir.attach(cannonDirPin);
  Serial.begin(9600);
}

void loop (){

  if(Serial.available()){
    Serial.readBytes(datos,4);
    //Velocidad Motores
    vel(datos[0]);
    //Dirección
    direccion(datos[1]);
    //Disparo
    disparo(datos[2]);
    //Apuntar cañón
    apuntar(datos[3]);
  }

}
