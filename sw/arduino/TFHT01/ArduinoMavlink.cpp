/*
  ArduinoMavlink.cpp adopted from PixhawkArduinoMAVLink.cpp
  Updated by Roman Dvorak, 2020-10, dvorakroman@thunderfly.cz, ThunderFly s.r.o,
  
  PixhawkArduinoMAVLink.cpp - Library for using Arduino to recieve Pixhawk's sensor data as well as some other usefull data which you might need.
  Created by Shashi Kant, June 23, 2018.
*/

#include "ArduinoMavlink.h"

ArduinoMavlink::ArduinoMavlink(HardwareSerial &hs){
  _MAVSerial = &hs;
  MILLIG_TO_MS2 = 9.80665 / 1000.0;
  system_id = 1; // Your i.e. Arduino sysid
  component_id = 158; // Your i.e. Arduino compid
  type = MAV_TYPE_QUADROTOR;
  autopilot =  MAV_AUTOPILOT_INVALID;
}

bool ArduinoMavlink::begin(){
  _MAVSerial->begin(57600);
  if(_MAVSerial->available()<=0){
    return 0;
  }else{
    return 1;
  }
}

// At first we will send some HeartBeats to Pixhawk to check whether it's available or not??
// After that we will check for whether we are recieving HeartBeats back from Pixhawk if Yes,
// We will note down its sysid and compid to send it a req to Stream Data.
void ArduinoMavlink::Stream(){
  delay(2000);
  int flag=1;
  Serial.println("Sending Heartbeats...");
  mavlink_message_t msghb;
  mavlink_heartbeat_t heartbeat;
  uint8_t bufhb[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_heartbeat_pack(system_id, component_id, &msghb, type, autopilot, MAV_MODE_PREFLIGHT, 0, MAV_STATE_STANDBY);
  uint16_t lenhb = mavlink_msg_to_send_buffer(bufhb, &msghb);
  delay(1000);
  _MAVSerial->write(bufhb,lenhb);
  Serial.println("Heartbeats sent! Now will check for recieved heartbeats to record sysid and compid...");

  // Looping untill we get the required data.
  while(flag==1){
    delay(1);
    while(_MAVSerial->available()>0){
      mavlink_message_t msgpx;
      mavlink_status_t statuspx;
      uint8_t ch = _MAVSerial->read();
      if(mavlink_parse_char(MAVLINK_COMM_0, ch, &msgpx, &statuspx)){
        Serial.println("Message Parsing Done!");
        switch(msgpx.msgid){
          case MAVLINK_MSG_ID_HEARTBEAT:
          {
            mavlink_heartbeat_t packet;
            mavlink_msg_heartbeat_decode(&msgpx, &packet);
            received_sysid = msgpx.sysid;
            received_compid = msgpx.compid;
            Serial.println("sysid and compid successfully recorded");
            flag = 0;
            break;
          }
        }
      }
    }
  }

//  Sending request for data stream...
//  Serial.println("Now sending request for data stream...");
//  delay(2000);
//  mavlink_message_t msgds;
//  uint8_t bufds[MAVLINK_MAX_PACKET_LEN];
//  mavlink_msg_request_data_stream_pack(system_id, component_id, &msgds, received_sysid, received_compid, MAV_DATA_STREAM_ALL , 0x05, 1);
//  uint16_t lends = mavlink_msg_to_send_buffer(bufds, &msgds);
//  delay(1000);
//  _MAVSerial->write(bufds,lends);
  Serial.println("Request sent! Now you are ready to recieve datas...");

}

void ArduinoMavlink::SendHeartBeat(){
  
  Serial.println("Sending Heartbeats...");
  mavlink_message_t msghb;
  mavlink_heartbeat_t heartbeat;
  uint8_t bufhb[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_heartbeat_pack(system_id, component_id, &msghb, type, autopilot, MAV_MODE_PREFLIGHT, 0, MAV_STATE_STANDBY);
  uint16_t lenhb = mavlink_msg_to_send_buffer(bufhb, &msghb);
  _MAVSerial->write(bufhb,lenhb);

  return;
}

void ArduinoMavlink::SendTunnelData(uint8_t *payload_data, uint8_t payload_length, uint8_t payload_type = 0, uint8_t sysid = 0, uint8_t compid = 0){
  
  Serial.println("Sending Tunnel data...");
  mavlink_message_t msgtn;
  mavlink_tunnel_t tunnel;
  uint8_t buftn[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_tunnel_pack(system_id, component_id, &msgtn, sysid, compid, payload_type, payload_length, payload_data);
  uint16_t lentn = mavlink_msg_to_send_buffer(buftn, &msgtn);
  _MAVSerial->write(buftn, lentn);

  return;
}


bool ArduinoMavlink::ReadSystemTime(uint64_t *time_unix_usec, uint32_t *time_boot_ms, uint32_t max_delay = 5000){
    unsigned long time_until;
    time_until = millis() + max_delay;
    
    
    while(_MAVSerial->available() > 0 ){
      delay(10);
      mavlink_message_t msg;
      mavlink_status_t status1;
      uint8_t ch = _MAVSerial->read();

      if(mavlink_parse_char(MAVLINK_COMM_0, ch, &msg, &status1)){
        if(msg.msgid == MAVLINK_MSG_ID_SYSTEM_TIME){
              mavlink_system_time_t data;
              mavlink_msg_system_time_decode(&msg, &data);

              *time_unix_usec = data.time_unix_usec;
              *time_boot_ms = data.time_boot_ms;
              
              return 1;
        }
      }

      if(time_until < millis()){
        Serial.print("TimeOut");
        return 0;
      }
    }
    return 0;
}
