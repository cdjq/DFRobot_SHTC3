/*!
 * @file DFRobot_SHTC3.cpp
 * @brief Implementation of DFRobot_SHTC3 class
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @SKU SEN0414
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-02-20
 * @url  https://github.com/DFRobot/DFRobot_SHTC3
 */
#include<DFRobot_SHTC3.h>

DFRobot_SHTC3::DFRobot_SHTC3(TwoWire *pWire):
_pWire(pWire),_deviceAddr(SHTC3_IIC_ADDR)
{
  _mode = 0;
  temperature = 0;
  humidity = 0;
}
bool DFRobot_SHTC3::begin(uint8_t mode)
{
  _pWire->begin();
  setMode(mode);
  wakeup();
  softwareReset();
  delay(1);
  if(!checkDeviceID()){
    return false; 
  }
  sleep();
  return true;
}
void DFRobot_SHTC3::softwareReset()
{
  writeCommand(COMMAND_SOFTWARE_RESET);
  delayMicroseconds(173);
}
void DFRobot_SHTC3::wakeup()
{
  writeCommand(COMMAND_WAKEUP);
  delayMicroseconds(230);
}
void DFRobot_SHTC3::sleep()
{
  writeCommand(COMMAND_SLEEP);
  delayMicroseconds(230);
}
void DFRobot_SHTC3::setMode(uint8_t mode){
  if((mode>disableClkStretch)||(mode == 0)){
    _mode = enableClkStretch;
  }else{
    _mode = mode;
  }
}
bool DFRobot_SHTC3::getTandRHData()
{
  uint16_t temp,RH;
  if(getTandRHRawData(&temp,&RH)){
    temperature = (((float)temp*175.0)/65536.0)-45.0;
    humidity = ((float)RH*100.0)/65536.0;
    return true;
  }
  return false;
}
bool DFRobot_SHTC3::checkDeviceID()
{
  uint8_t idArray[3];
  uint16_t id =0;
  readValue(COMMAND_DEVICE_ID,3,idArray);
  if(checkCrc(idArray[0],idArray[1],idArray[2])){
    id = (idArray[0]<<8)|idArray[1];
    if((id&0x807) == 0x807){
      return true;
    }
  }
  return false;
}
bool DFRobot_SHTC3::getTandRHRawData(uint16_t* temp,uint16_t* rh)
{
  uint8_t data[6];
  uint16_t command;
  switch(_mode){
  case enableClkStretch:
    command = COMMAND_MEAS_T_RH_EN_CLOCKSTR;
    readValue(command,6,data); 
    if(checkCrc(data[0],data[1],data[2]) && checkCrc(data[3],data[4],data[5])){
      *temp = (data[0]<<8)|data[1];
      *rh = (data[3]<<8)|data[4];
      return true;
    }
    break;
  case disableClkStretch:
    command = COMMAND_MEAS_T_RH_DIS_CLOCKSTR;
    readValue(command,6,data);
    if(checkCrc(data[0],data[1],data[2]) && checkCrc(data[3],data[4],data[5])){
      *temp = (data[0]<<8)|data[1];
      *rh = (data[3]<<8)|data[4];
      return true;
    }
    break;
  }
  return false;
}
void DFRobot_SHTC3::writeCommand(uint16_t command)
{
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(command>>8);
  _pWire->write(command&0xFF);
  _pWire->endTransmission();
}
void DFRobot_SHTC3::readValue(uint16_t command,uint8_t readnum,uint8_t *readArray)
{
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(command>>8);
  _pWire->write(command&0xFF);
  _pWire->endTransmission();
  delayMicroseconds(11000);
  if(_pWire->requestFrom(_deviceAddr,readnum)==readnum){
    for(uint8_t i = 0; i < readnum; i++){
      readArray[i] = _pWire->read();
    }
  }
}
bool DFRobot_SHTC3::checkCrc(uint8_t data1,uint8_t data2,uint8_t crcValue){
  uint8_t crc = 0xFF;
  uint8_t crcData[2];
  crcData[0]=data1;
  crcData[1]=data2;
  for(int i =0; i<2;i++){
    crc ^= crcData[i];
    for(uint8_t bit = 8;bit>0;--bit){
      if(crc & 0x80){
        crc = (crc << 1)^0x31;
      }else{
        crc = (crc << 1);
      }
    }
  }
  if(crc != crcValue){
    return false;
  }
  return true;
}