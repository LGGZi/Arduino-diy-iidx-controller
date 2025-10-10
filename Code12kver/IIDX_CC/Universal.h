#ifndef Universal_h
#define Universal_h
//编码器灵敏度vv
//键鼠模式灵敏度vv 值为起转脉冲数
#define TT_ACTIVE_COUNT 1
//手柄模式灵敏度vv 值为编码器脉冲数与转动一圈后上报的位置的位移数值的比值
#define ENCODER_PULSE_TIMES 600
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
#define ENC_R_A 1
#define ENC_R_B 0
//实现的按键数（作为数组脚标最大值的声名，需严格按照数组大小设置）
// #define BUTTONCOUNT 12
/*——————————全局变量声名——————————*/
volatile HIDConReport_t report;
volatile uint8_t ledPins[] = {A0,A1,A2,A3,A4,A5,8,9,10,11,12,13};
volatile uint8_t row_bt[] = {SCK,MOSI,MISO};
volatile uint8_t col_bt[] = {4,5,6,7};
volatile uint16_t ledbuf = 0;
volatile uint16_t buttonstate = 1;
volatile int lighton = 1;
volatile int32_t encL = 0;
volatile int32_t encR = 0;
volatile double encoder_sensitivity = ENCODER_PULSE_TIMES / 256;
volatile uint8_t max_bt = sizeof(col_bt)*sizeof(row_bt);
/*——————————通用函数——————————*/
void lights_test(uint16_t number){
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
  for(int i=0;i<max_bt;i++){
     if((lightDesc>>i)&1){
         digitalWrite(ledPins[i],LOW);
     } else {
         digitalWrite(ledPins[i],HIGH);
     }
  }
}
uint16_t button_scan(){
  uint16_t cur_scan_result = 0;
  for(int i=0;i< sizeof(col_bt);i++){
    digitalWrite(col_bt[i],LOW);
    switch(i){
      case 0: digitalWrite(col_bt[sizeof(col_bt)-1],HIGH); break;
      default: digitalWrite(col_bt[i-1],HIGH);  
    }
    for(int j=0;j< sizeof(row_bt);j++){
      if(digitalRead(row_bt[j])!=HIGH){
        cur_scan_result |= (uint16_t)1 << (j*4+i);
      }else{
        cur_scan_result &= ~((uint16_t)1 << (j*4+i));
      }
    }
  }
  return cur_scan_result;
}

void lightswitch(uint16_t lightswitch_bt1,uint16_t lightswitch_bt2,uint16_t lightswitch_bt3,uint16_t ori_bt_input){
  //灯光开关用，检查组合键来调整lighton的值以开关
  if(((ori_bt_input >> lightswitch_bt1) & 1)
  &&((ori_bt_input >> lightswitch_bt2) & 1)
  &&((ori_bt_input >> lightswitch_bt3) & 1))
  {
    if(lighton==1){
      lighton=0;
    }else{
      lighton=1;
    }
    while(((ori_bt_input >> lightswitch_bt1) & 1)
  &&((ori_bt_input >> lightswitch_bt2) & 1)
  &&((ori_bt_input >> lightswitch_bt3) & 1)){ori_bt_input = button_scan();delay(10);}
  }
}
#endif