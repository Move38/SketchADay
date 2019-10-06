/*
   #005 - PUSH POP

   Going for the effect of your finger pushing a light down
   and seeing another pop directly up


   --------------------
   Sketch-A-Day
   12.18.2018
   by Jonathan Bobrow

   @madewithblinks
   www.move38.com
   --------------------
*/

#define POP_DURATION 200
#define DELAY_DURATION 600

Timer popTimer;
Timer delayTimer;
bool push = false;

byte face = 0;  // start it on no face

byte hue, bri;

void setup() {
  // put your setup code here, to run once:
  delayTimer.set(1000000);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (buttonPressed()) {
    push = true;
    popTimer.set(POP_DURATION);
  }

  if (!popTimer.isExpired()) {
    if (push) {
      // animate a point down
      bri = map_m(popTimer.getRemaining(), POP_DURATION, 0, 255, 0);
    }
    else {
      // animate a point up
      bri = map_m(popTimer.getRemaining(), POP_DURATION, 0, 0, 255);
    }
  }
  else {
    if (push) {
      push = false;
      delayTimer.set(DELAY_DURATION);
      // pick a new spot to pop up
      face = getNewFace(face);
      // pick a new color
      hue = map_m(random(12), 0, 12, 0, 64); // a piece of the spectrum
    }
  }

  if (delayTimer.isExpired()) {
    delayTimer.set(1000000);
    popTimer.set(POP_DURATION);
  }

  // display
  setColor(OFF);
  setColorOnFace(makeColorHSB(hue, 255, bri), face);
}

byte getNewFace(byte f) {
  byte newF = f;
  while (newF == f) {
    newF = random(5);
  }
  return newF;
}

// Should not need this
long map_m(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
