#ifndef Universal_h
#define Universal_h
//编码器灵敏度vv
//键鼠模式灵敏度vv 值为起转脉冲数
#define TT_ACTIVE_COUNT 1
//手柄模式灵敏度vv 值为编码器脉冲数与转动一圈后上报的位置的位移数值的比值
#define ENCODER_SENSITIVITY (double) 2.34375
//The bigger the more sensitive

// encoder sensitivity = number of positions per rotation (600) / number of positions for HID report (256)
/*
 * connect encoders
 * TURNTABLE to pin 2 and 3
 */
//回报速率
#define REPORT_DELAY 1000
// Number of microseconds between HID reports
// 2000 = 500hz
//编码器AB相对应引脚
#define ENC_L_A 2
#define ENC_L_B 3
//实现的按键数（作为数组脚标最大值的声名，需严格按照数组大小设置）
#define BUTTONCOUNT 10
/*——————————全局变量声名——————————*/
volatile HIDConReport_t report;
volatile uint8_t ledPins[] = {A0,A1,A2,A3,A4,A5,1,11,12,13};
volatile uint8_t buttonPins[] = {4,5,6,7,8,9,10,MOSI,MISO,SCK};
volatile uint8_t muiltPins[][3] = {{MOSI,4,8}, {MOSI,5,8}, {MOSI,6,8}, {MOSI,7,8}, {MOSI,8,8}, {MOSI,9,8}, {SCK,MISO,MOSI}};
volatile uint16_t ledbuf = 0;
volatile uint16_t buttonbuf = 1;
volatile int lighton = 1;
volatile int32_t encL = 0;
/*——————————通用函数——————————*/
void lights_test(uint16_t number = 7){
  number = number > BUTTONCOUNT ? BUTTONCOUNT : number;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < number; j++){
        digitalWrite(ledPins[j],LOW);
    }
    delay(100);
    for(int j = 0; j < number; j++){
        digitalWrite(ledPins[j],HIGH);
    }
    delay(100);
  }
}

void lights(uint16_t lightDesc){
  //用于灯光控制的函数，根据参数lightDesc的每个二进制位的值启动ledPins[]对应的灯
  for(int i=0;i<BUTTONCOUNT;i++){
     if((lightDesc>>i)&1){
         digitalWrite(ledPins[i],LOW);
     } else {
         digitalWrite(ledPins[i],HIGH);
     }
  }
}

void lightswitch(uint8_t lightswitch_multiPins){
  //灯光开关用，检查组合键来调整lighton的值以开关
  if(digitalRead(muiltPins[lightswitch_multiPins][0]) != HIGH 
    && digitalRead(muiltPins[lightswitch_multiPins][1]) != HIGH 
    && digitalRead(muiltPins[lightswitch_multiPins][2]) != HIGH 
    && digitalRead(buttonPins[1]) != HIGH)
  {
    if(lighton==1){
      lighton=0;
    }else{
      lighton=1;
    }
    while(digitalRead(muiltPins[lightswitch_multiPins][0]) != HIGH 
    && digitalRead(muiltPins[lightswitch_multiPins][1]) != HIGH 
    && digitalRead(muiltPins[lightswitch_multiPins][2]) != HIGH 
    && digitalRead(buttonPins[1]) != HIGH){}
  }
}
#endif