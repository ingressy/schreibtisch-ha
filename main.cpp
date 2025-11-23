#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int lbutton = 2;
const int button = 0;
const int rbutton = 4;

int currentStatel;
int currentState;
int currentstater;
int site;
int pomodoro_time = 25*60;

void pomodoro();

void setup() {
  pinMode(lbutton, INPUT);
  pinMode(button, INPUT);
  pinMode(rbutton, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("HomeDash startet");

  lcd.setCursor(0,1);
  lcd.print("Bitte warten ...");
  delay(1000);
  site = 0;
}

void loop() {

  if (site == 0) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("0");
    lcd.write(byte(223));
    lcd.print("C 00%");
    lcd.setCursor(0,1);
    lcd.print("0A 0W");

    delay(1000);

    site = 0;
    currentStatel = digitalRead(lbutton);
    currentState = digitalRead(button);

    if(currentStatel == HIGH) {
      site = 1;
    } else if (currentState == HIGH) {
      lcd.noBacklight();
    }
  } else if (site == 1) {
    lcd.clear();
    pomodoro();
  }
  
}

void pomodoro() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pomodoro:");

  lcd.setCursor(0,1);
  lcd.print("25min 00sek");

  if (digitalRead(button) == HIGH) {
    for (int sec = pomodoro_time; sec >= 0; sec--) {
      int m = sec/60;
      int s = sec % 60;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pomodoro:");

      lcd.setCursor(0,1);
      if (m < 10) lcd.print("0");
      lcd.print(m);
      lcd.print("min ");
      if (s < 10) lcd.print("0");
      lcd.print(s);
      lcd.print("sek");

      delay(1000);
      currentState = digitalRead(lbutton);
      if(currentState == HIGH) {
        break;
      }
    }
  }

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Fertig!");
}
