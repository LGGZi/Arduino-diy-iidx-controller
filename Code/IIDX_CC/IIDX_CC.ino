#include "SubHID.h"
#include <EEPROM.h>
#include "iidx_Controller.h"
#include "iidx_Keyboard_N_Mouse.h"
extern volatile HIDConReport_t report;
extern volatile uint16_t HIDCon_led;
extern volatile uint8_t ledPins[];
extern volatile uint8_t buttonPins[];
extern volatile uint8_t muiltPins[][3];
extern volatile uint16_t ledbuf;
extern volatile uint16_t buttonbuf;
extern volatile int lighton;
extern volatile int32_t encL;

uint8_t mode = 0;
//模式选择
void mode_select(uint8_t modecode){
  if(modecode >= 1 && modecode <= 4){
    use_Controller_style(modecode);
  }else{
    use_KeyboardMouse_style(modecode);
  }
}
//初始化
void setup() {
  delay(1000);
  // Setup I/O for pins
  for(int i=0;i<BUTTONCOUNT;i++){
    pinMode(buttonPins[i],INPUT_PULLUP);
    pinMode(ledPins[i],OUTPUT);
  }
  pinMode(ENC_L_A,INPUT_PULLUP);
  pinMode(ENC_L_B,INPUT_PULLUP);
  //初始选择模式的部分
  if(digitalRead(muiltPins[0][0]) != HIGH && digitalRead(muiltPins[0][1]) != HIGH ) 
  { 
    EEPROM.write(0, 1);
  }
  else if(digitalRead(muiltPins[1][0]) != HIGH && digitalRead(muiltPins[1][1]) != HIGH ) 
  {
    EEPROM.write(0, 2);
  }
  else if(digitalRead(muiltPins[2][0]) != HIGH && digitalRead(muiltPins[2][1]) != HIGH ) 
  {
    EEPROM.write(0, 3);
  }
  else if(digitalRead(muiltPins[3][0]) != HIGH && digitalRead(muiltPins[3][1]) != HIGH ) 
  {
    EEPROM.write(0, 4);
  }  
  else if(digitalRead(muiltPins[4][0]) != HIGH && digitalRead(muiltPins[4][1]) != HIGH ) 
  {
    EEPROM.write(0, 5);
  }
  else if(digitalRead(muiltPins[5][0]) != HIGH && digitalRead(muiltPins[5][1]) != HIGH ) 
  {
    EEPROM.write(0, 6);
  }
  //EEPROM.write(0, 1);
  EEPROM.get(0 , mode);
  mode_select(mode);
  // Serial.begin(9600);
}

void loop() {
  //主程序选择
  if(mode >= 1 && mode <= 4){
    using_Controller_style();
  }else{
    using_KeyboardMouse_style();
  }
  lights(ledbuf);

  //灯光开关
  lightswitch(6);
  //每周期一次的report结构内容的上传
  HIDCon.setState(&report);
}