import cc.arduino.*;
import processing.serial.*;
Serial Puerto;
int estadoboton1 = 0;
int estadoboton2 = 0;
int estadoboton3 = 0;
int estadoboton4 = 0;
int estadoboton5 = 0;
int estadoboton6 = 0;
int estadoboton7 = 0;
int estadoboton8 = 0;
int estadoboton9 = 0;

void setup() {
  //printArray(Serial.list());
  Puerto = new Serial(this, "/dev/serial0", 9600);
  fullScreen();
  background(0);
}

void draw() {
  char Boton = Puerto.readChar();

  if ((Boton == '0') && (estadoboton1 == 1)) {
    fill(255, 255, 255);
    ellipse(100, 100, 100, 100);
    estadoboton1 = 0;
  } else if ((Boton == '1') && (estadoboton1 == 0)) {
    fill(255, 0, 0);
    ellipse(100, 100, 100, 100);
    estadoboton1 = 1;
  }

  if  ((Boton == '0') && (estadoboton2 == 1)) {
    fill(255, 255, 255);
    ellipse(350, 100, 100, 100);
    estadoboton2 = 0;
  } else if  ((Boton == '2') && (estadoboton2 == 0)) {
    fill(255, 0, 0);
    ellipse(350, 100, 100, 100);
    estadoboton2 = 1;
  }

  if  ((Boton == '0') && (estadoboton3 == 1)) {
    fill(255, 255, 255);
    ellipse(600, 100, 100, 100);
    estadoboton3 = 0;
  } else if  ((Boton == '3') && (estadoboton3 == 0)) {
    fill(255, 0, 0);
    ellipse(600, 100, 100, 100);
    estadoboton3 = 1;
  }

  if  ((Boton == '0') && (estadoboton4 == 1)) {
    fill(255, 255, 255);
    ellipse(850, 100, 100, 100);
    estadoboton4 = 0;
  } else if  ((Boton == '4') && (estadoboton4 == 0)) {
    fill(255, 0, 0);
    ellipse(850, 100, 100, 100);
    estadoboton4 = 1;
  }

  if  ((Boton == '0') && (estadoboton5 == 1)) {
    fill(255, 255, 255);
    ellipse(100, 300, 100, 100);
    estadoboton5 = 0;
  } else if  ((Boton == '5') && (estadoboton5 == 0)) {
    fill(255, 0, 0);
    ellipse(100, 300, 100, 100);
    estadoboton5 = 1;
  }

  if  ((Boton == '0') && (estadoboton6 == 1)) {
    fill(255, 255, 255);
    ellipse(275, 300, 100, 100);
    estadoboton6 = 0;
  } else if  ((Boton == '6') && (estadoboton6 == 0)) {
    fill(255, 0, 0);
    ellipse(275, 300, 100, 100);
    estadoboton6 = 1;
  }

  if  ((Boton == '0') && (estadoboton7 == 1)) {
    fill(255, 255, 255);
    ellipse(450, 300, 100, 100);
    estadoboton7 = 0;
  } else if ((Boton == '7') && (estadoboton7 == 0)) {
    fill(255, 0, 0);
    ellipse(450, 300, 100, 100);
    estadoboton7 = 1;
  }

  if  ((Boton == '0') && (estadoboton8 == 1)) {
    fill(255, 255, 255);
    ellipse(650, 300, 100, 100);
    estadoboton8 = 0;
  } else if  ((Boton == '8') && (estadoboton8 == 0)) {
    fill(255, 0, 0);
    ellipse(650, 300, 100, 100);
    estadoboton8 = 1;
  }

  if  ((Boton == '0') && (estadoboton9 == 1)) {
    fill(255, 255, 255);
    ellipse(850, 300, 100, 100);
    estadoboton9 = 0;
  } else if  ((Boton == '9') && (estadoboton9 == 0)) {
    fill(255, 0, 0);
    ellipse(850, 300, 100, 100);
    estadoboton9 = 1;
  }
}
