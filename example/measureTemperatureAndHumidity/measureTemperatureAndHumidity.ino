/*!
 * @file getTandRHData.ino
 * @brief Measurement of temperature and humidity
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2021-02-20
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHTC3
 */
#include<DFRobot_SHTC3.h>
DFRobot_SHTC3 SHTC3;
void setup() {
  Serial.begin(115200);

  /**
   * mode:
   *  enableClkStretch                     Clock Stretching Enabled
   *  disableClkStretch                    Clock Stretching Disabled
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
