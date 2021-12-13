#include "EEPROM.h"
#include "LedControl.h"

LedControl lc = LedControl(4, 3, 0, 1);

const int buttonCount = 2;
const int buzzer = 1;

int noteTime = 120;
int noteTime2 = 300;

int counter = 0;
unsigned long lastTime = 0;

//function to display a number on the 7-segment display
void printNumber(int v) {
    int ones;
    int tens;
    int hundreds;
    int thousands;

    int val = v;

    boolean negative = false;

    //number must be [-999,9999]
    if (v < -999 || v > 9999) return;
    if (v < 0) {
        negative = true;
        v = v * -1;
        val = val * -1;
    }
    ones = v % 10;
    v = v / 10;
    tens = v % 10;
    v = v / 10;
    hundreds = v % 10;
    v = v / 10;
    thousands = v;
    //set the numbers on display without a 0 in front of a number smaller than 1000
    if (negative) {
        lc.setChar(0, 0, '-', false);
    } else {
        thousands ? lc.setDigit(0, 0, (byte)thousands, false)
                  : lc.setChar(0, 0, ' ', false);
    }

    if (val < 10000 && val > 99) {
        lc.setDigit(0, 1, (byte)hundreds, false);
        lc.setDigit(0, 2, (byte)tens, false);
        lc.setDigit(0, 3, (byte)ones, false);
    } else if (val < 100 && val > 9) {
        lc.setChar(0, 1, ' ', false);
        lc.setDigit(0, 2, (byte)tens, false);
        lc.setDigit(0, 3, (byte)ones, false);
    } else {
        lc.setChar(0, 1, ' ', false);
        lc.setChar(0, 2, ' ', false);
        lc.setDigit(0, 3, (byte)ones, false);
    }
}

void playWinTone() {
    tone(buzzer, 587, noteTime - 10); //D
    delay(noteTime);
    noTone(buzzer);
    tone(buzzer, 784, noteTime - 10); //G
    delay(noteTime);
    noTone(buzzer);
    tone(buzzer, 587, noteTime - 10); //D
    delay(noteTime);
    noTone(buzzer);
    tone(buzzer, 784, noteTime - 10); //G
    delay(noteTime);
    digitalWrite(buzzer, LOW);
    pinMode(buzzer, INPUT); //helped getting rid of a small constant vibration of the buzzer
}

void playSadTone() {
    tone(buzzer, 784, noteTime2 - 10); //G
    delay(noteTime2);
    noTone(buzzer);
    tone(buzzer, 659, noteTime2 - 10); //E
    delay(noteTime2);
    noTone(buzzer);
    tone(buzzer, 523, noteTime2 - 10); //C
    delay(noteTime2);
    digitalWrite(buzzer, LOW);
    pinMode(buzzer, INPUT);
}

void setup() {
    //7-segment setup
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);

    pinMode(buttonCount, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);

    counter = EEPROM.read(0);
    printNumber(counter);
}

void loop() {
    if (digitalRead(buttonCount) == HIGH) {
        if (millis() - lastTime > 1000) {   //debounce button
            counter++;
            EEPROM.write(0, counter);   //saving value
            lastTime = millis();
            while (digitalRead(buttonCount) == HIGH) { //while loop for long press
                if (millis() - lastTime > 6000) {
                    counter = 0;
                    EEPROM.write(0, counter);
                    lastTime = millis();
                    printNumber(counter); //if long press, set counter to 0 and play sadtone 
                    playSadTone();
                    return;
                }
            }
            printNumber(counter); //if short press, count up and play wintone
            playWinTone();
        }
    }
}
