/*
   #023 - Polar Coordinates

   Square peg in a round hole
   draw a square with the light

   --------------------
   Sketch-A-Day
   07.12.2019
   by Jonathan Bobrow & Dan King

   @madewithblinks
   www.move38.com
   --------------------
*/

byte searchOrder[6] = {0, 1, 2, 3, 4, 5}; // used for searching faces, needs to be shuffled


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
   RANDOMIZE OUR SEARCH ORDER
   reference: http://www.cplusplus.com/reference/algorithm/random_shuffle/
*/

void shuffleSearchOrder() {

  for (byte i = 5; i > 0; i--) {
    // start with the right most, replace it with one of the 5 to the left
    // then move one to the left, and do this with the 4 to the left. 3, 2, 1
    byte swapA = i;
    byte swapB = random(i - 1);
    byte temp = searchOrder[swapA];
    searchOrder[swapA] = searchOrder[swapB];
    searchOrder[swapB] = temp;
  }
}
