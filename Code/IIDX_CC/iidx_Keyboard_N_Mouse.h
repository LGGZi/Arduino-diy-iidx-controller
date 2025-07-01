#include "Universal.h"

extern volatile HIDConReport_t report;
extern volatile uint16_t HIDCon_led;
extern volatile uint8_t ledPins[];
extern volatile uint8_t buttonPins[];
extern volatile uint8_t muiltPins[][3];
extern volatile uint16_t ledbuf;
extern volatile uint16_t buttonbuf;
extern volatile int lighton;
extern volatile int32_t encL;

int32_t pre_encL = 0;
int32_t diff_encL = 0;
int keys[]{41,34,39,19,18,21,37,42,43,44,0,1};
int key_map[BUTTONCOUNT+2][2] = {0};
int keys1[]{16,34,19,56,25,24,30,22,23,44,0,1};
// uint8_t TT_addr = 0;
unsigned long time_Now = 0;
unsigned long time_Pre[BUTTONCOUNT] = {0};
uint8_t modekeyboard;
void Encl_mouse(){
  //简单的将编码器脉冲顺增逆减后储存在encL里
  //Serial.print("+p");
  //startencl++;
  //if(startencl>numSTARTENCL){
  if (digitalRead(ENC_L_B) != HIGH) {
    //Serial.print("++");
    // TT_addr = 1;
    encL ++ ;
  } else {
    //Serial.print("__");
    // TT_addr = -1;
    encL -- ;
    }
}
//}

void keycode_find(){
  //键值转化函数，键盘报文以8位为一组，此函数将键值计算以寻找到其在report.keyboardKeys[]对应位置角标和bit位置
  for(int i=0;i<BUTTONCOUNT+2;i++){
    key_map[i][0] = keys[i] / 8;
    key_map[i][1] = keys[i] % 8;
    // delay(1000);
    // Serial.println("key_mapi");
    // Serial.println(key_map[i][0]);
    // Serial.println(key_map[i][1]);
  }
}
void keycode_find1(){
  //键值转化函数，键盘报文以8位为一组，此函数将键值计算以寻找到其在report.keyboardKeys[]对应位置角标和bit位置
  for(int i=0;i<BUTTONCOUNT+2;i++){
    key_map[i][0] = keys1[i] / 8;
    key_map[i][1] = keys1[i] % 8;
    // delay(1000);
    // Serial.println("key_mapi");
    // Serial.println(key_map[i][0]);
    // Serial.println(key_map[i][1]);
  }
}

void use_KeyboardMouse_style(uint8_t modecode){
  if(modecode == 5){
    lights_test(modecode);
    attachInterrupt(digitalPinToInterrupt(ENC_L_A), Encl_mouse, RISING);
    numSTARTENCL=0;
    keycode_find();
  }else  if(modecode == 6){
    lights_test(modecode);
    attachInterrupt(digitalPinToInterrupt(ENC_L_A), Encl_mouse, RISING);
    numSTARTENCL=0;
    keycode_find1();
  }
  modekeyboard = modecode;
}

void using_KeyboardMouse_style(){
  time_Now = millis();
  for(int i=0;i<BUTTONCOUNT;i++){
    if(digitalRead(buttonPins[i])==HIGH){
      buttonbuf &= ~((uint16_t)1 << i);
      
    }else{
      buttonbuf |= (uint16_t)1 << i;
      time_Pre[i] = millis();
    }
  }
  //检测按键按下状态，当有按下（电平为low|电平不为HIGH）时立刻改变report关于按键部分的值，如果有未按下部分，则对照time_Pre[i]检查是否抬起1ms来决定是否执行抬起操作
  for(int i=0;i<BUTTONCOUNT;i++){
    if(digitalRead(buttonPins[i])!=HIGH){
        report.keyboardKeys[key_map[i][0] - 2] |= ((uint8_t)1 << key_map[i][1]);
      } else if((digitalRead(buttonPins[i])==HIGH) && (time_Now - time_Pre[i] >= 1)) {
        report.keyboardKeys[key_map[i][0] - 2] &= ~((uint8_t)1 << key_map[i][1]);
      }
    }
  // 将从编码器读得的转盘数据处理后传递给report数据结构的对应部分
  diff_encL = encL - pre_encL;
  if(abs(diff_encL) >= TT_ACTIVE_COUNT){
    if(modekeyboard == 5)     report.mouseX = diff_encL;
    if(modekeyboard == 6)     report.wheel = -diff_encL;
    pre_encL = encL;
    diff_encL = 0;
  }else{
    if(modekeyboard == 5)     report.mouseX = 0;
    if(modekeyboard == 6)     report.wheel = 0;
  }

  //可开关的灯光部分
  //如果灯光处于开启状态，则将HID灯光与按键状态做或，并将结果传递给对应函数来使led发光
  if(lighton == 1) {ledbuf = buttonbuf | HIDCon_led;}else{ledbuf=0x00;}
}