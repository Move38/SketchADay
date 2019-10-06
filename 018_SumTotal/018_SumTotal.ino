/*
   #018 - Sum Total

   step 1) Seach each side 0-5, once a neighbor is found, 
   step 2) tell it to report the number connected to it, 
   step 3) wait for report
   step 4) receive report, add to sum total
   step 5) report number to side requested from after all other sides are reported or absent

   when asked to report the number connected, goto step 1

   --------------------
   Sketch-A-Day
   03.05.2019
   by Jonathan Bobrow

   @madewithblinks
   www.move38.com
   --------------------
*/

bool bMaster = false;
bool bAwaitingResponse = false;
byte numReportedOnFace[6];
bool hasReported[6];
byte faceRequestedFrom = NO_FACE;

enum States {
  
};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  if(buttonPressed()) {
    // start the count, you are responsible for letting everyone know the sum
    bMaster = true;
    // once we propogate the total, no need to be master anymore
  }

  
//   step 1) Seach each side 0-5, once a neighbor is found, 
  FOREACH_FACE(f) {
    if( f == faceRequestedFrom ) {
      continue;
    }
    if( hasReported[f] ) {
     continue;
    }
    else {
    // ask face to report and await response
    // break the loop while we await response
    }
    // if response available collect data
  }

  bool bAllReported = true;
  FOREACH_FACE(f) {
    if(!hasReported[f]) {
      bAllReported = false;
    }
  }

  if(bAllReported) {
    // now broadcast the result
    
    // no longer need to keep the role of master
    bMaster = false;
  }
//   step 2) tell it to report the number connected to it, 
//   step 3) wait for report
//   step 4) receive report, add to sum total
//   step 5) report number to side requested from after all other sides are reported or absent

}
