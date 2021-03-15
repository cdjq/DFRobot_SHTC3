# DFRobot_SHTC3

The SHTC3 is a digital humidity and temperature sensor designed especially for high-volume consumer electronics applications.

The sensor covers a humidity measurement range of 0 to 100 %RH and a temperature measurement range of - 40 °C to 125 °C with a typical accuracy of ±2 %RH and ±0.2°C.![](D:\Arduino\libraries\DFRobot_SHTC3\resources\images\SEN0427svg1.png)

## 产品链接（https://www.dfrobot.com/）
    SKU：SEN0414

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary
Measurement of temperature and humidity

## Installation

To use this library, download the library file first, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
   /**
   * @brief  Initialization function
   * @param  mode  The operating mode of the sensor
   *               enableClkStretch                     Clock Stretching Enabled
   *               disableClkStretch                    Clock Stretching Disabled
   *               enableClkStretchLowPower             Clock Stretching Enabled & Low Power
   *               disableClkStretchLowPower            Clock Stretching Disabled & Low Power
   * @return Whether the device is on or not. return true succeed ;return false failed.
   */
  bool begin(uint8_t mode = enableClkStretch);
  
  /**
   * @brief  wakeup
   */
  void wakeup();
  
  /**
   * @brief  device sleep
   */
  void sleep();
  
  /**
   * @brief  Obtain temperature and humidity data
   * @return Is the data obtained correct? return true  The data is correct ; return false  The data  is incorrect
   */
  bool getTandRHData();

```

## Compatibility

| MCU                | Work Well | Work Wrong | Untested | Remarks |
| ------------------ | :-------: | :--------: | :------: | ------- |
| Arduino uno        |     √     |            |          |         |
| FireBeetle esp32   |     √     |            |          |         |
| FireBeetle esp8266 |     √     |            |          |         |
| FireBeetle m0      |     √     |            |          |         |
| Leonardo           |     √     |            |          |         |
| Microbit           |     √     |            |          |         |
| Arduino MEGA2560   |     √     |            |          |         |


## History

- data 2021-02-22
- version V1.0


## Credits

Written by [yangfeng]<feng.yang@dfrobot.com>,2021,(Welcome to our [website](https://www.dfrobot.com/))
