# TFHT01 ThunderFly Humidity and Temperature sensor

Sensor could be directly connected to Pixhawk autopilot with PX4 firmware, or could be used as a sensor of [TF-ATMON monitoring system](https://www.thunderfly.cz/tf-atmon.html). 

## Parameters


| Parameter | Value | Description |
|-----------|-------|-------------|
| Sensing element | [SHT35](https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/2_Humidity_Sensors/Datasheets/Sensirion_Humidity_Sensors_SHT3x_Datasheet_digital.pdf) | Other possible sensors SHT30, SHT31 |
| I2C Connector | 4-pin JST-GH | The second connector could be installed on opposite side |
| I2C adress | 0x44 default | By switching of JP1 is possible change to 0x45 |
| Operating and storage temperature | -20 - +40°C |  |
| Operational humidity | 0-100 % | At humidity above 80% the performance of the sensor could be degraded in case of prolonged time periods |
| Operational input voltage | 3.6 - 5.4V | Overvoltage internally protected by zener diode |
| Mass | 2 g | PCB without cabling |
| Dimensions |  |  PCB |
| Weather resistance | IP40 | External connectors fully occupied. The sensor itself is protected by IP67 according the [sensirion datasheet](https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/2_Humidity_Sensors/Datasheets/Sensirion_Humidity_Sensors_SHT3x_Datasheet_Filter_Membrane.pdf) |
