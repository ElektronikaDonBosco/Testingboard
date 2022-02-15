int button = 0;
int contador = 0;
int boton1 = 0;
int boton1ANT = 0;
int conta = 0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  for (int pin1 = 2; pin1 <= 7; pin1++)
  {
    for (int pin2 = 2; pin2 <= 7; pin2++)
    {
      conta = 1;
      Serial.print (pin1);
      Serial.print (",");
      Serial.println(pin2);
      pinMode(pin1, OUTPUT);
      pinMode(pin2, INPUT);
      digitalWrite(pin1, HIGH);
      button = digitalRead (pin2);
      while ((button == LOW) && (conta == 1)) {
        contador++;
        Serial.println(contador);
        delay(200);
        button = digitalRead (pin2);
        if ((contador <= 9) && (button == HIGH)) {
          boton1 = HIGH;
          if ((boton1 == HIGH) && (boton1ANT == LOW)) {
            Serial.println("ok");
            delay(10);
            contador = 0;
          }
          boton1ANT = boton1;
        }
        else {
          boton1ANT = LOW;
        }
        if (contador == 10) {
          conta = 2;
          Serial.println("error");
          delay(10);
          contador = 0;
        }
      }
    }
  }
  conta = 0;
}
