# Arduino DIY IIDX Controller
*(Deepseek used)*  
An IIDX controller inspired by lizardbeans' work, using a design similar to the Overclock A case. Compatible with LR2, beatoraja, and official Konami games. Features include HID lighting support. Total build cost is approximately ¥300-400 (excluding some tools), varying based on component choices. Delivers excellent performance at an affordable price.

## Photos
![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/Controller.png)

## Current Features
1.  **Functional PCB:** Includes schematic, PCB layout, and Gerber files (in `PCB&BOM` folder). Manufactured via JLCPCB.
2.  **Enclosure CAD Files:** Full acrylic case + turntable. Includes an optional turntable version with coupling flange support (skip cutting if unused).
3.  **Multi-Mode Firmware:** Detailed functionality below.

## Controller Modes
Hold **START** (BTA on PCB) + **one button (1-6)** while plugging in USB to select mode. Modes are stored in EEPROM and reloaded on subsequent connections.

| Mode | Type              | Key Mapping              | Turntable Functionality                                  | Notes                          |
| :--- | :---------------- | :----------------------- | :------------------------------------------------------- | :----------------------------- |
| 1    | Analog Gamepad    | Gamepad Buttons          | Smooth analog X-axis movement based on speed/direction   |                                |
| 2    | Digital Gamepad   | Gamepad Buttons          | Instant full-left/full-right stick/button press          | **Highest Turntable Sensitivity** |
| 3    | Digital Gamepad   | Gamepad Buttons          | Instant full-left/full-right stick/button press          | Medium Sensitivity             |
| 4    | Digital Gamepad   | Gamepad Buttons          | Instant full-left/full-right stick/button press          | **Lowest Turntable Sensitivity**  |
| 5    | Keyboard + Mouse  | Keys: `Z S X D C F V`    | Mouse X-axis movement                                    | **Recommended for Official Games** |
| 6    | Keyboard + Mouse  | Keys: `Z S X D C F V`    | Mouse Scroll Wheel                                       | *Experimental (Not Recommended)* |

## PCB Guide
**Top View:**  
![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/PCB.png)

*   **Connections:** All components use 4-pin XH2.54 connectors.  
*   **Wiring Diagram:**  
    ![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/4Pin%20connection.png)
*   **Example (Button):**  
    ![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/WIREING.png)  
    *   **Connector Orientation:** Tab facing **UP**
    *   **Left 2 Pins:** Microswitch connections
    *   **Right 2 Pins:** LED connections
*   **Encoder:** Wired similarly (refer to diagram)
*   **USB:** Features reversible Type-C port (recommended to use an extension cable)

## Enclosure Design
*   **Material:** Laser-cut acrylic
*   **Frame:** 10mm thickness
*   **Panels:** Thickness specified in CAD files
*   **Assembly:** Connect top/bottom panels using **50mm M4 standoffs** inserted into screw holes
*   **Turntable Options:**
    1.  **D-shaft Mount:** Relies solely on encoder's D-shaped shaft. Provides good feel if cut accurately. *Controller cannot be inverted*
    2.  **Coupling Flange Mount:** Requires optional flange. **Potential shimming needed:** Encoder height may require adjustment (spacers/washers) to prevent turntable from floating
*   **CAD Features:** Includes anti-splinter chamfers and countersunk screw holes. Ready for laser cutting services
*   *(Photos pending future enclosure order)*

## Code Structure
*To be written later.* 💀
