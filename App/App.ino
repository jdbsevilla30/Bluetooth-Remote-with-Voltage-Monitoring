/*Servo library and instance*/
#include <Servo.h>
Servo myservo;

/*LOW/HIGH assignments for relay trigger*/
#define ON LOW
#define OFF HIGH

/*voltage sensor pin Analog 0*/
const int voltageSensorPin = A0;

/*relay pin (motor blade)*/
const int relayPin = 13;

/*non-blocking millis print for our function displayVoltage()*/
const long printInterval = 1000;
unsigned long previousMillis = 0;

void setup() {
  Serial1.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, OFF);
  myservo.attach(9);
}

void loop() {
  processBluetoothData();
  displayVoltage();
}

/*this function checks if an int value has bee nreceived from the app*/
void processBluetoothData() {
  while (Serial1.available( > 0) {
    processBluetoothResponse(Serial1.read());
  }
}

/*this is where the bluetooth response will be processed. depending on the int value get from app*/
void processBluetoothResponse(int btResponse) {
  if (btResponse > 0 && btResponse <= 180) {
    myservo.write(btResponse);
  } else if (btResponse > 180) {
    if (btResponse == 181) {
      digitalWrite(relayPin, ON);
    } else if (btResponse == 182) {
      digitalWrite(relayPin, OFF);
    } else {
      Serial1.println("ERROR")
    }
  }
}

/*function to display the value which was got from getVoltage() without using delay*/
void displayVoltage() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= printInterval) {
    previousMillis = currentMillis;
    getVoltage();
  }
}

/*calculate our voltage sensor value*/
void getVoltage() {
  const float reductionFactor = 5.128;  //reductionFactor = Adapter vOut / A3 vOut
  const float vcc = 5.00;               //arduino input voltage
  float voltageSensorRaw = analogRead(voltageSensorPin);
  float vOut = (voltageSensorRaw / 1024) * vcc;
  float vIn = vOut * reductionFactor;
  Serial1.println((String) "Battery Voltage = " + vIn + (String) "V");
}
