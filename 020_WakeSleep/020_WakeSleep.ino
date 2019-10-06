/*
 * Wake/Sleep Animation
 */

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
      wake.set(2000);
    }
    else {
      sleep.set(2000);
    }
  }
  
  // sleep
  // quickly fade up to blue
  if(sleep.getRemaining() > 1800) {
    setColor(dim(BLUE, 2000 - sleep.getRemaining());
  }
  else if(sleep.getRemaining() > 0) {
    // fade down to off in circle     
    FOREACH_FACE(f) {
      setColorOnFace(dim(BLUE, 2000 - sleep.getRemaining());      
    }
  }
}
