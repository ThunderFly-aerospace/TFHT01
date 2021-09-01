/*
  ArduinoMavlink.h adopted from PixhawkArduinoMAVLink.h
  Updated by Roman Dvorak, 2020-10, dvorakroman@thunderfly.cz, ThunderFly s.r.o,
  
  ArduinoMavlink.h - Library for using Arduino to recieve Pixhawk sensors data.
  Created by Shashi Kant, June 23, 2018.
*/

#ifndef ArduinoMavlink_h
#define ArduinoMavlink_h

#include "lib/c_library_v2/common/mavlink.h"
#include "lib/c_library_v2/checksum.h"
#include "lib/c_library_v2/mavlink_types.h"
#include "lib/c_library_v2/protocol.h"
#include <Arduino.h>
#include <HardwareSerial.h>

class ArduinoMavlink
{
  public:
    ArduinoMavlink(HardwareSerial &hs);
    bool begin();
    void SendHeartBeat();
    void SendTunnelData(uint8_t *payload_data, uint8_t payload_length, uint8_t payload_type, uint8_t sysid, uint8_t compid);
    bool ReadSystemTime(uint64_t *time_unix_usec, uint32_t *time_boot_ms, uint32_t max_delay);
    void Stream();
  private:
    HardwareSerial* _MAVSerial;
    double MILLIG_TO_MS2;
    uint8_t system_id;
    uint8_t component_id;
    uint8_t type;
    uint8_t autopilot;
    uint8_t received_sysid;
    uint8_t received_compid;
};

#endif
