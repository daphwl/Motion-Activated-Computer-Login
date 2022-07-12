#include "USBHIDKeyboard.h"
#include "USBHIDDevice.h"

USBHIDKeyboard keyboardDev;

int pirPin = 8;
static bool pirPrevState = false;
bool pirCurrentState;

void setup() {

  Serial.begin(115200);
  USBHIDDev.begin();
  pinMode(pirPin, INPUT);
  pirPrevState = digitalRead(pirPin);

}

void loop() {
  pirCurrentState = digitalRead(pirPin);
  if (USBHIDDev.USBconnected() && pirCurrentState) {
    if (pirPrevState == false && pirCurrentState == true) {
      Serial.println("Detected");
      keyboardDev.keyReleaseAll();
      delay(1000);
      keyboardDev.keyPress(HID_KEY_SPACE);
      delay(10);
      keyboardDev.keyRelease(HID_KEY_SPACE);
      delay(3000);
      keyboardDev.keyPress(HID_KEY_BACKSPACE);
      delay(10);
      keyboardDev.keyRelease(HID_KEY_BACKSPACE);
      delay(10);
	  //Change to your Computer's login password
      keyboardDev.keySequence("PASSWORD");
      delay(3000);
      keyboardDev.keyPress(HID_KEY_ENTER);
      keyboardDev.keyReleaseAll();
      delay(1000);
    }
  }  else {
    delay(10);
  }
  pirPrevState = pirCurrentState;
}
