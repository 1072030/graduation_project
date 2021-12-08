                                      /*
  Keyboard Message test

  For the Arduino Leonardo and Micro.

  Sends a text string when a button is pressed.

  The circuit:
  - pushbutton attached from pin 4 to +5V
  - 10 kilohm resistor attached from pin 4 to ground

  created 24 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe
  modified 11 Nov 2013
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardMessage
*/

#include "Keyboard.h"

#define DoPin 3          // input pin for pushbutton
#define RePin 4
#define MiPin 5
#define FaPin 6
#define SoPin 7
#define LaPin 8
#define SiPin 9
#define DoHPin 10
int previousDoPinState = HIGH;   // for checking the state of a pushButton
int previousRePinState = HIGH;
int previousMiPinState = HIGH;
int previousFaPinState = HIGH;
int previousSoPinState = HIGH;
int previousLaPinState = HIGH;
int previousSiPinState = HIGH;
int previousDoHPinState = HIGH;

void setup() {
  // make the pushButton pin an input:
  pinMode(DoPin, INPUT);
  pinMode(RePin, INPUT);
  pinMode(MiPin, INPUT);
  pinMode(FaPin, INPUT);
  pinMode(SoPin, INPUT);
  pinMode(LaPin, INPUT);
  pinMode(SiPin, INPUT);
  pinMode(DoHPin, INPUT);
  Keyboard.begin();
}

void loop() {
  // read the pushbutton:
  int DoPinState = digitalRead(DoPin); //Low 代表是按下 HIGH代表沒按
  int RePinState = digitalRead(RePin);
  int MiPinState = digitalRead(MiPin);
  int FaPinState = digitalRead(FaPin);
  int SoPinState = digitalRead(SoPin);
  int LaPinState = digitalRead(LaPin);
  int SiPinState = digitalRead(SiPin);
  int DoHPinState = digitalRead(DoHPin);
  if((!DoPinState) && (DoPinState != previousDoPinState)){
    Keyboard.write('u');
    delay(150);
    Keyboard.releaseAll();
  }
  if(!RePinState && (RePinState != previousRePinState)){
    Keyboard.press('y');
    delay(150);
    Keyboard.releaseAll();
  }
  if(!MiPinState && (MiPinState != previousMiPinState)){
    Keyboard.write('t');
    delay(150);
    Keyboard.releaseAll();
  }
  if(!FaPinState && (FaPinState != previousFaPinState)){
    Keyboard.write('r');
    delay(150);
    Keyboard.releaseAll();
  }
  if(!SoPinState && (SoPinState != previousSoPinState)){
    Keyboard.write('e');
    delay(150);
    Keyboard.releaseAll();
  }
  if(!LaPinState && (LaPinState != previousLaPinState)){
    Keyboard.write('w');
    delay(150);
    Keyboard.releaseAll();
  }
  if(!SiPinState && (SiPinState != previousSiPinState)){
    Keyboard.write('q');
    delay(150);
    Keyboard.releaseAll();
  }
  if(!DoHPinState && (DoHPinState != previousDoHPinState)){
    Keyboard.write(9);
    delay(150);
    Keyboard.releaseAll();
  }
  previousDoPinState = DoPinState;
  previousRePinState = RePinState;
  previousMiPinState = MiPinState;
  previousFaPinState = FaPinState;
  previousSoPinState = SoPinState;
  previousLaPinState = LaPinState;
  previousSiPinState = SiPinState;
  previousDoHPinState = DoHPinState;
}
