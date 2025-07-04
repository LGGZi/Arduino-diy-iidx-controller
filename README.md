# Arduino-diy-iidx-controller
(README_en.md in progress)
学着lizardbeans佬写代码，使用超频A类似的外壳设计做的IIDX手台，LR2、beatoraja、和本家都可用，功能上包含HID灯光。自己做出来的成本在300-400（去除部分工具费用的话），视选用的配件具体数值会有波动，游玩的效果很不错，算得上便宜好用。
## 实物图
<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/Controller.png)<br>
## 目前已实现
1、一个画的很随便但可用的电路板，嘉立创制作、原理图和PCB以及Gerber文件都放在PCB&BOM文件夹下了。<br>
2、外壳的CAD文件。全亚克力外壳，包括转盘，转盘额外提供了一个可连接联轴器的版本，不需要的话不用切割。<br>
3、实现了多种输入模式的代码，具体功能在下一部分详细描述。<br>
## 控制器功能
按住start键（PCB上的BTA）加1到6号按键的其中一个键并插入USB数据线即可进入不同模式，不同模式及其功能如下：<br>
------------------------------------------------------------------------------------<br>
* 模式1：手柄模拟量模式，此模式下会将按键映射为手柄的按钮，并将转盘映射为手柄x轴，转动转盘会视转动的方向和速度使手柄x轴平滑移动。<br>
* 模式2-4：三种不同灵敏度的手柄摇杆绝对值模式，按键与模式1相同，但转盘根据方向映射为按键和摇杆的最左或最右，相当于是全按键模式。2到4三个模式区别为转盘灵敏度不同，2最快，4最慢。<br>
* 模式5：键鼠模式，七个按键映射为键盘zsxdcfv，转盘映射为鼠标x轴，非常适合用于本家<br>
* 模式6：自己搞着玩的，依旧是映射为键鼠，不过转盘换成了滚轮，别用。<br>

------------------------------------------------------------------------------------<br>
通过使用EEPROM实现了模式的记忆，插入时不按组合键会从EEPROM中读取上次的模式并进入

## 电路板使用说明
实物图<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/PCB.png)<br>
所有配件通过XH2.54的4pin借口连接，连接方式如下图<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/4Pin%20connection.png)<br>
以按钮线举例如下图所示，公头防呆凸起面向上，左侧两个为连接微动的线，右侧两个为连接灯光的线，编码器的连接方式类似，根据上图连接即可<br>![](https://github.com/LGGZi/Arduino-diy-iidx-controller/blob/main/IMAGE/WIREING.png)<br>
电路板上有可正反插的Type-C接口（虽然还是建议搞个延长线连外边用，有一种type-c延长线是刚好能卡在外壳侧板的开孔里的）

## 代码结构
以后再施工，懒了💀
