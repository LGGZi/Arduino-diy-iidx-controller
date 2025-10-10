#include "SubHID.h"
#include <EEPROM.h>
#include "iidx_Controller.h"
#include "iidx_Keyboard_N_Mouse.h"
extern volatile HIDConReport_t report;
extern volatile uint16_t HIDCon_led;
extern volatile uint8_t ledPins[];
extern volatile uint8_t buttonPins[];
extern volatile uint16_t ledbuf;
extern volatile uint16_t buttonstate;
extern volatile int lighton;


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
  Serial.begin(9600);
  delay(1000);
  for(int i=0;i < sizeof(row_bt);i++){
    pinMode(row_bt[i],INPUT_PULLUP);
  }
  for(int i=0;i < sizeof(col_bt);i++){
    pinMode(col_bt[i],OUTPUT);
  }
  for(int i=0;i < sizeof(ledPins);i++){
    pinMode(ledPins[i],OUTPUT);
  }
  pinMode(ENC_L_A,INPUT_PULLUP);
  pinMode(ENC_L_B,INPUT_PULLUP);
  pinMode(ENC_R_A,INPUT_PULLUP);
  pinMode(ENC_R_B,INPUT_PULLUP);
  //初始选择模式的部分
  buttonstate = button_scan();
  delay(100);
  buttonstate &= button_scan();
  Serial.println(buttonstate);
  if(((buttonstate >> 0) & 1))
  { 
    EEPROM.write(0, 1);
  }
  else if(((buttonstate >> 1) & 1))
  {
    EEPROM.write(0, 2);
  }
  else if(((buttonstate >> 2) & 1))
  {
    EEPROM.write(0, 3);
  }
  else if(((buttonstate >> 3) & 1))
  {
    EEPROM.write(0, 5);
  }
  //EEPROM.write(0, 1);
  EEPROM.get(0 , mode);
  mode_select(mode);
}

void loop() {
  //主程序选择
  if(mode >= 1 && mode <= 4){
    using_Controller_style();
  }else{
    using_KeyboardMouse_style();
  }
  lights(ledbuf);

  //每周期一次的report结构内容的上传
  HIDCon.setState(&report);
}