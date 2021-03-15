/*!
 * @file measureTemperatureAndHumidity.ino
 * @brief Measurement of temperature and humidity
 * @n 本传感器可测量温湿度数据，温度的测量范围在-40~125 ℃ ，湿度的测量范围在 0~100 %RH。
 * @n 本传感器可通过四种模式测量数据，分别是 开启时钟延展、不开启时钟延展、低功耗模式加时钟延展、低功耗模式不加时钟延展。
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2021-02-20
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHTC3
 */
#include<DFRobot_SHTC3.h>

/*DFRobot_SHTC3 SHTC3(&Wire)*/

DFRobot_SHTC3 SHTC3;

void setup() {
  Serial.begin(115200);

  /**
   * mode:
   *  enableClkStretch                     Clock Stretching Enabled
   *  disableClkStretch                    Clock Stretching Disabled
   *  enableClkStretchLowPower             Clock Stretching Enabled & Low Power
   *  disableClkStretchLowPower            Clock Stretching Disabled & Low Power
   */
  while(!SHTC3.begin(/*mode*/SHTC3.enableClkStretch)){
    Serial.println("Please check that the sensor is properly connected!");
    delay(1000);
  }

}

void loop() {
  SHTC3.wakeup();
  if(SHTC3.getTandRHData()){
    Serial.print("temperature:"); Serial.print(SHTC3.temperature);Serial.print("C");
    Serial.print("  humidity:"); Serial.print(SHTC3.humidity);Serial.println(" %RH");
  }else{
    Serial.println("ERR:Checksum error!!!");
  }
  SHTC3.sleep();
  delay(1000);
}
