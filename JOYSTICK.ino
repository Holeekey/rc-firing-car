
int pinX = A0;
int pinY = A1;
byte datos[2];

byte dir (int x,int y) {

  //Zona muerta
  if(((x>-200)&&(x<200))&&((y>-200)&&(y<200))) return 0;
  //Izquierda
  if((y>-x)&&(y<x)) return 2;
  //Derecha
  if((y>x)&&(y<-x)) return 3;
  //Adelante
  if(y>=abs(x)) return 1;
  //Atrás
  if(y<abs(x)) return 4;

  return 0;
  
}

byte vel (int x,int y, byte dir) {
  //Adelante
  if(dir==1) return map(y,520,1023,0,255);
  //Atrás
  if(dir==4) return map(y,0,480,255,0);
  //Derecha
  if(dir==3) return map(x,0,480,255,0);
  //Izquierda
  if(dir==2) return map(x,520,1023,0,255);

  return 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pinX,INPUT);
  pinMode(pinY,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Dirección
  datos[1] = dir(analogRead(pinX)-512,analogRead(pinY)-512);

  //Velocidad
  datos[0] = vel(analogRead(pinX),analogRead(pinY),datos[1]);

  Serial.write(datos,2);
  delay(50);
}
