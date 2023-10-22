const int Pot_Pin_R = A0; // Potentiometer Red
const int Pot_Pin_G = A1; // Potentiometer Green
const int Pot_Pin_B = A2; // Potentiometer Blue

int PotR_Value = 0; //Potentiometer Red Value
int PotG_Value = 0; //Potentiometer Green Value
int PotB_Value = 0; //Potentiometer Blue Value

int Red_Value = 0; //Red Value
int Green_Value = 0; //Green Value
int Blue_Value = 0; //Blue Value

const int LEDRed_Pin = 9; // Pin Output Red
const int LEDGreen_Pin = 10; // Pin Output Green
const int LEDBlue_Pin = 11; // Pin Output Blue


void setup() {
  pinMode(Pot_Pin_R, INPUT);
  pinMode(Pot_Pin_G, INPUT);
  pinMode(Pot_Pin_B, INPUT);

  pinMode(LEDRed_Pin, OUTPUT);
  pinMode(LEDGreen_Pin, OUTPUT);
  pinMode(LEDBlue_Pin, OUTPUT);

}


void loop() {
  // Read analog input of potentiometers into the variables PotR, PotG, PotB
  PotR_Value = analogRead(Pot_Pin_R);
  PotG_Value = analogRead(Pot_Pin_G);
  PotB_Value = analogRead(Pot_Pin_B);

  // Map to LED scale (0-1023 to 0-255)
  Red_Value = map(PotR_Value, 0, 1023, 0, 255);
  Green_Value = map(PotG_Value, 0, 1023, 0, 255);
  Blue_Value = map(PotB_Value, 0, 1023, 0, 255);

  // Lighten up
  analogWrite(LEDRed_Pin, Red_Value);
  analogWrite(LEDGreen_Pin, Green_Value);
  analogWrite(LEDBlue_Pin, Blue_Value);
  
}
