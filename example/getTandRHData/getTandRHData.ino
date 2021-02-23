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
float data[2]={0,0};
void setup() {
  Serial.begin(115200);
  /**
   * mode:
   *  workingModeOne                    Clock Stretching Enabled and Read Temperature First
   *  workingModeTwo                    Clock Stretching Disabled and Read Temperature First
   */
  while(SHTC3.begin(/*mode*/SHTC3.workingModeOne)==false){
    Serial.println("Please check that the sensor is properly connected!");
    delay(1000);
  }
}

void loop() {
  if(SHTC3.getTandRHData(data)){
    Serial.print("temperature:"); Serial.print(data[0]);Serial.print("°C");
    Serial.print("  humidity:"); Serial.print(data[1]);Serial.println(" %RH");
  }else{
    Serial.println("ERR:Checksum error!!!");
  }
  delay(1000);
}