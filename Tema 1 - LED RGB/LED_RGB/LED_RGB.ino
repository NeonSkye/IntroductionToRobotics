const int Pin_R = A0; // Input Red
const int Pin_G = A1; // Input Green
const int Pin_B = A2; // Input Blue

int In_R_Value = 0; //Input Red Value
int In_G_Value = 0; //Input Green Value
int In_B_Value = 0; //Input Blue Value

int Out_R_Value = 0; //Output Red Value
int Out_G_Value = 0; //Output Green Value
int Out_B_Value = 0; //Output Blue Value

const int LEDRed_Pin = 9; // Pin Output Red
const int LEDGreen_Pin = 10; // Pin Output Green
const int LEDBlue_Pin = 11; // Pin Output Blue


void setup() {
  pinMode(Pin_R, INPUT);
  pinMode(Pin_G, INPUT);
  pinMode(Pin_B, INPUT);

  pinMode(LEDRed_Pin, OUTPUT);
  pinMode(LEDGreen_Pin, OUTPUT);
  pinMode(LEDBlue_Pin, OUTPUT);

}


void loop() {
  // Read analog input of potentiometers into the variables PotR, PotG, PotB
  In_R_Value = analogRead(Pin_R);
  In_G_Value = analogRead(Pin_G);
  In_B_Value = analogRead(Pin_B);

  // Map to LED scale (0-1023 to 0-255)
  Out_R_Value = map(In_R_Value, 0, 1023, 0, 255);
  Out_G_Value = map(In_G_Value, 0, 1023, 0, 255);
  Out_B_Value = map(In_B_Value, 0, 1023, 0, 255);

  // Lighten up
  analogWrite(LEDRed_Pin, Out_R_Value);
  analogWrite(LEDGreen_Pin, Out_G_Value);
  analogWrite(LEDBlue_Pin, Out_B_Value);
  
}
