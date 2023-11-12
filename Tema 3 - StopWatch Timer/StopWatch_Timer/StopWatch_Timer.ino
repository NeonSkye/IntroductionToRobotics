// defined pins for the timer controls
const int startButtonPin = 3;
const int resetButtonPin = 2;
const int lapButtonPin = 8;

// defining states so buttons don't repeat their action when held down
byte startButtonState = LOW;
byte resetButtonState = LOW;
byte lapButtonState = LOW;

byte lastStartButtonState = LOW;
byte lastResetButtonState = LOW;
byte lastLapButtonState = LOW;

byte startTimer = 0; // if 1, the stopwatch counts, otherwise it's paused

// Debounce variables for button debouncing 

byte lastDebounceTimeStartBtn = 0;
byte lastDebounceTimeResetBtn = 0;
byte lastDebounceTimeLapBtn = 0;

byte readingStartButton = LOW;
byte lastReadingStartButton = LOW;

byte readingResetButton = LOW;
byte lastReadingResetButton = LOW;

byte readingLapButton = LOW;
byte lastReadingLapButton = LOW;

unsigned int debounceDelay = 100;

unsigned long previousMillis;
unsigned long startMillis;
// defined pins for shift register interfacing
const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12;

// pin definitions for the individual digits of the 7-seg display
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;


const byte regSize = 8;  // register size defined to 8 bits ( 1 byte )

int time = 0;  // this will be used to show the time on the stopwatch

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

int savedTimes[4] = { 0, 0, 0, 0 };  // for saving laps in memory
int lapStorePointer = 0;
byte viewLaps = 0;  // If 1, the display will cycle through all the times
const int displayCount = 4;
const int encodingsNumber = 10;  // Number of encodings for characters 0-9

unsigned long lastIncrement = 0;
unsigned long delayCount = 100;
unsigned long number = 0;
byte displayStart = 0;  // When not 0, the 7-seg display will no longer display 0000


byte byteEncodings[encodingsNumber] = {
  //A B C D E F G DP
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110   // 9
};

// byte encodings for the 3rd digit (so it displays the DP to separate seconds from 10ths)
byte byteEncodingsDP[encodingsNumber] = {
  //A B C D E F G DP
  B11111101,  // 0
  B01100001,  // 1
  B11011011,  // 2
  B11110011,  // 3
  B01100111,  // 4
  B10110111,  // 5
  B10111111,  // 6
  B11100001,  // 7
  B11111111,  // 8
  B11110111   // 9
};


void setup() {
  // Initialize the pin modes for the shift register pins and the display control pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // initikalize pin modes for buttons
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(lapButtonPin, INPUT_PULLUP);

  // Initialize and turn off all display digit control pins
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  Serial.begin(9600);
}


void loop() {

  startButtonState = digitalRead(startButtonPin);
  readingStartButton = digitalRead(startButtonPin);

  resetButtonState = digitalRead(resetButtonPin);
  readingResetButton = digitalRead(resetButtonPin);

  lapButtonState = digitalRead(lapButtonPin);
  readingLapButton = digitalRead(lapButtonPin);

  if (readingStartButton != lastReadingStartButton) {
    lastDebounceTimeStartBtn = millis();
  }
  if (readingResetButton != lastReadingResetButton) {
    lastDebounceTimeResetBtn = millis();
  }
  if (readingLapButton != lastReadingLapButton) {
    lastDebounceTimeLapBtn = millis();
  }


  if (startButtonState != lastStartButtonState) {
    if((millis() - lastDebounceTimeStartBtn) > debounceDelay) {
    if (startButtonState == LOW) {
      startTimer = !startTimer;
      displayStart = 1;
      viewLaps = 0;
    }
    lastStartButtonState = startButtonState;
    }
  }

  if (resetButtonState != lastResetButtonState) {
    if((millis() - lastDebounceTimeResetBtn) > debounceDelay) {
    if (resetButtonState == LOW && startTimer == 0) {
      displayStart = 0;
      startTimer = 0;
      time = 0;
      }
    lastResetButtonState = resetButtonState;
    }
  }
  if (lapButtonState != lastLapButtonState) {
    if((millis() - lastDebounceTimeLapBtn) > debounceDelay) {
    if (lapButtonState == LOW && displayStart == 1 && startTimer == 1) {
      savedTimes[lapStorePointer] = time;
      lapStorePointer++;
      lapStorePointer %= 4;  // should wrap around on 5th press
    }
    if (lapButtonState == LOW && displayStart == 0) {
      if (viewLaps == 0) viewLaps = 1;
      else {
        lapStorePointer++;
        lapStorePointer %= 4;
        }
      }
    lastLapButtonState = lapButtonState;
    }
  }
  if (startTimer == 1) {
    if (millis() - lastIncrement > delayCount) {
      time++;

      lastIncrement = millis();
    }
  }


  writeNumber(time);
  if (displayStart == 0) {
    if (viewLaps == 0)
      writeNumber(10000);
    else
      writeNumber(savedTimes[lapStorePointer]);
  }
}


void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}
void activateDisplay(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}
void writeNumber(int number) {
  int currentNumber = number;
  int displayDigit = 3;  // Start with the least significant digit
  int lastDigit = 0;
  while (currentNumber != 0) {
    lastDigit = currentNumber % 10;
    activateDisplay(displayDigit);
    if (displayDigit == 2) writeReg(byteEncodingsDP[lastDigit]);
    else writeReg(byteEncodings[lastDigit])
      ;
    delay(0);
    displayDigit--;
    currentNumber /= 10;
    writeReg(B00000000);  // Clear the register to avoid ghosting
  }
}
