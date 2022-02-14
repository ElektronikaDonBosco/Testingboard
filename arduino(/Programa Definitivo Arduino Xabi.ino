// 2.0_V. bertsio honetan datu guztiak bi dimentsioko array baten
// gordetzen dira eta inprimatzen dira
// 2.1_V. pinHigh eta pinLow dira erreferentziak besteak, 1,1-etik hasten dira eta ez
// 54,54-etatik lehen analogikoak kalkultzeko + bounce + 3 aldiz sakatuta buttonTestLedak
// 2.2_V 3 array idatzi eta alderatu, 3 panel testeatzeko
// 2.3_V 3 panel arteko aldeak detektatu eta matxurak erakutsi
// 3.0 PLC moduan programatuta
// 3.1 array nagusian gorden eskema zuzena. "oso ondo funzionatzen du"
// 3.2 arreglado el problema en el que si había un fallo al principio luego se repetía. "p. ej 4-3 key2 defektuoso"
// 3.3 teklado guztien testeko 2. fasea OK
// 3.4 test leds
// 4.0 test botones al pulsar. funzionatzen du baina boton + teckla bateratua
// 5.0 OKOKOK
// 5.1 hobekuntzak

#include "MapFloat.h"
#include <Bounce2.h>


#define pinNumber 10
#define BUTTON_PIN 5

Bounce debouncer = Bounce(); // Instantiate a Bounce object

boolean f1 = LOW;
boolean f2 = LOW;
boolean f3 = LOW;
boolean f4 = LOW;
boolean f5 = LOW;
boolean f6 = LOW;
boolean statePushBotton = LOW;
boolean statePushing = LOW;

boolean buttonStateTestLedak = LOW;

int counterUp = 0;


int pinHigh = 1;
int pinLow = 1;
int pinHighD = 6;
int pinLowD = 6;
int pinHighA = 54;
int pinLowA = 54;
int countHasierakoZirkuituX = 0;
boolean failure = false;


typedef struct   {
  byte  kyNumber = 1;
  byte  pinHigh = 1;
  byte  pinLow = 1;
  float voltpinHigh = 0.0;
  float voltpinLow = 0.0;
  float voltageDrop = 0.0;
  boolean diode = false;
  boolean shortCut = false;
} ky_data;
ky_data testArray[pinNumber][pinNumber];
ky_data testArray1[pinNumber][pinNumber];
ky_data testArray2[pinNumber][pinNumber];
ky_data testArray3[pinNumber][pinNumber];

typedef struct   {
  byte  pinHigh = 1;
  byte  pinLow = 1;
  float voltpinHigh = 0.0;
  float voltpinLow = 0.0;
  float voltageDrop = 0.0;
  float resButton = 0.0;
  boolean stateButton = LOW;

} button_data;
button_data buttonDataArray[pinNumber][pinNumber];

void setup() {
  Serial.begin(115200);
  debouncer.attach(BUTTON_PIN, INPUT_PULLUP); // sakagailua PIN 2 eta masa artean konektaturik dago
  debouncer.interval(25); // Use a debounce interval of 25 milliseconds
  f1 = HIGH;

  pinMode (14, OUTPUT);
  digitalWrite (14, HIGH);
}

void loop() {
  f1_hasierakoPanelenTesta ();
  f2_testeatzen ();
  f3_testeatzen_ledak ();
  f4_testButtons ();
  f5_testingButtons ();
  f6_datorrena ();
}


void f1_hasierakoPanelenTesta ()
{
  while (f1 == HIGH) {
    failure = false;
    Serial.println ("");
    Serial.println ( "TEST 3 PRIMEROS KEY,s");
    Serial.println ("");
    Serial.print("Colocar teclado N.");
    Serial.print (countHasierakoZirkuituX + 1);
    Serial.println( " y pulsar boton");
    Serial.println ("");
    do
    {
      do
      {
        buttonTestLedak ();
      } while (buttonStateTestLedak == LOW); // itxaron panelak testeatzeko botoia sakatu arte
      for (int i = 0; i < pinNumber; i++)
      {
        for (int k = 0; k < pinNumber; k++)
        {
          //Serial.println (countHasierakoZirkuituX); // egiaztatzeko zenbat aldiz betetzen dira 2 for horiek
          pinHighD = pinHigh + 5; // 1. pinHighD-a zein den kalkulatzeko
          pinLowD = pinLow  + 5;
          pinHighA = pinHigh + 53; // 1. pinHighA-a kalkulatzeko
          pinHighA = pinHigh + 53; // 1. pinHighA-a kalkulatzeko
          pinLowA = pinLow  + 53;
          pinMode (pinHighD, OUTPUT);
          pinMode (pinLowD, OUTPUT);
          digitalWrite (pinHighD, HIGH);
          digitalWrite (pinLowD, LOW);
          float v_pinHighAFloat = mapFloat (analogRead (pinHighA), 0, 1023, 0, 5);
          float v_pinLowAFloat = mapFloat (analogRead (pinLowA), 0, 1023, 0, 5);

          if (countHasierakoZirkuituX == 0)
          {
            testArray1[i][k].kyNumber = countHasierakoZirkuituX + 1;
            testArray1[i][k].pinHigh = pinHigh;
            testArray1[i][k].pinLow = pinLow;
            testArray1[i][k].voltpinHigh = v_pinHighAFloat;
            testArray1[i][k].voltpinLow = v_pinLowAFloat;
            testArray1[i][k].voltageDrop = v_pinHighAFloat - v_pinLowAFloat;
            if (testArray1[i][k].voltageDrop < 3.8 && testArray1[i][k].voltageDrop > 1.6) {
              testArray1[i][k].diode = true;
            } else {
              testArray1[i][k].diode = false;
            }
            if (testArray1[i][k].voltageDrop >= 0.0 && testArray1[i][k].voltageDrop < 0.5 && testArray1[i][k].pinHigh != testArray1[i][k].pinLow) {
              testArray1[i][k].shortCut = true;
            } else {
              testArray1[i][k].shortCut = false;
            }


            //------------------------------------
            /*Serial.print  (i);
              Serial.print (",   ");
              Serial.print  (k);
              Serial.print (",   ");*/
            Serial.print (testArray1[i][k].kyNumber);
            Serial.print (",   ");
            Serial.print (testArray1[i][k].pinHigh);
            Serial.print (",   ");
            Serial.print (testArray1[i][k].pinLow);
            Serial.print (",   ");
            Serial.print (testArray1[i][k].voltpinHigh, 2);
            Serial.print (",   ");
            Serial.print  (testArray1[i][k].voltpinLow, 2);
            Serial.print (",   ");
            Serial.print  (testArray1[i][k].voltageDrop, 2);
            Serial.print (",   ");
            Serial.print  (testArray1[i][k].diode);
            Serial.print (",   ");
            Serial.println (testArray1[i][k].shortCut);
            //delay (1);
            //------------------------------------
          }

          if (countHasierakoZirkuituX == 1)
          {
            testArray2[i][k].kyNumber = countHasierakoZirkuituX + 1;
            testArray2[i][k].pinHigh = pinHigh;
            testArray2[i][k].pinLow = pinLow;
            testArray2[i][k].voltpinHigh = v_pinHighAFloat;
            testArray2[i][k].voltpinLow = v_pinLowAFloat;
            testArray2[i][k].voltageDrop = v_pinHighAFloat - v_pinLowAFloat;
            if (testArray2[i][k].voltageDrop < 3.8 && testArray2[i][k].voltageDrop > 1.6) {
              testArray2[i][k].diode = true;
            } else {
              testArray2[i][k].diode = false;
            }
            if (testArray2[i][k].voltageDrop >= 0.0 && testArray2[i][k].voltageDrop < 0.5 && testArray2[i][k].pinHigh != testArray2[i][k].pinLow) {
              testArray2[i][k].shortCut = true;
            } else {
              testArray2[i][k].shortCut = false;
            }

            //------------------------------------
            /*Serial.print  (i);
              Serial.print (",   ");
              Serial.print  (k);
              Serial.print (",   ");*/
            Serial.print (testArray2[i][k].kyNumber);
            Serial.print (",   ");
            Serial.print (testArray2[i][k].pinHigh);
            Serial.print (",   ");
            Serial.print (testArray2[i][k].pinLow);
            Serial.print (",   ");
            Serial.print (testArray2[i][k].voltpinHigh, 2);
            Serial.print (",   ");
            Serial.print  (testArray2[i][k].voltpinLow, 2);
            Serial.print (",   ");
            Serial.print  (testArray2[i][k].voltageDrop, 2);
            Serial.print (",   ");
            Serial.print (testArray2[i][k].diode);
            Serial.print (",   ");
            Serial.println (testArray2[i][k].shortCut);
            //delay (1);
            //------------------------------------
          }

          if (countHasierakoZirkuituX == 2)
          {
            testArray3[i][k].kyNumber = countHasierakoZirkuituX + 1;
            testArray3[i][k].pinHigh = pinHigh;
            testArray3[i][k].pinLow = pinLow;
            testArray3[i][k].voltpinHigh = v_pinHighAFloat;
            testArray3[i][k].voltpinLow = v_pinLowAFloat;
            testArray3[i][k].voltageDrop = v_pinHighAFloat - v_pinLowAFloat;
            if (testArray3[i][k].voltageDrop < 3.8 && testArray3[i][k].voltageDrop > 1.6) {
              testArray3[i][k].diode = true;
            } else {
              testArray3[i][k].diode = false;
            }
            if (testArray3[i][k].voltageDrop >= 0.0 && testArray3[i][k].voltageDrop < 0.5 && testArray3[i][k].pinHigh != testArray3[i][k].pinLow) {
              testArray3[i][k].shortCut = true;
            } else {
              testArray3[i][k].shortCut = false;
            }

            //------------------------------------
            /*Serial.print  (i);
              Serial.print (",   ");
              Serial.print  (k);
              Serial.print (",   ");*/
            Serial.print (testArray3[i][k].kyNumber);
            Serial.print (",   ");
            Serial.print (testArray3[i][k].pinHigh);
            Serial.print (",   ");
            Serial.print (testArray3[i][k].pinLow);
            Serial.print (",   ");
            Serial.print (testArray3[i][k].voltpinHigh, 2);
            Serial.print (",   ");
            Serial.print  (testArray3[i][k].voltpinLow, 2);
            Serial.print (",   ");
            Serial.print  (testArray3[i][k].voltageDrop, 2);
            Serial.print (",   ");
            Serial.print  (testArray3[i][k].diode);
            Serial.print (",   ");
            Serial.println (testArray3[i][k].shortCut);
            //delay (1);
            //------------------------------------
          }

          pinMode (pinHighD, INPUT); // behin tentsio irakurketa egin ondoren deskonektatu
          pinMode (pinLowD, INPUT);

          pinLow++;
        }

        pinHigh++;
        pinLow = pinLow - pinNumber; //hasieratzeko pinLowA-a
      }
      pinHigh = pinHigh - pinNumber; //hasieratzeko pinHighA-a

      countHasierakoZirkuituX++;
      //Serial.println ("");
      //Serial.println (countHasierakoZirkuituX);
      //Serial.println ("");
      Serial.println ("");
      if (countHasierakoZirkuituX < 3) {
        Serial.print("Colocar teclado N.");
        Serial.print (countHasierakoZirkuituX + 1);
        Serial.println( " y pulsa boton");
        Serial.println ("");
      }
      buttonStateTestLedak = LOW;

    } while (countHasierakoZirkuituX != 3);
    f2 = HIGH;


    if (countHasierakoZirkuituX == 3) // 3 panel testeatzeko
    {
      for (int i = 0; i < pinNumber; i++)
      {
        for (int k = 0; k < pinNumber; k++)
        {
          if (((testArray2[i][k].diode) == (testArray3[i][k].diode)) && ((testArray2[i][k].diode) != (testArray1[i][k].diode)))
          {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky1 diodo defectuoso");
            failure = true;
          }
          if (((testArray1[i][k].diode) == (testArray3[i][k].diode)) && ((testArray1[i][k].diode) != (testArray2[i][k].diode)))
          {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky2 diodo defectuoso");
            failure = true;
          }
          if (((testArray1[i][k].diode) == (testArray2[i][k].diode)) && ((testArray1[i][k].diode) != (testArray3[i][k].diode)))
          {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky3 diodo defectuoso");
            failure = true;
          }
          if (((testArray2[i][k].shortCut) == (testArray3[i][k].shortCut)) && ((testArray2[i][k].shortCut) != (testArray1[i][k].shortCut)))
          {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky1 cortocircuito!");
            failure = true;
          }
          if (((testArray1[i][k].shortCut) == (testArray3[i][k].shortCut)) && ((testArray1[i][k].shortCut) != (testArray2[i][k].shortCut)))
          {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky2 cortocircuito!");
            failure = true;
          }
          if (((testArray1[i][k].shortCut) == (testArray2[i][k].shortCut)) && ((testArray1[i][k].shortCut) != (testArray3[i][k].shortCut)))
          {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky3 cortocircuito!");
            failure = true;
          }
          //delay (1);
          pinLow++;
        }
        pinHigh++;
        pinLow = pinLow - pinNumber; //hasieratzeko pinLowA-a
      }
      pinHigh = pinHigh - pinNumber; //hasieratzeko pinHighA-a
    }
    ////delay (10);
    countHasierakoZirkuituX = 0;
    //Serial.println ("");
    //Serial.print ("failure: ");
    //Serial.println (failure);
    if (failure == true) {
      Serial.println ("");
      Serial.println ("cambiar teclado defectuoso y volver a empezar!");
      Serial.println ("");
    } else {
      f1 = LOW;
    }
  }
}


void f2_testeatzen () {
  while (f2 == HIGH) {
    failure = false;
    Serial.println ( "TEST REMESA");
    Serial.println ("");
    Serial.print("Colocar teclado a testear y pulsar boton");
    Serial.println ("");
    Serial.println ();
    do
    {
      do
      {
        buttonTestLedak ();
      } while (buttonStateTestLedak == LOW); // itxaron panelak testeatzeko botoia sakatu arte
      for (int i = 0; i < pinNumber; i++)
      {
        for (int k = 0; k < pinNumber; k++)
        {
          //Serial.println (countHasierakoZirkuituX); // egiaztatzeko zenbat aldiz betetzen dira 2 for horiek
          pinHighD = pinHigh + 5; // 1. pinHighD-a zein den kalkulatzeko
          pinLowD = pinLow  + 5;
          pinHighA = pinHigh + 53; // 1. pinHighA-a kalkulatzeko
          pinHighA = pinHigh + 53; // 1. pinHighA-a kalkulatzeko
          pinLowA = pinLow  + 53;
          pinMode (pinHighD, OUTPUT);
          pinMode (pinLowD, OUTPUT);
          digitalWrite (pinHighD, HIGH);
          digitalWrite (pinLowD, LOW);
          float v_pinHighAFloat = mapFloat (analogRead (pinHighA), 0, 1023, 0, 5);
          float v_pinLowAFloat = mapFloat (analogRead (pinLowA), 0, 1023, 0, 5);

          if (countHasierakoZirkuituX == 0)
          {
            testArray[i][k].kyNumber = countHasierakoZirkuituX + 1;
            testArray[i][k].pinHigh = pinHigh;
            testArray[i][k].pinLow = pinLow;
            testArray[i][k].voltpinHigh = v_pinHighAFloat;
            testArray[i][k].voltpinLow = v_pinLowAFloat;
            testArray[i][k].voltageDrop = v_pinHighAFloat - v_pinLowAFloat;
            if (testArray[i][k].voltageDrop < 3.8 && testArray[i][k].voltageDrop > 1.6) {
              testArray[i][k].diode = true;
            } else {
              testArray[i][k].diode = false;
            }
            if (testArray[i][k].voltageDrop >= 0.0 && testArray[i][k].voltageDrop < 0.5 && testArray[i][k].pinHigh != testArray[i][k].pinLow) {
              testArray[i][k].shortCut = true;
            } else {
              testArray[i][k].shortCut = false;
            }


            //------------------------------------
            /*Serial.print  (i);
              Serial.print (",   ");
              Serial.print  (k);
              Serial.print (",   ");*/
            Serial.print (testArray[i][k].kyNumber);
            Serial.print (",   ");
            Serial.print (testArray[i][k].pinHigh);
            Serial.print (",   ");
            Serial.print (testArray[i][k].pinLow);
            Serial.print (",   ");
            Serial.print (testArray[i][k].voltpinHigh, 2);
            Serial.print (",   ");
            Serial.print  (testArray[i][k].voltpinLow, 2);
            Serial.print (",   ");
            Serial.print  (testArray[i][k].voltageDrop, 2);
            Serial.print (",   ");
            Serial.print  (testArray[i][k].diode);
            Serial.print (",   ");
            Serial.println (testArray[i][k].shortCut);
            //delay (1);
            //------------------------------------
          }

          pinMode (pinHighD, INPUT); // behin tentsio irakurketa egin ondoren deskonektatu
          pinMode (pinLowD, INPUT);

          pinLow++;
        }

        pinHigh++;
        pinLow = pinLow - pinNumber; //hasieratzeko pinLowA-a
      }
      pinHigh = pinHigh - pinNumber; //hasieratzeko pinHighA-a

      countHasierakoZirkuituX++;
      //Serial.println ("");
      //Serial.println (countHasierakoZirkuituX);
      //Serial.println ("");
      Serial.println ("");
      if (countHasierakoZirkuituX < 1) {
        Serial.print("Colocar teclado a testear");
        Serial.print (countHasierakoZirkuituX + 1);
        Serial.println( " y pulsa boton");
        Serial.println ("");
      }
      buttonStateTestLedak = LOW;

    } while (countHasierakoZirkuituX != 1);
    f3 = HIGH;


    if (countHasierakoZirkuituX == 1) // 3 panel testeatzeko
    {
      for (int i = 0; i < pinNumber; i++)
      {
        for (int k = 0; k < pinNumber; k++)
        {
          if ((testArray1[i][k].diode) != (testArray[i][k].diode))  {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky diodo defectuoso");
            failure = true;
          }

          if ((testArray1[i][k].shortCut) != (testArray[i][k].shortCut))  {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println ("  ky1 cortocircuito!");
            failure = true;
          }

          //delay (1);
          pinLow++;
        }
        pinHigh++;
        pinLow = pinLow - pinNumber; //hasieratzeko pinLowA-a
      }
      pinHigh = pinHigh - pinNumber; //hasieratzeko pinHighA-a
    }
    ////delay (10);
    countHasierakoZirkuituX = 0;
    //Serial.println ("");
    //Serial.print ("failure: ");
    //Serial.println (failure);
    if (failure == true) {
      Serial.println ("");
      Serial.println ("teclado defectuoso, retirar!");
      Serial.println ("");
    } else {
      f2 = LOW;
    }
  }
}


void f3_testeatzen_ledak () {
  while (f3 == HIGH) {
    failure = false;
    Serial.print("Test leds 100ms. Pulsar boton para continuar");
    Serial.println ();
    Serial.println ("");
    do
    {
      do
      {
        buttonTestLedak ();
      } while (buttonStateTestLedak == LOW); // itxaron panelak testeatzeko botoia sakatu arte
      for (int i = 0; i < pinNumber; i++)
      {
        for (int k = 0; k < pinNumber; k++)
        {
          //Serial.println (countHasierakoZirkuituX); // egiaztatzeko zenbat aldiz betetzen dira 2 for horiek
          pinHighD = pinHigh + 5; // 1. pinHighD-a zein den kalkulatzeko
          pinLowD = pinLow  + 5;

          if ((testArray1[i][k].diode) == 1)  {
            Serial.print (pinHigh);
            Serial.print ("-");
            Serial.print (pinLow);
            Serial.println (" diodo test");
            pinMode (pinHighD, OUTPUT);
            pinMode (pinLowD, OUTPUT);
            digitalWrite (pinHighD, HIGH);
            digitalWrite (pinLowD, LOW);
            delay (500);
            pinMode (pinHighD, INPUT); // behin tentsioa eman ondoren deskonektatu
            pinMode (pinLowD, INPUT);
          }
          pinLow++;
        }

        pinHigh++;
        pinLow = pinLow - pinNumber; //hasieratzeko pinLowA-a
      }
      pinHigh = pinHigh - pinNumber; //hasieratzeko pinHighA-a

      countHasierakoZirkuituX++;

      Serial.println ("");
      if (countHasierakoZirkuituX < 1) {
        Serial.print("Colocar teclado a testear");
        Serial.print (countHasierakoZirkuituX + 1);
        Serial.println( " y pulsa boton");
        Serial.println ("");
      }
      buttonStateTestLedak = LOW;
    } while (countHasierakoZirkuituX != 1);
    f4 = HIGH;
    ////delay (10);
    countHasierakoZirkuituX = 0;
    f3 = LOW;
  }
}

void f4_testButtons () {
  while (f4 == HIGH) {

    failure = false;
    Serial.println("Test pulsadores. Pulsar boton y luego tecla a testear para continuar");
    Serial.println ("");
    Serial.println("Al finalizar Pulsar boton para testear siguiente teclado leds y botones");
    Serial.println ("");

    do
    {
      buttonTestLedak ();
    } while (buttonStateTestLedak == LOW); // itxaron panelak testeatzeko botoia sakatu arte

    buttonStateTestLedak = LOW;
    f4 = LOW;
    f5 = HIGH;
  }
}

void f5_testingButtons () {
  while (f5 == HIGH) {

    for (int i = 0; i < pinNumber; i++)
    {
      for (int k = 0; k < pinNumber; k++) {
        pinHighD = pinHigh + 5; // 1. pinHighD-a zein den kalkulatzeko
        pinLowD = pinLow  + 5;
        pinHighA = pinHigh + 53; // 1. pinHighA-a kalkulatzeko
        pinLowA = pinLow  + 53;
        pinMode (pinHighD, OUTPUT);
        pinMode (pinLowD, OUTPUT);
        digitalWrite (pinHighD, HIGH);
        digitalWrite (pinLowD, LOW);
        float v_pinHighAFloat = mapFloat (analogRead (pinHighA), 0, 1023, 0, 5);
        float v_pinLowAFloat = mapFloat (analogRead (pinLowA), 0, 1023, 0, 5);


        if (v_pinHighAFloat - v_pinLowAFloat < 0.4 && v_pinHighAFloat - v_pinLowAFloat > 0.1)  { // sakagailuErresistentzia = 18 ohm
          if (pinHighD < pinLowD) {
            buttonDataArray[i][k].pinHigh = pinHigh;
            buttonDataArray[i][k].pinLow = pinLow;
            buttonDataArray[i][k].voltpinHigh = v_pinHighAFloat;
            buttonDataArray[i][k].voltpinLow = v_pinLowAFloat;
            buttonDataArray[i][k].voltageDrop = v_pinHighAFloat - v_pinLowAFloat;
            buttonDataArray[i][k].resButton =  buttonDataArray[i][k].voltageDrop / ((5.0 - v_pinHighAFloat) / 102.0);



            if (buttonDataArray[i][k].stateButton == LOW) {
              Serial.println ("");
              Serial.print (buttonDataArray[i][k].pinHigh);
              Serial.print (",   ");
              Serial.print (buttonDataArray[i][k].pinLow);
              Serial.print (",   ");
              /*Serial.print (buttonDataArray[i][k].voltpinHigh, 2);
                Serial.print (",   ");
                Serial.print  (buttonDataArray[i][k].voltpinLow, 2);
                Serial.print (",   ");
                Serial.print  (buttonDataArray[i][k].voltageDrop, 2);
                Serial.print (",   ");*/
              Serial.print  (buttonDataArray[i][k].resButton, 2);
              Serial.print (" ohms");
              Serial.println ("");
            }


            buttonDataArray[i][k].stateButton = HIGH;


            pinMode (pinHighD, INPUT);
            pinMode (pinLowD, INPUT);


          }
        }
        if (((v_pinHighAFloat - v_pinLowAFloat < 0.4 && v_pinHighAFloat - v_pinLowAFloat > 0.1) == LOW) && buttonDataArray[i][k].stateButton == HIGH)  {

          if (pinHighD < pinLowD) {

            buttonDataArray[i][k].stateButton = LOW;
          }
        }

        pinLow++;
      }

      pinHigh++;
      pinLow = pinLow - pinNumber; //hasieratzeko pinLowA-a
    }
    pinHigh = pinHigh - pinNumber; //hasieratzeko pinHighA-a

    buttonTestLedak ();
    if  (buttonStateTestLedak == HIGH) {
      f2 = HIGH;
      f5 = LOW;
    }
  }
  buttonStateTestLedak = LOW;
}


void f6_datorrena ()
{
  while (f6 == HIGH) {
    Serial.println ("");
    Serial.println ("honeraino!");
    Serial.println ("");


    f6 = LOW;
  }
}

void   buttonTestLedak () {
  debouncer.update(); // Update the Bounce instance
  if ( debouncer.fell() ) {  // Call code if button transitions from HIGH to LOW
    buttonStateTestLedak = HIGH; // zatitzailea bi
  }
}
