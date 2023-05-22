#include <BluetoothSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

const int a = 2;
const int b = 4;
const int c = 5;
const int d = 13;
const int e = 26;
const int f = 27;
const int g = 33;

int counter = 0;
int digit = 0;
#define SERVO_PIN 14

BluetoothSerial SerialBT;
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  SerialBT.begin("ESP32 Bluetooth Servo");
  myservo.attach(SERVO_PIN);
  lcd.begin(16, 2);
  lcd.print("Ready");

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop()
{
  if (SerialBT.available())
  {
    char command = SerialBT.read();

    if (command == 'A')
    {
      if (counter < 5)
      {
        counter++;
        digit = counter;
        if (counter == 5)
          openServo();
        displayDigit();
        if (counter >= 1 && counter <= 4)
          lcd.setCursor(0, 1); lcd.print("Securing...");
      }
    }
    else if (command == 'B')
    {
      if (counter > 0)
      {
        counter--;
        digit = counter;
        if (counter == 0)
          closeServo();
        displayDigit();
        if (counter >= 1 && counter <= 4)
          lcd.setCursor(0, 1); lcd.print("Hacking...");
      }
    }
  }
}

void openServo()
{
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("ACCESS DENIED");
  lcd.setCursor(0, 1); lcd.print("LOCK CLOSED");
  myservo.write(55);
  delay(1000);
}

void closeServo()
{
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("SECURITY BREACHED");
  lcd.setCursor(0, 1); lcd.print("LOCK OPENED");
  myservo.write(25);
  delay(1000);
}

void displayDigit()
{
  int segments[] = {a, b, c, d, e, f, g};
  for (int i = 0; i < 7; i++)
    digitalWrite(segments[i], LOW);

  if (digit != 1 && digit != 4) digitalWrite(a, HIGH);
  if (digit != 5 && digit != 6) digitalWrite(b, HIGH);
  if (digit != 2) digitalWrite(c, HIGH);
  if (digit != 1 && digit != 4 && digit != 7) digitalWrite(d, HIGH);
  if (digit == 2 || digit == 6 || digit == 8 || digit == 0) digitalWrite(e, HIGH);
  if (digit != 1 && digit != 2 && digit != 3 && digit != 7) digitalWrite(f, HIGH);
  if (digit != 0 && digit != 1 && digit != 7) digitalWrite(g, HIGH);
}
