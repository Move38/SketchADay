/*
 * #003 - CHARGE UP
 * 
 * When button is pressed down, the Blink charges up
 * The longer it charges the faster the starting spin
 * 
 * --------------------
 * Sketch-A-Day
 * 12.16.2018
 * by Jonathan Bobrow
 * 
 * @madewithblinks
 * www.move38.com
 * --------------------
 */

byte brightness[6];

uint32_t timeOfPress;
uint32_t timeOfRelease;
word durationOfPress;

bool chargingUp = false;

byte fadeDecrement = 5;
word rotationDelay = 200;
byte currentFace = 0;

Timer rotationTimer;

void setup() {
  // nothing to do here :)
}

void loop() {
  // update
  if (buttonPressed()) {
    // start of down time
    timeOfPress = millis();
  }
  if (buttonReleased()) {
    // let it rip
    timeOfRelease = millis();
  }

  if (buttonDown()) {
    // how long have we been down...
    durationOfPress = millis() - timeOfPress;
    chargingUp = true;
  }
  else {
    chargingUp = false;
    uint32_t timeSinceRelease = millis() - timeOfRelease;
    if (timeSinceRelease < durationOfPress) {
      word timeScale = (timeSinceRelease * timeSinceRelease) / durationOfPress;
      rotationDelay = map_m(timeScale, 0, durationOfPress, 25, 200);
      fadeDecrement = map_m(rotationDelay, 25, 200, 16, 2);
    }
    else {
      rotationDelay = 300;
      fadeDecrement = 2;
    }
  }


  if (chargingUp) {
    FOREACH_FACE(f) {
      if (durationOfPress < 3000) {
        brightness[f] = map_m(durationOfPress, 0, 3000, 0, 255);
      }
      else {
        if ((millis() / 100) % 2 == 0) {
          brightness[f] = 255;
        }
        else {
          brightness[f] = 0;
        }
      }
    }
  }
  else {
    FOREACH_FACE(f) {
      if (brightness[f] <= fadeDecrement) {
        brightness[f] = 0;
      }
      else {
        brightness[f] -= fadeDecrement;
      }
    }

    if (rotationTimer.isExpired()) {
      rotationTimer.set(rotationDelay);
      currentFace++;
      if (currentFace > 5) {
        currentFace = 0;
      }
      brightness[currentFace] = 255;
    }
  }
  // display
  FOREACH_FACE(f) {
    setColorOnFace(dim(WHITE, brightness[f]), f);
  }
}

long map_m(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
