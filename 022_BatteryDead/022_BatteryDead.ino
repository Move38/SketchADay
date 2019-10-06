#define DURATION 100

Timer blinkTimer;
byte count = 6;
bool bOn = false;

void setup() {
  // put your setup code here, to run once:
  setColor(OFF);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(buttonPressed()){
    blinkTimer.set(DURATION);
    bOn = false;
    count = 6;
  }

  if(blinkTimer.isExpired() && count > 0) {
    bOn = !bOn;
    blinkTimer.set(DURATION);
    count--;
  }

  if(bOn){
    setColor(RED);
  }
  else {
    setColor(OFF);
  }
  
}
