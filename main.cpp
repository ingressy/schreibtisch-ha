#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
//#include <Wire.h>
#include <header.h>

const int lbutton = 13;
const int button = 8;
const int rbutton = 7;
const int led = 2;

int pomodoro_time = 25*60;
bool active = true;
int site = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0,0);
    lcd.print("HomeDash startet");

    lcd.setCursor(0,1);
    lcd.print("Bitte warten ...");

    connectWifi();
    printIP(lcd);

    pinMode(lbutton, INPUT);
    pinMode(button, INPUT);
    pinMode(rbutton, INPUT);

}

void loop() {
    if (site == 0) {
        startseite();
    }
    if (site == 1) {
        pomodoro();
    }

    for (int i = 0; i <= 10; i++ ) {
        delay(100);
        if (digitalRead(button) == HIGH) {
            delay(100);
            break;
        } if (digitalRead(lbutton) == HIGH) {
            delay(100);
            break;
        }
    }

    if(digitalRead(lbutton) == HIGH) {
        site = 1;
    }
    if(digitalRead(button) == HIGH && site == 0) {
        if (active) {
            lcd.noBacklight();
            active = false;
        } else {
            lcd.backlight();
            active = true;
        }

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
            if(digitalRead(button)== HIGH) {
                break;
            }
        }
    }

    if (pomodoro_time == 0) {
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Fertig!");
        while (pomodoro_time == 0) {
            digitalWrite(led, HIGH);
            delay(500);
            digitalWrite(led, LOW);
            delay(500);
        }
    }
}

void startseite() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Startseite");
}
