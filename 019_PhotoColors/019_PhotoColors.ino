/*
 * BLINKS PHOTO COLORS
 */
 
void setup() {
  // put your setup code here, to run once:
  FOREACH_FACE(f){
    setColorOnFace(makeColorHSB(f*255/6,255,255), f);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
