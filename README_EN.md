# Arduino-diy-iidx-controller
(README_EN.md for English)

Learn from lizardbeans' code, using a design similar to the "ChaoPin A" shell to build an IIDX controller. Works with LR2, beatoraja, and the official IIDX game, with HID lighting support. The total cost for a DIY build is around 300–400 RMB (excluding some tool expenses), varying depending on the specific components chosen. The performance is quite good—a cost-effective solution.

2025/10/10 Update:  
Added SDVX version code and CAD files. Note that the acrylic shell in the CAD files may have some strength issues.  
Added a 12-key, 2-encoder PCB and code that are compatible with both SDVX and IIDX.

2026/9/5 Update:  
Deprecated old designs; only the new PCB content is maintained now.  
For the legacy README, please refer to the file named with "_legacy".

## Photos
<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/Controller.png)<br>

## Currently Implemented
1. A fairly comprehensive PCB design, manufactured by JLCPCB. Schematics, PCB layout, and Gerber files are in the `PCB&BOM` folder.  
2. CAD files for the shell. Fully acrylic case, including the turntable. An additional turntable version with coupling connection is provided; if not needed, skip cutting that part.  
3. Multiple input mode codes, with detailed functions described in the next section.

## Controller Functions
Keys 1 to 4 are used for different modes. Hold one of these keys while plugging in the USB cable to enter the corresponding mode. The modes and their functions are as follows:  
------------------------------------------------------------------------------------  
* Mode 1: Joystick analog mode. Buttons are mapped to gamepad buttons; the turntable is mapped to the gamepad's X/Y axes. Turning the turntable smoothly moves the X/Y axis according to direction and speed.  
* Mode 2 & 3: Two different sensitivity levels of joystick absolute‑value mode. Buttons are the same as Mode 1, but the turntable maps direction to buttons and joystick extremes—essentially a full‑button mode. The difference between Mode 2 and Mode 3 is turntable sensitivity: Mode 2 = high sensitivity, Mode 3 = low sensitivity.  
* Mode 4: Keyboard/mouse mode. The seven buttons map to keyboard keys `z s x d c f v`; the turntable maps to mouse X and Y axes. Very suitable for the official IIDX game.  
------------------------------------------------------------------------------------  

Mode memory is implemented via EEPROM. If no key is pressed when plugging in (i.e., no mode selected), the controller will read the last used mode from EEPROM and enter that mode.  

Lighting can be toggled using a combo key press. The light switching function is `lightswitch()`, default set to `(11,0,3,button_buf)` — i.e., pressing buttons 1, 4, and 12 simultaneously toggles the lights.

## PCB Usage Instructions
Photo<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/Full.jpg)<br>
All components are connected via XH2.54 4‑pin connectors. Wiring diagram below:<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/BT%20connection.png)<br>
Example of a button wire as shown below: the connector's polarising tab faces upward; the left two pins connect to the microswitch, the right two pins connect to the LED. Encoder connections are similar, follow the above diagram.<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/WIREING.png)<br>
The USB section is brought out as a 4‑pin header, allowing an external USB module to be connected.<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/USB%20part.jpg)<br>
Gerber files for the USB module are in `PCB&BOM`.

## Shell Design
All‑acrylic shell. The frame plates use 10mm acrylic; the panel thickness is marked within the files. The turntable can be cut together with the shell. The CAD files include anti‑cut chamfers and counterbores for screw holes—just send the CAD files directly to a laser‑cutting service.

Use 50mm long M4 standoffs between the top and bottom plates (through the screw holes) to connect the upper/lower frames and mount the panels.

The turntable provides two versions: one using a flange coupling for fixation, and another that relies solely on the encoder's D‑shaft for联动. If cutting tolerances are not too large, the D‑shaft version can still offer good手感, though the turntable is not fixed, so the controller cannot be turned upside down. Due to the encoder shaft length and turntable base height, the flange‑coupling version may require additional spacers to lower the encoder height; otherwise, the turntable might hover.

I have also designed a simple turntable base (disc holder) that can be 3D‑printed as a replacement for the disc holder in the CAD files—available in `3D_Model`.

The acrylic shells come in two sizes (large and small). The small version is in the `small` folder. Files with "3dprint" in the name use the 3D‑printed disc holder.
