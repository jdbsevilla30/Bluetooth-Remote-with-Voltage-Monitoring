/*LOW/HIGH assignments for relay trigger*/
#define ON LOW
#define OFF HIGH

/*NewLine*/
#define NewLine Serial1.println();

/*"|" as delimiter*/
#define Delimiter Serial1.print("|");
/*solar  sensor pin Analog 0*/
const int voltageSensorPinSolar = A0;

/*turbine sensor pin Analog 1*/
const int voltageSensorPinTurbine = A1;

/*Battery sensor pin Analog 2*/
const int voltageSensorPinBattery = A2;

/*a value we need for our voltage sensor*/
const float vcc = 5.00;  //arduino input voltage

/*Servo library and instance*/
#include <Servo.h>
Servo myservo;
const int myServoPin = 9;

/*relay pin (motor blade)*/
const int relayPin = 13;

/*non-blocking millis print for our function displayVoltage()*/
const long printInterval = 1000;  //1000 = 1 sec
unsigned long previousMillis = 0;

/*run once*/
void setup() {
  Serial1.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, OFF);
  myservo.attach(myServoPin);
}

/*runs forever*/
void loop() {
  processBluetoothData();
  displayVoltage();
}

/*this function checks if an int value has bee nreceived from the app*/
void processBluetoothData() {
  while (Serial1.available() > 0) {
    processBluetoothResponse(Serial1.read());
  }
}

/*this is where the bluetooth response will be processed. depending on the int value get from app*/
void processBluetoothResponse(int btResponse) {
  if (btResponse == 1) {
    myservo.detach();
  } else if (btResponse > 0 && btResponse <= 180) {
    myservo.attach(myServoPin);
    myservo.write(btResponse);
  } else if (btResponse > 180) {
    if (btResponse == 181) {
      digitalWrite(relayPin, ON);
    } else if (btResponse == 182) {
      digitalWrite(relayPin, OFF);
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
  getSolar();
  Delimiter;
  getTurbine();
  Delimiter;
  getBattery();
  NewLine;
}

/*this function gets the voltage of the solar panel*/
void getSolar() {
  const float reductionFactorSolar = 5.128;  //reductionFactor = Adapter vOut / A0 vOut
  float voltageSensorRawSolar = analogRead(voltageSensorPinSolar);
  float vOutSolar = (voltageSensorRawSolar / 1024) * vcc;
  float vInSolar = vOutSolar * reductionFactorSolar;
  Serial1.print(vInSolar + (String) "V");
  Serial.print("Solar voltage: ");
  Serial.print(vInSolar);
  Serial.println("");
}

/*this function gets the voltage of the wind turbine*/
void getTurbine() {
  const float reductionFactorTurbine = 5.128;  //reductionFactor = Adapter vOut / A1 vOut
  float voltageSensorRawTurbine = analogRead(voltageSensorPinTurbine);
  float vOutTurbine = (voltageSensorRawTurbine / 1024) * vcc;
  float vInTurbine = vOutTurbine * reductionFactorTurbine;
  Serial1.print(vInTurbine + (String) "V");
  Serial.print("Turbine voltage: ");
  Serial.print(vInTurbine);
  Serial.println("");
}

/*this function gets the voltage of the battery*/
void getBattery() {
  const float reductionFactorBattery = 5.128;  //reductionFactor = Adapter vOut / A2 vOut
  float voltageSensorRawBattery = analogRead(voltageSensorPinBattery);
  float vOutBattery = (voltageSensorRawBattery / 1024) * vcc;
  float vInBattery = vOutBattery * reductionFactorBattery;
  Serial1.print(vInBattery + (String) "V");
  Serial.print("Battery voltage: ");
  Serial.print(vInBattery);
  Serial.println("");
}