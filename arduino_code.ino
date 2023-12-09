#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Servo.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
Servo servoMotor;

String tagId = "None";
byte nuidPICC[4];

int servo_pin = 8; 

int redPin= 11;
int greenPin = 10;
int bluePin = 9;

void setup(void) 
{

 pinMode(redPin, OUTPUT);
 pinMode(bluePin, OUTPUT);
 pinMode(greenPin, OUTPUT);

 servoMotor.attach(servo_pin);
 servoMotor.write(0);

  
 Serial.begin(115200);
//  Serial.println("System initialized");
 nfc.begin();
}
 
void loop() 
{
 readNFC();
}
 
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void readNFC() 
{
 if (nfc.tagPresent())
 {
   NfcTag tag = nfc.read();
   tagId = tag.getUidString();
  //  Serial.println(tagId);

   if (tagId == "F3 F 26 F") {
      Serial.println("1");
      setColor(255, 255, 255);
      delay(1000);
      setColor(255, 0, 0);
      servoMotor.write(90);
      delay(5000);
      servoMotor.write(0);
   }
   else {
      Serial.println("0");
      setColor(0, 255, 0);
      delay(1000);
      setColor(255, 0, 0);
   }
 }
 delay(5000);
}
