int button = 0;
int contador = 0;
int boton1 = 0;
int boton1ANT = 0;
int conta = 0;
int N = 1;

void setup() {
  Serial.begin(9600);
}
void loop() {
  for (int pin1 = 6; pin1 <= 11; pin1++)
  {
    for (int pin2 = 6; pin2 <= 11; pin2++)
    {
      conta = 1;
      // Serial.print (pin1);
      // Serial.print (",");
      // Serial.println(pin2);
      pinMode(pin1, OUTPUT);
      pinMode(pin2, INPUT);
      digitalWrite(pin1, HIGH);
      button = digitalRead (pin2);
      while ((button == LOW) && (conta == 1)) {
        contador++;
        //  Serial.println(contador);
        delay(800);
        button = digitalRead (pin2);
        if ((contador <= 9) && (button == HIGH)) {
          boton1 = HIGH;
          if ((boton1 == HIGH) && (boton1ANT == LOW)) {
            //   Serial.println("ok");
            Serial.println(N);
            delay(10);
            contador = 0;
            N++;
          }
          boton1ANT = boton1;
        }
        else {
          boton1ANT = LOW;
        }
        if (contador == 10) {
          conta = 2;
          Serial.println("no hay boton");
          delay(10);
          contador = 0;
        }
      }
    }
  }
  conta = 0;
}
