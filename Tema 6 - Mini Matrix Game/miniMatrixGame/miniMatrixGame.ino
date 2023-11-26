#include "LedControl.h" // need the library
const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte matrixSize = 8;
const int pinX = A1;
const int pinY = A0;
const int pinSW = 2;
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER
byte matrixBrightness = 2;

// Objects: 1 = WALL, 2 = PLAYER, 3 = BOMB
byte matrix[matrixSize][matrixSize] = {
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 3, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 2, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1}
};

// Used for blinking the player;
unsigned long int playerBlinkDelay = 70;
unsigned long int startPlayerBlink = 0;
unsigned long int statePlayerBlink = 0;
 

unsigned long int bombBlinkDelay = 500;
unsigned long int startBombBlink = 0;
unsigned long int stateBombBlink = 0;
bool bombPlaced = false;
// Joystick values and thresholds
int xValue = 0;
int yValue = 0;

int minThreshold = 400;
int maxThreshold = 600;
bool joyMoved = false;

// button state
//byte swState = LOW; commented for now, I can't get bombs to work
//byte lastSwState = LOW;

void setup() {
pinMode(pinSW, INPUT_PULLUP);
lc.shutdown(0, false); // turn off power saving, enables display
lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
lc.clearDisplay(0);// clear screen
for (int row = 0; row < matrixSize; row++) {
  for (int col = 0; col < matrixSize; col++) {
    if (matrix[row][col] < 2)
    lc.setLed(0, row, col, matrix[row][col]);
    }
  }
Serial.begin(9600);
}

void loop() {
  blinkLed(getObjRow(2), getObjCol(2), 2); // BLINK PLAYER
  blinkLed(getObjRow(3), getObjCol(3), 3); // BLINK DEMONSTRATION BOMB
  // this would make bombs move and blink! too bad I can't get the bombs to [REDACTED] move
  /* if (bombPlaced == true) 
  {
  moveObject(getObjRow(3), getObjCol(3), 1, 3); // MOVE BOMB
  blinkLed(getObjRow(3), getObjCol(3), 3); // BLINK BOMB
  } */
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  // swState = digitalRead(pinSW); TODO: for bomb

  // These are all for moving the player
  if(xValue > maxThreshold && joyMoved == false) {
    moveObject(getObjRow(2), getObjCol(2), 1, 2); // GO UP
    joyMoved = true;
  }
  if (xValue < minThreshold && joyMoved == false) {
    moveObject(getObjRow(2), getObjCol(2), 2, 2); // GO DOWN
    joyMoved = true;
  }
  if (yValue > maxThreshold && joyMoved == false) {
    moveObject(getObjRow(2), getObjCol(2), 3, 2); // GO LEFT
    joyMoved = true;
  }
  if (yValue < minThreshold && joyMoved == false) {
    moveObject(getObjRow(2), getObjCol(2), 4, 2); // GO RIGHT
    joyMoved = true;
  }
  
  /* if(swState != lastSwState) {
    if(swState == LOW) {
      setObjectCoords(getObjRow(2)-1, getObjCol(2), 3); 
      bombPlaced = true;
    }
    lastSwState = swState;
  } */ // Bomb placement. TODO

  if(xValue >= minThreshold && xValue <= maxThreshold && yValue >= minThreshold && yValue <= maxThreshold) {
    joyMoved = false;
  }
}

int blinkLed(int row, int col, int object) { 
  // TODO: implement better blink function to work with multiple bombs. (for now it would only blink the first bomb it finds)
  switch(object) {
    case 2:
    if (millis() - startPlayerBlink >= playerBlinkDelay) {
    statePlayerBlink = !statePlayerBlink;
    lc.setLed(0, row, col, statePlayerBlink);
    startPlayerBlink = millis();
    }
    break;
    case 3:
    if (millis() - startBombBlink >= bombBlinkDelay) {
    stateBombBlink = !stateBombBlink;
    lc.setLed(0, row, col, stateBombBlink);
    startBombBlink = millis();
    break;
    }
  }
}

int getObjRow(int object)
{
  int result  = 0;
  
  for (int row = 0; row < matrixSize; row++) {
    
    for (int col = 0; col < matrixSize; col++)
    {
      if(matrix[row][col] == object) {
      result = row;
      break;
      }
    }
  }
  
  return result;
}

int getObjCol(int object)
{
  int result;
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++)
    {
      if(matrix[row][col] == object){
      result = col;
      break;
      }
    }
  }
  return result;
}

// Function to move bomb. For some reason it simply does not work. It just doesn't want to move. TODO
/* int moveBomb(int row, int col) {
  Serial.println(row);
  if(matrix[row-1][col] == 0) 
  {
    setObjectCoords(row-1, col, 3);

  } else {
    matrix[row-1][col] == 0;
    lc.setLed(0, row-2, col, 0);
    bombPlaced = false;
  }
}
*/
int moveObject(int row, int col, int direction, int object)
{

  // if(object == 3) moveBomb(row, col); // call function for bomb movement instead
  //else  
  switch(direction) {
    case 1:  // MOVE UP
      matrix[row][col] = 0;
      lc.setLed(0, row, col, 0);
      {
        if(row==0) 
          {
            setObjectCoords(7, col, object);
          }
        else setObjectCoords(row-1, col, object);
      }
    break;
    case 2:  // MOVE DOWN
      matrix[row][col] = 0;
      lc.setLed(0, row, col, 0);
      if(row==7) 
      {
        setObjectCoords(0, col, object);
      }
      else setObjectCoords(row+1, col, object);
    break;
    case 3: // MOVE LEFT
      matrix[row][col] = 0;
      lc.setLed(0, row, col, 0);
      if(col==0) 
      {
        setObjectCoords(row, 7, object);
      }
      else setObjectCoords(row, col-1, object);
    break;
    case 4: // MOVE RIGHT
      matrix[row][col] = 0;
      lc.setLed(0, row, col, 0);
      if(col==7)
      {
        setObjectCoords(row, 0, object);
      }
      else setObjectCoords(row, col+1, object);
    break;
    default:
    break;
  }
}

int setObjectCoords(int row, int col, int object)
{
  matrix[row][col] = object;
  //lc.setLed(0, row, col, 1);
}

