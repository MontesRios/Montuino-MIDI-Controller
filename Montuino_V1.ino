// ## Version 1 : Montuino MIDI Controller ##
// Controlador MIDI basico con 3 botones, 3 leds, dos potenciometros (10K) y sensor infrarrojo (tcrt5000).

// = = Uso del controlador = =
// Boton 1 : Envia mensaje de cambio de control MIDI modificando el valor con el potenciometro 1 [canal 4].
           // Envia nota MIDI modificando el valor de la nota con el potenciometro 1 [canal 1].
// Boton 2 : Envia mensaje de cambio de control MIDI modificando el valor con el potenciometro 2. [canal 5]
           // Envia nota MIDI modificando el valor de la nota con el potenciometro 2 [canal 2].
// Boton 3 : Envia mensaje de cambio de control MIDI modificando el valor con el sensor. [canal 6]
          // Envia nota MIDI modificando el valor de la nota con el sensor [canal 3].

#include <MIDI.h>
//Iniciando MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

//Declaracion de entradas digitales
static const int button1 = 2;
static const int button2 = 3;
static const int button3 = 4;
static const int led1 = 10;
static const int led2 = 12;
static const int led3 = 11;

//Declaracion de entradas analogas
static const int potPin1 = A0;
static const int potPin2 = A1;
static const int sensorPin = A2;

//Estados de los botones
boolean currentB1State = 0;
boolean lastB1State = 0;
boolean currentB2State = 0;
boolean lastB2State = 0;
boolean currentB3State = 0;
boolean lastB3State = 0;

void setup() {

//Iniciamos canales MIDI  
MIDI.begin(1);
MIDI.begin(2);
MIDI.begin(3);
MIDI.begin(4);
MIDI.begin(5);
MIDI.begin(6);
//Iniciamos Puerto Serial a 9600 baudios
Serial.begin(9600);
//Declaramos los pines como E/S
    pinMode(button1,INPUT);
    pinMode(button2,INPUT);
      pinMode(led1,OUTPUT);
      pinMode(led2,OUTPUT);
      pinMode(led3,OUTPUT);
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
          lastB1State = digitalRead(button1);
          lastB2State = digitalRead(button2);
}

//Funcion leer boton 1
inline void readB1()
{
  currentB1State = digitalRead(button1);
    if (currentB1State != lastB1State){                
      MIDI.sendNoteOn(readPot1(), currentB1State == LOW ? 0 : 127, 1);                                                
      digitalWrite(led1, currentB1State);              
      lastB1State = currentB1State;       
     }   
}

// -------------------------------------

//Funcion leer boton 2
inline void readB2()
{
  currentB2State = digitalRead(button2);
    if (currentB2State != lastB2State){                
      MIDI.sendNoteOn(readPot2(), currentB2State == LOW ? 0 : 127, 2);
      digitalWrite(led2, currentB2State);
      lastB2State = currentB2State;
  }                 
}

//Funcion leer boton 3
inline void readB3()
{
  currentB3State = digitalRead(button3);
    if (currentB3State != lastB3State){                
      MIDI.sendNoteOn(readSensor(), currentB3State == LOW ? 0 : 127, 3);          
      digitalWrite(led3, currentB3State);              
      lastB3State = currentB3State;             
  }                 
}
            
// -------------------------------------

//Funcion leer potenciometro 1
int readPot1()
{
   int potVal = analogRead(potPin1);//read data from potentiometer
   byte velocity = map(potVal, 0, 1023, 0, 127);
   return velocity;
}


// -------------------------------------

//Funcion leer potenciometro 2
int readPot2()
{
   int potVal2 = analogRead(potPin2);//read data from potentiometer
   byte velocity2 = map(potVal2, 0, 1023, 0, 127);
   return velocity2;
}

// -------------------------------------

//Funcion leer sensor
int readSensor()
{
   int sensorValue = analogRead(sensorPin);
   byte velocity3 = map(sensorValue, 0, 1023, 0 , 127);
   return velocity3; 
}

// -------------------------------------

void loop() 
{  
  readB1();
  if (currentB1State == HIGH){MIDI.sendControlChange(16,readPot1(),4);}  
  readB2();
  if (currentB2State == HIGH){MIDI.sendControlChange(16,readPot2(),5);}  
  readB3();
  if (currentB3State == HIGH){MIDI.sendControlChange(16,readSensor(),6);}
 }

