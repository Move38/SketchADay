/*
 * #004 - WAKE SLEEP
 * 
 * A simple sketch to prototype Blinks default OS behaviors
 * 
 * Wake - simple spiral before loading game state
 * Sleep - simple spiral in reverse before going dark
 * Program - flash with urgency
 * 
 * --------------------
 * Sketch-A-Day
 * 12.17.2018
 * by Jonathan Bobrow
 * 
 * @madewithblinks
 * www.move38.com
 * --------------------
 */

uint32_t timeOfPress;

bool isAwake = false;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  if (buttonPressed()) {
    timeOfPress = millis();

    if (!isAwake) {
      // wake up animation
      isAwake = true;
    }

  }

  if (isAwake) {
    setColor(OFF);
    if ((millis() - timeOfPress) < 525 ) {
      FOREACH_FACE(f) {
        if ((millis() - timeOfPress) / 75 > f ) {
          setColorOnFace(WHITE, f);
        }
      }
    }
  }

  if (buttonDown()) {
    uint32_t timeSincePress = millis() - timeOfPress;
    if (timeSincePress > 1000 && timeSincePress < 2500) {
      // flash
      if ((millis() / 100) % 2 == 0) {
        setColor(BLUE);
      }
      else {
        setColor(OFF);
      }

    }
    else if (timeSincePress > 2500) {
      // start sleep animation
      isAwake = false;
      // sleep animation
      setColor(BLUE);
      if (timeSincePress - 2500 < 525 ) {
        FOREACH_FACE(f) {
          if (6 - ((timeSincePress - 2500) / 75) < f ) {
            setColorOnFace(OFF, f);
          }
        }
      }
      else {
        setColor(OFF);
      }

    }
  }


}
