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

int numSTARTENCL = 4;
int startencl = 0;



int16_t Axis_buf;

uint8_t stopFlag = 0;
uint8_t stopThreshold = 0;

void EncL(){
  //简单的将编码器脉冲顺增逆减后储存在encL里
  //Serial.print("+p");
  //startencl++;
  //if(startencl>numSTARTENCL){
  if (digitalRead(ENC_L_B) != HIGH) {
    //Serial.print("++");
    encL ++ ;
  } else {
    //Serial.print("__");
    encL -- ;
    }
}
//}

void EncL_AbsoluteOn(){
  //绝对值模式的正反转检测与按键映射
  stopFlag = 0;
  startencl++;
  if(startencl>numSTARTENCL){
    if (digitalRead(ENC_L_B) != HIGH) {
      encL = 599;
      
      report.xboxButtons &= ~((uint16_t)1 << BUTTONCOUNT);
      report.xboxButtons |= (uint16_t)1 << (BUTTONCOUNT + 1);
    } else {
      encL = 0 ;
      
      report.xboxButtons &= ~((uint16_t)1 << (BUTTONCOUNT + 1));
      report.xboxButtons |= (uint16_t)1 << BUTTONCOUNT;
    }
  }
}

void EncL_AbsoluteOff(){
  //绝对值模式的归中函数
  if(stopFlag < stopThreshold){
      stopFlag++;
    } else {
      encL = 300;
      startencl=0;
      report.xboxButtons &= ~((uint16_t)1 << BUTTONCOUNT);
      report.xboxButtons &= ~((uint16_t)1 << (BUTTONCOUNT + 1));
    }
}

void use_Controller_style(uint8_t modecode){
  switch(modecode){
    case 1:
      lights_test(modecode);
      attachInterrupt(digitalPinToInterrupt(ENC_L_A), EncL, RISING);
      numSTARTENCL=0;
    break;
    case 2:
      lights_test(modecode);
      stopThreshold = 3; 
      numSTARTENCL=1;
      attachInterrupt(digitalPinToInterrupt(ENC_L_A), EncL_AbsoluteOn, RISING);
    break;
    case 3:
      lights_test(modecode);
      stopThreshold = 5; 
      numSTARTENCL=2;
      attachInterrupt(digitalPinToInterrupt(ENC_L_A), EncL_AbsoluteOn, RISING);
    break;
    case 4:
      lights_test(modecode);
      stopThreshold = 6; 
      numSTARTENCL=5;
      attachInterrupt(digitalPinToInterrupt(ENC_L_A), EncL_AbsoluteOn, RISING);
    break;
    default: break;
  }
}

void using_Controller_style(){
   // 按钮检测相关
  //去抖原理为按下时直接执行按下指令，抬起则先检测一次将结果存入到buttonbuf中，在下一周期（1ms后）再次检测时依旧为抬起状态的确立为抬起，并执行抬起指令
  for(int i=0;i<BUTTONCOUNT;i++){
    if(digitalRead(buttonPins[i])==HIGH){
      buttonbuf |= (uint16_t)1 << i;
    }else{
      buttonbuf &= ~((uint16_t)1 << i);
    }
  }
  //延时函数在两检测部分中间，保证第一次检测得到buttonbuf（缓冲区）后一定经过1ms后才进行再检测
  delayMicroseconds(REPORT_DELAY);
  //检测按键按下状态，当有按下（电平为low|电平不为HIGH）时立刻改变report关于按键部分的值，如果有未按下部分，则对照buttonbuf做与来延时1ms再执行抬起操作
  for(int i=0;i<BUTTONCOUNT;i++){
    if(digitalRead(buttonPins[i])!=HIGH){
        report.xboxButtons |= (uint16_t)1 << i;
      } else if((digitalRead(buttonPins[i])==HIGH) && (buttonbuf << i)) {
        report.xboxButtons &= ~((uint16_t)1 << i);
      }
    }

  //模式为绝对值模式时利用此函数归中
  if(stopThreshold != 0){
    EncL_AbsoluteOff();
  }
  //Serial.println(ledbuf);
  // 将从编码器读得的转盘数据处理后传递给report数据结构的对应部分
  Axis_buf = (uint8_t)((int16_t)(encL / ENCODER_SENSITIVITY) % 256) - 128;
  report.lxAxis = Axis_buf;

  // 可开关的灯光部分
  //如果灯光处于开启状态，则将HID灯光与按键状态做或，并将结果传递给对应函数来使led发光
  if(lighton == 1) {ledbuf=report.xboxButtons|HIDCon_led;}else{ledbuf=0x00;}
}