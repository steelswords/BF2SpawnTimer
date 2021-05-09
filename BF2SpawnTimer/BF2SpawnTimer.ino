//#include <LCDKeypad.h>
#include <LiquidCrystal.h>

#define DELAY_UNTIL_US(x) (while (micros() < x) ; )



LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
int greenLightPin = 13;
int maxCount = 15;
int count = maxCount;
int analogPinReference = 0;

unsigned long curTime;

// TODO: Accurate timing, using wait untils instead of delays

void setup() {
  // put your setup code here, to run once:
  pinMode(greenLightPin, OUTPUT);
  pinMode(A0, INPUT);
  analogPinReference = analogRead(A0);
  lcd.begin(16,2);
  lcd.clear();
  curTime = micros();
}

void flashDisplay()
{
  lcd.home();
  lcd.print("    ]**********");
  lcd.setCursor(1,0);
  lcd.print("****************");
  delay(150);
  lcd.clear();
  delay(150);
}

void printCount()
{
  lcd.clear();
  lcd.home();
  lcd.print(count);  
}

bool buttonPushed()
{
  return analogRead(A0) < analogPinReference - 50;
}

void noGreenLight()
{
  digitalWrite(greenLightPin, HIGH);
}

void greenLight()
{
  digitalWrite(greenLightPin, LOW);
}


void loop() {
  if ( buttonPushed() )
  {
    curTime = micros();
    count = maxCount;

  }
  else if (micros() >= curTime + 1000000) // A second has passed
  {
    count--;
    curTime = curTime + 1000000;
    if (count <= 0)
    {
      count = maxCount;
      noGreenLight();
    }
    else if (count <= 3)
      greenLight();
    
    printCount();
  }
}
