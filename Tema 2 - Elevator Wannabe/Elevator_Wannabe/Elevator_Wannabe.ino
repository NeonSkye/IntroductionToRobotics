#include "pitches.h"

const int ElevatorBuzzPin = 3;
const int Function_LEDPin = 4;
byte FUNC_LED_State = 1;

const int floor1_ButtonPin = 8;
const int floor1_LEDPin = 5;

const int floor2_ButtonPin = 9;
const int floor2_LEDPin = 6;

const int floor3_ButtonPin = 10;
const int floor3_LEDPin = 7;

int floorPointer = 0;
int floorTarget = 0;

byte BTN_Floor1_State = 0;
byte BTN_Floor2_State = 0;
byte BTN_Floor3_State = 0;

byte LED_Floor1_State = 1;
byte LED_Floor2_State = 0;
byte LED_Floor3_State = 0;

int Floor_Array[3] = {LED_Floor1_State, LED_Floor2_State, LED_Floor3_State};

int Moving_Elevator[2] = {NOTE_G3, NOTE_B3};
int Arrival_Ring[6] = {NOTE_D7, NOTE_B6, NOTE_A6, NOTE_C7, NOTE_E7};
int Door_Sound[4] = {NOTE_AS3, NOTE_G3, NOTE_E3, NOTE_CS3};

byte RingArrival = 0;
int thisNote = 0;
int doorNote = 2;
byte doorOpenSound = 1;

unsigned long previousMillis;
unsigned long startMillis;
const long interval = 3000;
const long State_Interval = 150;
const long Ring_Interval = 150;
const long Note_Duration = 150;
unsigned long prevRingMillis;

unsigned int lastDebounceTime_BTN1 = 0;
unsigned int lastDebounceTime_BTN2 = 0;
unsigned int lastDebounceTime_BTN3 = 0;
unsigned int debounceDelay = 100;

byte reading_Floor1 = LOW;
byte lastReading_Floor1 = LOW;

byte reading_Floor2 = LOW;
byte lastReading_Floor2 = LOW;

byte reading_Floor3 = LOW;
byte lastReading_Floor3 = LOW;

void setup() {
  pinMode (floor1_ButtonPin, INPUT_PULLUP);
  pinMode (floor2_ButtonPin, INPUT_PULLUP);
  pinMode (floor3_ButtonPin, INPUT_PULLUP);

  pinMode (floor1_LEDPin, OUTPUT);
  pinMode (floor2_LEDPin, OUTPUT);
  pinMode (floor3_LEDPin, OUTPUT);
  pinMode (Function_LEDPin, OUTPUT);

  startMillis = millis();
  Serial.begin(9600);
}

void loop() {

  BTN_Floor1_State = digitalRead(floor1_ButtonPin);
  reading_Floor1 = digitalRead(floor1_ButtonPin);

  BTN_Floor2_State = digitalRead(floor2_ButtonPin);
  reading_Floor2 = digitalRead(floor2_ButtonPin);
  
  BTN_Floor3_State = digitalRead(floor3_ButtonPin);
  reading_Floor3 = digitalRead(floor3_ButtonPin);

  if (reading_Floor1 != lastReading_Floor1) { 
    lastDebounceTime_BTN1 = millis();
  }
  if (reading_Floor2 != lastReading_Floor2) {
    lastDebounceTime_BTN2 = millis();
  }
  if (reading_Floor3 != lastReading_Floor3) {
    lastDebounceTime_BTN3 = millis();
  }

  unsigned long currentMillis = millis();
  

if (floorPointer == floorTarget) 
{
  doorNote = 0;
  digitalWrite(Function_LEDPin, 1);
    if(RingArrival == 1)
  {
      tone(ElevatorBuzzPin, Arrival_Ring[thisNote], Note_Duration);
     
      if((currentMillis - prevRingMillis) >= Ring_Interval) {
        thisNote++;
        prevRingMillis = currentMillis;
        if (thisNote == 5)
          RingArrival = 0;
      }
  }
    if(BTN_Floor1_State == 0)
    {
        if ((millis() - lastDebounceTime_BTN1) > debounceDelay)
        {
        floorTarget = 0;
        startMillis = currentMillis;
        doorOpenSound = 1;
        }
    }

    if(BTN_Floor2_State == 0)
    {
      if ((millis() - lastDebounceTime_BTN2) > debounceDelay)
      {
      floorTarget = 1;
      startMillis = currentMillis;
      doorOpenSound = 1;
      }
    }

    if(BTN_Floor3_State == 0)
    {
      if ((millis() - lastDebounceTime_BTN3) > debounceDelay)
      {
      floorTarget = 2;
      startMillis = currentMillis;
      doorOpenSound = 1;
      }
    }
} else
  if(currentMillis - previousMillis >= State_Interval)
{
    previousMillis = currentMillis;
    if (FUNC_LED_State == LOW)
    {
        FUNC_LED_State = HIGH;
    }   
    else {
        FUNC_LED_State = LOW;
    }
    digitalWrite(Function_LEDPin, FUNC_LED_State);
}

  if(floorTarget != floorPointer && doorOpenSound == 1)
  {

      tone(ElevatorBuzzPin, Door_Sound[doorNote], Note_Duration);
     
      if((currentMillis - prevRingMillis) >= 500) {
        doorNote++;
        prevRingMillis = currentMillis;
      
      if (doorNote == 4)
        doorOpenSound = 0;
  }
  }
  Serial.println(doorNote);
  if(floorTarget > floorPointer && doorOpenSound == 0)
    {
      
      tone(ElevatorBuzzPin, Moving_Elevator[0], 500);
      tone(ElevatorBuzzPin, Moving_Elevator[1], 500);
      thisNote = 0;
      doorNote = 0;

      if(currentMillis - startMillis >= interval)
      {
        Floor_Array[floorPointer] = 0;
        floorPointer++;
        Floor_Array[floorPointer] = 1;
        startMillis = currentMillis;
        RingArrival = 1;
      }
    }

      if(floorTarget < floorPointer && doorOpenSound == 0)
    {
      tone(ElevatorBuzzPin, Moving_Elevator[0], 500);
      tone(ElevatorBuzzPin, Moving_Elevator[1], 500);
      thisNote = 0;
      doorNote = 0;

  if(currentMillis - startMillis >= interval)
      {
        Floor_Array[floorPointer] = 0;
        floorPointer--;
        Floor_Array[floorPointer] = 1;
        startMillis = currentMillis;
        RingArrival = 1;
      }
    }
  LED_Floor1_State = Floor_Array[0];
  LED_Floor2_State = Floor_Array[1];
  LED_Floor3_State = Floor_Array[2];

  digitalWrite(floor1_LEDPin, LED_Floor1_State);
  digitalWrite(floor2_LEDPin, LED_Floor2_State);
  digitalWrite(floor3_LEDPin, LED_Floor3_State);
}
