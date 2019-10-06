/*
 * Wake/Sleep Animation
 */
#define DURATION 300
#define MAX_BRI  200

bool isAwake = false;

Timer wake;
Timer sleep;
 
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if(buttonPressed()) {
    isAwake = !isAwake;
    if(isAwake) {
      wake.set(DURATION);
    }
    else {
      sleep.set(DURATION);
    }
  }

  if(isAwake) {
    setColor(GREEN);
  }
  else {
    setColor(OFF);
  }
  // sleep
  // quickly fade up to blue
  if(sleep.getRemaining() > 0) {
    setColor(dim(BLUE, map(sleep.getRemaining(),0,DURATION,0,MAX_BRI)));
  }

  // wake
  if(wake.getRemaining() > 0) {
    setColor(dim(WHITE, MAX_BRI-map(wake.getRemaining(),0,DURATION,0,MAX_BRI)));
  }
  
}
