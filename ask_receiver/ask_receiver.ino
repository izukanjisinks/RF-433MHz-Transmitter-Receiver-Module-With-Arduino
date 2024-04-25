#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(2000, 2, 4, 5);


void setup()
{
    Serial.begin(115200);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      // Create a string to store the received characters
  String receivedMessage = "";
  
  // Iterate through each character in the buffer
  for (int i = 0; i < buflen; i++) {
    // Append the current character to the received message string
    receivedMessage += (char)buf[i];
  }
  
  // Message with a good checksum received, dump it.
  Serial.print("Co2: ");
  Serial.print(receivedMessage); // Print the received message
  Serial.println(" ppm");
  }        
}
