/*
   #009 - Hello Goodbye
    
   Signal when a neighbor is present and signal when you think they left

   This is a previous sketch for testing communications but felt at home in sketch a day :)

   --------------------
   Sketch-A-Day
   12.22.2018
   by Jonathan Bobrow

   @madewithblinks
   www.move38.com
   --------------------

    Blinks Communication Test

    Use this test to see how well the Blinks are communicating with each other.
    If they are communicating well, you will see all green at the connections.
    If they are losing signal due to sunlight, halogen lamps, or other source
    of interference, they will flicker with blue at some of the connections.
    If they are receiving invalid data (or connected to a Blink not running this sketch)
    they will show red.

    You should only see blue when seperating Blinks, never see red, and see green while connected.

    The rules are as follows:
    1. Show Green when connected
    2. Show Blue for 200ms when separated (then OFF)
    3. Show Red for 200ms when bad data received

    by Jonathan Bobrow
    11.04.2018

*/

#define DISPLAY_ISSUE_DURATION 200    // how long to display an issue for

bool neighborPresent[6];  // keep track of neighbors present from last check

Timer timer[6];           // a timer for each face when it needs to display an issue

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  FOREACH_FACE( f ) {
    if (timer[f].isExpired()) {
      if ( !isValueReceivedOnFaceExpired( f ) ) {
        neighborPresent[f] = true;
        byte neighbor = getLastValueReceivedOnFace( f );
        if (neighbor == 0) {
          setColorOnFace(GREEN, f);
        }
        else {
          setColorOnFace(RED, f);
          timer[f].set(DISPLAY_ISSUE_DURATION);
        }
      }
      else {
        if (neighborPresent[f]) {
          setColorOnFace(BLUE, f);
          timer[f].set(DISPLAY_ISSUE_DURATION);
          neighborPresent[f] = false;
        }
        else {
          setColorOnFace(OFF, f);
        }
      }
    }
  }
}
