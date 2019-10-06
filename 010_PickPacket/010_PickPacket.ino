/*
   #010 - Pick Packet

   Send more information 

   --------------------
   Sketch-A-Day
   12.23.2018
   by Jonathan Bobrow

   @madewithblinks
   www.move38.com
   --------------------
*/

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // send packet
  byte sendPacketLength;
  byte sendPacket[]; 

  FOREACH_FACE(f) {
    sendPacketOnFace(f, (byte *) sendPacket, sendPacketLength);
  }

  // receive packet
  FOREACH_FACE(f) {
    
    if (isPacketReadyOnFace(f)) { //is there a packet?

      byte packetLength = getPacketLengthOnFace(f);

      byte *data = (byte *) getPacketDataOnFace(f); //grab the data

      for (byte i = 0; i < packetLength; i++) {
        // store the data in an array
      }
    }
  }
}
