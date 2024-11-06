#include <RH_RF95.h>


void default1()
{
  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server
  uint8_t data[] = "Hello World!";
  rf95.send(data, sizeof(data));
  
  rf95.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.waitAvailableTimeout(3000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
//      Serial.print("RSSI: ");
//      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf95_server running?");
  }
  delay(400);
}

void sendMss(uint8_t data[],int size){
  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server
  //uint8_t data[] = "Hello World!";
  rf95.send(data, size);
  if (rf95.waitAvailableTimeout(3000))
  { 
   
  }
  else
  {
    Serial.println("No reply, is rf95_server running?");
  }
}