# TFHT01 - UAV Humidity and Temperature sensor

The TFHT01 hygrometer sensor offers flexible integration options, including direct connection to a Pixhawk autopilot with PX4 firmware, or utilization as a sensor for the [TF-ATMON monitoring system](https://www.thunderfly.cz/tf-atmon.html).

Sensors mounted on UAVs can be used for a variety of use. It can be used to measure air temperature and humidity, which can be used to estimate icing conditions that could result in the form of ice on aerodynamic surfaces. Or to determine if the flight is conducted within the operating range of the drone. Another use can be to measure the temperature of selected UAV components. For example the temperature of batteries, ESC, motor, or some bearings. 

![TFHT01A top view](/doc/img/TFHT01A2.jpg)

## Where to get it?

ThunderFly Humidity and Temperature sensor (TFHT01) is commercially available from [ThunderFly s.r.o.](https://www.thunderfly.cz/), write an email to info@thunderfly.cz or shop at [Tindie store](https://www.tindie.com/products/thunderfly/tfht01-aerial-hygrometer-and-thermometer/).

## Parameters

| Parameter | Value | Description |
|-----------|-------|-------------|
| Sensing element | [SHT35](https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf) | Other possible sensors SHT30, SHT31 |
| I2C connector | 4-pin JST-GH | The second connector could be installed on the opposite side |
| I2C address | 0x44 default | By switching of JP1 is possible change to 0x45 |
| Operating and storage temperature | -20 - +40°C |  |
| Operational humidity | 0-100 % | At humidity above 80% the performance of the sensor could be degraded in case of prolonged time periods |
| Operational input voltage | 3.6 - 5.4V | Overvoltage internally protected by zener diode |
| Mass | 2 g | PCB without cabling |
| Dimensions | 30 x 15 x 6.5 mm |  PCB |
| Weather resistance | IP40 | External connectors fully occupied. The sensor itself is protected by IP67 according the [sensirion datasheet](https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/2_Humidity_Sensors/Datasheets/Sensirion_Humidity_Sensors_SHT3x_Datasheet_Filter_Membrane.pdf) |

## Usage in PX4 
The sensor is currently supported by the PX4 autopilot. Multiple sensors can be connected to one autopilot. The measured data are immediately sent to the ground station and they are also logged in the onboard ulog file. Sensor support can be enabled by setting the [SENS_EN_SHT3X](http://docs.px4.io/master/en/advanced_config/parameter_reference.html#SENS_EN_SHT3X) parameter to 1. 

