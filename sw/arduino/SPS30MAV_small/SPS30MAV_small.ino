#include "ArduinoMavlink.h"
#include <sps30.h>
/*

                     Mighty 1284p    
                      +---\/---+
           (D 0) PB0 1|        |40 PA0 (AI 0 / D24)
           (D 1) PB1 2|        |39 PA1 (AI 1 / D25)
      INT2 (D 2) PB2 3|        |38 PA2 (AI 2 / D26)
       PWM (D 3) PB3 4|        |37 PA3 (AI 3 / D27)
    PWM/SS (D 4) PB4 5|        |36 PA4 (AI 4 / D28)
      MOSI (D 5) PB5 6|        |35 PA5 (AI 5 / D29)
  PWM/MISO (D 6) PB6 7|        |34 PA6 (AI 6 / D30)
   PWM/SCK (D 7) PB7 8|        |33 PA7 (AI 7 / D31)
                 RST 9|        |32 AREF
                VCC 10|        |31 GND
                GND 11|        |30 AVCC
              XTAL2 12|        |29 PC7 (D 23)
              XTAL1 13|        |28 PC6 (D 22)
      RX0 (D 8) PD0 14|        |27 PC5 (D 21) TDI
      TX0 (D 9) PD1 15|        |26 PC4 (D 20) TDO
RX1/INT0 (D 10) PD2 16|        |25 PC3 (D 19) TMS
TX1/INT1 (D 11) PD3 17|        |24 PC2 (D 18) TCK
     PWM (D 12) PD4 18|        |23 PC1 (D 17) SDA
     PWM (D 13) PD5 19|        |22 PC0 (D 16) SCL
     PWM (D 14) PD6 20|        |21 PD7 (D 15) PWM
                      +--------+
*/

HardwareSerial &hs = Serial1;
ArduinoMavlink mav(hs);

#define PPS  12     // PD4
boolean led_status = false;
uint8_t data[42];

void setup() 
{
  int16_t ret;

  pinMode(PPS, INPUT);    // sets the digital pin as input

  Serial.begin(9600);
  Serial1.begin(57600);

  delay(250);
  while(!mav.begin())
  {
    Serial.println("Not Connected!");
    delay(250);
  }

  sensirion_i2c_init();

  while (sps30_probe() != 0) 
  {
    Serial.print("SPS sensor probing failed\n");
    delay(500);
  }
  Serial.print("SPS sensor probing successful\n");

  ret = sps30_start_measurement();
  if (ret < 0) 
  {
    Serial.print("error starting measurement\n");
  }
  Serial.print("measurements started\n");
  
  //mav.Stream();
  delay(2000);
}


void loop() 
{
  struct sps30_measurement m;
  char serial[SPS30_MAX_SERIAL_LEN];
  uint16_t data_ready;
  int16_t ret;

  while(digitalRead(PPS) == false);  // Waiting for 1PPS signal from GPS

  do 
  {
    ret = sps30_read_data_ready(&data_ready);
    if (ret < 0) 
    {
      Serial.print("error reading data-ready flag: ");
      Serial.println(ret);
    } 
    else if (!data_ready)
    {
      Serial.print("data not ready, no new measurement available\n");
      delay(100); /* retry in 100 ms */
    }
    else
      break;
  } while (1);
  
  ret = sps30_read_measurement(&m);
  if (ret < 0) {
    Serial.print("error reading measurement\n");
  } 
  else 
  {
    Serial.println();

    uint32_t MC1p0 = round(m.mc_1p0 * 100);
    uint32_t MC2p5 = round((m.mc_2p5 - m.mc_1p0) * 100);
    uint32_t MC4p0 = round((m.mc_4p0 - m.mc_2p5) * 100);
    uint32_t MC10p0 = round((m.mc_10p0 - m.mc_4p0) * 100);

    Serial.print("PM  0.3 - 1.0: ");
    Serial.println(m.mc_1p0);
    Serial.print("PM  1.0 - 2.5: ");
    Serial.println(m.mc_2p5 - m.mc_1p0);
    Serial.print("PM  2.5 - 4.0: ");
    Serial.println(m.mc_4p0 - m.mc_2p5);
    Serial.print("PM 4.0 - 10.0: ");
    Serial.println(m.mc_10p0 - m.mc_4p0);

    uint32_t NC0p5 = round(m.nc_0p5 * 100);
    uint32_t NC1p0 = round((m.nc_1p0 - m.nc_0p5) * 100);
    uint32_t NC2p5 = round((m.nc_2p5 - m.nc_1p0) * 100);
    uint32_t NC4p0 = round((m.nc_4p0 - m.nc_2p5) * 100);
    uint32_t NC10p0 = round((m.nc_10p0 - m.nc_4p0) * 100);
    
    mav.SendHeartBeat();

    Serial.print("NC  0.3 - 0.5:  ");
    Serial.println(m.nc_0p5);
    Serial.print("NC  0.5 - 1.0:  ");
    Serial.println(m.nc_1p0 - m.nc_0p5);
    Serial.print("NC  1.0 - 2.5:  ");
    Serial.println(m.nc_2p5 - m.nc_1p0);
    Serial.print("NC  2.5 - 4.0:  ");
    Serial.println(m.nc_4p0 - m.nc_2p5);
    Serial.print("NC  4.0 - 10.0: ");
    Serial.println(m.nc_10p0 - m.nc_4p0);

    uint32_t TPS = round(m.typical_particle_size * 100);
    
    Serial.print("Typical partical size: ");
    Serial.println(m.typical_particle_size);
  
    data[0] = (NC0p5) & 0xFF;
    data[1] = (NC0p5 >> 8) & 0xFF;
    data[2] = (NC0p5 >> 16) & 0xFF;
    data[3] = (NC0p5 >> 24) & 0xFF;
    data[4] = (NC1p0) & 0xFF;
    data[5] = (NC1p0 >> 8) & 0xFF;
    data[6] = (NC1p0 >> 16) & 0xFF;
    data[7] = (NC1p0 >> 24) & 0xFF;
    data[8] = (NC2p5) & 0xFF;
    data[9] = (NC2p5 >> 8) & 0xFF;
    data[10] = (NC2p5 >> 16) & 0xFF;
    data[11] = (NC2p5 >> 24) & 0xFF;
    data[12] = (NC4p0) & 0xFF;
    data[13] = (NC4p0 >> 8) & 0xFF;
    data[14] = (NC4p0 >> 16) & 0xFF;
    data[15] = (NC4p0 >> 24) & 0xFF;
    data[16] = (NC10p0) & 0xFF;
    data[17] = (NC10p0 >> 8) & 0xFF;
    data[18] = (NC10p0 >> 16) & 0xFF;
    data[19] = (NC10p0 >> 24) & 0xFF;
    data[20] = (MC1p0) & 0xFF;
    data[21] = (MC1p0 >> 8) & 0xFF;
    data[22] = (MC1p0 >> 16) & 0xFF;
    data[23] = (MC1p0 >> 24) & 0xFF;
    data[24] = (MC2p5) & 0xFF;
    data[25] = (MC2p5 >> 8) & 0xFF;
    data[26] = (MC2p5 >> 16) & 0xFF;
    data[27] = (MC2p5 >> 24) & 0xFF;
    data[28] = (MC4p0) & 0xFF;
    data[29] = (MC4p0 >> 8) & 0xFF;
    data[30] = (MC4p0 >> 16) & 0xFF;
    data[31] = (MC4p0 >> 24) & 0xFF;
    data[32] = (MC10p0) & 0xFF;
    data[33] = (MC10p0 >> 8) & 0xFF;
    data[34] = (MC10p0 >> 16) & 0xFF;
    data[35] = (MC10p0 >> 24) & 0xFF;
    data[36] = (TPS) & 0xFF;
    data[37] = (TPS >> 8) & 0xFF;
    data[38] = (TPS >> 16) & 0xFF;
    data[39] = (TPS >> 24) & 0xFF;
    data[40] = 255;
    data[41] = 255;

    // data array (max length 128), data array size, data type (0 default - unknown), target sysid, target compid
    // For unicast (only for logging purposes) set sysid and compid to match the autopilot. For realtime visualisation, you can
    // set sysid and comid to broadcast (0, 0)
    mav.SendTunnelData(data, sizeof(data), 0, 0, 0);
    
    led_status = !led_status;
    digitalWrite(13, led_status);
  }
  //delay(100);
}
