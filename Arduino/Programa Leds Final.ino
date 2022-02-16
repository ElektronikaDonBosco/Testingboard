int A0v = 0;
int A1v = 0;
int pin1 = 2 && A0;
int pin2 = 2 && A0;
int N = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (pin1 = 2 && A0; pin1 <= 5 && A5; pin1++)
  {
    for (pin2 = 2 && A0; pin2 <= 5 && A5; pin2++)
    {
      // Serial.print (pin1);
      // Serial.print (",");
      // Serial.println(pin2);
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      int A_0 = analogRead (pin1);
      int A_1 = analogRead (pin2);
      A0v = map (A_0, 0, 1023, 0, 5000);
      A1v = map (A_1, 0, 1023, 0, 5000);
      // Serial.print (A0v);
      //Serial.print (",");
      // Serial.println  (A1v);
      if ((A0v + A1v > 2200) && (A0v + A1v < 6500) && (A0v > 1000) && (A1v > 1200)) {
        // Serial.print ("ok");
          Serial.println(N);
        // Serial.print (pin1);
        // Serial.print (",");
        //  Serial.print (pin2);
        N++;
      }
      delay(1000);
      pinMode(pin1, INPUT);
      pinMode(pin2, INPUT);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
    }
  }
  N = 0;
}
