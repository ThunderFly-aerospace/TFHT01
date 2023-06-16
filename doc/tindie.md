The TFHT01 hygrometer sensor offers flexible integration options, including direct connection to a Pixhawk autopilot with PX4 firmware, or utilization as a sensor for the [TF-ATMON monitoring system](https://www.thunderfly.cz/tf-atmon.html). 

Once mounted on a UAV, the sensor provides a wealth of valuable data for various applications. Its ability to measure atmospheric temperature and humidity can help estimate that icing may form on aerodynamic surfaces or determine if the drone is operating within the recommended range. Furthermore, the sensor can also be utilized to measure the temperature of specific UAV components such as batteries, ESCs, motors, or bearings, enabling the identification of potential issues before they escalate and supporting proactive maintenance and repairs.

Choose the TFHT01 hygrometer sensor for unparalleled flexibility, precision, and versatility in data collection. Whether you require temperature and humidity data for agricultural or industrial equipment monitoring or need to monitor drone component temperatures for optimal performance, the TFHT01 has you covered.

### What is it?

TFHT01 is a hygrometer and thermometer with an I2C interface for use on drones as an onboard weather station. Relative humidity and temperature are quantities that can affect both the flight characteristics of the drone and the execution of aerial works. At certain temperatures and relative humidity, icing can form on the lifting surfaces resulting in worsening of its flight characteristics or even causing a crash. Meteorological conditions can affect the payload as well - they can cause e.g. fogging on camera lenses, etc. It is therefore important to know about the presence of these phenomena during the flight.

| Parameter | Value | Description |
|-----------|-------|-------------|
| Sensing element | [SHT35](https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf) | Other possible sensors SHT30, SHT31 |
| Typical accuracy | 1.5 %RH and 0.1 °C | |
| Repeatability | 0.15 %RH , 0.08 °C | The stated repeatability is 3 times the standard deviation (3σ) of multiple consecutive measurements at constant ambient conditions. |
| Operating temperature range| 0 °C - +65 °C | Sensor physically measures in range -40°C to +120°C with reduced accuracy |
| Operating humidity range| 0-100 % | At humidity above 80% the performance of the sensor could be degraded in case of prolonged time periods |
| I2C connector | 4-pin JST-GH | The second connector could be installed on the opposite side |
| I2C address | 0x44 default | By switching of JP1 is possible change address to 0x45 |
| Storage temperature range| -20 °C - +40 °C |  |
| Operational input voltage | 3.6 - 5.4V | Overvoltage internally protected by zener diode |
| Mass | 2 g | PCB without cabling |
| Dimensions | 30 x 15 x 6.5 mm |  PCB |
| Weather resistance | IP40 |  |

### How could be used 
We developed the TFHT01 because we needed to know the temperature and humidity of the environment in which we operate our drones. At that time no such sensor was commercially available on the market.

### Special features
The sensor is unique because it is ready to be immediately used on drones. It complies with the widely used dronecode standards and it is equipped with indicator diodes that help with quick diagnostics of the status of the sensor and its operating status.

Furthermore, the sensor has a specific construction makes it possible to place it in the outdoor environment easily. Alternatively, the sensor can be used as a diagnostics probe for drone avionics’ (e.g. engines, regulators, or batteries).

### Compatibility with autopilots

Our sensor is fully compatible with the dronecode standards. In terms of software, the sensor is supported by [PX4 autopilot](https://px4.io/). The driver is programmed as a so-called multi-instance. Thanks to this it is possible to connect multiple TFHT01 sensors to the autopilot (they can be located in different parts of the drone or measure data from different drone’s components). This should be done with respect to I2C bus properties, e.g. requirement of [different addresses for each device on the bus](https://www.tindie.com/products/thunderfly/tfi2cadt01-i2c-address-translator/).

### Use with PX4

Complete settings and driver options under PX4 can be found in the [official documentation](https://docs.px4.io/main/en/modules/modules_driver.html#sht3x).

To start the driver automatically it is only necessary to connect the sensor to any I2C port and set the `SENS_EN_SHT3x` parameter to 1 (enabled). The sensor should initialize during the next start. The prerequisite is to use the PX4 firmware version newer than 2022/03.

You can check that the driver is running and the sensor is initialized, after turning the driver on, the LED ‘ALERT’ is off.

Data is logged locally in the drone’s onboard avionics and is sent via mavlink to the ground station. The values can be viewed in real-time using control software e.g. [QGC](http://qgroundcontrol.com/).

### Another usage
The sensor can be used outside of drones and PX4 devices as well. I2C interface is the 4-pin JST-GH connector. The sensor board also contains I2C pull-ups and that’s why the sensor can be connected to e.g. Arduino or other single-board computers and they can be used to read the data from the sensor. The suggested supply voltage is 5V.


### What’s included?

- 1x TFHT01A with SHT35 sensor mounted
- 1x JST-GH 4-pin I2C cable in accordance to [cable style](https://docs.px4.io/master/en/assembly/cable_wiring.html#i2c-cables), Optionally
