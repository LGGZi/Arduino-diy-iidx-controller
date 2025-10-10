/*
  Keyboard.cpp

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "SubHID.h"

#if defined(_USING_HID)

//================================================================================
//================================================================================
//	所有输入的 Sub descriptor

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  /********** Xbox手柄描述 (Report ID 1)**********///=====================================================================
  0x05, 0x01,  // USAGE_PAGE (Generic Desktop)
  0x09, 0x05,  // USAGE (Game Pad)
  0xA1, 0x01,  // COLLECTION (Application)
  0x85, 0x01,  //   REPORT_ID (1)
  // 16个按钮
  0x05, 0x09,  //   USAGE_PAGE (Button)
  0x19, 0x01,  //   USAGE_MINIMUM (Button 1)
  0x29, 0x10,  //   Usage Maximum (Button 16)
  0x15, 0x00,  //   LOGICAL_MINIMUM (0)
  0x25, 0x01,  //   LOGICAL_MAXIMUM (1)
  0x75, 0x01,  //   REPORT_SIZE (1)
  0x95, 0x10,  //   Report Count (16)
  0x81, 0x02,  //   INPUT (Data,Var,Abs)
  // 摇杆
  0x05, 0x01,        //   USAGE_PAGE (Generic Desktop)
  0x09, 0x30,        //   USAGE (X)
  0x09, 0x31,        //   USAGE (Y)
  0x09, 0x33,        //   USAGE (Rx)
  0x09, 0x34,        //   USAGE (Ry)
  0x15, 0x81,        //   LOGICAL_MINIMUM (-127) 
  0x25, 0x7f,        //   LOGICAL_MAXIMUM (127) 
  0x75, 0x10,        //   REPORT_SIZE (16)
  0x95, 0x04,        //   REPORT_COUNT (4)
  0x81, 0x02,        //   INPUT (Data,Var,Abs)
  // 扳机
  0x05, 0x02,  //   USAGE_PAGE (Simulation Controls)
  0x09, 0xC5,  //   USAGE (Accelerator)
  0x09, 0xC4,  //   USAGE (Brake)
  0x15, 0x00,  //   LOGICAL_MINIMUM (0)
  0x25, 0xFF,  //   LOGICAL_MAXIMUM (255)
  0x75, 0x08,  //   REPORT_SIZE (8)
  0x95, 0x02,  //   REPORT_COUNT (2)
  0x81, 0x02,  //   INPUT (Data,Var,Abs)
  /********** LED控制,与手柄处于同一collection中，单独使一个collection由于未知原因行不通**********/
  0x85, 0x04,  //   REPORT_ID (4)
  0x15, 0x00,  /*     LOGICAL_MINIMUM (0) */
  0x25, 0x01,  /*     LOGICAL_MAXIMUM (1) */
  /*Led 1 */
  0x05, 0x0a, /*     USAGE_PAGE (Ordinals) */
  0x09, 0x01, /*     USAGE (Instance 1) */
  0xa1, 0x02, /*     COLLECTION (Logical) */
  0x05, 0x08, /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b, /*       USAGE (Generic Indicator 1) */
  0x75, 0x01, /*       REPORT_SIZE (1) */
  0x95, 0x01, /*       REPORT_COUNT (1) */
  0x91, 0x02, /*       OUTPUT (Data,Var,Abs) */
  0xc0,       /*     END_COLLECTION */
  /*Led 2 */
  0x05, 0x0a, /*     USAGE_PAGE (Ordinals) */
  0x09, 0x02, /*     USAGE (Instance 2) */
  0xa1, 0x02, /*     COLLECTION (Logical) */
  0x05, 0x08, /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b, /*       USAGE (Generic Indicator 1) */ 
  0x75, 0x01, /*       REPORT_SIZE (1) */
  0x95, 0x01, /*       REPORT_COUNT (1) */
  0x91, 0x02, /*       OUTPUT (Data,Var,Abs) */
  0xc0,       /*     END_COLLECTION */
  /*Led 3 */
  0x05, 0x0a, /*     USAGE_PAGE (Ordinals) */
  0x09, 0x03, /*     USAGE (Instance 3) */
  0xa1, 0x02, /*     COLLECTION (Logical) */
  0x05, 0x08, /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b, /*       USAGE (Generic Indicator 1) */
  0x75, 0x01, /*       REPORT_SIZE (1) */
  0x95, 0x01, /*       REPORT_COUNT (1) */
  0x91, 0x02, /*       OUTPUT (Data,Var,Abs) */
  0xc0,       /*     END_COLLECTION */
  /*Led 4 */
  0x05, 0x0a, /*     USAGE_PAGE (Ordinals) */
  0x09, 0x04, /*     USAGE (Instance 4) */
  0xa1, 0x02, /*     COLLECTION (Logical) */
  0x05, 0x08, /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b, /*       USAGE (Generic Indicator 1) */
  0x75, 0x01, /*       REPORT_SIZE (1) */
  0x95, 0x01, /*       REPORT_COUNT (1) */
  0x91, 0x02, /*       OUTPUT (Data,Var,Abs) */
  0xc0,       /*     END_COLLECTION */
  /*Led 5 */
  0x05, 0x0a, /*     USAGE_PAGE (Ordinals) */
  0x09, 0x05, /*     USAGE (Instance 5) */
  0xa1, 0x02, /*     COLLECTION (Logical) */
  0x05, 0x08, /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b, /*       USAGE (Generic Indicator 1) */
  0x75, 0x01, /*       REPORT_SIZE (1) */
  0x95, 0x01, /*       REPORT_COUNT (1) */
  0x91, 0x02, /*       OUTPUT (Data,Var,Abs) */
  0xc0,       /*     END_COLLECTION */
  /*Led 6 */
  0x05, 0x0a, /*     USAGE_PAGE (Ordinals) */
  0x09, 0x06, /*     USAGE (Instance 6) */
  0xa1, 0x02, /*     COLLECTION (Logical) */
  0x05, 0x08, /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b, /*       USAGE (Generic Indicator 1) */
  0x75, 0x01, /*       REPORT_SIZE (1) */
  0x95, 0x01, /*       REPORT_COUNT (1) */
  0x91, 0x02, /*       OUTPUT (Data,Var,Abs) */
  0xc0,       /*     END_COLLECTION */
  /*Led 7 */
  0x05, 0x0a, /*     USAGE_PAGE (Ordinals) */
  0x09, 0x07, /*     USAGE (Instance 7) */
  0xa1, 0x02, /*     COLLECTION (Logical) */
  0x05, 0x08, /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b, /*       USAGE (Generic Indicator 1) */
  0x75, 0x01, /*       REPORT_SIZE (1) */
  0x95, 0x01, /*       REPORT_COUNT (1) */
  0x91, 0x02, /*       OUTPUT (Data,Var,Abs) */
  0xc0,       /*     END_COLLECTION */
  /*Led 8 */
  0x05, 0x0a,       /*     USAGE_PAGE (Ordinals) */
  0x09, 0x08,       /*     USAGE (Instance 8) */
  0xa1, 0x02,      /*     COLLECTION (Logical) */
  0x05, 0x08,       /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b,       /*       USAGE (Generic Indicator 1) */
  0x75, 0x01,      /*       REPORT_SIZE (1) */
  0x95, 0x01,      /*       REPORT_COUNT (1) */
  0x91, 0x02,       /*       OUTPUT (Data,Var,Abs) */
  0xc0,             /*     END_COLLECTION */
  /*Led 9 */
  0x05, 0x0a,       /*     USAGE_PAGE (Ordinals) */
  0x09, 0x09,       /*     USAGE (Instance 9) */
  0xa1, 0x02,       /*     COLLECTION (Logical) */
  0x05, 0x08,       /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b,       /*       USAGE (Generic Indicator 1) */
  0x75, 0x01,       /*       REPORT_SIZE (1) */
  0x95, 0x01,       /*       REPORT_COUNT (1) */
  0x91, 0x02,       /*       OUTPUT (Data,Var,Abs) */
  0xc0,             /*     END_COLLECTION */
  /*Led 10 */
  0x05, 0x0a,       /*     USAGE_PAGE (Ordinals) */
  0x09, 0x0a,       /*     USAGE (Instance 10) */
  0xa1, 0x02,      /*     COLLECTION (Logical) */
  0x05, 0x08,       /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b,       /*       USAGE (Generic Indicator 1) */
  0x75, 0x01,       /*       REPORT_SIZE (1) */
  0x95, 0x01,       /*       REPORT_COUNT (1) */
  0x91, 0x02,       /*       OUTPUT (Data,Var,Abs) */
  0xc0,             /*     END_COLLECTION */
  /*Led 11 */
  0x05, 0x0a,       /*     USAGE_PAGE (Ordinals) */
  0x09, 0x0b,       /*     USAGE (Instance 11) */
  0xa1, 0x02,       /*     COLLECTION (Logical) */
  0x05, 0x08,       /*       USAGE_PAGE (LEDs) */
  0x09, 0x4b,       /*       USAGE (Generic Indicator 1) */
  0x75, 0x01,       /*       REPORT_SIZE (1) */
  0x95, 0x01,       /*       REPORT_COUNT (1) */
  0x91, 0x02,       /*       OUTPUT (Data,Var,Abs) */
  0xc0,             /*     END_COLLECTION */
  /*  Reserved 5 bits */
  0x95, 0x01,      /*   REPORT_COUNT (1) */
  0x75, 0x05,       /*   REPORT_SIZE (5) */
  0x91, 0x03,       /*   OUTPUT (Cnst,Var,Abs) */
  0xc0,                          /* END_COLLECTION */ 

  /********** 键盘描述 (Report ID 2)**********///=====================================================================
  0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
  0x09, 0x06,        // USAGE (Keyboard)
  0xA1, 0x01,        // COLLECTION (Application)
  0x85, 0x02,        // REPORT_ID (2)
  // 修饰键（8位：Ctrl/Shift/Alt等）
  0x05, 0x07,       //   Usage Page (Key Codes)
  0x19, 0xE0,       //   Usage Minimum (Keyboard LeftControl)
  0x29, 0xE7,       //   Usage Maximum (Keyboard Right GUI)
  0x15, 0x00,       //   Logical Minimum (0)
  0x25, 0x01,       //   Logical Maximum (1)
  0x75, 0x01,       //   Report Size  (1)
  0x95, 0x08,       //   Report Count (8)
  0x81, 0x02,       //   Input (Data, Variable, Absolute)
  //保留位
  0x95, 0x01,                    //   REPORT_COUNT (1)
  0x75, 0x08,                    //   REPORT_SIZE (8)
  0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
  // 普通键（14个字节）
  0x05, 0x07,       //   Usage Page (Key Codes),
  0x95, 0x70,       //   Report Count (112),
  0x75, 0x01,       //   Report Size  (1),
  0x15, 0x00,       //   Logical Minimum (0),
  0x25, 0x01,       //   Logical Maximum (1),
  0x19, 0x04,       //   USAGE_MINIMUM (Keyboard a and A)
  0x29, 0x65,       //   USAGE_MAXIMUM (Keyboard Application)
  0x81, 0x02,       //   Input (Data, Var, Abs),
  0xc0,                          /* END_COLLECTION */ 

 /********** 鼠标描述 (Report ID 3)**********///=====================================================================
  0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
  0x09, 0x02,        // USAGE (Mouse)
  0xA1, 0x01,        // COLLECTION (Application)
  0x85, 0x03,        //   REPORT_ID (3)
  // 按钮（3个按钮）
  0x05, 0x09,        //   USAGE_PAGE (Button)
  0x19, 0x01,        //   USAGE_MINIMUM (Button 1)
  0x29, 0x03,        //   USAGE_MAXIMUM (Button 3)
  0x15, 0x00,        //   LOGICAL_MINIMUM (0)
  0x25, 0x01,        //   LOGICAL_MAXIMUM (1)
  0x95, 0x03,        //   REPORT_COUNT (3)
  0x75, 0x01,        //   REPORT_SIZE (1)
  0x81, 0x02,        //   INPUT (Data,Var,Abs)
  //填充5bit，补齐一字节
  0x95, 0x01,        //   REPORT_COUNT (1)（填充5位）
  0x75, 0x05,        //   REPORT_SIZE (5)
  0x81, 0x03,        //   INPUT (Cnst,Var,Abs)
  // X/Y轴移动
  0x05, 0x01,        //   USAGE_PAGE (Generic Desktop)
  0x09, 0x30,        //   USAGE (X)
  0x09, 0x31,        //   USAGE (Y)
  0x09, 0x38,        //   WHEEL
  0x15, 0x81,        //   LOGICAL_MINIMUM (-127)
  0x25, 0x7F,        //   LOGICAL_MAXIMUM (127)
  0x75, 0x08,        //   REPORT_SIZE (8)
  0x95, 0x03,        //   REPORT_COUNT (3)
  0x81, 0x06,        //   INPUT (Data,Var,Rel)
  0xc0                          /* END_COLLECTION */ 
};

HIDCon_::HIDCon_(void) {
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

void HIDCon_::setState(HIDConReport_t *report) {

  // Xbox手柄数据 (Report ID 1)
  uint8_t xboxData[12]; // 2(按钮) + 8(摇杆) + 2(扳机) = 14字节
  memcpy(xboxData, &report->xboxButtons, 2);    // 32位按钮
  memcpy(xboxData + 2, &report->lxAxis, 8);     // 4个16位摇杆轴
  memcpy(xboxData + 10, &report->lt, 2);        // 2个8位扳机
  HID().SendReport(1, xboxData, sizeof(xboxData));

  // 键盘数据 (Report ID 2)
  uint8_t keyboardData[16] = {
    report->keyboardModifiers, // 修饰键（1字节）
    report->reserved_key,      // 保留位
    report->keyboardKeys[0],   // 普通键
    report->keyboardKeys[1],   // 普通键
    report->keyboardKeys[2],   // etc
    report->keyboardKeys[3],
    report->keyboardKeys[4],
    report->keyboardKeys[5],
    report->keyboardKeys[6],
    report->keyboardKeys[7],
    report->keyboardKeys[8],
    report->keyboardKeys[9],
    report->keyboardKeys[10],
    report->keyboardKeys[11],
    report->keyboardKeys[12],
    report->keyboardKeys[13]
  };
  HID().SendReport(2, keyboardData, sizeof(keyboardData));

  // 鼠标数据 (Report ID 3)
  uint8_t mouseData[4] = {
    report->mouseButtons, // 按钮状态（低3位有效）
    report->mouseX,        // X轴
    report->mouseY,        // Y轴
    report->wheel
  };
  HID().SendReport(3, mouseData, sizeof(mouseData));

}

HIDCon_ HIDCon;

#endif
