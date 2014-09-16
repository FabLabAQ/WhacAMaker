// Pin numbers: Joystick
const int joystickP1 = 7;
const int joystickP2 = 8;
const int joystickX = A0;
const int joystickY = A1;

const int tmpLed = 11;
const int tmpLedPWMX = 3;
const int tmpLedPWMY = 5;

void setup() {
  // Initialize serial
  Serial.begin(115200);

  // Initialize pins
  pinMode(joystickP1, INPUT_PULLUP);
  pinMode(joystickP2, INPUT_PULLUP);
  
  pinMode(tmpLed, OUTPUT);
  pinMode(tmpLedPWMX, OUTPUT);
  pinMode(tmpLedPWMY, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:   
  int pwmValueX = analogRead(joystickX); 
  int pwmValueY = analogRead(joystickY); 
  analogWrite(tmpLedPWMX, pwmValueX >> 2);
  analogWrite(tmpLedPWMY, pwmValueY >> 2);

  if ((digitalRead(joystickP1) == LOW) || (digitalRead(joystickP2) == LOW)) {
    digitalWrite(tmpLed, HIGH);
  } else {
    digitalWrite(tmpLed, LOW);
  }
  
  Serial.print(pwmValueX);
  Serial.print(" ");
  Serial.println(pwmValueY);
}
