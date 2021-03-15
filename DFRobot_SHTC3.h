/*!
 * @file DFRobot_SHTC3.h
 * @brief Define the infrastructure for the DFRobot_SHTC3 class
 * @n This is a DFRobot_SHTC3 sensor that supports IIC communication. The IIC address cannot be changed, default to 0x70. The functions are as follows:
 * @n The sensor covers a humidity measurement range of 0 to 100 %RH and a temperature measurement range of - 40 °C to 125 °C with a typical accuracy of ±2 %RH and ±0.2°C.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @SKU SEN0414
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-02-20
 * @url  https://github.com/DFRobot/DFRobot_SHTC3
 */
#ifndef _DFROBOT_SHTC3_H_
#define _DFROBOT_SHTC3_H_

#include <Arduino.h>
#include <Wire.h>

#define SHTC3_IIC_ADDR                             0x70
#define COMMAND_SLEEP                              0xB098

#define COMMAND_WAKEUP                             0x3517

#define COMMAND_MEAS_T_RH_EN_CLOCKSTR              0x7CA2
#define COMMAND_MEAS_T_RH_DIS_CLOCKSTR             0x7866
#define COMMAND_MEAS_T_RH_EN_CLOCKSTR_LOW_POWER    0x6458
#define COMMAND_MEAS_T_RH_DIS_CLOCKSTR_LOW_POWER   0x609C

#define COMMAND_SOFTWARE_RESET                     0x805D
#define COMMAND_DEVICE_ID                          0xEFC8



class DFRobot_SHTC3{
public:
  typedef enum{
    enableClkStretch =1,
    disableClkStretch,
    enableClkStretchLowPower,
    disableClkStretchLowPower,
  }eWorkingMode;
  float temperature;
  float humidity;
public:
  /**
   * @brief  constructed function
   * @param  pWire  When instantiate this class, you can specify its twowire
   */
  DFRobot_SHTC3(TwoWire *pWire=&Wire);
  
  /**
   * @brief  Destructor
   */
  ~DFRobot_SHTC3(){};
  
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
  
private:
  /**
   * @brief  software reset
   */
  void softwareReset();
  


  /**
   * @brief  set the operating mode of the sensor
   * @param  mode  The operating mode of the sensor
   */
  void setMode(uint8_t mode);

  /**
   * @brief  Obtain raw data of temperature and humidity
   * @param  temp Pointer to the address of the original value of the temperature
   * @param  rh   Pointer to the address of the original value of the humidity
   * @return Is the data obtained correct? return true  The data is correct ; return false  The data  is incorrect
   */
  bool getTandRHRawData(uint16_t* temp,uint16_t* rh);
  
  /**
   * @brief  check sensor id
   * @return id correct return true ,id incorrect return false
   */
  bool checkDeviceID();
  
  /**
   * @brief  Check checksum
   * @param  data1  High 8 bits to check value
   * @param  data2  LOW 8 bits to check value
   * @param  crcValue  Check value returned by the sensor
   * @return Check success return true ;Check failed return false
   */
  bool checkCrc(uint8_t data1,uint8_t data2,uint8_t crcValue);

  /**
   * @brief  Write a command to the sensor
   * @param  command  
   */
  void writeCommand(uint16_t command);

  /**
   * @brief  Read data from the sensor
   * @param  command  Write a command to the sensor
   * @param  readnum  The amount of data read
   * @param  readArray  A container for storing data
   */
  void readValue(uint16_t command,uint8_t readnum,uint8_t *readArray);
  
private:
  TwoWire *_pWire;
  uint8_t _deviceAddr;
  uint8_t _mode;
};



#endif
