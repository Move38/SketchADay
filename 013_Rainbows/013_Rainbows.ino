/*
   #013 - Rainbows

   spread a rainbow from Blink to Blink with delay

   --------------------
   Sketch-A-Day
   12.26.2018
   by Jonathan Bobrow

   @madewithblinks
   www.move38.com
   --------------------
*/

#define DURATION_OF_RAINBOW 2000
#define DELAY_OF_RAINBOW     200

Timer sendRainbowTimer;
Timer rainbowTimer;

byte count = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  if (buttonPressed()) {
    // share the rainbow
    sendRainbowTimer.set(DELAY_OF_RAINBOW);
    
    // send rainbow (prevent loops by passing a higher value)
    count++;
    if (count > 63) {
      count = 0;
    }
  }

  if (sendRainbowTimer.isExpired()) {
    // show rainbow
    rainbowTimer.set(DURATION_OF_RAINBOW);

    setValueSentOnAllFaces(count);
    sendRainbowTimer.never(); // don't keep sending
  }


  if (rainbowTimer.isExpired()) {
    // nothing to display, just wait
    setColor(OFF);

    // check for shared rainbow
    FOREACH_FACE(f) {
      if (!isValueReceivedOnFaceExpired(f)) {
        byte data = getLastValueReceivedOnFace(f);
        if ( data > count || (count == 63 && data == 0) ) {
          sendRainbowTimer.set(DELAY_OF_RAINBOW);
          count = data;
        }
      }
    }
  }
  else {
    // find the hue we should display
    byte hue = (rainbowTimer.getRemaining() * 255) / DURATION_OF_RAINBOW;
    // fade at the end
    byte bri;
    if ( rainbowTimer.getRemaining() < 1000 ) {
      bri = rainbowTimer.getRemaining() / 4;
    }
    else {
      bri = 255;
    }
    setColor(makeColorHSB(hue, 255, bri));
  }

}
