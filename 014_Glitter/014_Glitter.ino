/*
   #014 - Glitter

   Make the whole thang sparkle
   https://www.nytimes.com/2018/12/21/style/glitter-factory.html

   --------------------
   Sketch-A-Day
   12.27.2018
   by Jonathan Bobrow

   @madewithblinks
   www.move38.com
   --------------------
*/

#define SPARKLE_DELAY     75
#define SPARKLE_DURATION  500

byte sparkleOffset[6] = {0, 3, 5, 1, 4, 2};
byte brightness[6];
Timer sparkleTimer[6];

void setup() {
  // put your setup code here, to run once:
  FOREACH_FACE(f) {
    sparkleTimer[f].never();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // start bright and then fade down quickly
  if (buttonPressed()) {
    FOREACH_FACE(f) {
      // randomize the face offsets
      // TODO: reorder sparkleOffset
      randomize(sparkleOffset, 6);
      sparkleTimer[sparkleOffset[f]].set(SPARKLE_DURATION + SPARKLE_DELAY * f);
    }
  }

  // display
  FOREACH_FACE(f) {
    if (!sparkleTimer[f].isExpired()) {
      if (sparkleTimer[f].getRemaining() > SPARKLE_DURATION) {
        setColorOnFace(OFF, f);
      }
      else {
        brightness[f] = (255 * sparkleTimer[f].getRemaining()) / SPARKLE_DURATION;
        setColorOnFace(dim(WHITE, brightness[f]), f);
      }
    }
    else {
      setColorOnFace(OFF, f);
    }
  }

}

// A utility function to swap to integers 
void swap (byte *a, byte *b) 
{ 
    byte temp = *a; 
    *a = *b; 
    *b = temp; 
} 

// https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
// A function to generate a random permutation of arr[] 
void randomize ( byte arr[], byte n ) 
{   
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        byte j = random(100) % (i+1); 
  
        // Swap arr[i] with the element at random index 
        swap(&arr[i], &arr[j]); 
    } 
}
