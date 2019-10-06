/*
   #012 - Inhale Exhale

   Based on the Dodow sleep inhibitor
   https://www.mydodow.com/dodow/en-us/scientific-demonstration

   Details:
   Starts at 11 breaths per minute
   Ends at 6 breaths per minute
   40% inhalation, 60% exhalation
   Blue light (supposedly reduces stress, not bright enough to keep you awake)

   --------------------
   Sketch-A-Day
   12.25.2018
   by Jonathan Bobrow

   @madewithblinks
   www.move38.com
   --------------------
*/

#include "Serial.h"

ServicePortSerial Serial;

#define SHORT_PROGRAM_DURATION   480000 // (1000 * 60 * 8)  // 8 minutes
#define LONG_PROGRAM_DURATION   1200000 // (1000 * 60 * 20)  // 20 minutes

// Blinks go to sleep before the long timer here...
// perhaps an override could be useful

#define START_BPS 660 //(11 * 60) // 11 BPM
#define END_BPS   360 //(6 * 60)  // 6 BPM

word bps = START_BPS;

Timer sleepTimer;
Timer breathTimer;

bool isRunning = false;
bool isShortProgram = true;

word breath_duration_ms;
word inhale_duration_ms;
word exhale_duration_ms;

void setup() {
  // put your setup code here, to run once:

}

void loop() {

  // TODO: a way to switch between short and long program
  if (buttonDoubleClicked()) {
    Serial.println("switching timer setting");
    isShortProgram = !isShortProgram;
    sleepTimer.set(0);
  }

  if (buttonPressed()) {
    // start the cycle
    if (isShortProgram) {
      Serial.print("setting timer for: ");
      Serial.print(SHORT_PROGRAM_DURATION);
      Serial.println("ms");
      sleepTimer.set(SHORT_PROGRAM_DURATION);
    }
    else {
      Serial.print("setting timer for: ");
      Serial.print(LONG_PROGRAM_DURATION);
      Serial.println("ms");
      sleepTimer.set(LONG_PROGRAM_DURATION);
    }
  }

  // check the amount of time remaining and update the bpm
  if (sleepTimer.isExpired()) {
    isRunning = false;
  }
  else {
    isRunning = true;

    //    Serial.print("sleep timer remaining: ");
    //    Serial.print(sleepTimer.getRemaining());
    //    Serial.println("ms");

    uint32_t remainder = sleepTimer.getRemaining() / 100;
    uint32_t max_in;
    if (isShortProgram) {
      max_in = SHORT_PROGRAM_DURATION / 100;
    }
    else {
      max_in = LONG_PROGRAM_DURATION / 100;
    }
    //    bps = map(remainder, max_in, 0, START_BPS, END_BPS);
    bps = END_BPS + ((remainder * (START_BPS - END_BPS) ) / max_in);
    //    Serial.print("bps: ");
    //    Serial.println(bps);
    //    Serial.print("bpm: ");
    //    Serial.println((bps/60));
  }

  if ( isRunning ) {

    if (breathTimer.isExpired()) {
      // animate the pulse based on bpm
      //      Serial.print("breath timer remaining: ");
      //      Serial.print(breathTimer.getRemaining());
      //      Serial.println("ms");

      breath_duration_ms = (word)(1000 * (3600 / bps));  // convert bps to duration
      inhale_duration_ms = (4 * breath_duration_ms) / 10;  // 40% inhale
      exhale_duration_ms = (6 * breath_duration_ms) / 10;  // 60% exhale

      breathTimer.set(breath_duration_ms);
    }

    //    Serial.print("breath timer remaining: ");
    //    Serial.print(breathTimer.getRemaining());
    //    Serial.println("ms");

    if (breathTimer.getRemaining() > exhale_duration_ms) {
      byte bri = 10 + (245 - (245 * (breathTimer.getRemaining() - exhale_duration_ms)) / inhale_duration_ms);
      // light up a number of LEDs based on the progress of the breath
      setColor(OFF);
      FOREACH_FACE(f) {
        if ((bri / 42) >= f) {
          setColorOnFace(dim(BLUE, bri), f);
        }
      }
    }
    else {
      byte bri = 10 + ((245 * breathTimer.getRemaining()) / exhale_duration_ms);
      //      light up a number of LEDs based on the progress of the breath
      setColor(OFF);
      FOREACH_FACE(f) {
        if ((bri / 42) >= f) {
          setColorOnFace(dim(BLUE, bri), f);
        }
      }
    }
  }
  else {
    setColor(OFF);
    FOREACH_FACE(f) {
      if ((millis() / 500) % 6 == f ) {
        if (isShortProgram) {
          setColorOnFace(dim(GREEN, 127), f);
        }
        else {
          setColorOnFace(dim(ORANGE, 127), f);
        }
      }
    }
  }
}
