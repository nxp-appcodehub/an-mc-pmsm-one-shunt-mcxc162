# NXP Application Code Hub
[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## AN one shunt FOC on MCXC162
This application note describes the implementation of sensorless one shunt FOC on NXP MCXC162 MCU. <!--Please refer to [AN14619](https://www.nxp.com/webapp/Download?colCode=AN14619&location=null&isHTMLorPDF=HTML) for complete instructions on how to use this software. -->   
This application note mainly introduces the principle of one shunt PMSM FOC, hardware and software implementation with NXP development kit, including a detailed peripheral setup,driver description and FreeMASTER operation guide.

#### Boards: FRDM-MCXC162
#### Categories: Motor Control
#### Peripherals: PWM, ADC
#### Toolchains: MCUXpresso IDE, VS code

## Table of Contents
1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [FreeMASTER operation](#step4)
5. [FAQs](#step5) 
6. [Support](#step6)
7. [Release Notes](#step7)

## 1. Software<a name="step1"></a>
- Download and install [MCUXpresso IDE V25.06 or later](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE).
- Down load MCUXpresso SDK SDK_26_06_00_FRDM-MCXC162 for MCUXpresso IDE.
- Download and install the latest version of [FreeMASTER](https://www.nxp.com/design/software/development-software/freemaster-run-time-debugging-tool:FREEMASTER)(3.2.2.2).
- Download the code from Git repository an-mc-pmsm-one-shunt-mcxc162<!--[an-pmsm-foc-mcxa153](https://github.com/nxp-appcodehub/an-mc-pmsm-one-shunt-mcxa153)-->.  
- MCUXpresso for Visual Studio Code: This example supports MCUXpresso for Visual Studio Code, for more information about how to use Visual Studio Code please refer [here](https://www.nxp.com/design/training/getting-started-with-mcuxpresso-for-visual-studio-code:TIP-GETTING-STARTED-WITH-MCUXPRESSO-FOR-VS-CODE).

## 2. Hardware<a name="step2"></a>
- [FRDM-MCXC162 Development Board](https://www.nxp.com/part/FRDM-MCXC162).
- [FRDM-MC-LVPMSM](https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/nxp-freedom-development-platform-for-low-voltage-3-phase-pmsm-motor-control:FRDM-MC-LVPMSM).
- [LINIX 45ZWN24 motor](https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/low-voltage-3-phase-motor-for-frdm-platform:FRDM-MC-LVMTR).
- Personal Computer
- USB type-C cable and 24V adaptor.

## 3. Setup<a name="step3"></a>
### 3.1 Import project
#### 3.1.A Import project from Application Code Hub
1. Open MCUXpresso IDE, in the Quick Start Panel, choose **Import from Application Code Hub**.  
2. Found demo you need by searching the name directly or selecting tags you interested in. Open the project, click the **GitHub link** to then **Next**.  
3. Select **main** branch and then click **Next**.  
4. Select your local path for the repo in **Destination->Directory:** window. The MCUXpresso IDE will clone the repo to the path that your selected, **Next** after the clone process.  
5. Select **Import existing Eclipse projects** in **Wizard for project import** window then **Next**.  
6. Select the project in this repo(only one project in this repo) then **Finish**.  
#### 3.1.B Import project after clone git repo to your local path
1. Clone repo **an-mc-pmsm-one-shunt-mcxc162** from **GitHub**. Open MCUXpresso IDE, in the Quick Start Panel, choose **Import project(s) from file system**.  
2. Select your local path of the repo in **Project directory(unpacked)** item then **Next**. If you download a compressed pack from GitHub, Select your local path of the package in **Project archive(zip)** item.  
3. Select the project in this repo(show in **Projects:** window, only one project in this repo), then **Finish**. . The project will be pasted to your IDE workspace if you click **Copy projects into workspace** in **Options** item, the change you made will be saved in the copy in workspace.  
#### 3.1.2 Then you will see the project in **Project Explorer** window.  
### 3.2 Compiler the project
Use build botton in toolbar to compiler the project.  

### 3.3 Hardware setup
Connect the **FRDM-MC-LVPMSM** shield to the **J1~J4** arduino connector of **FRDM-MCXC162** board. Connect the 3-phase wire of the motor to the J7 connector on FRDM-MC-LVPMSM according to phase sequence.  

For motor LINIX 45ZWN24-40:  
**White wide** --phase**A**;  
**Bule wide** --phase**B**;  
**Green wide** --phase**C**.  

<!--For motor Teknic M-2310P:  
**Black wide**--phase**A**;  
**Red wide**--phase**B**;  
**White wide**--phase**C**.  -->
Then power the FRDM-MC-LVPMSM board with a 24V adaptor.  

Use a USB cable to connect to the FRDM board via **J15** connector. Download the code using debug button in tool bar after compiler. Select **CMSIS-DAP** or **J-Link** in **Debug As** according firmware in your on-board debugger. 

### 3.4 Run the demo
Press SW2 on FRDM board to control the motor to run or stop. Or use FreeMASTER project **"pmsm_frac.pmpx"** in the code package to control the motor, change rotor speed and obverse the speed or other value. 

||Code in flash |Part code in sramx|
|:----|:----:|:----:|
|Fast loop interval|125us(8kHz)|125us(8kHz)|<!--3539/487 3111/412 -- >
|Fast loop processing time for M1 |49.2us |43.2us |
|Fast loop loading for M1|39.3% |134.6% |
|Slow loop interval|1ms(1kHz)|1ms(1kHz)|
|Slow loop processing time for M1|6.8us |5.7us |
|Slow loop loading for M1 |0.7% |0.6% |
|Total CPU loading|40.0% |35.1% |

## 4. FreeMASTER operation
The FreeMASTER can be used to completely control and easily tune the sensorless FOC application. The operation of FreeMASTER setup is introduced here. 

Open **an-mc-pmsm-one-shunt-mcxc162\motor_control\freemaster\pmsm_frac.pmpx** in project path.  
Open **Project->Options..** in FreeMASTER menu and go to **Comm** tag to configure COM number and communication speed.  

Then go to **MAP Files** tag. Select IDE generated map file **an-mc-pmsm-one-shunt-mcxc162\Debug\an-mc-pmsm-one-shunt-mcxc162.axf** or **an-mc-pmsm-one-shunt-mcxc162\Release\an-mc-pmsm-one-shunt-mcxc162.axf** in project path, generated after compiler the project. Choose **Binary ELF with DWARF2/DWARF4 dbg format.** tag in **File format:** window.  
Click **Start Communication** in menu to connect to MCU board when MCU is running.  

## 5. FAQs<a name="step5"></a>
*Include FAQs here if appropriate. If there are none, then remove this section.*

## 6. Support<a name="step6"></a>
*Provide URLs for help here.*

#### Project Metadata

<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXC162-blue)]()

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-MOTOR%20CONTROL-yellowgreen)](https://mcuxpresso.nxp.com/appcodehub?category=motor_control)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-PWM-yellow)](https://mcuxpresso.nxp.com/appcodehub?peripheral=pwm)
[![Peripheral badge](https://img.shields.io/badge/Peripheral-ADC-yellow)](https://mcuxpresso.nxp.com/appcodehub?peripheral=adc)

<!----- Toolchains ----->
[![Toolchain badge](https://img.shields.io/badge/Toolchain-MCUXPRESSO%20IDE-orange)](https://mcuxpresso.nxp.com/appcodehub?toolchain=mcux)
[![Toolchain badge](https://img.shields.io/badge/Toolchain-VS%20CODE-orange)](https://mcuxpresso.nxp.com/appcodehub?toolchain=vscode)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

>**Note**: For more general technical questions regarding NXP Microcontrollers and the difference in expected functionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/X-Follow%20us%20on%20X-black.svg)](https://x.com/NXP)

## 7. Release Notes<a name="step7"></a>
| Version | Description / Update                           | Date                        |
|:-------:|------------------------------------------------|----------------------------:|
| 1.0     | Initial release on Application Code Hub        | August 10<sup>nd</sup> 2026 |