
void setup() {
  Serial.begin(9600);
}
void loop() {
  for (int pin1 = 2; pin1 <=7; pin1++) 
  {
    for (int pin2 = 2; pin2 <=7; pin2++) 
    {
      Serial.print (pin1);
      Serial.print (",");
      Serial.println(pin2);
      delay(100);
      pinMode(pin1,OUTPUT);
      pinMode(pin2,OUTPUT);
      delay(100);
      digitalWrite(pin1,HIGH);
      digitalWrite(pin2,LOW);
      delay(1000);
      pinMode(pin1,INPUT);
      pinMode(pin2,INPUT);
      delay(100);
    }
  }
}
