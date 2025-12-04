#include <WiFiS3.h>
#include "LiquidCrystal_I2C.h"

#include <header.h>

const char ssid[] = "";
const char password[] = "";
int status = WL_IDLE_STATUS;

void connectWifi() {
    while (status != WL_CONNECTED) {
        status = WiFi.begin(ssid, password);
        delay(2000);
    }
}

void printIP(LiquidCrystal_I2C lcd) {
    IPAddress ip = WiFi.localIP();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(ip);
    delay(2000);
}
