/* Tes Mode Sleep Attiny85 Digspark
   10 desember 2021
   

*/

#include <avr/sleep.h>

// Utility macro
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)

// constants 
const int Speaker = 1;              // buzzer + ke pin PB1 buzzer - ke ground
const int Lamp = 0;
const unsigned long Alarm = 30000; // alarm time - 30 second
unsigned long StartTime = 0;        // start time

void setup () {
  pinMode(Lamp, OUTPUT);
  pinMode(Speaker, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  adc_disable(); // ADC uses ~320uA
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

// Fungsi enterSleep
void enterSleep (void)
{
  sleep_enable();
  sleep_cpu();
}

// Fungsi playbeep
void playBeep (void) { // bunyi beep sebanyak 20x
  for (int i=0; i < 20; i++) {
    digitalWrite(Speaker, HIGH);
    delay(100);
    digitalWrite(Speaker, LOW);
    delay(100);
  }
}

// Fungsi flashLed
void flashLed (int wait) {
  digitalWrite(Lamp, HIGH);
  delay(wait);
  digitalWrite(Lamp, LOW);
}

// Program utama

void loop () {
  // Long flash
  flashLed(125);
  delay(125);
  flashLed(125);
  do {
    // Flash light
    flashLed(1);
    delay(2000);
  } while (millis() - StartTime < Alarm);
  // Alarm
  playBeep();
  enterSleep();
  // Continue after reset
}
