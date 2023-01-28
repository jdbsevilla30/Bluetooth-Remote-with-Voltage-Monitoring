/*voltage sensor pin Analog 0*/
const int voltageSensorPin = A0;

void setup() {

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// void getVoltage() {
//   float vIn;
//   float vOut;
//   float voltageSensorRaw;
//   const float reductionFactor = 5.128;
//   const float vcc = 5.00;  //arduino input voltage

//   voltageSensorRaw = analogRead(voltageSensorPin);
//   vOut = (voltageSensorRaw / 1024) * vcc;
//   vIn = vOut * factor;
//   return vIn;
// }

void getVoltage() {
  const float reductionFactor = 5.128;
  const float vcc = 5.00;  //arduino input voltage
  float voltageSensorRaw = analogRead(voltageSensorPin);
  float vOut = (voltageSensorRaw / 1024) * vcc;
  float vIn = vOut * factor;
  return vIn;
}