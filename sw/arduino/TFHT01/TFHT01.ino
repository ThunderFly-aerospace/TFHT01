#include "ArduinoMavlink.h"
#include <HardwareSerial.h>
#include <SimpleTimer.h>
#include "Wire.h"
#include "SHT31.h"

#define SDAPIN  20
#define SCLPIN  21
#define RSTPIN  7

// SHT35 sensor(SCLPIN);
SHT31 sht;

SimpleTimer HbTim(1000);
SimpleTimer SensTim(500);

HardwareSerial &hs = Serial1;
ArduinoMavlink mav(hs);

const int LED1_PIN    = 1;
const int LED2_PIN    = 0;
int led1State = 0;
int led2State = 0;

uint8_t data[6]={0};

void setup() 
{

  
  Serial.begin(9600);
  Serial1.begin(57600);
  Wire.begin();
  Wire.setClock(100000);
  
  sht.begin(0x44, &Wire);    //Sensor I2C Address
  sht.heatOff();
  sht.reset();
  sht.clearStatus();
  Serial.print(sht.getError(), HEX);
  Serial.println();

  
  Serial.print(sht.getError(), HEX);
  Serial.println();
  

  Serial.println("Hello!");

  //while(!mav.begin())
  //{
  //  Serial.println("Not Connected!");
  //}

//  if(sensor.init())
//  {
//    Serial.println("sensor init failed!!!");
//  }
//  delay(100);

//  mav.Stream();

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, led1State);

  
  uint16_t stat = sht.readStatus();
  Serial.print(stat, BIN);
  Serial.println();

  
  Serial.print(sht.getError(), HEX);
  Serial.println();

    if (stat & SHT31_STATUS_HEATER_ON)
  {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

}


  uint16_t loop_c = 0;


void loop() 
{

    //Serial.println("loop");

   if (HbTim.isReady()) {
        mav.SendHeartBeat();
        
        led1State = !led1State;
        digitalWrite(LED1_PIN, led1State);
          
          // sht.heatOff();
//          sht.read();
//          Serial.print(sht.getTemperature());
//          Serial.print("\t");
//          Serial.println(sht.getHumidity());
//          sht.requestData();


        HbTim.reset();
   }


   if (SensTim.isReady()) {
        
        Serial.println("Sens loop");
        digitalWrite(LED2_PIN, 1);
        float temp,hum;
        sht.read();
        temp = sht.getTemperature();
        hum = sht.getHumidity();
        
        //led2State = !led2State;
        //digitalWrite(LED2_PIN, led2State);

        data[0] = (int) loop_c;
        data[1] = (int) temp;
        data[2] = (int) ((temp - (int)temp)*100);
        data[3] = (int) hum;
        data[4] = (int) ((hum - (int)hum)*100);
        
        mav.SendTunnelData(data, sizeof(data), 2, 1, 1);
        // 2 - datatype for TFHT01

        Serial.print("\t");
        Serial.print(temp);
        Serial.print("\t");
        Serial.print(hum);
        Serial.print("\n");

        loop_c += 1;
        SensTim.reset();
        digitalWrite(LED2_PIN, 0);
    }

}
