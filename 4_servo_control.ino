#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <Servo.h> // servo library
#include <HCPCA9685.h>
#define I2CAdd 0x40 // i2c address
HCPCA9685 HCPCA9685(I2CAdd);
Servo myservo1, myservo2, myservo3, myservo4; // servo name
int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  HCPCA9685.Output(6, 1024, 3072); // 25% on cycle and 75% off cycle
  HCPCA9685.Output(7, 1024, 3072);
  HCPCA9685.Output(11, 1024, 3072);
  HCPCA9685.Output(15, 1024, 3072);

//Setup usb serial connection to computer
Serial.begin(9600);
//Setup Bluetooth serial connection to android
bluetooth.begin(9600);
}
void loop()
{
//Read from bluetooth and write to usb serial
if(bluetooth.available()>= 2 ) /*
With this line
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);you define a new serial port called bluetooth. It's not a HW but a SW emulated serial port 5.

The SoftwareSerial has an instruction called available() 24which gets the number of bytes (characters) available for reading from a software serial port.

So the line tests if the number of bytes currently in the serial buffer is greater than 2.

*/
{
unsigned int servopos = bluetooth.read();
unsigned int servopos1 = bluetooth.read();
unsigned int realservo = (servopos1 *256) + servopos;
Serial.println(realservo);
if (realservo >= 1000 && realservo < 1180) { // 1000 to 1180 is for first servo on your phone or the first slider

int servo1 = realservo;
servo1 = map(servo1, 1000, 1180, 0, 180);
int servo1map = map(servo1, 0, 180, 10, 450);
HCPCA9685.Servo(3, servo1map);
Serial.println("Servo 1 ON");
delay(10);
}
if (realservo >= 2000 && realservo < 2180) {
int servo2 = realservo;
servo2 = map(servo2, 2000, 2180, 0, 180);
int servo2map = map(servo2, 0, 180, 10, 450);
HCPCA9685.Servo(7, servo2map);
Serial.println("Servo 2 ON");
delay(10);
}
if (realservo >= 3000 && realservo <3180) {
int servo3 = realservo;
servo3 = map(servo3, 3000, 3180, 0, 180);
int servo3map = map(servo3, 0, 180, 10, 450);
HCPCA9685.Servo(11,servo3map);
Serial.println("Servo 3 ON");
delay(10);
}
if (realservo >= 4000 && realservo<4180) {
int servo4 = realservo;
servo4 = map(servo4, 4000, 4180, 0, 180);
int servo4map = map(servo4, 0, 180, 10, 450);
HCPCA9685.Servo(15, servo4map);
Serial.println("Servo 4 ON");
delay(10);
}

}
}
