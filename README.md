# STM32Framework_SaltyProject
一个STM32框架，电设比赛用的，完成度比较低，目前无力维护。因为sd卡损坏，之前的版本库丢失，只剩一个工作目录<br>
程序使用visualgdb编译<br>
trunk部分为stm32代码，功能比较多，所有做过的训练题等的代码都在里面，入口在user文件夹下面。理论上不少代码因为年久失修已经不能运行。<br>
程序主体结构试图构建基于消息和窗口的机制，但完成度比较低。效率差。<br>
图形绘制有一个比较完善的双缓冲/剪切绘制的功能<br>
字体部分用了外部norflash保存字库，支持多种字体简单混排。支持nandflash里面保存图片并显示。使用usb虚拟串口烧写flash<br>
架构考虑了触摸屏，但实际根本没有实现。<br>
另外os这个名字是唬人的，最初想跑rtos，但没有去写。<br>
branch有部分移植到MSP432的代码，功能为18年电子设计省赛的电流测量题<br>
PCB： https://github.com/wtywtykk/SaltySTM32_Board
