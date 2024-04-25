#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

#include <DFRobot_SCD4X.h>
int led1 = 13;
int delayTime = 1000;

RH_ASK driver(2000, 2, 4, 5);//2 is the receiver pin, 4 is the transmitter pin

DFRobot_SCD4X SCD4X(&Wire, /*i2cAddr = */SCD4X_I2C_ADDR);

void setup()
{
    Serial.begin(115200);    // Debugging only
    if (!driver.init()){
      
      Serial.println("init failed");
      
      }else{
        while( !SCD4X.begin() ){
        Serial.println("Communication with device failed, please check connection");
        delay(1000);
          }
          Serial.println("Begin ok!");

  SCD4X.enablePeriodMeasure(SCD4X_STOP_PERIODIC_MEASURE);


  SCD4X.setTempComp(4.0);

  float temp = 0;
  temp = SCD4X.getTempComp();
  Serial.print("The current temperature compensation value : ");
  Serial.print(temp);
  Serial.println(" C");

  SCD4X.setSensorAltitude(540);

  uint16_t altitude = 0;
  altitude = SCD4X.getSensorAltitude();
  Serial.print("Set the current environment altitude : ");
  Serial.print(altitude);
  Serial.println(" m");


  SCD4X.enablePeriodMeasure(SCD4X_START_PERIODIC_MEASURE);

  Serial.println();
      }
         
}

void loop()
{
    
    
if(SCD4X.getDataReadyStatus()) {
    
    DFRobot_SCD4X::sSensorMeasurement_t data;
    SCD4X.readMeasurement(&data);

    Serial.print("Carbon dioxide concentration : ");
    Serial.print(data.CO2ppm);
    Serial.println(" ppm");

    int CO2_level = data.CO2ppm; // Assuming data.CO2ppm is the CO2 level as an integer

    // Convert the CO2 level to a string
    char CO2_string[10]; // Allocate enough space to hold the string representation
    sprintf(CO2_string, "%d", CO2_level); // Convert integer to string
    
    // Calculate the length of the CO2 level string
    uint8_t length = strlen(CO2_string);
    
    // Send the CO2 level string
    driver.send((uint8_t *)CO2_string, length);
    driver.waitPacketSent();
    Serial.println("CO2 level sent");


     if (data.CO2ppm > 1000) {
      Serial.println("CO2 level is too high!");
      digitalWrite(13,LOW);
      digitalWrite(12,HIGH);
    }else{
      digitalWrite(13,HIGH);
      }


//    Serial.print("Environment temperature : ");
//    Serial.print(data.temp);
//    Serial.println(" C");

//    Serial.print("Relative humidity : ");
//    Serial.print(data.humidity);
//    Serial.println(" RH");

    Serial.println();
  }
  
  delay(delayTime);
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
}
