The TFHT01 hygrometer sensor offers flexible integration options, including direct connection to a Pixhawk autopilot with PX4 firmware, or utilization as a sensor for the [TF-ATMON monitoring system](https://www.thunderfly.cz/tf-atmon.html). 

Once mounted on a UAV, the sensor provides a wealth of valuable data for various applications. Its ability to measure atmospheric temperature and humidity can help estimate whether icing may form on aerodynamic surfaces or determine if the drone is operating within the recommended range. Furthermore, the sensor can also be utilized to measure the temperature of specific UAV components such as batteries, ESCs, motors, or bearings, enabling the identification of potential issues before they escalate and supporting proactive maintenance and repairs.

Choose the TFHT01 hygrometer sensor for unparalleled flexibility, precision, and versatility in data collection. Whether you require temperature and humidity data for agricultural or industrial equipment monitoring or need to monitor drone component temperatures for optimal performance, the TFHT01 has you covered.


### What is it?
TFHT01 is a hygrometer and thermometer with an I2C interface for use on drones as an onboard weather station. Relative humidity and temperature are quantities that can affect both the flight characteristics of the drone and the execution of aerial works. At certain temperatures and relative humidity, icing can form on the lifting surfaces resulting in worsening of its flight characteristics or even causing a crash. Meteorological conditions can affect the payload as well - they can cause e.g. fogging on camera lenses, etc. It is therefore important to know about the presence of these phenomena during the flight.

### Why did we make it?
We developed the TFHT01 because we needed to know the temperature and humidity of the environment in which we operate our drones. At that time no such sensor was commercially available on the market.

### What makes it special?
The sensor is unique because it is ready to be immediately used on drones. It complies with the widely used dronecode standards and it is equipped with indicator diodes that help with quick diagnostics of the status of the sensor and its operating software.

Furthermore, the sensor has a specific construction makes it possible to place it in the outdoor environment easily. Alternatively, the sensor can be used as a diagnostics probe for drone avionics’ (e.g. engines, regulators, or batteries).

### What is the sensor’s compatibility with autopilots?
Our sensor is fully compatible with the dronecode standards. In terms of software, the sensor is supported by PX4 autopilot. The driver is programmed as a so-called multi-instance. Thanks to this it is possible to connect multiple TFHT01 sensors to the autopilot (they can be located in different parts of the drone or measure data from different drone’s components). This should be done with respect to I2C bus properties, e.g. requirement of [different addresses](https://www.tindie.com/products/thunderfly/tfi2cadt01-i2c-address-translator/).

### Use with PX4
Complete settings and driver options under PX4 can be found in the official documentation.

To start the driver automatically it is only necessary to connect the sensor to any I2C port and set the `SENS_EN_SHT3x` parameter to 1 (enabled). The sensor should initialize during the next start. The prerequisite is to use the PX4 firmware version newer than 2022/03.

You can tell that the driver is running and the sensor is initialized when, after turning the driver on, the LED ‘ALERT’ is off.

Data is logged locally in the drone’s onboard avionics and is sent via mavlink to the ground station. The values can be viewed in real-time using e.g. QGC.

### Another usage
The sensor can be used outside of drones and PX4 devices as well. I2C output from the sensor is realized through the 4-pin JST-GH connector. The sensor board also contains I2C pull-ups and that’s why the sensor can be connected to e.g. Arduino or other single-board computers and they can be used to read the data from the sensor. The proposed supply voltage is 5V.


### What’s included?

- 1x TFHT01A
- 1x JST-GH 4-pin I2C cable in accordance to [cable style](https://docs.px4.io/master/en/assembly/cable_wiring.html#i2c-cables), Optionally
