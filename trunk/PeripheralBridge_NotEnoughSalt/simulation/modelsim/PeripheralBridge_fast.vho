-- Copyright (C) 2017  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Intel and sold by Intel or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 17.0.2 Build 602 07/19/2017 SJ Standard Edition"

-- DATE "05/01/2018 16:29:54"

-- 
-- Device: Altera EPM570T144C5 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY IEEE;
USE IEEE.std_logic_1164.all;

PACKAGE PeripheralBridge_data_type IS

TYPE IOPort_8_0_type IS ARRAY (8 DOWNTO 0) OF std_logic;
TYPE IOPort_8_0_0_7_type IS ARRAY (0 TO 7) OF IOPort_8_0_type;
SUBTYPE IOPort_type IS IOPort_8_0_0_7_type;

END PeripheralBridge_data_type;

LIBRARY IEEE;
LIBRARY MAXII;
LIBRARY WORK;
USE IEEE.STD_LOGIC_1164.ALL;
USE MAXII.MAXII_COMPONENTS.ALL;
USE WORK.PERIPHERALBRIDGE_DATA_TYPE.ALL;

ENTITY 	PeripheralBridge IS
    PORT (
	NE : IN std_logic;
	NOE : IN std_logic;
	NWE : IN std_logic;
	FSMCAdd : IN std_logic_vector(5 DOWNTO 0);
	FSMCData : BUFFER std_logic_vector(15 DOWNTO 0);
	IOPort : BUFFER IOPort_type;
	FPGAData : IN std_logic_vector(15 DOWNTO 0);
	FPGAClk : BUFFER std_logic;
	SysClk : IN std_logic;
	STM32Clk : BUFFER std_logic
	);
END PeripheralBridge;

-- Design Ports Information


ARCHITECTURE structure OF PeripheralBridge IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_NE : std_logic;
SIGNAL ww_NOE : std_logic;
SIGNAL ww_NWE : std_logic;
SIGNAL ww_FSMCAdd : std_logic_vector(5 DOWNTO 0);
SIGNAL ww_FSMCData : std_logic_vector(15 DOWNTO 0);
SIGNAL ww_IOPort : IOPort_type;
SIGNAL ww_FPGAData : std_logic_vector(15 DOWNTO 0);
SIGNAL ww_FPGAClk : std_logic;
SIGNAL ww_SysClk : std_logic;
SIGNAL ww_STM32Clk : std_logic;
SIGNAL \FSMCData[0]~0\ : std_logic;
SIGNAL \FSMCData[1]~1\ : std_logic;
SIGNAL \FSMCData[2]~2\ : std_logic;
SIGNAL \FSMCData[3]~3\ : std_logic;
SIGNAL \FSMCData[4]~4\ : std_logic;
SIGNAL \FSMCData[5]~5\ : std_logic;
SIGNAL \FSMCData[6]~6\ : std_logic;
SIGNAL \FSMCData[7]~7\ : std_logic;
SIGNAL \FSMCData[8]~8\ : std_logic;
SIGNAL \FSMCData[9]~9\ : std_logic;
SIGNAL \FSMCData[10]~10\ : std_logic;
SIGNAL \FSMCData[11]~11\ : std_logic;
SIGNAL \FSMCData[12]~12\ : std_logic;
SIGNAL \FSMCData[13]~13\ : std_logic;
SIGNAL \FSMCData[14]~14\ : std_logic;
SIGNAL \FSMCData[15]~15\ : std_logic;
SIGNAL \IOPort[7][0]~0\ : std_logic;
SIGNAL \IOPort[7][1]~1\ : std_logic;
SIGNAL \IOPort[7][2]~2\ : std_logic;
SIGNAL \IOPort[7][3]~3\ : std_logic;
SIGNAL \IOPort[7][4]~4\ : std_logic;
SIGNAL \IOPort[7][5]~5\ : std_logic;
SIGNAL \IOPort[7][6]~6\ : std_logic;
SIGNAL \IOPort[7][7]~7\ : std_logic;
SIGNAL \IOPort[7][8]~8\ : std_logic;
SIGNAL \IOPort[6][0]~9\ : std_logic;
SIGNAL \IOPort[6][1]~10\ : std_logic;
SIGNAL \IOPort[6][2]~11\ : std_logic;
SIGNAL \IOPort[6][3]~12\ : std_logic;
SIGNAL \IOPort[6][4]~13\ : std_logic;
SIGNAL \IOPort[6][5]~14\ : std_logic;
SIGNAL \IOPort[6][6]~15\ : std_logic;
SIGNAL \IOPort[6][7]~16\ : std_logic;
SIGNAL \IOPort[6][8]~17\ : std_logic;
SIGNAL \IOPort[5][0]~18\ : std_logic;
SIGNAL \IOPort[5][1]~19\ : std_logic;
SIGNAL \IOPort[5][2]~20\ : std_logic;
SIGNAL \IOPort[5][3]~21\ : std_logic;
SIGNAL \IOPort[5][4]~22\ : std_logic;
SIGNAL \IOPort[5][5]~23\ : std_logic;
SIGNAL \IOPort[5][6]~24\ : std_logic;
SIGNAL \IOPort[5][7]~25\ : std_logic;
SIGNAL \IOPort[5][8]~26\ : std_logic;
SIGNAL \IOPort[4][0]~27\ : std_logic;
SIGNAL \IOPort[4][1]~28\ : std_logic;
SIGNAL \IOPort[4][2]~29\ : std_logic;
SIGNAL \IOPort[4][3]~30\ : std_logic;
SIGNAL \IOPort[4][4]~31\ : std_logic;
SIGNAL \IOPort[4][5]~32\ : std_logic;
SIGNAL \IOPort[4][6]~33\ : std_logic;
SIGNAL \IOPort[4][7]~34\ : std_logic;
SIGNAL \IOPort[4][8]~35\ : std_logic;
SIGNAL \IOPort[3][0]~36\ : std_logic;
SIGNAL \IOPort[3][1]~37\ : std_logic;
SIGNAL \IOPort[3][2]~38\ : std_logic;
SIGNAL \IOPort[3][3]~39\ : std_logic;
SIGNAL \IOPort[3][4]~40\ : std_logic;
SIGNAL \IOPort[3][5]~41\ : std_logic;
SIGNAL \IOPort[3][6]~42\ : std_logic;
SIGNAL \IOPort[3][7]~43\ : std_logic;
SIGNAL \IOPort[3][8]~44\ : std_logic;
SIGNAL \IOPort[2][0]~45\ : std_logic;
SIGNAL \IOPort[2][1]~46\ : std_logic;
SIGNAL \IOPort[2][2]~47\ : std_logic;
SIGNAL \IOPort[2][3]~48\ : std_logic;
SIGNAL \IOPort[2][4]~49\ : std_logic;
SIGNAL \IOPort[2][5]~50\ : std_logic;
SIGNAL \IOPort[2][6]~51\ : std_logic;
SIGNAL \IOPort[2][7]~52\ : std_logic;
SIGNAL \IOPort[2][8]~53\ : std_logic;
SIGNAL \IOPort[1][0]~54\ : std_logic;
SIGNAL \IOPort[1][1]~55\ : std_logic;
SIGNAL \IOPort[1][2]~56\ : std_logic;
SIGNAL \IOPort[1][3]~57\ : std_logic;
SIGNAL \IOPort[1][4]~58\ : std_logic;
SIGNAL \IOPort[1][5]~59\ : std_logic;
SIGNAL \IOPort[1][6]~60\ : std_logic;
SIGNAL \IOPort[1][7]~61\ : std_logic;
SIGNAL \IOPort[1][8]~62\ : std_logic;
SIGNAL \IOPort[0][0]~63\ : std_logic;
SIGNAL \IOPort[0][1]~64\ : std_logic;
SIGNAL \IOPort[0][2]~65\ : std_logic;
SIGNAL \IOPort[0][3]~66\ : std_logic;
SIGNAL \IOPort[0][4]~67\ : std_logic;
SIGNAL \IOPort[0][5]~68\ : std_logic;
SIGNAL \IOPort[0][6]~69\ : std_logic;
SIGNAL \IOPort[0][7]~70\ : std_logic;
SIGNAL \IOPort[0][8]~71\ : std_logic;
SIGNAL \Equal8~0_combout\ : std_logic;
SIGNAL \Equal8~1_combout\ : std_logic;
SIGNAL \NOE~combout\ : std_logic;
SIGNAL \NE~combout\ : std_logic;
SIGNAL \ParPort|InternalClk~combout\ : std_logic;
SIGNAL \NWE~combout\ : std_logic;
SIGNAL \FSMCCtrl|InDataClk~combout\ : std_logic;
SIGNAL \Gen_IOController1:2:PortX|Config_Reset~0_combout\ : std_logic;
SIGNAL \Equal0~1_combout\ : std_logic;
SIGNAL \Gen_IOController1:3:PortX|Config_Reset~regout\ : std_logic;
SIGNAL \Equal9~0_combout\ : std_logic;
SIGNAL \Gen_IOController1:3:PortX|InternalReset\ : std_logic;
SIGNAL \Gen_IOController1:3:PortX|Dir[8]~4_combout\ : std_logic;
SIGNAL \FSMCCtrl|InData[0]~0\ : std_logic;
SIGNAL \GlobalReset~regout\ : std_logic;
SIGNAL \ParPort|IOClk~0_combout\ : std_logic;
SIGNAL \SysClk~combout\ : std_logic;
SIGNAL \Equal10~0_combout\ : std_logic;
SIGNAL \Equal10~1_combout\ : std_logic;
SIGNAL \Gen_IOController1:3:PortX|Mux26~1_combout\ : std_logic;
SIGNAL \Gen_IOController2:7:PortX|Config_Reset~regout\ : std_logic;
SIGNAL \Gen_IOController2:7:PortX|InternalReset~combout\ : std_logic;
SIGNAL \Equal10~2_combout\ : std_logic;
SIGNAL \Equal10~3_combout\ : std_logic;
SIGNAL \Gen_IOController2:7:PortX|Mux26~0\ : std_logic;
SIGNAL \Gen_IOController2:7:PortX|Mux26~1_combout\ : std_logic;
SIGNAL \Equal0~3_combout\ : std_logic;
SIGNAL \Gen_IOController1:1:PortX|Config_Reset~regout\ : std_logic;
SIGNAL \Gen_IOController1:1:PortX|InternalReset~combout\ : std_logic;
SIGNAL \Gen_IOController1:1:PortX|Dir[8]~4_combout\ : std_logic;
SIGNAL \Gen_IOController1:1:PortX|Mux26~0\ : std_logic;
SIGNAL \Gen_IOController1:1:PortX|Mux26~1_combout\ : std_logic;
SIGNAL \Equal0~2_combout\ : std_logic;
SIGNAL \Gen_IOController2:5:PortX|Config_Reset~regout\ : std_logic;
SIGNAL \Gen_IOController2:5:PortX|InternalReset~combout\ : std_logic;
SIGNAL \Gen_IOController2:5:PortX|Dir[8]~4_combout\ : std_logic;
SIGNAL \Gen_IOController2:5:PortX|Mux26~0\ : std_logic;
SIGNAL \Gen_IOController2:5:PortX|Mux26~1_combout\ : std_logic;
SIGNAL \OutData~14_combout\ : std_logic;
SIGNAL \Gen_IOController1:3:PortX|Mux26~0_combout\ : std_logic;
SIGNAL \Gen_IOController1:3:PortX|Mux26~2_combout\ : std_logic;
SIGNAL \OutData~15_combout\ : std_logic;
SIGNAL \Equal0~4_combout\ : std_logic;
SIGNAL \Gen_IOController1:2:PortX|Config_Reset~regout\ : std_logic;
SIGNAL \Gen_IOController1:2:PortX|InternalReset~combout\ : std_logic;
SIGNAL \Gen_IOController1:2:PortX|Dir[8]~4_combout\ : std_logic;
SIGNAL \Gen_IOController1:2:PortX|Mux26~0\ : std_logic;
SIGNAL \Gen_IOController1:2:PortX|Mux26~1_combout\ : std_logic;
SIGNAL \Equal0~5_combout\ : std_logic;
SIGNAL \Gen_IOController2:6:PortX|Config_Reset~regout\ : std_logic;
SIGNAL \Gen_IOController2:6:PortX|InternalReset~combout\ : std_logic;
SIGNAL \Gen_IOController2:6:PortX|Dir[8]~4_combout\ : std_logic;
SIGNAL \Gen_IOController2:6:PortX|Mux26~0\ : std_logic;
SIGNAL \Gen_IOController2:6:PortX|Mux26~1_combout\ : std_logic;
SIGNAL \Gen_IOController1:0:PortX|Config_Reset~regout\ : std_logic;
SIGNAL \Gen_IOController1:0:PortX|InternalReset~combout\ : std_logic;
SIGNAL \Gen_IOController1:0:PortX|Dir[8]~4_combout\ : std_logic;
SIGNAL \Gen_IOController1:0:PortX|Mux26~0\ : std_logic;
SIGNAL \Gen_IOController1:0:PortX|Mux26~1_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide~regout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ClkDiv|ClkOut~regout\ : std_logic;
SIGNAL \FSMCCtrl|InData[1]~1\ : std_logic;
SIGNAL \OutData[14]~184\ : std_logic;
SIGNAL \Port4|DedicatedPort|Config_Reset~regout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[0]~7\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[0]~7COUT1_14\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[1]~9\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[1]~9COUT1_15\ : std_logic;
SIGNAL \Port4|DedicatedPort|Convert~2_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[2]~11\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[2]~11COUT1_16\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[3]~3\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[3]~3COUT1_17\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter[3]~12_combout\ : std_logic;
SIGNAL \DedicatedFunctionUsed~regout\ : std_logic;
SIGNAL \Port4|GenericPort|Config_Reset~0_combout\ : std_logic;
SIGNAL \Port4|GenericPort|Config_Reset~regout\ : std_logic;
SIGNAL \Port4|GenericPort|InternalReset~combout\ : std_logic;
SIGNAL \Port4|GenericPort|OutputData[0]~2_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|Convert~regout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ADC_RD_CONVST~regout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ChannelAData[0]~2_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ChannelAData[0]~3_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[0]~3\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[0]~3COUT1_11\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[1]~5\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[1]~5COUT1_12\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[2]~7\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[2]~7COUT1_13\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[3]~9\ : std_logic;
SIGNAL \Port4|DedicatedPort|TransferCounter[3]~9COUT1_14\ : std_logic;
SIGNAL \Port4|DedicatedPort|Equal1~0_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|Equal1~1_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ChannelABuf[14]~18_combout\ : std_logic;
SIGNAL \Port4|GenericPort|Mux26~0\ : std_logic;
SIGNAL \Port4|GenericPort|Mux26~1_combout\ : std_logic;
SIGNAL \Port4|GenericPort|Dir[0]~2_combout\ : std_logic;
SIGNAL \Port4|GenericPort|Mux26~2\ : std_logic;
SIGNAL \Port4|GenericPort|Mux26~3_combout\ : std_logic;
SIGNAL \Port4|GenericPort|Mux26~4_combout\ : std_logic;
SIGNAL \OutData~16_combout\ : std_logic;
SIGNAL \OutData~17_combout\ : std_logic;
SIGNAL \OutData[0]~18_combout\ : std_logic;
SIGNAL \OutData[0]~19\ : std_logic;
SIGNAL \OutData[0]~20_combout\ : std_logic;
SIGNAL \OutData[0]~21\ : std_logic;
SIGNAL \FSMCCtrl|OutDataClk~combout\ : std_logic;
SIGNAL \Gen_IOController2:5:PortX|Mux25~0\ : std_logic;
SIGNAL \Gen_IOController1:1:PortX|Mux25~0\ : std_logic;
SIGNAL \OutData~23_combout\ : std_logic;
SIGNAL \Gen_IOController2:7:PortX|Mux25~0\ : std_logic;
SIGNAL \Gen_IOController1:3:PortX|Mux25~0_combout\ : std_logic;
SIGNAL \OutData~24_combout\ : std_logic;
SIGNAL \Gen_IOController2:6:PortX|Mux25~0\ : std_logic;
SIGNAL \Gen_IOController1:0:PortX|Mux25~0\ : std_logic;
SIGNAL \Port4|GenericPort|Mux25~0\ : std_logic;
SIGNAL \Port4|GenericPort|Mux25~1\ : std_logic;
SIGNAL \Port4|GenericPort|Mux25~2\ : std_logic;
SIGNAL \OutData~25_combout\ : std_logic;
SIGNAL \Gen_IOController1:2:PortX|Mux25~0\ : std_logic;
SIGNAL \OutData~26_combout\ : std_logic;
SIGNAL \OutData[1]~27_combout\ : std_logic;
SIGNAL \OutData[1]~22\ : std_logic;
SIGNAL \OutData[1]~28_combout\ : std_logic;
SIGNAL \OutData[1]~29\ : std_logic;
SIGNAL \OutData[8]~31_combout\ : std_logic;
SIGNAL \FSMCCtrl|InData[2]~2\ : std_logic;
SIGNAL \OutData[2]~35\ : std_logic;
SIGNAL \OutData[2]~36_combout\ : std_logic;
SIGNAL \OutData[2]~37_combout\ : std_logic;
SIGNAL \OutData[2]~38\ : std_logic;
SIGNAL \OutData[2]~30_combout\ : std_logic;
SIGNAL \OutData[2]~32_combout\ : std_logic;
SIGNAL \OutData[2]~33_combout\ : std_logic;
SIGNAL \OutData[2]~34\ : std_logic;
SIGNAL \OutData[8]~39_combout\ : std_logic;
SIGNAL \OutData[2]~42\ : std_logic;
SIGNAL \OutData[2]~43_combout\ : std_logic;
SIGNAL \OutData[2]~44_combout\ : std_logic;
SIGNAL \OutData[2]~45\ : std_logic;
SIGNAL \Equal0~0_combout\ : std_logic;
SIGNAL \OutData[8]~50_combout\ : std_logic;
SIGNAL \OutData[8]~47_combout\ : std_logic;
SIGNAL \OutData[8]~46_combout\ : std_logic;
SIGNAL \OutData[2]~48\ : std_logic;
SIGNAL \OutData[2]~49\ : std_logic;
SIGNAL \OutData[2]~236_combout\ : std_logic;
SIGNAL \OutData[2]~237_combout\ : std_logic;
SIGNAL \OutData[2]~51_combout\ : std_logic;
SIGNAL \OutData[8]~41_combout\ : std_logic;
SIGNAL \OutData[2]~40_combout\ : std_logic;
SIGNAL \OutData[2]~52\ : std_logic;
SIGNAL \OutData[2]~217_combout\ : std_logic;
SIGNAL \OutData[8]~53_combout\ : std_logic;
SIGNAL \OutData[2]~54\ : std_logic;
SIGNAL \OutData[2]~55_combout\ : std_logic;
SIGNAL \OutData[2]~56\ : std_logic;
SIGNAL \FSMCCtrl|InData[3]~3\ : std_logic;
SIGNAL \OutData[3]~58_combout\ : std_logic;
SIGNAL \OutData[3]~59_combout\ : std_logic;
SIGNAL \OutData[3]~57_combout\ : std_logic;
SIGNAL \OutData[3]~60\ : std_logic;
SIGNAL \OutData[3]~61\ : std_logic;
SIGNAL \OutData[3]~62_combout\ : std_logic;
SIGNAL \OutData[3]~63_combout\ : std_logic;
SIGNAL \OutData[3]~64\ : std_logic;
SIGNAL \OutData[3]~65_combout\ : std_logic;
SIGNAL \OutData[3]~66\ : std_logic;
SIGNAL \OutData[3]~67_combout\ : std_logic;
SIGNAL \OutData[3]~68_combout\ : std_logic;
SIGNAL \OutData[3]~69\ : std_logic;
SIGNAL \OutData[3]~70\ : std_logic;
SIGNAL \OutData[3]~71\ : std_logic;
SIGNAL \OutData[3]~234_combout\ : std_logic;
SIGNAL \OutData[3]~235_combout\ : std_logic;
SIGNAL \OutData[3]~72_combout\ : std_logic;
SIGNAL \OutData[3]~73\ : std_logic;
SIGNAL \OutData[3]~218_combout\ : std_logic;
SIGNAL \OutData[3]~74\ : std_logic;
SIGNAL \OutData[3]~75_combout\ : std_logic;
SIGNAL \OutData[3]~76\ : std_logic;
SIGNAL \OutData[4]~77_combout\ : std_logic;
SIGNAL \FSMCCtrl|InData[4]~4\ : std_logic;
SIGNAL \OutData[4]~78_combout\ : std_logic;
SIGNAL \OutData[4]~79_combout\ : std_logic;
SIGNAL \OutData[4]~80\ : std_logic;
SIGNAL \OutData[4]~81\ : std_logic;
SIGNAL \OutData[4]~82_combout\ : std_logic;
SIGNAL \OutData[4]~83_combout\ : std_logic;
SIGNAL \OutData[4]~84\ : std_logic;
SIGNAL \OutData[4]~90\ : std_logic;
SIGNAL \OutData[4]~91\ : std_logic;
SIGNAL \OutData[4]~232_combout\ : std_logic;
SIGNAL \OutData[4]~233_combout\ : std_logic;
SIGNAL \OutData[4]~86\ : std_logic;
SIGNAL \OutData[4]~87_combout\ : std_logic;
SIGNAL \OutData[4]~88_combout\ : std_logic;
SIGNAL \OutData[4]~89\ : std_logic;
SIGNAL \OutData[4]~92_combout\ : std_logic;
SIGNAL \OutData[4]~85_combout\ : std_logic;
SIGNAL \OutData[4]~93\ : std_logic;
SIGNAL \OutData[4]~219_combout\ : std_logic;
SIGNAL \OutData[4]~94\ : std_logic;
SIGNAL \OutData[4]~95_combout\ : std_logic;
SIGNAL \OutData[4]~96\ : std_logic;
SIGNAL \OutData[5]~98_combout\ : std_logic;
SIGNAL \OutData[5]~99_combout\ : std_logic;
SIGNAL \OutData[5]~97_combout\ : std_logic;
SIGNAL \FSMCCtrl|InData[5]~5\ : std_logic;
SIGNAL \OutData[5]~100\ : std_logic;
SIGNAL \OutData[5]~105_combout\ : std_logic;
SIGNAL \OutData[5]~110\ : std_logic;
SIGNAL \OutData[5]~111\ : std_logic;
SIGNAL \OutData[5]~230_combout\ : std_logic;
SIGNAL \OutData[5]~231_combout\ : std_logic;
SIGNAL \OutData[5]~106\ : std_logic;
SIGNAL \OutData[5]~107_combout\ : std_logic;
SIGNAL \OutData[5]~108_combout\ : std_logic;
SIGNAL \OutData[5]~109\ : std_logic;
SIGNAL \OutData[5]~112_combout\ : std_logic;
SIGNAL \OutData[5]~113\ : std_logic;
SIGNAL \OutData[5]~220_combout\ : std_logic;
SIGNAL \OutData[5]~114\ : std_logic;
SIGNAL \OutData[5]~101\ : std_logic;
SIGNAL \OutData[5]~102_combout\ : std_logic;
SIGNAL \OutData[5]~103_combout\ : std_logic;
SIGNAL \OutData[5]~104\ : std_logic;
SIGNAL \OutData[5]~115_combout\ : std_logic;
SIGNAL \OutData[5]~116\ : std_logic;
SIGNAL \FSMCCtrl|InData[6]~6\ : std_logic;
SIGNAL \OutData[6]~121\ : std_logic;
SIGNAL \OutData[6]~122_combout\ : std_logic;
SIGNAL \OutData[6]~123_combout\ : std_logic;
SIGNAL \OutData[6]~124\ : std_logic;
SIGNAL \OutData[6]~130\ : std_logic;
SIGNAL \OutData[6]~131\ : std_logic;
SIGNAL \OutData[6]~228_combout\ : std_logic;
SIGNAL \OutData[6]~229_combout\ : std_logic;
SIGNAL \OutData[6]~126\ : std_logic;
SIGNAL \OutData[6]~127_combout\ : std_logic;
SIGNAL \OutData[6]~128_combout\ : std_logic;
SIGNAL \OutData[6]~129\ : std_logic;
SIGNAL \OutData[6]~132_combout\ : std_logic;
SIGNAL \OutData[6]~125_combout\ : std_logic;
SIGNAL \OutData[6]~133\ : std_logic;
SIGNAL \OutData[6]~221_combout\ : std_logic;
SIGNAL \OutData[6]~134\ : std_logic;
SIGNAL \OutData[6]~117_combout\ : std_logic;
SIGNAL \OutData[6]~118_combout\ : std_logic;
SIGNAL \OutData[6]~119_combout\ : std_logic;
SIGNAL \OutData[6]~120\ : std_logic;
SIGNAL \OutData[6]~135_combout\ : std_logic;
SIGNAL \OutData[6]~136\ : std_logic;
SIGNAL \OutData[7]~138_combout\ : std_logic;
SIGNAL \OutData[7]~139_combout\ : std_logic;
SIGNAL \FSMCCtrl|InData[7]~7\ : std_logic;
SIGNAL \OutData[7]~137_combout\ : std_logic;
SIGNAL \OutData[7]~140\ : std_logic;
SIGNAL \OutData[7]~141\ : std_logic;
SIGNAL \OutData[7]~142_combout\ : std_logic;
SIGNAL \OutData[7]~143_combout\ : std_logic;
SIGNAL \OutData[7]~144\ : std_logic;
SIGNAL \OutData[7]~145_combout\ : std_logic;
SIGNAL \OutData[7]~150\ : std_logic;
SIGNAL \OutData[7]~151\ : std_logic;
SIGNAL \OutData[7]~226_combout\ : std_logic;
SIGNAL \OutData[7]~227_combout\ : std_logic;
SIGNAL \OutData[7]~146\ : std_logic;
SIGNAL \OutData[7]~147_combout\ : std_logic;
SIGNAL \OutData[7]~148_combout\ : std_logic;
SIGNAL \OutData[7]~149\ : std_logic;
SIGNAL \OutData[7]~152_combout\ : std_logic;
SIGNAL \OutData[7]~153\ : std_logic;
SIGNAL \OutData[7]~222_combout\ : std_logic;
SIGNAL \OutData[7]~154\ : std_logic;
SIGNAL \OutData[7]~155_combout\ : std_logic;
SIGNAL \OutData[7]~156\ : std_logic;
SIGNAL \FSMCCtrl|InData[8]~8\ : std_logic;
SIGNAL \OutData[8]~170\ : std_logic;
SIGNAL \OutData[8]~171\ : std_logic;
SIGNAL \OutData[8]~224_combout\ : std_logic;
SIGNAL \OutData[8]~225_combout\ : std_logic;
SIGNAL \OutData[8]~166\ : std_logic;
SIGNAL \OutData[8]~167_combout\ : std_logic;
SIGNAL \OutData[8]~168_combout\ : std_logic;
SIGNAL \OutData[8]~169\ : std_logic;
SIGNAL \OutData[8]~172_combout\ : std_logic;
SIGNAL \OutData[8]~165_combout\ : std_logic;
SIGNAL \OutData[8]~173\ : std_logic;
SIGNAL \OutData[8]~223_combout\ : std_logic;
SIGNAL \OutData[8]~174\ : std_logic;
SIGNAL \OutData[8]~161\ : std_logic;
SIGNAL \OutData[8]~162_combout\ : std_logic;
SIGNAL \OutData[8]~163_combout\ : std_logic;
SIGNAL \OutData[8]~164\ : std_logic;
SIGNAL \OutData[8]~158_combout\ : std_logic;
SIGNAL \OutData[8]~159_combout\ : std_logic;
SIGNAL \OutData[8]~157_combout\ : std_logic;
SIGNAL \OutData[8]~160\ : std_logic;
SIGNAL \OutData[8]~175_combout\ : std_logic;
SIGNAL \OutData[8]~176\ : std_logic;
SIGNAL \OutData[9]~180\ : std_logic;
SIGNAL \OutData[14]~178_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|InternalReset~combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|SendData[15]~2_combout\ : std_logic;
SIGNAL \FSMCCtrl|InData[9]~9\ : std_logic;
SIGNAL \OutData[14]~181_combout\ : std_logic;
SIGNAL \OutData[9]~182\ : std_logic;
SIGNAL \OutData[9]~177\ : std_logic;
SIGNAL \OutData[14]~179_combout\ : std_logic;
SIGNAL \OutData[9]~183\ : std_logic;
SIGNAL \OutData[9]~185_combout\ : std_logic;
SIGNAL \OutData[10]~186\ : std_logic;
SIGNAL \FSMCCtrl|InData[10]~10\ : std_logic;
SIGNAL \OutData[10]~187\ : std_logic;
SIGNAL \OutData[10]~188\ : std_logic;
SIGNAL \OutData[10]~189\ : std_logic;
SIGNAL \OutData[10]~190_combout\ : std_logic;
SIGNAL \OutData[11]~191\ : std_logic;
SIGNAL \FSMCCtrl|InData[11]~11\ : std_logic;
SIGNAL \OutData[11]~192\ : std_logic;
SIGNAL \OutData[11]~193\ : std_logic;
SIGNAL \OutData[11]~194\ : std_logic;
SIGNAL \OutData[11]~195_combout\ : std_logic;
SIGNAL \OutData[12]~197\ : std_logic;
SIGNAL \FSMCCtrl|InData[12]~12\ : std_logic;
SIGNAL \OutData[12]~198\ : std_logic;
SIGNAL \OutData[12]~196\ : std_logic;
SIGNAL \OutData[12]~199\ : std_logic;
SIGNAL \OutData[12]~200_combout\ : std_logic;
SIGNAL \OutData[13]~202\ : std_logic;
SIGNAL \FSMCCtrl|InData[13]~13\ : std_logic;
SIGNAL \OutData[13]~203\ : std_logic;
SIGNAL \OutData[13]~201\ : std_logic;
SIGNAL \OutData[13]~204\ : std_logic;
SIGNAL \OutData[13]~205_combout\ : std_logic;
SIGNAL \OutData[14]~207\ : std_logic;
SIGNAL \FSMCCtrl|InData[14]~14\ : std_logic;
SIGNAL \OutData[14]~208\ : std_logic;
SIGNAL \OutData[14]~206\ : std_logic;
SIGNAL \OutData[14]~209\ : std_logic;
SIGNAL \OutData[14]~210_combout\ : std_logic;
SIGNAL \OutData[15]~211\ : std_logic;
SIGNAL \OutData[15]~212\ : std_logic;
SIGNAL \FSMCCtrl|InData[15]~15\ : std_logic;
SIGNAL \OutData[15]~213\ : std_logic;
SIGNAL \OutData[15]~214\ : std_logic;
SIGNAL \OutData[15]~215_combout\ : std_logic;
SIGNAL \OutData[8]~216_combout\ : std_logic;
SIGNAL \Gen_IOController1:0:PortX|OutputData[0]~0_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[0]~9\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[0]~10_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ADC_SDI~regout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[1]~11_combout\ : std_logic;
SIGNAL \Port4|GenericPort|Mux25~3_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[2]~12_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[2]~13\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[3]~14_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[3]~15\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[4]~16_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[4]~17\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[5]~18_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[5]~19\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[6]~20_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[6]~21\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[7]~22_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[7]~23\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[8]~24_combout\ : std_logic;
SIGNAL \Port4|GenericPort|IOPort[8]~25\ : std_logic;
SIGNAL \Port4|DedicatedPort|ConvertCounter\ : std_logic_vector(4 DOWNTO 0);
SIGNAL STM32ClkDiv1 : std_logic_vector(1 DOWNTO 0);
SIGNAL \Gen_IOController1:3:PortX|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController1:1:PortX|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|SendBuf\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \Gen_IOController2:7:PortX|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \FSMCAdd~combout\ : std_logic_vector(5 DOWNTO 0);
SIGNAL \Gen_IOController2:5:PortX|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController2:7:PortX|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|ChannelBData\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \Gen_IOController1:2:PortX|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController1:0:PortX|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|ChannelAData\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \Gen_IOController2:5:PortX|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Port4|GenericPort|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController2:6:PortX|Dir\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \ParPort|BufData\ : std_logic_vector(15 DOWNTO 0);
SIGNAL CommTestVar : std_logic_vector(15 DOWNTO 0);
SIGNAL \Gen_IOController2:6:PortX|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Port4|GenericPort|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController1:3:PortX|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController1:2:PortX|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController1:1:PortX|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \Gen_IOController1:0:PortX|OutputData\ : std_logic_vector(8 DOWNTO 0);
SIGNAL \FPGAData~combout\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|ChannelABuf\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|TransferCounter\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|ChannelBBuf\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|SendData\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|ClkDiv|Counter\ : std_logic_vector(2 DOWNTO 0);
SIGNAL \Port4|DedicatedPort|ALT_INV_ChannelAData[0]~3_combout\ : std_logic;
SIGNAL \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\ : std_logic;
SIGNAL \ALT_INV_SysClk~combout\ : std_logic;

BEGIN

ww_NE <= NE;
ww_NOE <= NOE;
ww_NWE <= NWE;
ww_FSMCAdd <= FSMCAdd;
FSMCData <= ww_FSMCData;
IOPort <= ww_IOPort;
ww_FPGAData <= FPGAData;
FPGAClk <= ww_FPGAClk;
ww_SysClk <= SysClk;
STM32Clk <= ww_STM32Clk;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\Port4|DedicatedPort|ALT_INV_ChannelAData[0]~3_combout\ <= NOT \Port4|DedicatedPort|ChannelAData[0]~3_combout\;
\Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\ <= NOT \Port4|DedicatedPort|ClkDiv|ClkOut~regout\;
\ALT_INV_SysClk~combout\ <= NOT \SysClk~combout\;

-- Location: PIN_107,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[0]~21\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(0),
	combout => \FSMCData[0]~0\);

-- Location: PIN_108,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[1]~29\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(1),
	combout => \FSMCData[1]~1\);

-- Location: PIN_109,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[2]~56\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(2),
	combout => \FSMCData[2]~2\);

-- Location: PIN_110,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[3]~76\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(3),
	combout => \FSMCData[3]~3\);

-- Location: PIN_106,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[4]~96\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(4),
	combout => \FSMCData[4]~4\);

-- Location: PIN_105,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[5]~116\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(5),
	combout => \FSMCData[5]~5\);

-- Location: PIN_104,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[6]~136\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(6),
	combout => \FSMCData[6]~6\);

-- Location: PIN_103,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[7]~156\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(7),
	combout => \FSMCData[7]~7\);

-- Location: PIN_102,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[8]~176\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(8),
	combout => \FSMCData[8]~8\);

-- Location: PIN_101,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[9]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[9]~185_combout\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(9),
	combout => \FSMCData[9]~9\);

-- Location: PIN_98,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[10]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[10]~190_combout\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(10),
	combout => \FSMCData[10]~10\);

-- Location: PIN_97,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[11]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[11]~195_combout\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(11),
	combout => \FSMCData[11]~11\);

-- Location: PIN_96,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[12]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[12]~200_combout\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(12),
	combout => \FSMCData[12]~12\);

-- Location: PIN_95,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[13]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[13]~205_combout\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(13),
	combout => \FSMCData[13]~13\);

-- Location: PIN_94,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[14]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[14]~210_combout\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(14),
	combout => \FSMCData[14]~14\);

-- Location: PIN_93,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FSMCData[15]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \OutData[15]~215_combout\,
	oe => \FSMCCtrl|OutDataClk~combout\,
	padio => ww_FSMCData(15),
	combout => \FSMCData[15]~15\);

-- Location: PIN_44,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(0),
	oe => \Gen_IOController2:7:PortX|Dir\(0),
	padio => ww_IOPort(7)(0),
	combout => \IOPort[7][0]~0\);

-- Location: PIN_43,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(1),
	oe => \Gen_IOController2:7:PortX|Dir\(1),
	padio => ww_IOPort(7)(1),
	combout => \IOPort[7][1]~1\);

-- Location: PIN_42,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(2),
	oe => \Gen_IOController2:7:PortX|Dir\(2),
	padio => ww_IOPort(7)(2),
	combout => \IOPort[7][2]~2\);

-- Location: PIN_41,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(3),
	oe => \Gen_IOController2:7:PortX|Dir\(3),
	padio => ww_IOPort(7)(3),
	combout => \IOPort[7][3]~3\);

-- Location: PIN_40,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(4),
	oe => \Gen_IOController2:7:PortX|Dir\(4),
	padio => ww_IOPort(7)(4),
	combout => \IOPort[7][4]~4\);

-- Location: PIN_39,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(5),
	oe => \Gen_IOController2:7:PortX|Dir\(5),
	padio => ww_IOPort(7)(5),
	combout => \IOPort[7][5]~5\);

-- Location: PIN_38,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(6),
	oe => \Gen_IOController2:7:PortX|Dir\(6),
	padio => ww_IOPort(7)(6),
	combout => \IOPort[7][6]~6\);

-- Location: PIN_37,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(7),
	oe => \Gen_IOController2:7:PortX|Dir\(7),
	padio => ww_IOPort(7)(7),
	combout => \IOPort[7][7]~7\);

-- Location: PIN_32,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[7][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:7:PortX|OutputData\(8),
	oe => \Gen_IOController2:7:PortX|Dir\(8),
	padio => ww_IOPort(7)(8),
	combout => \IOPort[7][8]~8\);

-- Location: PIN_68,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(0),
	oe => \Gen_IOController2:6:PortX|Dir\(0),
	padio => ww_IOPort(6)(0),
	combout => \IOPort[6][0]~9\);

-- Location: PIN_67,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(1),
	oe => \Gen_IOController2:6:PortX|Dir\(1),
	padio => ww_IOPort(6)(1),
	combout => \IOPort[6][1]~10\);

-- Location: PIN_66,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(2),
	oe => \Gen_IOController2:6:PortX|Dir\(2),
	padio => ww_IOPort(6)(2),
	combout => \IOPort[6][2]~11\);

-- Location: PIN_63,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(3),
	oe => \Gen_IOController2:6:PortX|Dir\(3),
	padio => ww_IOPort(6)(3),
	combout => \IOPort[6][3]~12\);

-- Location: PIN_62,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(4),
	oe => \Gen_IOController2:6:PortX|Dir\(4),
	padio => ww_IOPort(6)(4),
	combout => \IOPort[6][4]~13\);

-- Location: PIN_61,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(5),
	oe => \Gen_IOController2:6:PortX|Dir\(5),
	padio => ww_IOPort(6)(5),
	combout => \IOPort[6][5]~14\);

-- Location: PIN_60,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(6),
	oe => \Gen_IOController2:6:PortX|Dir\(6),
	padio => ww_IOPort(6)(6),
	combout => \IOPort[6][6]~15\);

-- Location: PIN_59,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(7),
	oe => \Gen_IOController2:6:PortX|Dir\(7),
	padio => ww_IOPort(6)(7),
	combout => \IOPort[6][7]~16\);

-- Location: PIN_58,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[6][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:6:PortX|OutputData\(8),
	oe => \Gen_IOController2:6:PortX|Dir\(8),
	padio => ww_IOPort(6)(8),
	combout => \IOPort[6][8]~17\);

-- Location: PIN_77,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(0),
	oe => \Gen_IOController2:5:PortX|Dir\(0),
	padio => ww_IOPort(5)(0),
	combout => \IOPort[5][0]~18\);

-- Location: PIN_76,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(1),
	oe => \Gen_IOController2:5:PortX|Dir\(1),
	padio => ww_IOPort(5)(1),
	combout => \IOPort[5][1]~19\);

-- Location: PIN_75,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(2),
	oe => \Gen_IOController2:5:PortX|Dir\(2),
	padio => ww_IOPort(5)(2),
	combout => \IOPort[5][2]~20\);

-- Location: PIN_74,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(3),
	oe => \Gen_IOController2:5:PortX|Dir\(3),
	padio => ww_IOPort(5)(3),
	combout => \IOPort[5][3]~21\);

-- Location: PIN_73,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(4),
	oe => \Gen_IOController2:5:PortX|Dir\(4),
	padio => ww_IOPort(5)(4),
	combout => \IOPort[5][4]~22\);

-- Location: PIN_72,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(5),
	oe => \Gen_IOController2:5:PortX|Dir\(5),
	padio => ww_IOPort(5)(5),
	combout => \IOPort[5][5]~23\);

-- Location: PIN_71,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(6),
	oe => \Gen_IOController2:5:PortX|Dir\(6),
	padio => ww_IOPort(5)(6),
	combout => \IOPort[5][6]~24\);

-- Location: PIN_70,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(7),
	oe => \Gen_IOController2:5:PortX|Dir\(7),
	padio => ww_IOPort(5)(7),
	combout => \IOPort[5][7]~25\);

-- Location: PIN_69,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[5][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController2:5:PortX|OutputData\(8),
	oe => \Gen_IOController2:5:PortX|Dir\(8),
	padio => ww_IOPort(5)(8),
	combout => \IOPort[5][8]~26\);

-- Location: PIN_31,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[0]~9\,
	oe => \Port4|GenericPort|IOPort[0]~10_combout\,
	padio => ww_IOPort(4)(0),
	combout => \IOPort[4][0]~27\);

-- Location: PIN_30,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[1]~11_combout\,
	oe => \Port4|GenericPort|Mux25~3_combout\,
	padio => ww_IOPort(4)(1),
	combout => \IOPort[4][1]~28\);

-- Location: PIN_29,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[2]~12_combout\,
	oe => \Port4|GenericPort|IOPort[2]~13\,
	padio => ww_IOPort(4)(2),
	combout => \IOPort[4][2]~29\);

-- Location: PIN_28,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[3]~14_combout\,
	oe => \Port4|GenericPort|IOPort[3]~15\,
	padio => ww_IOPort(4)(3),
	combout => \IOPort[4][3]~30\);

-- Location: PIN_27,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[4]~16_combout\,
	oe => \Port4|GenericPort|IOPort[4]~17\,
	padio => ww_IOPort(4)(4),
	combout => \IOPort[4][4]~31\);

-- Location: PIN_24,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[5]~18_combout\,
	oe => \Port4|GenericPort|IOPort[5]~19\,
	padio => ww_IOPort(4)(5),
	combout => \IOPort[4][5]~32\);

-- Location: PIN_23,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[6]~20_combout\,
	oe => \Port4|GenericPort|IOPort[6]~21\,
	padio => ww_IOPort(4)(6),
	combout => \IOPort[4][6]~33\);

-- Location: PIN_22,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[7]~22_combout\,
	oe => \Port4|GenericPort|IOPort[7]~23\,
	padio => ww_IOPort(4)(7),
	combout => \IOPort[4][7]~34\);

-- Location: PIN_21,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[4][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Port4|GenericPort|IOPort[8]~24_combout\,
	oe => \Port4|GenericPort|IOPort[8]~25\,
	padio => ww_IOPort(4)(8),
	combout => \IOPort[4][8]~35\);

-- Location: PIN_130,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(0),
	oe => \Gen_IOController1:3:PortX|Dir\(0),
	padio => ww_IOPort(3)(0),
	combout => \IOPort[3][0]~36\);

-- Location: PIN_131,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(1),
	oe => \Gen_IOController1:3:PortX|Dir\(1),
	padio => ww_IOPort(3)(1),
	combout => \IOPort[3][1]~37\);

-- Location: PIN_132,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(2),
	oe => \Gen_IOController1:3:PortX|Dir\(2),
	padio => ww_IOPort(3)(2),
	combout => \IOPort[3][2]~38\);

-- Location: PIN_133,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(3),
	oe => \Gen_IOController1:3:PortX|Dir\(3),
	padio => ww_IOPort(3)(3),
	combout => \IOPort[3][3]~39\);

-- Location: PIN_134,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(4),
	oe => \Gen_IOController1:3:PortX|Dir\(4),
	padio => ww_IOPort(3)(4),
	combout => \IOPort[3][4]~40\);

-- Location: PIN_137,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(5),
	oe => \Gen_IOController1:3:PortX|Dir\(5),
	padio => ww_IOPort(3)(5),
	combout => \IOPort[3][5]~41\);

-- Location: PIN_138,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(6),
	oe => \Gen_IOController1:3:PortX|Dir\(6),
	padio => ww_IOPort(3)(6),
	combout => \IOPort[3][6]~42\);

-- Location: PIN_139,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(7),
	oe => \Gen_IOController1:3:PortX|Dir\(7),
	padio => ww_IOPort(3)(7),
	combout => \IOPort[3][7]~43\);

-- Location: PIN_140,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[3][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:3:PortX|OutputData\(8),
	oe => \Gen_IOController1:3:PortX|Dir\(8),
	padio => ww_IOPort(3)(8),
	combout => \IOPort[3][8]~44\);

-- Location: PIN_57,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(0),
	oe => \Gen_IOController1:2:PortX|Dir\(0),
	padio => ww_IOPort(2)(0),
	combout => \IOPort[2][0]~45\);

-- Location: PIN_55,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(1),
	oe => \Gen_IOController1:2:PortX|Dir\(1),
	padio => ww_IOPort(2)(1),
	combout => \IOPort[2][1]~46\);

-- Location: PIN_53,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(2),
	oe => \Gen_IOController1:2:PortX|Dir\(2),
	padio => ww_IOPort(2)(2),
	combout => \IOPort[2][2]~47\);

-- Location: PIN_52,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(3),
	oe => \Gen_IOController1:2:PortX|Dir\(3),
	padio => ww_IOPort(2)(3),
	combout => \IOPort[2][3]~48\);

-- Location: PIN_51,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(4),
	oe => \Gen_IOController1:2:PortX|Dir\(4),
	padio => ww_IOPort(2)(4),
	combout => \IOPort[2][4]~49\);

-- Location: PIN_50,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(5),
	oe => \Gen_IOController1:2:PortX|Dir\(5),
	padio => ww_IOPort(2)(5),
	combout => \IOPort[2][5]~50\);

-- Location: PIN_49,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(6),
	oe => \Gen_IOController1:2:PortX|Dir\(6),
	padio => ww_IOPort(2)(6),
	combout => \IOPort[2][6]~51\);

-- Location: PIN_48,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(7),
	oe => \Gen_IOController1:2:PortX|Dir\(7),
	padio => ww_IOPort(2)(7),
	combout => \IOPort[2][7]~52\);

-- Location: PIN_45,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[2][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:2:PortX|OutputData\(8),
	oe => \Gen_IOController1:2:PortX|Dir\(8),
	padio => ww_IOPort(2)(8),
	combout => \IOPort[2][8]~53\);

-- Location: PIN_119,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(0),
	oe => \Gen_IOController1:1:PortX|Dir\(0),
	padio => ww_IOPort(1)(0),
	combout => \IOPort[1][0]~54\);

-- Location: PIN_120,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(1),
	oe => \Gen_IOController1:1:PortX|Dir\(1),
	padio => ww_IOPort(1)(1),
	combout => \IOPort[1][1]~55\);

-- Location: PIN_121,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(2),
	oe => \Gen_IOController1:1:PortX|Dir\(2),
	padio => ww_IOPort(1)(2),
	combout => \IOPort[1][2]~56\);

-- Location: PIN_122,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(3),
	oe => \Gen_IOController1:1:PortX|Dir\(3),
	padio => ww_IOPort(1)(3),
	combout => \IOPort[1][3]~57\);

-- Location: PIN_123,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(4),
	oe => \Gen_IOController1:1:PortX|Dir\(4),
	padio => ww_IOPort(1)(4),
	combout => \IOPort[1][4]~58\);

-- Location: PIN_124,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(5),
	oe => \Gen_IOController1:1:PortX|Dir\(5),
	padio => ww_IOPort(1)(5),
	combout => \IOPort[1][5]~59\);

-- Location: PIN_125,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(6),
	oe => \Gen_IOController1:1:PortX|Dir\(6),
	padio => ww_IOPort(1)(6),
	combout => \IOPort[1][6]~60\);

-- Location: PIN_127,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(7),
	oe => \Gen_IOController1:1:PortX|Dir\(7),
	padio => ww_IOPort(1)(7),
	combout => \IOPort[1][7]~61\);

-- Location: PIN_129,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[1][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:1:PortX|OutputData\(8),
	oe => \Gen_IOController1:1:PortX|Dir\(8),
	padio => ww_IOPort(1)(8),
	combout => \IOPort[1][8]~62\);

-- Location: PIN_88,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(0),
	oe => \Gen_IOController1:0:PortX|Dir\(0),
	padio => ww_IOPort(0)(0),
	combout => \IOPort[0][0]~63\);

-- Location: PIN_87,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(1),
	oe => \Gen_IOController1:0:PortX|Dir\(1),
	padio => ww_IOPort(0)(1),
	combout => \IOPort[0][1]~64\);

-- Location: PIN_86,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(2),
	oe => \Gen_IOController1:0:PortX|Dir\(2),
	padio => ww_IOPort(0)(2),
	combout => \IOPort[0][2]~65\);

-- Location: PIN_85,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(3),
	oe => \Gen_IOController1:0:PortX|Dir\(3),
	padio => ww_IOPort(0)(3),
	combout => \IOPort[0][3]~66\);

-- Location: PIN_84,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(4),
	oe => \Gen_IOController1:0:PortX|Dir\(4),
	padio => ww_IOPort(0)(4),
	combout => \IOPort[0][4]~67\);

-- Location: PIN_81,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(5),
	oe => \Gen_IOController1:0:PortX|Dir\(5),
	padio => ww_IOPort(0)(5),
	combout => \IOPort[0][5]~68\);

-- Location: PIN_80,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(6),
	oe => \Gen_IOController1:0:PortX|Dir\(6),
	padio => ww_IOPort(0)(6),
	combout => \IOPort[0][6]~69\);

-- Location: PIN_79,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(7),
	oe => \Gen_IOController1:0:PortX|Dir\(7),
	padio => ww_IOPort(0)(7),
	combout => \IOPort[0][7]~70\);

-- Location: PIN_78,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\IOPort[0][8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => \Gen_IOController1:0:PortX|OutputData\(8),
	oe => \Gen_IOController1:0:PortX|Dir\(8),
	padio => ww_IOPort(0)(8),
	combout => \IOPort[0][8]~71\);

-- Location: PIN_114,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FSMCAdd[2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FSMCAdd(2),
	combout => \FSMCAdd~combout\(2));

-- Location: PIN_112,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FSMCAdd[4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FSMCAdd(4),
	combout => \FSMCAdd~combout\(4));

-- Location: PIN_113,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FSMCAdd[3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FSMCAdd(3),
	combout => \FSMCAdd~combout\(3));

-- Location: PIN_111,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FSMCAdd[5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FSMCAdd(5),
	combout => \FSMCAdd~combout\(5));

-- Location: LC_X12_Y6_N0
\Equal8~0\ : maxii_lcell
-- Equation(s):
-- \Equal8~0_combout\ = (!\FSMCAdd~combout\(4) & (!\FSMCAdd~combout\(3) & ((!\FSMCAdd~combout\(5)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(4),
	datab => \FSMCAdd~combout\(3),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal8~0_combout\);

-- Location: PIN_118,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FSMCAdd[0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FSMCAdd(0),
	combout => \FSMCAdd~combout\(0));

-- Location: PIN_117,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FSMCAdd[1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FSMCAdd(1),
	combout => \FSMCAdd~combout\(1));

-- Location: LC_X12_Y5_N8
\Equal8~1\ : maxii_lcell
-- Equation(s):
-- \Equal8~1_combout\ = (\FSMCAdd~combout\(2) & (\Equal8~0_combout\ & (\FSMCAdd~combout\(0) & !\FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0080",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \Equal8~0_combout\,
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal8~1_combout\);

-- Location: PIN_89,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\NOE~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_NOE,
	combout => \NOE~combout\);

-- Location: PIN_18,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\NE~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_NE,
	combout => \NE~combout\);

-- Location: LC_X10_Y3_N2
\ParPort|InternalClk\ : maxii_lcell
-- Equation(s):
-- \ParPort|InternalClk~combout\ = LCELL(((\Equal8~1_combout\ & (!\NOE~combout\ & !\NE~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \Equal8~1_combout\,
	datac => \NOE~combout\,
	datad => \NE~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \ParPort|InternalClk~combout\);

-- Location: PIN_91,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\NWE~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_NWE,
	combout => \NWE~combout\);

-- Location: LC_X10_Y3_N6
\FSMCCtrl|InDataClk\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InDataClk~combout\ = LCELL((((\NWE~combout\) # (\NE~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \NWE~combout\,
	datad => \NE~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InDataClk~combout\);

-- Location: LC_X12_Y5_N3
\Gen_IOController1:2:PortX|Config_Reset~0\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|Config_Reset~0_combout\ = (\FSMCAdd~combout\(2) & (((!\FSMCAdd~combout\(0) & !\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:2:PortX|Config_Reset~0_combout\);

-- Location: LC_X6_Y5_N0
\Equal0~1\ : maxii_lcell
-- Equation(s):
-- \Equal0~1_combout\ = ((\FSMCAdd~combout\(3) & (!\FSMCAdd~combout\(5) & \FSMCAdd~combout\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0c00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(3),
	datac => \FSMCAdd~combout\(5),
	datad => \FSMCAdd~combout\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal0~1_combout\);

-- Location: LC_X10_Y5_N1
\Gen_IOController1:3:PortX|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|Config_Reset~regout\ = DFFEAS((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\Equal0~1_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Equal0~1_combout\ & (\Gen_IOController1:3:PortX|Config_Reset~regout\)))) # 
-- (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & (\Gen_IOController1:3:PortX|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:3:PortX|Config_Reset~regout\,
	datab => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datac => \Equal0~1_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|Config_Reset~regout\);

-- Location: LC_X11_Y6_N8
\Equal9~0\ : maxii_lcell
-- Equation(s):
-- \Equal9~0_combout\ = (\FSMCAdd~combout\(2) & (\Equal8~0_combout\ & (!\FSMCAdd~combout\(0) & \FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0800",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \Equal8~0_combout\,
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal9~0_combout\);

-- Location: LC_X10_Y5_N6
GlobalReset : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|InternalReset\ = (((GlobalReset) # (\Gen_IOController1:3:PortX|Config_Reset~regout\)))
-- \GlobalReset~regout\ = DFFEAS(\Gen_IOController1:3:PortX|InternalReset\, GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , \Equal9~0_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \Gen_IOController1:3:PortX|Config_Reset~regout\,
	aclr => GND,
	sload => VCC,
	ena => \Equal9~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:3:PortX|InternalReset\,
	regout => \GlobalReset~regout\);

-- Location: LC_X8_Y5_N1
\Gen_IOController1:3:PortX|Dir[8]~4\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|Dir[8]~4_combout\ = (\FSMCAdd~combout\(1) & (\FSMCAdd~combout\(0) & ((\Equal0~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8800",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(0),
	datad => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:3:PortX|Dir[8]~4_combout\);

-- Location: LC_X9_Y4_N2
\Gen_IOController1:3:PortX|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[0]~0\ = (!\NE~combout\ & (((\FSMCData[0]~0\))))
-- \Gen_IOController1:3:PortX|Dir\(0) = DFFEAS(\FSMCCtrl|InData[0]~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datac => \FSMCData[0]~0\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[0]~0\,
	regout => \Gen_IOController1:3:PortX|Dir\(0));

-- Location: LC_X4_Y4_N8
\ParPort|IOClk~0\ : maxii_lcell
-- Equation(s):
-- \ParPort|IOClk~0_combout\ = (((\ParPort|InternalClk~combout\ & !\GlobalReset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \ParPort|InternalClk~combout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \ParPort|IOClk~0_combout\);

-- Location: PIN_20,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\SysClk~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_SysClk,
	combout => \SysClk~combout\);

-- Location: LC_X1_Y7_N4
\STM32ClkDiv1[0]\ : maxii_lcell
-- Equation(s):
-- STM32ClkDiv1(0) = DFFEAS((((!STM32ClkDiv1(0)))), GLOBAL(\SysClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0f0f",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \SysClk~combout\,
	datac => STM32ClkDiv1(0),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => STM32ClkDiv1(0));

-- Location: LC_X1_Y7_N2
\STM32ClkDiv1[1]\ : maxii_lcell
-- Equation(s):
-- STM32ClkDiv1(1) = DFFEAS(((STM32ClkDiv1(0) $ (STM32ClkDiv1(1)))), GLOBAL(\SysClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0ff0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \SysClk~combout\,
	datac => STM32ClkDiv1(0),
	datad => STM32ClkDiv1(1),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => STM32ClkDiv1(1));

-- Location: LC_X6_Y5_N1
\Equal10~0\ : maxii_lcell
-- Equation(s):
-- \Equal10~0_combout\ = ((\FSMCAdd~combout\(3) & (\FSMCAdd~combout\(5) & \FSMCAdd~combout\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(3),
	datac => \FSMCAdd~combout\(5),
	datad => \FSMCAdd~combout\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal10~0_combout\);

-- Location: LC_X8_Y5_N5
\Equal10~1\ : maxii_lcell
-- Equation(s):
-- \Equal10~1_combout\ = (\FSMCAdd~combout\(1) & (\FSMCAdd~combout\(0) & (\FSMCAdd~combout\(2) & \Equal10~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(2),
	datad => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal10~1_combout\);

-- Location: PIN_15,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(0),
	combout => \FPGAData~combout\(0));

-- Location: LC_X12_Y5_N9
\Gen_IOController1:3:PortX|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|Mux26~1_combout\ = (!\FSMCAdd~combout\(2) & ((\FSMCAdd~combout\(0) $ (!\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5005",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:3:PortX|Mux26~1_combout\);

-- Location: LC_X10_Y5_N8
\Gen_IOController2:7:PortX|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|Config_Reset~regout\ = DFFEAS((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\Equal10~0_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Equal10~0_combout\ & (\Gen_IOController2:7:PortX|Config_Reset~regout\)))) # 
-- (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & (\Gen_IOController2:7:PortX|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController2:7:PortX|Config_Reset~regout\,
	datab => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datac => \Equal10~0_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|Config_Reset~regout\);

-- Location: LC_X10_Y5_N7
\Gen_IOController2:7:PortX|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|InternalReset~combout\ = (((\GlobalReset~regout\) # (\Gen_IOController2:7:PortX|Config_Reset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \GlobalReset~regout\,
	datad => \Gen_IOController2:7:PortX|Config_Reset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:7:PortX|InternalReset~combout\);

-- Location: LC_X4_Y4_N5
\Equal10~2\ : maxii_lcell
-- Equation(s):
-- \Equal10~2_combout\ = (((\FSMCAdd~combout\(1) & \FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal10~2_combout\);

-- Location: LC_X6_Y5_N2
\Equal10~3\ : maxii_lcell
-- Equation(s):
-- \Equal10~3_combout\ = (\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(3) & (\Equal10~2_combout\ & \FSMCAdd~combout\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(3),
	datac => \Equal10~2_combout\,
	datad => \FSMCAdd~combout\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal10~3_combout\);

-- Location: LC_X8_Y5_N3
\Gen_IOController2:7:PortX|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|Mux26~0\ = ((\FSMCAdd~combout\(1) & ((B8_Dir[0]))) # (!\FSMCAdd~combout\(1) & (\IOPort[7][0]~0\)))
-- \Gen_IOController2:7:PortX|Dir\(0) = DFFEAS(\Gen_IOController2:7:PortX|Mux26~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0cc",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \IOPort[7][0]~0\,
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:7:PortX|Mux26~0\,
	regout => \Gen_IOController2:7:PortX|Dir\(0));

-- Location: LC_X12_Y5_N6
\Gen_IOController2:7:PortX|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|Mux26~1_combout\ = (\FSMCAdd~combout\(2) & ((\Gen_IOController2:7:PortX|Config_Reset~regout\) # ((\Gen_IOController1:3:PortX|Mux26~1_combout\ & \Gen_IOController2:7:PortX|Mux26~0\)))) # (!\FSMCAdd~combout\(2) & 
-- (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\Gen_IOController2:7:PortX|Mux26~0\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eca0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datac => \Gen_IOController2:7:PortX|Config_Reset~regout\,
	datad => \Gen_IOController2:7:PortX|Mux26~0\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:7:PortX|Mux26~1_combout\);

-- Location: LC_X8_Y4_N2
\Equal0~3\ : maxii_lcell
-- Equation(s):
-- \Equal0~3_combout\ = ((\FSMCAdd~combout\(3) & (!\FSMCAdd~combout\(4) & !\FSMCAdd~combout\(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(3),
	datac => \FSMCAdd~combout\(4),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal0~3_combout\);

-- Location: LC_X10_Y5_N3
\Gen_IOController1:1:PortX|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|Config_Reset~regout\ = DFFEAS((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\Equal0~3_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Equal0~3_combout\ & (\Gen_IOController1:1:PortX|Config_Reset~regout\)))) # 
-- (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & (\Gen_IOController1:1:PortX|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:1:PortX|Config_Reset~regout\,
	datab => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datac => \Equal0~3_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|Config_Reset~regout\);

-- Location: LC_X9_Y6_N6
\Gen_IOController1:1:PortX|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|InternalReset~combout\ = (\GlobalReset~regout\) # (((\Gen_IOController1:1:PortX|Config_Reset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ffaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \GlobalReset~regout\,
	datad => \Gen_IOController1:1:PortX|Config_Reset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:1:PortX|InternalReset~combout\);

-- Location: LC_X10_Y6_N7
\Gen_IOController1:1:PortX|Dir[8]~4\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|Dir[8]~4_combout\ = (\Equal0~3_combout\ & (((\FSMCAdd~combout\(0) & \FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Equal0~3_combout\,
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:1:PortX|Dir[8]~4_combout\);

-- Location: LC_X9_Y6_N1
\Gen_IOController1:1:PortX|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|Mux26~0\ = ((\FSMCAdd~combout\(1) & (B3_Dir[0])) # (!\FSMCAdd~combout\(1) & ((\IOPort[1][0]~54\))))
-- \Gen_IOController1:1:PortX|Dir\(0) = DFFEAS(\Gen_IOController1:1:PortX|Mux26~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f3c0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \IOPort[1][0]~54\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:1:PortX|Mux26~0\,
	regout => \Gen_IOController1:1:PortX|Dir\(0));

-- Location: LC_X10_Y5_N5
\Gen_IOController1:1:PortX|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|Mux26~1_combout\ = (\Gen_IOController1:1:PortX|Config_Reset~regout\ & ((\FSMCAdd~combout\(2)) # ((\Gen_IOController1:1:PortX|Mux26~0\ & \Gen_IOController1:3:PortX|Mux26~1_combout\)))) # 
-- (!\Gen_IOController1:1:PortX|Config_Reset~regout\ & (\Gen_IOController1:1:PortX|Mux26~0\ & (\Gen_IOController1:3:PortX|Mux26~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eac0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:1:PortX|Config_Reset~regout\,
	datab => \Gen_IOController1:1:PortX|Mux26~0\,
	datac => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datad => \FSMCAdd~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:1:PortX|Mux26~1_combout\);

-- Location: LC_X11_Y3_N1
\Equal0~2\ : maxii_lcell
-- Equation(s):
-- \Equal0~2_combout\ = (\FSMCAdd~combout\(3) & (((\FSMCAdd~combout\(5) & !\FSMCAdd~combout\(4)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00a0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(3),
	datac => \FSMCAdd~combout\(5),
	datad => \FSMCAdd~combout\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal0~2_combout\);

-- Location: LC_X11_Y3_N7
\Gen_IOController2:5:PortX|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|Config_Reset~regout\ = DFFEAS((\Equal0~2_combout\ & ((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & 
-- (\Gen_IOController2:5:PortX|Config_Reset~regout\)))) # (!\Equal0~2_combout\ & (((\Gen_IOController2:5:PortX|Config_Reset~regout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f870",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal0~2_combout\,
	datab => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datac => \Gen_IOController2:5:PortX|Config_Reset~regout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|Config_Reset~regout\);

-- Location: LC_X11_Y3_N0
\Gen_IOController2:5:PortX|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|InternalReset~combout\ = (((\Gen_IOController2:5:PortX|Config_Reset~regout\) # (\GlobalReset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Gen_IOController2:5:PortX|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:5:PortX|InternalReset~combout\);

-- Location: LC_X12_Y3_N4
\Gen_IOController2:5:PortX|Dir[8]~4\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|Dir[8]~4_combout\ = ((\FSMCAdd~combout\(1) & (\Equal0~2_combout\ & \FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(1),
	datac => \Equal0~2_combout\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:5:PortX|Dir[8]~4_combout\);

-- Location: LC_X12_Y3_N5
\Gen_IOController2:5:PortX|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|Mux26~0\ = ((\FSMCAdd~combout\(1) & (B6_Dir[0])) # (!\FSMCAdd~combout\(1) & ((\IOPort[5][0]~18\))))
-- \Gen_IOController2:5:PortX|Dir\(0) = DFFEAS(\Gen_IOController2:5:PortX|Mux26~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f3c0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \IOPort[5][0]~18\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:5:PortX|Mux26~0\,
	regout => \Gen_IOController2:5:PortX|Dir\(0));

-- Location: LC_X12_Y4_N5
\Gen_IOController2:5:PortX|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|Mux26~1_combout\ = (\Gen_IOController2:5:PortX|Mux26~0\ & ((\Gen_IOController1:3:PortX|Mux26~1_combout\) # ((\Gen_IOController2:5:PortX|Config_Reset~regout\ & \FSMCAdd~combout\(2))))) # (!\Gen_IOController2:5:PortX|Mux26~0\ & 
-- (\Gen_IOController2:5:PortX|Config_Reset~regout\ & (\FSMCAdd~combout\(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eac0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController2:5:PortX|Mux26~0\,
	datab => \Gen_IOController2:5:PortX|Config_Reset~regout\,
	datac => \FSMCAdd~combout\(2),
	datad => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:5:PortX|Mux26~1_combout\);

-- Location: LC_X12_Y4_N1
\OutData~14\ : maxii_lcell
-- Equation(s):
-- \OutData~14_combout\ = (\FSMCAdd~combout\(4) & (((\FSMCAdd~combout\(5))))) # (!\FSMCAdd~combout\(4) & ((\FSMCAdd~combout\(5) & ((\Gen_IOController2:5:PortX|Mux26~1_combout\))) # (!\FSMCAdd~combout\(5) & (\Gen_IOController1:1:PortX|Mux26~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc22",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:1:PortX|Mux26~1_combout\,
	datab => \FSMCAdd~combout\(4),
	datac => \Gen_IOController2:5:PortX|Mux26~1_combout\,
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~14_combout\);

-- Location: LC_X7_Y7_N8
\Gen_IOController1:3:PortX|Mux26~0\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|Mux26~0_combout\ = ((\FSMCAdd~combout\(1) & (\Gen_IOController1:3:PortX|Dir\(0))) # (!\FSMCAdd~combout\(1) & ((\IOPort[3][0]~36\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f3c0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(1),
	datac => \Gen_IOController1:3:PortX|Dir\(0),
	datad => \IOPort[3][0]~36\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:3:PortX|Mux26~0_combout\);

-- Location: LC_X10_Y5_N0
\Gen_IOController1:3:PortX|Mux26~2\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|Mux26~2_combout\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\Gen_IOController1:3:PortX|Mux26~0_combout\) # ((\Gen_IOController1:3:PortX|Config_Reset~regout\ & \FSMCAdd~combout\(2))))) # 
-- (!\Gen_IOController1:3:PortX|Mux26~1_combout\ & (((\Gen_IOController1:3:PortX|Config_Reset~regout\ & \FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f888",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datab => \Gen_IOController1:3:PortX|Mux26~0_combout\,
	datac => \Gen_IOController1:3:PortX|Config_Reset~regout\,
	datad => \FSMCAdd~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:3:PortX|Mux26~2_combout\);

-- Location: LC_X12_Y4_N4
\OutData~15\ : maxii_lcell
-- Equation(s):
-- \OutData~15_combout\ = (\FSMCAdd~combout\(4) & ((\OutData~14_combout\ & (\Gen_IOController2:7:PortX|Mux26~1_combout\)) # (!\OutData~14_combout\ & ((\Gen_IOController1:3:PortX|Mux26~2_combout\))))) # (!\FSMCAdd~combout\(4) & (((\OutData~14_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bcb0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController2:7:PortX|Mux26~1_combout\,
	datab => \FSMCAdd~combout\(4),
	datac => \OutData~14_combout\,
	datad => \Gen_IOController1:3:PortX|Mux26~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~15_combout\);

-- Location: LC_X5_Y4_N9
\Equal0~4\ : maxii_lcell
-- Equation(s):
-- \Equal0~4_combout\ = ((\FSMCAdd~combout\(4) & (!\FSMCAdd~combout\(5) & !\FSMCAdd~combout\(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(4),
	datac => \FSMCAdd~combout\(5),
	datad => \FSMCAdd~combout\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal0~4_combout\);

-- Location: LC_X5_Y4_N8
\Gen_IOController1:2:PortX|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|Config_Reset~regout\ = DFFEAS((\Equal0~4_combout\ & ((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & 
-- (\Gen_IOController1:2:PortX|Config_Reset~regout\)))) # (!\Equal0~4_combout\ & (\Gen_IOController1:2:PortX|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:2:PortX|Config_Reset~regout\,
	datab => \Equal0~4_combout\,
	datac => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|Config_Reset~regout\);

-- Location: LC_X6_Y4_N0
\Gen_IOController1:2:PortX|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|InternalReset~combout\ = (\Gen_IOController1:2:PortX|Config_Reset~regout\) # (((\GlobalReset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ffaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:2:PortX|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:2:PortX|InternalReset~combout\);

-- Location: LC_X7_Y4_N3
\Gen_IOController1:2:PortX|Dir[8]~4\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|Dir[8]~4_combout\ = ((\FSMCAdd~combout\(1) & (\Equal0~4_combout\ & \FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(1),
	datac => \Equal0~4_combout\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:2:PortX|Dir[8]~4_combout\);

-- Location: LC_X7_Y4_N8
\Gen_IOController1:2:PortX|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|Mux26~0\ = ((\FSMCAdd~combout\(1) & ((B4_Dir[0]))) # (!\FSMCAdd~combout\(1) & (\IOPort[2][0]~45\)))
-- \Gen_IOController1:2:PortX|Dir\(0) = DFFEAS(\Gen_IOController1:2:PortX|Mux26~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0cc",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \IOPort[2][0]~45\,
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:2:PortX|Mux26~0\,
	regout => \Gen_IOController1:2:PortX|Dir\(0));

-- Location: LC_X8_Y4_N1
\Gen_IOController1:2:PortX|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|Mux26~1_combout\ = (\FSMCAdd~combout\(2) & ((\Gen_IOController1:2:PortX|Config_Reset~regout\) # ((\Gen_IOController1:3:PortX|Mux26~1_combout\ & \Gen_IOController1:2:PortX|Mux26~0\)))) # (!\FSMCAdd~combout\(2) & 
-- (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\Gen_IOController1:2:PortX|Mux26~0\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eca0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datac => \Gen_IOController1:2:PortX|Config_Reset~regout\,
	datad => \Gen_IOController1:2:PortX|Mux26~0\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:2:PortX|Mux26~1_combout\);

-- Location: LC_X8_Y4_N0
\Equal0~5\ : maxii_lcell
-- Equation(s):
-- \Equal0~5_combout\ = ((!\FSMCAdd~combout\(3) & (\FSMCAdd~combout\(4) & \FSMCAdd~combout\(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(3),
	datac => \FSMCAdd~combout\(4),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal0~5_combout\);

-- Location: LC_X10_Y5_N2
\Gen_IOController2:6:PortX|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|Config_Reset~regout\ = DFFEAS((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\Equal0~5_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Equal0~5_combout\ & (\Gen_IOController2:6:PortX|Config_Reset~regout\)))) # 
-- (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & (\Gen_IOController2:6:PortX|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ec4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datab => \Gen_IOController2:6:PortX|Config_Reset~regout\,
	datac => \Equal0~5_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|Config_Reset~regout\);

-- Location: LC_X9_Y5_N7
\Gen_IOController2:6:PortX|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|InternalReset~combout\ = ((\GlobalReset~regout\) # ((\Gen_IOController2:6:PortX|Config_Reset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fcfc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \GlobalReset~regout\,
	datac => \Gen_IOController2:6:PortX|Config_Reset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:6:PortX|InternalReset~combout\);

-- Location: LC_X10_Y2_N1
\Gen_IOController2:6:PortX|Dir[8]~4\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|Dir[8]~4_combout\ = (\FSMCAdd~combout\(0) & (\FSMCAdd~combout\(1) & ((\Equal0~5_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8800",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(1),
	datad => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:6:PortX|Dir[8]~4_combout\);

-- Location: LC_X10_Y2_N0
\Gen_IOController2:6:PortX|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|Mux26~0\ = (\FSMCAdd~combout\(1) & (((B7_Dir[0])))) # (!\FSMCAdd~combout\(1) & (\IOPort[6][0]~9\))
-- \Gen_IOController2:6:PortX|Dir\(0) = DFFEAS(\Gen_IOController2:6:PortX|Mux26~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e2e2",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \IOPort[6][0]~9\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[0]~0\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:6:PortX|Mux26~0\,
	regout => \Gen_IOController2:6:PortX|Dir\(0));

-- Location: LC_X10_Y4_N0
\Gen_IOController2:6:PortX|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|Mux26~1_combout\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\Gen_IOController2:6:PortX|Mux26~0\) # ((\FSMCAdd~combout\(2) & \Gen_IOController2:6:PortX|Config_Reset~regout\)))) # 
-- (!\Gen_IOController1:3:PortX|Mux26~1_combout\ & (\FSMCAdd~combout\(2) & (\Gen_IOController2:6:PortX|Config_Reset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eac0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \Gen_IOController2:6:PortX|Config_Reset~regout\,
	datad => \Gen_IOController2:6:PortX|Mux26~0\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:6:PortX|Mux26~1_combout\);

-- Location: LC_X12_Y4_N2
\Gen_IOController1:0:PortX|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|Config_Reset~regout\ = DFFEAS((\Equal8~0_combout\ & ((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & 
-- (\Gen_IOController1:0:PortX|Config_Reset~regout\)))) # (!\Equal8~0_combout\ & (\Gen_IOController1:0:PortX|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e4cc",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal8~0_combout\,
	datab => \Gen_IOController1:0:PortX|Config_Reset~regout\,
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|Config_Reset~regout\);

-- Location: LC_X11_Y4_N1
\Gen_IOController1:0:PortX|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|InternalReset~combout\ = (((\Gen_IOController1:0:PortX|Config_Reset~regout\) # (\GlobalReset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Gen_IOController1:0:PortX|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:0:PortX|InternalReset~combout\);

-- Location: LC_X8_Y4_N9
\Gen_IOController1:0:PortX|Dir[8]~4\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|Dir[8]~4_combout\ = (\Equal10~2_combout\ & (!\FSMCAdd~combout\(3) & (!\FSMCAdd~combout\(4) & !\FSMCAdd~combout\(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0002",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Equal10~2_combout\,
	datab => \FSMCAdd~combout\(3),
	datac => \FSMCAdd~combout\(4),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:0:PortX|Dir[8]~4_combout\);

-- Location: LC_X12_Y4_N0
\Gen_IOController1:0:PortX|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|Mux26~0\ = ((\FSMCAdd~combout\(1) & (B2_Dir[0])) # (!\FSMCAdd~combout\(1) & ((\IOPort[0][0]~63\))))
-- \Gen_IOController1:0:PortX|Dir\(0) = DFFEAS(\Gen_IOController1:0:PortX|Mux26~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f3c0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \IOPort[0][0]~63\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:0:PortX|Mux26~0\,
	regout => \Gen_IOController1:0:PortX|Dir\(0));

-- Location: LC_X12_Y4_N8
\Gen_IOController1:0:PortX|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|Mux26~1_combout\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\Gen_IOController1:0:PortX|Mux26~0\) # ((\FSMCAdd~combout\(2) & \Gen_IOController1:0:PortX|Config_Reset~regout\)))) # 
-- (!\Gen_IOController1:3:PortX|Mux26~1_combout\ & (((\FSMCAdd~combout\(2) & \Gen_IOController1:0:PortX|Config_Reset~regout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f888",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datab => \Gen_IOController1:0:PortX|Mux26~0\,
	datac => \FSMCAdd~combout\(2),
	datad => \Gen_IOController1:0:PortX|Config_Reset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:0:PortX|Mux26~1_combout\);

-- Location: LC_X9_Y4_N3
\Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide~regout\ = DFFEAS((((!\Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide~regout\))), \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\, VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00ff",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\,
	datad => \Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide~regout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide~regout\);

-- Location: LC_X9_Y4_N0
\Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\ = LCELL(\Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide~regout\ $ ((((\SysClk~combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "55aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|ClkDiv|FreqDoubler|PostDivide~regout\,
	datad => \SysClk~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\);

-- Location: LC_X9_Y4_N6
\Port4|DedicatedPort|ClkDiv|Counter[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ClkDiv|Counter\(0) = DFFEAS((((!\Port4|DedicatedPort|ClkDiv|Counter\(0) & !\Port4|DedicatedPort|ClkDiv|Counter\(2)))), \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\, VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000f",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\,
	datac => \Port4|DedicatedPort|ClkDiv|Counter\(0),
	datad => \Port4|DedicatedPort|ClkDiv|Counter\(2),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ClkDiv|Counter\(0));

-- Location: LC_X9_Y4_N9
\Port4|DedicatedPort|ClkDiv|Counter[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ClkDiv|Counter\(1) = DFFEAS(((!\Port4|DedicatedPort|ClkDiv|Counter\(2) & (\Port4|DedicatedPort|ClkDiv|Counter\(0) $ (\Port4|DedicatedPort|ClkDiv|Counter\(1))))), \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\, VCC, , , , , 
-- , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0066",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\,
	dataa => \Port4|DedicatedPort|ClkDiv|Counter\(0),
	datab => \Port4|DedicatedPort|ClkDiv|Counter\(1),
	datad => \Port4|DedicatedPort|ClkDiv|Counter\(2),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ClkDiv|Counter\(1));

-- Location: LC_X9_Y4_N7
\Port4|DedicatedPort|ClkDiv|Counter[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ClkDiv|Counter\(2) = DFFEAS((\Port4|DedicatedPort|ClkDiv|Counter\(0) & (\Port4|DedicatedPort|ClkDiv|Counter\(1) & ((!\Port4|DedicatedPort|ClkDiv|Counter\(2))))), \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\, VCC, , , , , 
-- , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0088",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\,
	dataa => \Port4|DedicatedPort|ClkDiv|Counter\(0),
	datab => \Port4|DedicatedPort|ClkDiv|Counter\(1),
	datad => \Port4|DedicatedPort|ClkDiv|Counter\(2),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ClkDiv|Counter\(2));

-- Location: LC_X10_Y3_N9
\Port4|DedicatedPort|ClkDiv|ClkOut\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ClkDiv|ClkOut~regout\ = DFFEAS(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\ $ (((\Port4|DedicatedPort|ClkDiv|Counter\(2) & ((!\Port4|DedicatedPort|ClkDiv|Counter\(1)) # (!\Port4|DedicatedPort|ClkDiv|Counter\(0)))))), 
-- \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\, VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c666",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|FreqDoubler|DoubleClk~combout\,
	dataa => \Port4|DedicatedPort|ClkDiv|Counter\(2),
	datab => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	datac => \Port4|DedicatedPort|ClkDiv|Counter\(0),
	datad => \Port4|DedicatedPort|ClkDiv|Counter\(1),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\);

-- Location: LC_X9_Y4_N5
\Gen_IOController1:3:PortX|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[1]~1\ = (!\NE~combout\ & (((\FSMCData[1]~1\))))
-- \Gen_IOController1:3:PortX|Dir\(1) = DFFEAS(\FSMCCtrl|InData[1]~1\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datad => \FSMCData[1]~1\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[1]~1\,
	regout => \Gen_IOController1:3:PortX|Dir\(1));

-- Location: LC_X6_Y5_N8
DedicatedFunctionUsed : maxii_lcell
-- Equation(s):
-- \OutData[14]~184\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(4) & (DedicatedFunctionUsed & !\FSMCAdd~combout\(3))))
-- \DedicatedFunctionUsed~regout\ = DFFEAS(\OutData[14]~184\, GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , \Equal9~0_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0020",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(4),
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \FSMCAdd~combout\(3),
	aclr => GND,
	sload => VCC,
	ena => \Equal9~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~184\,
	regout => \DedicatedFunctionUsed~regout\);

-- Location: LC_X9_Y7_N3
\Port4|DedicatedPort|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|Config_Reset~regout\ = DFFEAS((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\OutData[14]~184\ & ((\FSMCCtrl|InData[0]~0\))) # (!\OutData[14]~184\ & (\Port4|DedicatedPort|Config_Reset~regout\)))) # 
-- (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & (\Port4|DedicatedPort|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "caaa",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Port4|DedicatedPort|Config_Reset~regout\,
	datab => \FSMCCtrl|InData[0]~0\,
	datac => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datad => \OutData[14]~184\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|Config_Reset~regout\);

-- Location: LC_X2_Y4_N5
\Port4|DedicatedPort|ConvertCounter[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ConvertCounter\(0) = DFFEAS((!\Port4|DedicatedPort|ConvertCounter\(0)), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , \Port4|DedicatedPort|ConvertCounter[3]~12_combout\, )
-- \Port4|DedicatedPort|ConvertCounter[0]~7\ = CARRY((\Port4|DedicatedPort|ConvertCounter\(0)))
-- \Port4|DedicatedPort|ConvertCounter[0]~7COUT1_14\ = CARRY((\Port4|DedicatedPort|ConvertCounter\(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "55aa",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ConvertCounter\(0),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ConvertCounter[3]~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ConvertCounter\(0),
	cout0 => \Port4|DedicatedPort|ConvertCounter[0]~7\,
	cout1 => \Port4|DedicatedPort|ConvertCounter[0]~7COUT1_14\);

-- Location: LC_X2_Y4_N6
\Port4|DedicatedPort|ConvertCounter[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ConvertCounter\(1) = DFFEAS(\Port4|DedicatedPort|ConvertCounter\(1) $ ((((\Port4|DedicatedPort|ConvertCounter[0]~7\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , 
-- \Port4|DedicatedPort|ConvertCounter[3]~12_combout\, )
-- \Port4|DedicatedPort|ConvertCounter[1]~9\ = CARRY(((!\Port4|DedicatedPort|ConvertCounter[0]~7\)) # (!\Port4|DedicatedPort|ConvertCounter\(1)))
-- \Port4|DedicatedPort|ConvertCounter[1]~9COUT1_15\ = CARRY(((!\Port4|DedicatedPort|ConvertCounter[0]~7COUT1_14\)) # (!\Port4|DedicatedPort|ConvertCounter\(1)))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ConvertCounter\(1),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ConvertCounter[3]~12_combout\,
	cin0 => \Port4|DedicatedPort|ConvertCounter[0]~7\,
	cin1 => \Port4|DedicatedPort|ConvertCounter[0]~7COUT1_14\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ConvertCounter\(1),
	cout0 => \Port4|DedicatedPort|ConvertCounter[1]~9\,
	cout1 => \Port4|DedicatedPort|ConvertCounter[1]~9COUT1_15\);

-- Location: LC_X2_Y4_N7
\Port4|DedicatedPort|ConvertCounter[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ConvertCounter\(2) = DFFEAS((\Port4|DedicatedPort|ConvertCounter\(2) $ ((!\Port4|DedicatedPort|ConvertCounter[1]~9\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , 
-- \Port4|DedicatedPort|ConvertCounter[3]~12_combout\, )
-- \Port4|DedicatedPort|ConvertCounter[2]~11\ = CARRY(((\Port4|DedicatedPort|ConvertCounter\(2) & !\Port4|DedicatedPort|ConvertCounter[1]~9\)))
-- \Port4|DedicatedPort|ConvertCounter[2]~11COUT1_16\ = CARRY(((\Port4|DedicatedPort|ConvertCounter\(2) & !\Port4|DedicatedPort|ConvertCounter[1]~9COUT1_15\)))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ConvertCounter\(2),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ConvertCounter[3]~12_combout\,
	cin0 => \Port4|DedicatedPort|ConvertCounter[1]~9\,
	cin1 => \Port4|DedicatedPort|ConvertCounter[1]~9COUT1_15\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ConvertCounter\(2),
	cout0 => \Port4|DedicatedPort|ConvertCounter[2]~11\,
	cout1 => \Port4|DedicatedPort|ConvertCounter[2]~11COUT1_16\);

-- Location: LC_X2_Y4_N2
\Port4|DedicatedPort|Convert~2\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|Convert~2_combout\ = (\Port4|DedicatedPort|ConvertCounter\(0) & (!\Port4|DedicatedPort|ConvertCounter\(2) & (\Port4|DedicatedPort|ConvertCounter\(1) & !\Port4|DedicatedPort|ConvertCounter\(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0020",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|ConvertCounter\(0),
	datab => \Port4|DedicatedPort|ConvertCounter\(2),
	datac => \Port4|DedicatedPort|ConvertCounter\(1),
	datad => \Port4|DedicatedPort|ConvertCounter\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|Convert~2_combout\);

-- Location: LC_X2_Y4_N8
\Port4|DedicatedPort|ConvertCounter[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ConvertCounter\(3) = DFFEAS(\Port4|DedicatedPort|ConvertCounter\(3) $ ((((\Port4|DedicatedPort|ConvertCounter[2]~11\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , 
-- \Port4|DedicatedPort|ConvertCounter[3]~12_combout\, )
-- \Port4|DedicatedPort|ConvertCounter[3]~3\ = CARRY(((!\Port4|DedicatedPort|ConvertCounter[2]~11\)) # (!\Port4|DedicatedPort|ConvertCounter\(3)))
-- \Port4|DedicatedPort|ConvertCounter[3]~3COUT1_17\ = CARRY(((!\Port4|DedicatedPort|ConvertCounter[2]~11COUT1_16\)) # (!\Port4|DedicatedPort|ConvertCounter\(3)))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ConvertCounter\(3),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ConvertCounter[3]~12_combout\,
	cin0 => \Port4|DedicatedPort|ConvertCounter[2]~11\,
	cin1 => \Port4|DedicatedPort|ConvertCounter[2]~11COUT1_16\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ConvertCounter\(3),
	cout0 => \Port4|DedicatedPort|ConvertCounter[3]~3\,
	cout1 => \Port4|DedicatedPort|ConvertCounter[3]~3COUT1_17\);

-- Location: LC_X2_Y4_N9
\Port4|DedicatedPort|ConvertCounter[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ConvertCounter\(4) = DFFEAS(((\Port4|DedicatedPort|ConvertCounter[3]~3\ $ (!\Port4|DedicatedPort|ConvertCounter\(4)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , 
-- \Port4|DedicatedPort|ConvertCounter[3]~12_combout\, )

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "f00f",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datad => \Port4|DedicatedPort|ConvertCounter\(4),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ConvertCounter[3]~12_combout\,
	cin0 => \Port4|DedicatedPort|ConvertCounter[3]~3\,
	cin1 => \Port4|DedicatedPort|ConvertCounter[3]~3COUT1_17\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ConvertCounter\(4));

-- Location: LC_X2_Y4_N4
\Port4|DedicatedPort|ConvertCounter[3]~12\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ConvertCounter[3]~12_combout\ = (\Port4|DedicatedPort|Config_Reset~regout\) # ((\GlobalReset~regout\) # ((\Port4|DedicatedPort|Convert~2_combout\ & \Port4|DedicatedPort|ConvertCounter\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fefa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|Config_Reset~regout\,
	datab => \Port4|DedicatedPort|Convert~2_combout\,
	datac => \GlobalReset~regout\,
	datad => \Port4|DedicatedPort|ConvertCounter\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|ConvertCounter[3]~12_combout\);

-- Location: LC_X5_Y5_N7
\Port4|GenericPort|Config_Reset~0\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Config_Reset~0_combout\ = (!\FSMCAdd~combout\(3) & (!\FSMCAdd~combout\(4) & (\FSMCAdd~combout\(5) & !\DedicatedFunctionUsed~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(3),
	datab => \FSMCAdd~combout\(4),
	datac => \FSMCAdd~combout\(5),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Config_Reset~0_combout\);

-- Location: LC_X10_Y5_N9
\Port4|GenericPort|Config_Reset\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Config_Reset~regout\ = DFFEAS((\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & ((\Port4|GenericPort|Config_Reset~0_combout\ & ((\FSMCCtrl|InData[0]~0\))) # (!\Port4|GenericPort|Config_Reset~0_combout\ & 
-- (\Port4|GenericPort|Config_Reset~regout\)))) # (!\Gen_IOController1:2:PortX|Config_Reset~0_combout\ & (\Port4|GenericPort|Config_Reset~regout\)), GLOBAL(\FSMCCtrl|InDataClk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ec4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:2:PortX|Config_Reset~0_combout\,
	datab => \Port4|GenericPort|Config_Reset~regout\,
	datac => \Port4|GenericPort|Config_Reset~0_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|Config_Reset~regout\);

-- Location: LC_X10_Y5_N4
\Port4|GenericPort|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|InternalReset~combout\ = (((\GlobalReset~regout\) # (\Port4|GenericPort|Config_Reset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \GlobalReset~regout\,
	datad => \Port4|GenericPort|Config_Reset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|InternalReset~combout\);

-- Location: LC_X5_Y5_N5
\Port4|GenericPort|OutputData[0]~2\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData[0]~2_combout\ = (!\FSMCAdd~combout\(2) & (\Port4|GenericPort|Config_Reset~0_combout\ & ((!\FSMCAdd~combout\(0)) # (!\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0444",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \Port4|GenericPort|Config_Reset~0_combout\,
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|OutputData[0]~2_combout\);

-- Location: LC_X5_Y5_N4
\Port4|GenericPort|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(0) = DFFEAS((\FSMCCtrl|InData[0]~0\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[0]~0\ & (\Port4|GenericPort|OutputData\(0) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(1),
	datac => \Port4|GenericPort|OutputData\(0),
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(0));

-- Location: LC_X2_Y4_N1
\Port4|DedicatedPort|Convert\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|Convert~regout\ = DFFEAS((!\Port4|DedicatedPort|Config_Reset~regout\ & (\Port4|DedicatedPort|Convert~2_combout\ & (!\GlobalReset~regout\ & \Port4|DedicatedPort|ConvertCounter\(4)))), 
-- !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0400",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Config_Reset~regout\,
	datab => \Port4|DedicatedPort|Convert~2_combout\,
	datac => \GlobalReset~regout\,
	datad => \Port4|DedicatedPort|ConvertCounter\(4),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|Convert~regout\);

-- Location: LC_X3_Y4_N0
\Port4|DedicatedPort|ADC_RD_CONVST\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[0]~9\ = (\DedicatedFunctionUsed~regout\ & (((F1_ADC_RD_CONVST)))) # (!\DedicatedFunctionUsed~regout\ & (\Port4|GenericPort|OutputData\(0)))
-- \Port4|DedicatedPort|ADC_RD_CONVST~regout\ = DFFEAS(\Port4|GenericPort|IOPort[0]~9\, !GLOBAL(\SysClk~combout\), VCC, , , \Port4|DedicatedPort|Convert~regout\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e2e2",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_SysClk~combout\,
	dataa => \Port4|GenericPort|OutputData\(0),
	datab => \DedicatedFunctionUsed~regout\,
	datac => \Port4|DedicatedPort|Convert~regout\,
	aclr => GND,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[0]~9\,
	regout => \Port4|DedicatedPort|ADC_RD_CONVST~regout\);

-- Location: LC_X4_Y7_N7
\Port4|DedicatedPort|ChannelAData[0]~2\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelAData[0]~2_combout\ = ((\Port4|DedicatedPort|ADC_RD_CONVST~regout\) # ((\Port4|DedicatedPort|Config_Reset~regout\) # (\GlobalReset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fffc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \Port4|DedicatedPort|ADC_RD_CONVST~regout\,
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|ChannelAData[0]~2_combout\);

-- Location: LC_X4_Y7_N9
\Port4|DedicatedPort|ChannelAData[0]~3\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelAData[0]~3_combout\ = (\Port4|DedicatedPort|Equal1~1_combout\ & (!\Port4|DedicatedPort|ADC_RD_CONVST~regout\ & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0002",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|Equal1~1_combout\,
	datab => \Port4|DedicatedPort|ADC_RD_CONVST~regout\,
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|ChannelAData[0]~3_combout\);

-- Location: LC_X4_Y7_N0
\Port4|DedicatedPort|TransferCounter[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|TransferCounter\(0) = DFFEAS(((!\Port4|DedicatedPort|TransferCounter\(0))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , !\Port4|DedicatedPort|ChannelAData[0]~3_combout\, , , 
-- \Port4|DedicatedPort|ChannelAData[0]~2_combout\, )
-- \Port4|DedicatedPort|TransferCounter[0]~3\ = CARRY(((\Port4|DedicatedPort|TransferCounter\(0))))
-- \Port4|DedicatedPort|TransferCounter[0]~3COUT1_11\ = CARRY(((\Port4|DedicatedPort|TransferCounter\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33cc",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|TransferCounter\(0),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ChannelAData[0]~2_combout\,
	ena => \Port4|DedicatedPort|ALT_INV_ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|TransferCounter\(0),
	cout0 => \Port4|DedicatedPort|TransferCounter[0]~3\,
	cout1 => \Port4|DedicatedPort|TransferCounter[0]~3COUT1_11\);

-- Location: LC_X4_Y7_N1
\Port4|DedicatedPort|TransferCounter[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|TransferCounter\(1) = DFFEAS((\Port4|DedicatedPort|TransferCounter\(1) $ ((\Port4|DedicatedPort|TransferCounter[0]~3\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , !\Port4|DedicatedPort|ChannelAData[0]~3_combout\, , 
-- , \Port4|DedicatedPort|ChannelAData[0]~2_combout\, )
-- \Port4|DedicatedPort|TransferCounter[1]~5\ = CARRY(((!\Port4|DedicatedPort|TransferCounter[0]~3\) # (!\Port4|DedicatedPort|TransferCounter\(1))))
-- \Port4|DedicatedPort|TransferCounter[1]~5COUT1_12\ = CARRY(((!\Port4|DedicatedPort|TransferCounter[0]~3COUT1_11\) # (!\Port4|DedicatedPort|TransferCounter\(1))))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|TransferCounter\(1),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ChannelAData[0]~2_combout\,
	ena => \Port4|DedicatedPort|ALT_INV_ChannelAData[0]~3_combout\,
	cin0 => \Port4|DedicatedPort|TransferCounter[0]~3\,
	cin1 => \Port4|DedicatedPort|TransferCounter[0]~3COUT1_11\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|TransferCounter\(1),
	cout0 => \Port4|DedicatedPort|TransferCounter[1]~5\,
	cout1 => \Port4|DedicatedPort|TransferCounter[1]~5COUT1_12\);

-- Location: LC_X4_Y7_N2
\Port4|DedicatedPort|TransferCounter[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|TransferCounter\(2) = DFFEAS((\Port4|DedicatedPort|TransferCounter\(2) $ ((!\Port4|DedicatedPort|TransferCounter[1]~5\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , !\Port4|DedicatedPort|ChannelAData[0]~3_combout\, , 
-- , \Port4|DedicatedPort|ChannelAData[0]~2_combout\, )
-- \Port4|DedicatedPort|TransferCounter[2]~7\ = CARRY(((\Port4|DedicatedPort|TransferCounter\(2) & !\Port4|DedicatedPort|TransferCounter[1]~5\)))
-- \Port4|DedicatedPort|TransferCounter[2]~7COUT1_13\ = CARRY(((\Port4|DedicatedPort|TransferCounter\(2) & !\Port4|DedicatedPort|TransferCounter[1]~5COUT1_12\)))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|TransferCounter\(2),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ChannelAData[0]~2_combout\,
	ena => \Port4|DedicatedPort|ALT_INV_ChannelAData[0]~3_combout\,
	cin0 => \Port4|DedicatedPort|TransferCounter[1]~5\,
	cin1 => \Port4|DedicatedPort|TransferCounter[1]~5COUT1_12\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|TransferCounter\(2),
	cout0 => \Port4|DedicatedPort|TransferCounter[2]~7\,
	cout1 => \Port4|DedicatedPort|TransferCounter[2]~7COUT1_13\);

-- Location: LC_X4_Y7_N3
\Port4|DedicatedPort|TransferCounter[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|TransferCounter\(3) = DFFEAS(\Port4|DedicatedPort|TransferCounter\(3) $ ((((\Port4|DedicatedPort|TransferCounter[2]~7\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , !\Port4|DedicatedPort|ChannelAData[0]~3_combout\, 
-- , , \Port4|DedicatedPort|ChannelAData[0]~2_combout\, )
-- \Port4|DedicatedPort|TransferCounter[3]~9\ = CARRY(((!\Port4|DedicatedPort|TransferCounter[2]~7\)) # (!\Port4|DedicatedPort|TransferCounter\(3)))
-- \Port4|DedicatedPort|TransferCounter[3]~9COUT1_14\ = CARRY(((!\Port4|DedicatedPort|TransferCounter[2]~7COUT1_13\)) # (!\Port4|DedicatedPort|TransferCounter\(3)))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|TransferCounter\(3),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ChannelAData[0]~2_combout\,
	ena => \Port4|DedicatedPort|ALT_INV_ChannelAData[0]~3_combout\,
	cin0 => \Port4|DedicatedPort|TransferCounter[2]~7\,
	cin1 => \Port4|DedicatedPort|TransferCounter[2]~7COUT1_13\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|TransferCounter\(3),
	cout0 => \Port4|DedicatedPort|TransferCounter[3]~9\,
	cout1 => \Port4|DedicatedPort|TransferCounter[3]~9COUT1_14\);

-- Location: LC_X4_Y7_N4
\Port4|DedicatedPort|TransferCounter[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|TransferCounter\(4) = DFFEAS(\Port4|DedicatedPort|TransferCounter\(4) $ ((((!\Port4|DedicatedPort|TransferCounter[3]~9\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , !\Port4|DedicatedPort|ChannelAData[0]~3_combout\, 
-- , , \Port4|DedicatedPort|ChannelAData[0]~2_combout\, )

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "a5a5",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|TransferCounter\(4),
	aclr => GND,
	sclr => \Port4|DedicatedPort|ChannelAData[0]~2_combout\,
	ena => \Port4|DedicatedPort|ALT_INV_ChannelAData[0]~3_combout\,
	cin0 => \Port4|DedicatedPort|TransferCounter[3]~9\,
	cin1 => \Port4|DedicatedPort|TransferCounter[3]~9COUT1_14\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|TransferCounter\(4));

-- Location: LC_X4_Y7_N8
\Port4|DedicatedPort|Equal1~0\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|Equal1~0_combout\ = (((!\Port4|DedicatedPort|TransferCounter\(0) & !\Port4|DedicatedPort|TransferCounter\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Port4|DedicatedPort|TransferCounter\(0),
	datad => \Port4|DedicatedPort|TransferCounter\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|Equal1~0_combout\);

-- Location: LC_X4_Y7_N6
\Port4|DedicatedPort|Equal1~1\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|Equal1~1_combout\ = (!\Port4|DedicatedPort|TransferCounter\(3) & (!\Port4|DedicatedPort|TransferCounter\(2) & (\Port4|DedicatedPort|TransferCounter\(4) & \Port4|DedicatedPort|Equal1~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|TransferCounter\(3),
	datab => \Port4|DedicatedPort|TransferCounter\(2),
	datac => \Port4|DedicatedPort|TransferCounter\(4),
	datad => \Port4|DedicatedPort|Equal1~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|Equal1~1_combout\);

-- Location: LC_X4_Y7_N5
\Port4|DedicatedPort|ChannelABuf[14]~18\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\ = (\Port4|DedicatedPort|Config_Reset~regout\) # ((\GlobalReset~regout\) # ((!\Port4|DedicatedPort|Equal1~1_combout\ & !\Port4|DedicatedPort|ADC_RD_CONVST~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff1",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|Equal1~1_combout\,
	datab => \Port4|DedicatedPort|ADC_RD_CONVST~regout\,
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\);

-- Location: LC_X3_Y6_N8
\Port4|DedicatedPort|ChannelBBuf[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(0) = DFFEAS(((\IOPort[4][2]~29\ & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , 
-- )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \IOPort[4][2]~29\,
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(0));

-- Location: LC_X3_Y7_N1
\Port4|DedicatedPort|ChannelBData[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBData\(0) = DFFEAS(GND, !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , \Port4|DedicatedPort|ChannelAData[0]~3_combout\, \Port4|DedicatedPort|ChannelBBuf\(0), , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(0),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBData\(0));

-- Location: LC_X2_Y7_N9
\Port4|DedicatedPort|ChannelABuf[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(0) = DFFEAS((!\GlobalReset~regout\ & (((\IOPort[4][3]~30\ & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , 
-- , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datac => \IOPort[4][3]~30\,
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(0));

-- Location: LC_X2_Y7_N7
\Port4|DedicatedPort|ChannelAData[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux26~0\ = (\FSMCAdd~combout\(0) & ((\Port4|DedicatedPort|ChannelBData\(0)) # ((\FSMCAdd~combout\(1))))) # (!\FSMCAdd~combout\(0) & (((F1_ChannelAData[0] & !\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ccb8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBData\(0),
	datab => \FSMCAdd~combout\(0),
	datac => \Port4|DedicatedPort|ChannelABuf\(0),
	datad => \FSMCAdd~combout\(1),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux26~0\,
	regout => \Port4|DedicatedPort|ChannelAData\(0));

-- Location: LC_X2_Y4_N3
\Port4|GenericPort|Mux26~1\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux26~1_combout\ = (\Port4|GenericPort|Mux26~0\) # ((!\Port4|DedicatedPort|ConvertCounter\(3) & (!\Port4|DedicatedPort|ConvertCounter\(4) & \FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f1f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|ConvertCounter\(3),
	datab => \Port4|DedicatedPort|ConvertCounter\(4),
	datac => \Port4|GenericPort|Mux26~0\,
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux26~1_combout\);

-- Location: LC_X4_Y5_N7
\Port4|GenericPort|Dir[0]~2\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Dir[0]~2_combout\ = ((\FSMCAdd~combout\(1) & (\FSMCAdd~combout\(0) & \Port4|GenericPort|Config_Reset~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCAdd~combout\(0),
	datad => \Port4|GenericPort|Config_Reset~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Dir[0]~2_combout\);

-- Location: LC_X5_Y5_N6
\Port4|GenericPort|Dir[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux26~2\ = (\FSMCAdd~combout\(1) & (((B1_Dir[0] & \FSMCAdd~combout\(0))))) # (!\FSMCAdd~combout\(1) & (\IOPort[4][0]~27\ & ((!\FSMCAdd~combout\(0)))))
-- \Port4|GenericPort|Dir\(0) = DFFEAS(\Port4|GenericPort|Mux26~2\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c022",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \IOPort[4][0]~27\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \FSMCAdd~combout\(0),
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux26~2\,
	regout => \Port4|GenericPort|Dir\(0));

-- Location: LC_X4_Y4_N7
\Port4|GenericPort|Mux26~3\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux26~3_combout\ = (\FSMCAdd~combout\(2) & ((\Port4|GenericPort|Config_Reset~regout\) # ((\DedicatedFunctionUsed~regout\)))) # (!\FSMCAdd~combout\(2) & (((\Port4|GenericPort|Mux26~2\ & !\DedicatedFunctionUsed~regout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aad8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \Port4|GenericPort|Config_Reset~regout\,
	datac => \Port4|GenericPort|Mux26~2\,
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux26~3_combout\);

-- Location: LC_X4_Y4_N4
\Port4|GenericPort|Mux26~4\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux26~4_combout\ = (\Port4|GenericPort|Mux26~3_combout\ & (((\Port4|DedicatedPort|Config_Reset~regout\) # (!\DedicatedFunctionUsed~regout\)))) # (!\Port4|GenericPort|Mux26~3_combout\ & (\Port4|GenericPort|Mux26~1_combout\ & 
-- ((\DedicatedFunctionUsed~regout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e2cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|GenericPort|Mux26~1_combout\,
	datab => \Port4|GenericPort|Mux26~3_combout\,
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux26~4_combout\);

-- Location: LC_X12_Y4_N9
\OutData~16\ : maxii_lcell
-- Equation(s):
-- \OutData~16_combout\ = (\FSMCAdd~combout\(4) & (((\FSMCAdd~combout\(5))))) # (!\FSMCAdd~combout\(4) & ((\FSMCAdd~combout\(5) & ((\Port4|GenericPort|Mux26~4_combout\))) # (!\FSMCAdd~combout\(5) & (\Gen_IOController1:0:PortX|Mux26~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc22",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:0:PortX|Mux26~1_combout\,
	datab => \FSMCAdd~combout\(4),
	datac => \Port4|GenericPort|Mux26~4_combout\,
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~16_combout\);

-- Location: LC_X12_Y4_N7
\OutData~17\ : maxii_lcell
-- Equation(s):
-- \OutData~17_combout\ = (\FSMCAdd~combout\(4) & ((\OutData~16_combout\ & ((\Gen_IOController2:6:PortX|Mux26~1_combout\))) # (!\OutData~16_combout\ & (\Gen_IOController1:2:PortX|Mux26~1_combout\)))) # (!\FSMCAdd~combout\(4) & (((\OutData~16_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f388",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:2:PortX|Mux26~1_combout\,
	datab => \FSMCAdd~combout\(4),
	datac => \Gen_IOController2:6:PortX|Mux26~1_combout\,
	datad => \OutData~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~17_combout\);

-- Location: LC_X12_Y4_N3
\OutData[0]~18\ : maxii_lcell
-- Equation(s):
-- \OutData[0]~18_combout\ = ((\FSMCAdd~combout\(3) & (\OutData~15_combout\)) # (!\FSMCAdd~combout\(3) & ((\OutData~17_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aaf0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData~15_combout\,
	datac => \OutData~17_combout\,
	datad => \FSMCAdd~combout\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[0]~18_combout\);

-- Location: LC_X11_Y7_N6
\ParPort|BufData[0]\ : maxii_lcell
-- Equation(s):
-- \OutData[0]~19\ = (\Equal8~1_combout\ & (((D1_BufData[0])))) # (!\Equal8~1_combout\ & (((\OutData[0]~18_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f5a0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \Equal8~1_combout\,
	datac => \FPGAData~combout\(0),
	datad => \OutData[0]~18_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[0]~19\,
	regout => \ParPort|BufData\(0));

-- Location: LC_X11_Y7_N7
\OutData[0]~20\ : maxii_lcell
-- Equation(s):
-- \OutData[0]~20_combout\ = ((\Equal9~0_combout\ & (\GlobalReset~regout\)) # (!\Equal9~0_combout\ & ((\OutData[0]~19\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ccf0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \GlobalReset~regout\,
	datac => \OutData[0]~19\,
	datad => \Equal9~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[0]~20_combout\);

-- Location: LC_X11_Y7_N8
\CommTestVar[0]\ : maxii_lcell
-- Equation(s):
-- \OutData[0]~21\ = ((\Equal10~1_combout\ & (!CommTestVar[0])) # (!\Equal10~1_combout\ & ((\OutData[0]~20_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3f0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \Equal10~1_combout\,
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \OutData[0]~20_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[0]~21\,
	regout => CommTestVar(0));

-- Location: LC_X12_Y5_N4
\FSMCCtrl|OutDataClk\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|OutDataClk~combout\ = (((!\NOE~combout\ & !\NE~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \NOE~combout\,
	datad => \NE~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|OutDataClk~combout\);

-- Location: LC_X11_Y2_N5
\Gen_IOController2:5:PortX|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|Mux25~0\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\FSMCAdd~combout\(1) & ((B6_Dir[1]))) # (!\FSMCAdd~combout\(1) & (\IOPort[5][1]~19\))))
-- \Gen_IOController2:5:PortX|Dir\(1) = DFFEAS(\Gen_IOController2:5:PortX|Mux25~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c088",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \IOPort[5][1]~19\,
	datab => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:5:PortX|Mux25~0\,
	regout => \Gen_IOController2:5:PortX|Dir\(1));

-- Location: LC_X9_Y6_N2
\Gen_IOController1:1:PortX|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|Mux25~0\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\FSMCAdd~combout\(1) & (B3_Dir[1])) # (!\FSMCAdd~combout\(1) & ((\IOPort[1][1]~55\)))))
-- \Gen_IOController1:1:PortX|Dir\(1) = DFFEAS(\Gen_IOController1:1:PortX|Mux25~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a280",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \IOPort[1][1]~55\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:1:PortX|Mux25~0\,
	regout => \Gen_IOController1:1:PortX|Dir\(1));

-- Location: LC_X11_Y2_N6
\OutData~23\ : maxii_lcell
-- Equation(s):
-- \OutData~23_combout\ = (\FSMCAdd~combout\(5) & ((\FSMCAdd~combout\(4)) # ((\Gen_IOController2:5:PortX|Mux25~0\)))) # (!\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(4) & ((\Gen_IOController1:1:PortX|Mux25~0\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b9a8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(4),
	datac => \Gen_IOController2:5:PortX|Mux25~0\,
	datad => \Gen_IOController1:1:PortX|Mux25~0\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~23_combout\);

-- Location: LC_X8_Y5_N6
\Gen_IOController2:7:PortX|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|Mux25~0\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\FSMCAdd~combout\(1) & ((B8_Dir[1]))) # (!\FSMCAdd~combout\(1) & (\IOPort[7][1]~1\))))
-- \Gen_IOController2:7:PortX|Dir\(1) = DFFEAS(\Gen_IOController2:7:PortX|Mux25~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e400",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(1),
	datab => \IOPort[7][1]~1\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:7:PortX|Mux25~0\,
	regout => \Gen_IOController2:7:PortX|Dir\(1));

-- Location: LC_X9_Y4_N1
\Gen_IOController1:3:PortX|Mux25~0\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|Mux25~0_combout\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\FSMCAdd~combout\(1) & ((\Gen_IOController1:3:PortX|Dir\(1)))) # (!\FSMCAdd~combout\(1) & (\IOPort[3][1]~37\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e200",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[3][1]~37\,
	datab => \FSMCAdd~combout\(1),
	datac => \Gen_IOController1:3:PortX|Dir\(1),
	datad => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:3:PortX|Mux25~0_combout\);

-- Location: LC_X9_Y4_N8
\OutData~24\ : maxii_lcell
-- Equation(s):
-- \OutData~24_combout\ = (\OutData~23_combout\ & ((\Gen_IOController2:7:PortX|Mux25~0\) # ((!\FSMCAdd~combout\(4))))) # (!\OutData~23_combout\ & (((\FSMCAdd~combout\(4) & \Gen_IOController1:3:PortX|Mux25~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "da8a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData~23_combout\,
	datab => \Gen_IOController2:7:PortX|Mux25~0\,
	datac => \FSMCAdd~combout\(4),
	datad => \Gen_IOController1:3:PortX|Mux25~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~24_combout\);

-- Location: LC_X10_Y2_N6
\Gen_IOController2:6:PortX|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|Mux25~0\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\FSMCAdd~combout\(1) & ((B7_Dir[1]))) # (!\FSMCAdd~combout\(1) & (\IOPort[6][1]~10\))))
-- \Gen_IOController2:6:PortX|Dir\(1) = DFFEAS(\Gen_IOController2:6:PortX|Mux25~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a088",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datab => \IOPort[6][1]~10\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController2:6:PortX|Mux25~0\,
	regout => \Gen_IOController2:6:PortX|Dir\(1));

-- Location: LC_X10_Y4_N5
\Gen_IOController1:0:PortX|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|Mux25~0\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\FSMCAdd~combout\(1) & ((B2_Dir[1]))) # (!\FSMCAdd~combout\(1) & (\IOPort[0][1]~64\))))
-- \Gen_IOController1:0:PortX|Dir\(1) = DFFEAS(\Gen_IOController1:0:PortX|Mux25~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a088",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datab => \IOPort[0][1]~64\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:0:PortX|Mux25~0\,
	regout => \Gen_IOController1:0:PortX|Dir\(1));

-- Location: LC_X2_Y7_N6
\Port4|DedicatedPort|ChannelABuf[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(1) = DFFEAS((!\GlobalReset~regout\ & (\Port4|DedicatedPort|ChannelABuf\(0) & ((!\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0044",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datab => \Port4|DedicatedPort|ChannelABuf\(0),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(1));

-- Location: LC_X2_Y5_N9
\Port4|DedicatedPort|ChannelAData[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux25~0\ = (\FSMCAdd~combout\(0) & (((\DedicatedFunctionUsed~regout\)))) # (!\FSMCAdd~combout\(0) & ((\DedicatedFunctionUsed~regout\ & ((F1_ChannelAData[1]))) # (!\DedicatedFunctionUsed~regout\ & (\IOPort[4][1]~28\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc22",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \IOPort[4][1]~28\,
	datab => \FSMCAdd~combout\(0),
	datac => \Port4|DedicatedPort|ChannelABuf\(1),
	datad => \DedicatedFunctionUsed~regout\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux25~0\,
	regout => \Port4|DedicatedPort|ChannelAData\(1));

-- Location: LC_X3_Y6_N5
\Port4|DedicatedPort|ChannelBBuf[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(1) = DFFEAS((\Port4|DedicatedPort|ChannelBBuf\(0) & (((!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBBuf\(0),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(1));

-- Location: LC_X5_Y6_N9
\Port4|DedicatedPort|ChannelBData[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux25~1\ = (\FSMCAdd~combout\(2) & (((!\FSMCAdd~combout\(1))))) # (!\FSMCAdd~combout\(2) & (\FSMCAdd~combout\(0) & ((\FSMCAdd~combout\(1)) # (!F1_ChannelBData[1]))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "338a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelBBuf\(1),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux25~1\,
	regout => \Port4|DedicatedPort|ChannelBData\(1));

-- Location: LC_X4_Y5_N3
\Port4|GenericPort|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux25~2\ = (\Port4|GenericPort|Mux25~0\ & (\Port4|GenericPort|Mux25~1\ $ (((!\FSMCAdd~combout\(1)))))) # (!\Port4|GenericPort|Mux25~0\ & (\Port4|GenericPort|Mux25~1\ & (B1_Dir[1] & \FSMCAdd~combout\(1))))
-- \Port4|GenericPort|Dir\(1) = DFFEAS(\Port4|GenericPort|Mux25~2\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c822",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Port4|GenericPort|Mux25~0\,
	datab => \Port4|GenericPort|Mux25~1\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux25~2\,
	regout => \Port4|GenericPort|Dir\(1));

-- Location: LC_X11_Y2_N9
\OutData~25\ : maxii_lcell
-- Equation(s):
-- \OutData~25_combout\ = (\FSMCAdd~combout\(4) & (((\FSMCAdd~combout\(5))))) # (!\FSMCAdd~combout\(4) & ((\FSMCAdd~combout\(5) & ((\Port4|GenericPort|Mux25~2\))) # (!\FSMCAdd~combout\(5) & (\Gen_IOController1:0:PortX|Mux25~0\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f2c2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:0:PortX|Mux25~0\,
	datab => \FSMCAdd~combout\(4),
	datac => \FSMCAdd~combout\(5),
	datad => \Port4|GenericPort|Mux25~2\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~25_combout\);

-- Location: LC_X7_Y4_N1
\Gen_IOController1:2:PortX|Dir[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|Mux25~0\ = (\Gen_IOController1:3:PortX|Mux26~1_combout\ & ((\FSMCAdd~combout\(1) & ((B4_Dir[1]))) # (!\FSMCAdd~combout\(1) & (\IOPort[2][1]~46\))))
-- \Gen_IOController1:2:PortX|Dir\(1) = DFFEAS(\Gen_IOController1:2:PortX|Mux25~0\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a088",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:3:PortX|Mux26~1_combout\,
	datab => \IOPort[2][1]~46\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:2:PortX|Mux25~0\,
	regout => \Gen_IOController1:2:PortX|Dir\(1));

-- Location: LC_X11_Y2_N7
\OutData~26\ : maxii_lcell
-- Equation(s):
-- \OutData~26_combout\ = (\OutData~25_combout\ & ((\Gen_IOController2:6:PortX|Mux25~0\) # ((!\FSMCAdd~combout\(4))))) # (!\OutData~25_combout\ & (((\Gen_IOController1:2:PortX|Mux25~0\ & \FSMCAdd~combout\(4)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b8cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController2:6:PortX|Mux25~0\,
	datab => \OutData~25_combout\,
	datac => \Gen_IOController1:2:PortX|Mux25~0\,
	datad => \FSMCAdd~combout\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData~26_combout\);

-- Location: LC_X10_Y3_N5
\OutData[1]~27\ : maxii_lcell
-- Equation(s):
-- \OutData[1]~27_combout\ = (!\Equal8~1_combout\ & ((\FSMCAdd~combout\(3) & (\OutData~24_combout\)) # (!\FSMCAdd~combout\(3) & ((\OutData~26_combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00d8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(3),
	datab => \OutData~24_combout\,
	datac => \OutData~26_combout\,
	datad => \Equal8~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[1]~27_combout\);

-- Location: PIN_14,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(1),
	combout => \FPGAData~combout\(1));

-- Location: LC_X5_Y4_N2
\ParPort|BufData[1]\ : maxii_lcell
-- Equation(s):
-- \OutData[1]~22\ = (\Equal8~1_combout\ & (((D1_BufData[1]))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a0a0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \Equal8~1_combout\,
	datac => \FPGAData~combout\(1),
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[1]~22\,
	regout => \ParPort|BufData\(1));

-- Location: LC_X5_Y4_N0
\OutData[1]~28\ : maxii_lcell
-- Equation(s):
-- \OutData[1]~28_combout\ = (\Equal9~0_combout\ & (((\DedicatedFunctionUsed~regout\)))) # (!\Equal9~0_combout\ & ((\OutData[1]~27_combout\) # ((\OutData[1]~22\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f5e4",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => \OutData[1]~27_combout\,
	datac => \DedicatedFunctionUsed~regout\,
	datad => \OutData[1]~22\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[1]~28_combout\);

-- Location: LC_X11_Y7_N3
\CommTestVar[1]\ : maxii_lcell
-- Equation(s):
-- \OutData[1]~29\ = ((\Equal10~1_combout\ & (!CommTestVar[1])) # (!\Equal10~1_combout\ & ((\OutData[1]~28_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3f0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \Equal10~1_combout\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \OutData[1]~28_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[1]~29\,
	regout => CommTestVar(1));

-- Location: LC_X5_Y6_N8
\OutData[8]~31\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~31_combout\ = ((\FSMCAdd~combout\(5) & ((\FSMCAdd~combout\(0)) # (!\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "af00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~31_combout\);

-- Location: LC_X9_Y4_N4
\Gen_IOController1:3:PortX|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[2]~2\ = (!\NE~combout\ & (((\FSMCData[2]~2\))))
-- \Gen_IOController1:3:PortX|Dir\(2) = DFFEAS(\FSMCCtrl|InData[2]~2\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datac => \FSMCData[2]~2\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[2]~2\,
	regout => \Gen_IOController1:3:PortX|Dir\(2));

-- Location: LC_X10_Y6_N1
\Gen_IOController1:1:PortX|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~35\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B3_Dir[2])))
-- \Gen_IOController1:1:PortX|Dir\(2) = DFFEAS(\OutData[2]~35\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[2]~2\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~35\,
	regout => \Gen_IOController1:1:PortX|Dir\(2));

-- Location: LC_X10_Y6_N6
\OutData[2]~36\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~36_combout\ = (\FSMCAdd~combout\(0) & (\OutData[2]~35\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[2]~35\) # (\IOPort[1][2]~56\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "88dc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \OutData[2]~35\,
	datac => \IOPort[1][2]~56\,
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~36_combout\);

-- Location: LC_X12_Y2_N0
\OutData[2]~37\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~37_combout\ = (\OutData[8]~31_combout\ & ((\FSMCAdd~combout\(0)) # ((!\OutData[2]~36_combout\) # (!\IOPort[5][2]~20\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8aaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~31_combout\,
	datab => \FSMCAdd~combout\(0),
	datac => \IOPort[5][2]~20\,
	datad => \OutData[2]~36_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~37_combout\);

-- Location: LC_X12_Y3_N7
\Gen_IOController2:5:PortX|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~38\ = (!\FSMCAdd~combout\(2) & ((\OutData[2]~37_combout\ & (!\OutData[2]~36_combout\ & B6_Dir[2])) # (!\OutData[2]~37_combout\ & (\OutData[2]~36_combout\))))
-- \Gen_IOController2:5:PortX|Dir\(2) = DFFEAS(\OutData[2]~38\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0064",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[2]~37_combout\,
	datab => \OutData[2]~36_combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \FSMCAdd~combout\(2),
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~38\,
	regout => \Gen_IOController2:5:PortX|Dir\(2));

-- Location: LC_X6_Y5_N9
\OutData[2]~30\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~30_combout\ = ((\IOPort[7][2]~2\ & (!\FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0c0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \IOPort[7][2]~2\,
	datac => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~30_combout\);

-- Location: LC_X10_Y6_N4
\OutData[2]~32\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~32_combout\ = (\FSMCAdd~combout\(1) & (\Gen_IOController1:3:PortX|Dir\(2) & (!\FSMCAdd~combout\(5)))) # (!\FSMCAdd~combout\(1) & (((\FSMCAdd~combout\(5)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3838",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:3:PortX|Dir\(2),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~32_combout\);

-- Location: LC_X10_Y6_N2
\OutData[2]~33\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~33_combout\ = (\FSMCAdd~combout\(0) & (\OutData[2]~32_combout\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[2]~32_combout\) # (\IOPort[3][2]~38\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a0ae",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[2]~32_combout\,
	datab => \IOPort[3][2]~38\,
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~33_combout\);

-- Location: LC_X11_Y5_N8
\Gen_IOController2:7:PortX|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~34\ = (\OutData[8]~31_combout\ & ((\OutData[2]~33_combout\ & (\OutData[2]~30_combout\)) # (!\OutData[2]~33_combout\ & ((B8_Dir[2]))))) # (!\OutData[8]~31_combout\ & (((\OutData[2]~33_combout\))))
-- \Gen_IOController2:7:PortX|Dir\(2) = DFFEAS(\OutData[2]~34\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bbc0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[2]~30_combout\,
	datab => \OutData[8]~31_combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \OutData[2]~33_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~34\,
	regout => \Gen_IOController2:7:PortX|Dir\(2));

-- Location: LC_X12_Y7_N3
\OutData[8]~39\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~39_combout\ = (\FSMCAdd~combout\(3) & (((!\FSMCAdd~combout\(2)) # (!\FSMCAdd~combout\(4)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0aaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(3),
	datac => \FSMCAdd~combout\(4),
	datad => \FSMCAdd~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~39_combout\);

-- Location: LC_X7_Y4_N6
\Gen_IOController1:2:PortX|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~42\ = ((\FSMCAdd~combout\(1) & (B4_Dir[2] & !\FSMCAdd~combout\(5))) # (!\FSMCAdd~combout\(1) & ((\FSMCAdd~combout\(5)))))
-- \Gen_IOController1:2:PortX|Dir\(2) = DFFEAS(\OutData[2]~42\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33c0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \FSMCAdd~combout\(5),
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~42\,
	regout => \Gen_IOController1:2:PortX|Dir\(2));

-- Location: LC_X10_Y2_N4
\OutData[2]~43\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~43_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[2]~42\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[2][2]~47\) # (\OutData[2]~42\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bb10",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(1),
	datac => \IOPort[2][2]~47\,
	datad => \OutData[2]~42\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~43_combout\);

-- Location: LC_X10_Y2_N2
\OutData[2]~44\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~44_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\OutData[2]~43_combout\)) # (!\IOPort[6][2]~11\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa2a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~31_combout\,
	datab => \IOPort[6][2]~11\,
	datac => \OutData[2]~43_combout\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~44_combout\);

-- Location: LC_X10_Y2_N5
\Gen_IOController2:6:PortX|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~45\ = (!\FSMCAdd~combout\(2) & ((\OutData[2]~44_combout\ & (B7_Dir[2] & !\OutData[2]~43_combout\)) # (!\OutData[2]~44_combout\ & ((\OutData[2]~43_combout\)))))
-- \Gen_IOController2:6:PortX|Dir\(2) = DFFEAS(\OutData[2]~45\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1140",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(2),
	datab => \OutData[2]~44_combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \OutData[2]~43_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~45\,
	regout => \Gen_IOController2:6:PortX|Dir\(2));

-- Location: LC_X4_Y6_N0
\Equal0~0\ : maxii_lcell
-- Equation(s):
-- \Equal0~0_combout\ = (!\FSMCAdd~combout\(4) & (((!\FSMCAdd~combout\(5)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0055",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(4),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal0~0_combout\);

-- Location: LC_X4_Y6_N9
\OutData[8]~50\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~50_combout\ = ((\FSMCAdd~combout\(4)) # ((!\FSMCAdd~combout\(5) & \FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff30",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(5),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~50_combout\);

-- Location: LC_X2_Y5_N2
\OutData[8]~47\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~47_combout\ = ((\DedicatedFunctionUsed~regout\ & ((\FSMCAdd~combout\(0)))) # (!\DedicatedFunctionUsed~regout\ & (\FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ccaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(0),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~47_combout\);

-- Location: LC_X2_Y5_N1
\OutData[8]~46\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~46_combout\ = ((\DedicatedFunctionUsed~regout\ & ((!\FSMCAdd~combout\(0)) # (!\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7700",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(0),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~46_combout\);

-- Location: LC_X3_Y6_N0
\Port4|DedicatedPort|ChannelBBuf[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(2) = DFFEAS((\Port4|DedicatedPort|ChannelBBuf\(1) & (((!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBBuf\(1),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(2));

-- Location: LC_X2_Y7_N1
\Port4|DedicatedPort|ChannelABuf[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(2) = DFFEAS((!\GlobalReset~regout\ & (\Port4|DedicatedPort|ChannelABuf\(1) & ((!\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0044",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datab => \Port4|DedicatedPort|ChannelABuf\(1),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(2));

-- Location: LC_X2_Y5_N4
\Port4|DedicatedPort|ChannelAData[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~48\ = (!\FSMCAdd~combout\(1) & (!\FSMCAdd~combout\(2) & (F1_ChannelAData[2])))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(2),
	datac => \Port4|DedicatedPort|ChannelABuf\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~48\,
	regout => \Port4|DedicatedPort|ChannelAData\(2));

-- Location: LC_X2_Y5_N5
\Port4|DedicatedPort|ChannelBData[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~49\ = (\OutData[8]~47_combout\ & (((!F1_ChannelBData[2])) # (!\OutData[8]~46_combout\))) # (!\OutData[8]~47_combout\ & (\OutData[8]~46_combout\ & ((!\OutData[2]~48\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "2a6e",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[8]~47_combout\,
	datab => \OutData[8]~46_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(2),
	datad => \OutData[2]~48\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~49\,
	regout => \Port4|DedicatedPort|ChannelBData\(2));

-- Location: LC_X5_Y5_N1
\Port4|GenericPort|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[2]~13\ = (((B1_Dir[2] & !\DedicatedFunctionUsed~regout\)))
-- \Port4|GenericPort|Dir\(2) = DFFEAS(\Port4|GenericPort|IOPort[2]~13\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \DedicatedFunctionUsed~regout\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[2]~13\,
	regout => \Port4|GenericPort|Dir\(2));

-- Location: LC_X3_Y4_N4
\OutData[2]~236\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~236_combout\ = (!\FSMCAdd~combout\(2) & ((\OutData[2]~49\ & (\FSMCAdd~combout\(0) & \Port4|GenericPort|Dir\(2))) # (!\OutData[2]~49\ & (!\FSMCAdd~combout\(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0901",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[2]~49\,
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(2),
	datad => \Port4|GenericPort|Dir\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~236_combout\);

-- Location: LC_X3_Y4_N2
\OutData[2]~237\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~237_combout\ = (\DedicatedFunctionUsed~regout\ & (((!\OutData[2]~49\)))) # (!\DedicatedFunctionUsed~regout\ & (\OutData[2]~236_combout\ & ((\IOPort[4][2]~29\) # (\OutData[2]~49\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0af8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[2]~236_combout\,
	datab => \IOPort[4][2]~29\,
	datac => \DedicatedFunctionUsed~regout\,
	datad => \OutData[2]~49\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~237_combout\);

-- Location: LC_X3_Y4_N3
\OutData[2]~51\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~51_combout\ = (\Equal0~0_combout\ & (((!\OutData[8]~50_combout\)))) # (!\Equal0~0_combout\ & ((\OutData[8]~50_combout\ & (\OutData[2]~45\)) # (!\OutData[8]~50_combout\ & ((\OutData[2]~237_combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "2f2c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[2]~45\,
	datab => \Equal0~0_combout\,
	datac => \OutData[8]~50_combout\,
	datad => \OutData[2]~237_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~51_combout\);

-- Location: LC_X11_Y2_N4
\OutData[8]~41\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~41_combout\ = (!\FSMCAdd~combout\(4) & (!\FSMCAdd~combout\(5) & ((\FSMCAdd~combout\(0)) # (!\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0203",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(4),
	datac => \FSMCAdd~combout\(5),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~41_combout\);

-- Location: LC_X12_Y2_N3
\OutData[2]~40\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~40_combout\ = (!\FSMCAdd~combout\(0) & (((\IOPort[0][2]~65\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datad => \IOPort[0][2]~65\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~40_combout\);

-- Location: LC_X10_Y4_N2
\Gen_IOController1:0:PortX|Dir[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~52\ = (\OutData[2]~51_combout\ & (((\OutData[2]~40_combout\)) # (!\OutData[8]~41_combout\))) # (!\OutData[2]~51_combout\ & (\OutData[8]~41_combout\ & (B2_Dir[2])))
-- \Gen_IOController1:0:PortX|Dir\(2) = DFFEAS(\OutData[2]~52\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea62",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[2]~51_combout\,
	datab => \OutData[8]~41_combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \OutData[2]~40_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~52\,
	regout => \Gen_IOController1:0:PortX|Dir\(2));

-- Location: LC_X12_Y6_N1
\OutData[2]~217\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~217_combout\ = (\OutData[2]~52\ & ((\FSMCAdd~combout\(4)) # ((\FSMCAdd~combout\(5)) # (!\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ef00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(4),
	datab => \FSMCAdd~combout\(5),
	datac => \FSMCAdd~combout\(2),
	datad => \OutData[2]~52\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~217_combout\);

-- Location: LC_X12_Y6_N7
\OutData[8]~53\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~53_combout\ = ((\FSMCAdd~combout\(3) & ((\FSMCAdd~combout\(4)))) # (!\FSMCAdd~combout\(3) & (\Equal8~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc30",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(3),
	datac => \Equal8~1_combout\,
	datad => \FSMCAdd~combout\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~53_combout\);

-- Location: PIN_13,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(2),
	combout => \FPGAData~combout\(2));

-- Location: LC_X12_Y6_N4
\ParPort|BufData[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~54\ = (\OutData[8]~53_combout\ & (((D1_BufData[2] & !\FSMCAdd~combout\(3))))) # (!\OutData[8]~53_combout\ & ((\OutData[2]~217_combout\) # ((\FSMCAdd~combout\(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33e2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \OutData[2]~217_combout\,
	datab => \OutData[8]~53_combout\,
	datac => \FPGAData~combout\(2),
	datad => \FSMCAdd~combout\(3),
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~54\,
	regout => \ParPort|BufData\(2));

-- Location: LC_X11_Y6_N1
\OutData[2]~55\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~55_combout\ = (\OutData[8]~39_combout\ & ((\OutData[2]~54\ & (\OutData[2]~38\)) # (!\OutData[2]~54\ & ((\OutData[2]~34\))))) # (!\OutData[8]~39_combout\ & (((\OutData[2]~54\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "afc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[2]~38\,
	datab => \OutData[2]~34\,
	datac => \OutData[8]~39_combout\,
	datad => \OutData[2]~54\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~55_combout\);

-- Location: LC_X11_Y6_N0
\CommTestVar[2]\ : maxii_lcell
-- Equation(s):
-- \OutData[2]~56\ = (\Equal10~1_combout\ & (((!CommTestVar[2])))) # (!\Equal10~1_combout\ & (!\Equal9~0_combout\ & (\OutData[2]~55_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0f44",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal9~0_combout\,
	datab => \OutData[2]~55_combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \Equal10~1_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[2]~56\,
	regout => CommTestVar(2));

-- Location: LC_X7_Y5_N0
\Gen_IOController1:3:PortX|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[3]~3\ = (!\NE~combout\ & (((\FSMCData[3]~3\))))
-- \Gen_IOController1:3:PortX|Dir\(3) = DFFEAS(\FSMCCtrl|InData[3]~3\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datad => \FSMCData[3]~3\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[3]~3\,
	regout => \Gen_IOController1:3:PortX|Dir\(3));

-- Location: LC_X10_Y6_N0
\OutData[3]~58\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~58_combout\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (\Gen_IOController1:3:PortX|Dir\(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \Gen_IOController1:3:PortX|Dir\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~58_combout\);

-- Location: LC_X10_Y6_N5
\OutData[3]~59\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~59_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[3]~58_combout\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[3][3]~39\) # (\OutData[3]~58_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a0f4",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \IOPort[3][3]~39\,
	datac => \OutData[3]~58_combout\,
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~59_combout\);

-- Location: LC_X6_Y5_N5
\OutData[3]~57\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~57_combout\ = (!\FSMCAdd~combout\(0) & (((\IOPort[7][3]~3\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datac => \IOPort[7][3]~3\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~57_combout\);

-- Location: LC_X11_Y5_N0
\Gen_IOController2:7:PortX|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~60\ = (\OutData[3]~59_combout\ & ((\OutData[3]~57_combout\) # ((!\OutData[8]~31_combout\)))) # (!\OutData[3]~59_combout\ & (((B8_Dir[3] & \OutData[8]~31_combout\))))
-- \Gen_IOController2:7:PortX|Dir\(3) = DFFEAS(\OutData[3]~60\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[3]~3\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d8aa",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[3]~59_combout\,
	datab => \OutData[3]~57_combout\,
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \OutData[8]~31_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~60\,
	regout => \Gen_IOController2:7:PortX|Dir\(3));

-- Location: LC_X9_Y6_N0
\Gen_IOController1:1:PortX|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~61\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B3_Dir[3])))
-- \Gen_IOController1:1:PortX|Dir\(3) = DFFEAS(\OutData[3]~61\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[3]~3\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[3]~3\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~61\,
	regout => \Gen_IOController1:1:PortX|Dir\(3));

-- Location: LC_X10_Y6_N9
\OutData[3]~62\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~62_combout\ = (\FSMCAdd~combout\(0) & (\OutData[3]~61\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[3]~61\) # (\IOPort[1][3]~57\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a0ae",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[3]~61\,
	datab => \IOPort[1][3]~57\,
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~62_combout\);

-- Location: LC_X12_Y2_N5
\OutData[3]~63\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~63_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\IOPort[5][3]~21\)) # (!\OutData[3]~62_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f070",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[3]~62_combout\,
	datab => \IOPort[5][3]~21\,
	datac => \OutData[8]~31_combout\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~63_combout\);

-- Location: LC_X12_Y3_N1
\Gen_IOController2:5:PortX|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~64\ = (!\FSMCAdd~combout\(2) & ((\OutData[3]~62_combout\ & ((!\OutData[3]~63_combout\))) # (!\OutData[3]~62_combout\ & (B6_Dir[3] & \OutData[3]~63_combout\))))
-- \Gen_IOController2:5:PortX|Dir\(3) = DFFEAS(\OutData[3]~64\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[3]~3\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1022",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[3]~62_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \OutData[3]~63_combout\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~64\,
	regout => \Gen_IOController2:5:PortX|Dir\(3));

-- Location: LC_X12_Y2_N4
\OutData[3]~65\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~65_combout\ = (((\IOPort[0][3]~66\ & !\FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \IOPort[0][3]~66\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~65_combout\);

-- Location: LC_X7_Y4_N2
\Gen_IOController1:2:PortX|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~66\ = ((\FSMCAdd~combout\(1) & (B4_Dir[3] & !\FSMCAdd~combout\(5))) # (!\FSMCAdd~combout\(1) & ((\FSMCAdd~combout\(5)))))
-- \Gen_IOController1:2:PortX|Dir\(3) = DFFEAS(\OutData[3]~66\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[3]~3\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33c0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \FSMCAdd~combout\(5),
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~66\,
	regout => \Gen_IOController1:2:PortX|Dir\(3));

-- Location: LC_X8_Y4_N7
\OutData[3]~67\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~67_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[3]~66\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[2][3]~48\) # (\OutData[3]~66\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f302",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[2][3]~48\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCAdd~combout\(0),
	datad => \OutData[3]~66\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~67_combout\);

-- Location: LC_X8_Y4_N5
\OutData[3]~68\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~68_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\OutData[3]~67_combout\)) # (!\IOPort[6][3]~12\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f700",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[6][3]~12\,
	datab => \OutData[3]~67_combout\,
	datac => \FSMCAdd~combout\(0),
	datad => \OutData[8]~31_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~68_combout\);

-- Location: LC_X9_Y5_N2
\Gen_IOController2:6:PortX|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~69\ = (!\FSMCAdd~combout\(2) & ((\OutData[3]~68_combout\ & (B7_Dir[3] & !\OutData[3]~67_combout\)) # (!\OutData[3]~68_combout\ & ((\OutData[3]~67_combout\)))))
-- \Gen_IOController2:6:PortX|Dir\(3) = DFFEAS(\OutData[3]~69\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[3]~3\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1120",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[3]~68_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \OutData[3]~67_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~69\,
	regout => \Gen_IOController2:6:PortX|Dir\(3));

-- Location: LC_X4_Y5_N0
\Port4|GenericPort|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[3]~15\ = (((B1_Dir[3] & !\DedicatedFunctionUsed~regout\)))
-- \Port4|GenericPort|Dir\(3) = DFFEAS(\Port4|GenericPort|IOPort[3]~15\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[3]~3\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \DedicatedFunctionUsed~regout\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[3]~15\,
	regout => \Port4|GenericPort|Dir\(3));

-- Location: LC_X2_Y7_N3
\Port4|DedicatedPort|ChannelABuf[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(3) = DFFEAS((!\GlobalReset~regout\ & (\Port4|DedicatedPort|ChannelABuf\(2) & ((!\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0044",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datab => \Port4|DedicatedPort|ChannelABuf\(2),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(3));

-- Location: LC_X2_Y7_N0
\Port4|DedicatedPort|ChannelAData[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~70\ = (!\FSMCAdd~combout\(2) & (((F1_ChannelAData[3] & !\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(2),
	datac => \Port4|DedicatedPort|ChannelABuf\(3),
	datad => \FSMCAdd~combout\(1),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~70\,
	regout => \Port4|DedicatedPort|ChannelAData\(3));

-- Location: LC_X3_Y6_N2
\Port4|DedicatedPort|ChannelBBuf[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(3) = DFFEAS(((\Port4|DedicatedPort|ChannelBBuf\(2) & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ChannelBBuf\(2),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(3));

-- Location: LC_X3_Y5_N2
\Port4|DedicatedPort|ChannelBData[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~71\ = (\OutData[8]~46_combout\ & ((\OutData[8]~47_combout\ & ((!F1_ChannelBData[3]))) # (!\OutData[8]~47_combout\ & (!\OutData[3]~70\)))) # (!\OutData[8]~46_combout\ & (((\OutData[8]~47_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5f22",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[8]~46_combout\,
	datab => \OutData[3]~70\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(3),
	datad => \OutData[8]~47_combout\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~71\,
	regout => \Port4|DedicatedPort|ChannelBData\(3));

-- Location: LC_X3_Y5_N4
\OutData[3]~234\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~234_combout\ = (!\FSMCAdd~combout\(2) & ((\FSMCAdd~combout\(0) & (\Port4|GenericPort|Dir\(3) & \OutData[3]~71\)) # (!\FSMCAdd~combout\(0) & ((!\OutData[3]~71\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4011",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \FSMCAdd~combout\(0),
	datac => \Port4|GenericPort|Dir\(3),
	datad => \OutData[3]~71\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~234_combout\);

-- Location: LC_X3_Y5_N3
\OutData[3]~235\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~235_combout\ = (\DedicatedFunctionUsed~regout\ & (((!\OutData[3]~71\)))) # (!\DedicatedFunctionUsed~regout\ & (\OutData[3]~234_combout\ & ((\OutData[3]~71\) # (\IOPort[4][3]~30\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33a8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[3]~234_combout\,
	datab => \OutData[3]~71\,
	datac => \IOPort[4][3]~30\,
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~235_combout\);

-- Location: LC_X3_Y4_N1
\OutData[3]~72\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~72_combout\ = (\Equal0~0_combout\ & (((!\OutData[8]~50_combout\)))) # (!\Equal0~0_combout\ & ((\OutData[8]~50_combout\ & (\OutData[3]~69\)) # (!\OutData[8]~50_combout\ & ((\OutData[3]~235_combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "2f2c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[3]~69\,
	datab => \Equal0~0_combout\,
	datac => \OutData[8]~50_combout\,
	datad => \OutData[3]~235_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~72_combout\);

-- Location: LC_X11_Y4_N0
\Gen_IOController1:0:PortX|Dir[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~73\ = (\OutData[8]~41_combout\ & ((\OutData[3]~72_combout\ & (\OutData[3]~65_combout\)) # (!\OutData[3]~72_combout\ & ((B2_Dir[3]))))) # (!\OutData[8]~41_combout\ & (((\OutData[3]~72_combout\))))
-- \Gen_IOController1:0:PortX|Dir\(3) = DFFEAS(\OutData[3]~73\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[3]~3\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bbc0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[3]~65_combout\,
	datab => \OutData[8]~41_combout\,
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \OutData[3]~72_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~73\,
	regout => \Gen_IOController1:0:PortX|Dir\(3));

-- Location: LC_X12_Y6_N6
\OutData[3]~218\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~218_combout\ = (\OutData[3]~73\ & ((\FSMCAdd~combout\(4)) # ((\FSMCAdd~combout\(5)) # (!\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ef00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(4),
	datab => \FSMCAdd~combout\(5),
	datac => \FSMCAdd~combout\(2),
	datad => \OutData[3]~73\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~218_combout\);

-- Location: PIN_12,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(3),
	combout => \FPGAData~combout\(3));

-- Location: LC_X12_Y6_N5
\ParPort|BufData[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~74\ = (\OutData[8]~53_combout\ & (((D1_BufData[3] & !\FSMCAdd~combout\(3))))) # (!\OutData[8]~53_combout\ & ((\OutData[3]~218_combout\) # ((\FSMCAdd~combout\(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33e2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \OutData[3]~218_combout\,
	datab => \OutData[8]~53_combout\,
	datac => \FPGAData~combout\(3),
	datad => \FSMCAdd~combout\(3),
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~74\,
	regout => \ParPort|BufData\(3));

-- Location: LC_X12_Y6_N8
\OutData[3]~75\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~75_combout\ = (\OutData[3]~74\ & (((\OutData[3]~64\) # (!\OutData[8]~39_combout\)))) # (!\OutData[3]~74\ & (\OutData[3]~60\ & ((\OutData[8]~39_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "caf0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[3]~60\,
	datab => \OutData[3]~64\,
	datac => \OutData[3]~74\,
	datad => \OutData[8]~39_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~75_combout\);

-- Location: LC_X11_Y7_N5
\CommTestVar[3]\ : maxii_lcell
-- Equation(s):
-- \OutData[3]~76\ = (\Equal10~1_combout\ & (((!CommTestVar[3])))) # (!\Equal10~1_combout\ & (!\Equal9~0_combout\ & ((\OutData[3]~75_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1b0a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal10~1_combout\,
	datab => \Equal9~0_combout\,
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \OutData[3]~75_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[3]~76\,
	regout => CommTestVar(3));

-- Location: LC_X10_Y3_N4
\OutData[4]~77\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~77_combout\ = (\IOPort[7][4]~4\ & (((!\FSMCAdd~combout\(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[7][4]~4\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~77_combout\);

-- Location: LC_X7_Y5_N6
\Gen_IOController1:3:PortX|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[4]~4\ = ((!\NE~combout\ & ((\FSMCData[4]~4\))))
-- \Gen_IOController1:3:PortX|Dir\(4) = DFFEAS(\FSMCCtrl|InData[4]~4\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3300",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datab => \NE~combout\,
	datad => \FSMCData[4]~4\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[4]~4\,
	regout => \Gen_IOController1:3:PortX|Dir\(4));

-- Location: LC_X5_Y6_N1
\OutData[4]~78\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~78_combout\ = (\FSMCAdd~combout\(5) & (((!\FSMCAdd~combout\(1))))) # (!\FSMCAdd~combout\(5) & (\Gen_IOController1:3:PortX|Dir\(4) & (\FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "2c2c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Gen_IOController1:3:PortX|Dir\(4),
	datab => \FSMCAdd~combout\(5),
	datac => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~78_combout\);

-- Location: LC_X5_Y6_N0
\OutData[4]~79\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~79_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[4]~78_combout\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[3][4]~40\) # (\OutData[4]~78_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "af04",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \IOPort[3][4]~40\,
	datac => \FSMCAdd~combout\(1),
	datad => \OutData[4]~78_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~79_combout\);

-- Location: LC_X11_Y5_N2
\Gen_IOController2:7:PortX|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~80\ = (\OutData[8]~31_combout\ & ((\OutData[4]~79_combout\ & (\OutData[4]~77_combout\)) # (!\OutData[4]~79_combout\ & ((B8_Dir[4]))))) # (!\OutData[8]~31_combout\ & (((\OutData[4]~79_combout\))))
-- \Gen_IOController2:7:PortX|Dir\(4) = DFFEAS(\OutData[4]~80\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bbc0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[4]~77_combout\,
	datab => \OutData[8]~31_combout\,
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \OutData[4]~79_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~80\,
	regout => \Gen_IOController2:7:PortX|Dir\(4));

-- Location: LC_X10_Y6_N3
\Gen_IOController1:1:PortX|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~81\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B3_Dir[4])))
-- \Gen_IOController1:1:PortX|Dir\(4) = DFFEAS(\OutData[4]~81\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[4]~4\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~81\,
	regout => \Gen_IOController1:1:PortX|Dir\(4));

-- Location: LC_X10_Y6_N8
\OutData[4]~82\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~82_combout\ = (\FSMCAdd~combout\(0) & (\OutData[4]~81\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[4]~81\) # (\IOPort[1][4]~58\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a0ae",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[4]~81\,
	datab => \IOPort[1][4]~58\,
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~82_combout\);

-- Location: LC_X12_Y2_N7
\OutData[4]~83\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~83_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\IOPort[5][4]~22\)) # (!\OutData[4]~82_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a2aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~31_combout\,
	datab => \OutData[4]~82_combout\,
	datac => \FSMCAdd~combout\(0),
	datad => \IOPort[5][4]~22\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~83_combout\);

-- Location: LC_X12_Y3_N2
\Gen_IOController2:5:PortX|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~84\ = (!\FSMCAdd~combout\(2) & ((\OutData[4]~82_combout\ & ((!\OutData[4]~83_combout\))) # (!\OutData[4]~82_combout\ & (B6_Dir[4] & \OutData[4]~83_combout\))))
-- \Gen_IOController2:5:PortX|Dir\(4) = DFFEAS(\OutData[4]~84\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1022",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[4]~82_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \OutData[4]~83_combout\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~84\,
	regout => \Gen_IOController2:5:PortX|Dir\(4));

-- Location: PIN_11,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(4),
	combout => \FPGAData~combout\(4));

-- Location: LC_X4_Y5_N6
\Port4|GenericPort|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[4]~17\ = (((B1_Dir[4] & !\DedicatedFunctionUsed~regout\)))
-- \Port4|GenericPort|Dir\(4) = DFFEAS(\Port4|GenericPort|IOPort[4]~17\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \DedicatedFunctionUsed~regout\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[4]~17\,
	regout => \Port4|GenericPort|Dir\(4));

-- Location: LC_X3_Y6_N9
\Port4|DedicatedPort|ChannelBBuf[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(4) = DFFEAS(((\Port4|DedicatedPort|ChannelBBuf\(3) & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ChannelBBuf\(3),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(4));

-- Location: LC_X2_Y7_N2
\Port4|DedicatedPort|ChannelABuf[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(4) = DFFEAS((\Port4|DedicatedPort|ChannelABuf\(3) & (!\Port4|DedicatedPort|Config_Reset~regout\ & ((!\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0022",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelABuf\(3),
	datab => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(4));

-- Location: LC_X2_Y5_N3
\Port4|DedicatedPort|ChannelAData[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~90\ = (!\FSMCAdd~combout\(1) & (!\FSMCAdd~combout\(2) & (F1_ChannelAData[4])))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(2),
	datac => \Port4|DedicatedPort|ChannelABuf\(4),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~90\,
	regout => \Port4|DedicatedPort|ChannelAData\(4));

-- Location: LC_X2_Y5_N0
\Port4|DedicatedPort|ChannelBData[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~91\ = (\OutData[8]~47_combout\ & (((!F1_ChannelBData[4])) # (!\OutData[8]~46_combout\))) # (!\OutData[8]~47_combout\ & (\OutData[8]~46_combout\ & ((!\OutData[4]~90\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "2a6e",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[8]~47_combout\,
	datab => \OutData[8]~46_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(4),
	datad => \OutData[4]~90\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~91\,
	regout => \Port4|DedicatedPort|ChannelBData\(4));

-- Location: LC_X3_Y4_N7
\OutData[4]~232\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~232_combout\ = (!\FSMCAdd~combout\(2) & ((\OutData[4]~91\ & (\Port4|GenericPort|Dir\(4) & \FSMCAdd~combout\(0))) # (!\OutData[4]~91\ & ((!\FSMCAdd~combout\(0))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0803",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|GenericPort|Dir\(4),
	datab => \OutData[4]~91\,
	datac => \FSMCAdd~combout\(2),
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~232_combout\);

-- Location: LC_X3_Y4_N5
\OutData[4]~233\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~233_combout\ = (\DedicatedFunctionUsed~regout\ & (((!\OutData[4]~91\)))) # (!\DedicatedFunctionUsed~regout\ & (\OutData[4]~232_combout\ & ((\IOPort[4][4]~31\) # (\OutData[4]~91\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "30ec",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[4][4]~31\,
	datab => \DedicatedFunctionUsed~regout\,
	datac => \OutData[4]~232_combout\,
	datad => \OutData[4]~91\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~233_combout\);

-- Location: LC_X6_Y4_N7
\Gen_IOController1:2:PortX|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~86\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B4_Dir[4])))
-- \Gen_IOController1:2:PortX|Dir\(4) = DFFEAS(\OutData[4]~86\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[4]~4\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~86\,
	regout => \Gen_IOController1:2:PortX|Dir\(4));

-- Location: LC_X5_Y4_N1
\OutData[4]~87\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~87_combout\ = (\FSMCAdd~combout\(0) & (\OutData[4]~86\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[4]~86\) # (\IOPort[2][4]~49\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa32",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[4]~86\,
	datab => \FSMCAdd~combout\(1),
	datac => \IOPort[2][4]~49\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~87_combout\);

-- Location: LC_X8_Y4_N3
\OutData[4]~88\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~88_combout\ = (\OutData[8]~31_combout\ & ((\FSMCAdd~combout\(0)) # ((!\IOPort[6][4]~13\) # (!\OutData[4]~87_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bf00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \OutData[4]~87_combout\,
	datac => \IOPort[6][4]~13\,
	datad => \OutData[8]~31_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~88_combout\);

-- Location: LC_X8_Y4_N8
\Gen_IOController2:6:PortX|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~89\ = (!\FSMCAdd~combout\(2) & ((\OutData[4]~87_combout\ & ((!\OutData[4]~88_combout\))) # (!\OutData[4]~87_combout\ & (B7_Dir[4] & \OutData[4]~88_combout\))))
-- \Gen_IOController2:6:PortX|Dir\(4) = DFFEAS(\OutData[4]~89\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1044",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(2),
	datab => \OutData[4]~87_combout\,
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \OutData[4]~88_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~89\,
	regout => \Gen_IOController2:6:PortX|Dir\(4));

-- Location: LC_X3_Y4_N8
\OutData[4]~92\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~92_combout\ = (\Equal0~0_combout\ & (((!\OutData[8]~50_combout\)))) # (!\Equal0~0_combout\ & ((\OutData[8]~50_combout\ & ((\OutData[4]~89\))) # (!\OutData[8]~50_combout\ & (\OutData[4]~233_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3e0e",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[4]~233_combout\,
	datab => \Equal0~0_combout\,
	datac => \OutData[8]~50_combout\,
	datad => \OutData[4]~89\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~92_combout\);

-- Location: LC_X10_Y4_N1
\OutData[4]~85\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~85_combout\ = (\IOPort[0][4]~67\ & (((!\FSMCAdd~combout\(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0a0a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[0][4]~67\,
	datac => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~85_combout\);

-- Location: LC_X10_Y4_N6
\Gen_IOController1:0:PortX|Dir[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~93\ = (\OutData[4]~92_combout\ & (((\OutData[4]~85_combout\)) # (!\OutData[8]~41_combout\))) # (!\OutData[4]~92_combout\ & (\OutData[8]~41_combout\ & (B2_Dir[4])))
-- \Gen_IOController1:0:PortX|Dir\(4) = DFFEAS(\OutData[4]~93\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea62",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[4]~92_combout\,
	datab => \OutData[8]~41_combout\,
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \OutData[4]~85_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~93\,
	regout => \Gen_IOController1:0:PortX|Dir\(4));

-- Location: LC_X12_Y7_N6
\OutData[4]~219\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~219_combout\ = (\OutData[4]~93\ & ((\FSMCAdd~combout\(5)) # ((\FSMCAdd~combout\(4)) # (!\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c8cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(5),
	datab => \OutData[4]~93\,
	datac => \FSMCAdd~combout\(4),
	datad => \FSMCAdd~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~219_combout\);

-- Location: LC_X12_Y7_N7
\ParPort|BufData[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~94\ = (\FSMCAdd~combout\(3) & (!\OutData[8]~53_combout\)) # (!\FSMCAdd~combout\(3) & ((\OutData[8]~53_combout\ & (D1_BufData[4])) # (!\OutData[8]~53_combout\ & ((\OutData[4]~219_combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7362",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \FSMCAdd~combout\(3),
	datab => \OutData[8]~53_combout\,
	datac => \FPGAData~combout\(4),
	datad => \OutData[4]~219_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~94\,
	regout => \ParPort|BufData\(4));

-- Location: LC_X12_Y7_N8
\OutData[4]~95\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~95_combout\ = (\OutData[4]~94\ & (((\OutData[4]~84\) # (!\OutData[8]~39_combout\)))) # (!\OutData[4]~94\ & (\OutData[4]~80\ & ((\OutData[8]~39_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "caf0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[4]~80\,
	datab => \OutData[4]~84\,
	datac => \OutData[4]~94\,
	datad => \OutData[8]~39_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~95_combout\);

-- Location: LC_X11_Y7_N4
\CommTestVar[4]\ : maxii_lcell
-- Equation(s):
-- \OutData[4]~96\ = (\Equal10~1_combout\ & (((!CommTestVar[4])))) # (!\Equal10~1_combout\ & (\OutData[4]~95_combout\ & ((!\Equal9~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0a4e",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal10~1_combout\,
	datab => \OutData[4]~95_combout\,
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[4]~96\,
	regout => CommTestVar(4));

-- Location: LC_X7_Y5_N5
\Gen_IOController1:3:PortX|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[5]~5\ = (!\NE~combout\ & (((\FSMCData[5]~5\))))
-- \Gen_IOController1:3:PortX|Dir\(5) = DFFEAS(\FSMCCtrl|InData[5]~5\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datac => \FSMCData[5]~5\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[5]~5\,
	regout => \Gen_IOController1:3:PortX|Dir\(5));

-- Location: LC_X5_Y6_N3
\OutData[5]~98\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~98_combout\ = ((\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & \Gen_IOController1:3:PortX|Dir\(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3c0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(5),
	datac => \FSMCAdd~combout\(1),
	datad => \Gen_IOController1:3:PortX|Dir\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~98_combout\);

-- Location: LC_X5_Y6_N6
\OutData[5]~99\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~99_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[5]~98_combout\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[3][5]~41\) # (\OutData[5]~98_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "af04",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \IOPort[3][5]~41\,
	datac => \FSMCAdd~combout\(1),
	datad => \OutData[5]~98_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~99_combout\);

-- Location: LC_X6_Y5_N4
\OutData[5]~97\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~97_combout\ = (((!\FSMCAdd~combout\(0) & \IOPort[7][5]~5\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0f00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \FSMCAdd~combout\(0),
	datad => \IOPort[7][5]~5\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~97_combout\);

-- Location: LC_X11_Y5_N9
\Gen_IOController2:7:PortX|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~100\ = (\OutData[5]~99_combout\ & ((\OutData[5]~97_combout\) # ((!\OutData[8]~31_combout\)))) # (!\OutData[5]~99_combout\ & (((B8_Dir[5] & \OutData[8]~31_combout\))))
-- \Gen_IOController2:7:PortX|Dir\(5) = DFFEAS(\OutData[5]~100\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d8aa",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[5]~99_combout\,
	datab => \OutData[5]~97_combout\,
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \OutData[8]~31_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~100\,
	regout => \Gen_IOController2:7:PortX|Dir\(5));

-- Location: LC_X12_Y5_N7
\OutData[5]~105\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~105_combout\ = ((!\FSMCAdd~combout\(0) & (\IOPort[0][5]~68\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3030",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(0),
	datac => \IOPort[0][5]~68\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~105_combout\);

-- Location: LC_X2_Y6_N0
\Port4|DedicatedPort|ChannelABuf[5]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(5) = DFFEAS((!\GlobalReset~regout\ & (((\Port4|DedicatedPort|ChannelABuf\(4) & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datac => \Port4|DedicatedPort|ChannelABuf\(4),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(5));

-- Location: LC_X2_Y5_N6
\Port4|DedicatedPort|ChannelAData[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~110\ = (!\FSMCAdd~combout\(1) & (!\FSMCAdd~combout\(2) & (F1_ChannelAData[5])))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(2),
	datac => \Port4|DedicatedPort|ChannelABuf\(5),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~110\,
	regout => \Port4|DedicatedPort|ChannelAData\(5));

-- Location: LC_X3_Y6_N1
\Port4|DedicatedPort|ChannelBBuf[5]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(5) = DFFEAS(((\Port4|DedicatedPort|ChannelBBuf\(4) & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ChannelBBuf\(4),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(5));

-- Location: LC_X3_Y5_N0
\Port4|DedicatedPort|ChannelBData[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~111\ = (\OutData[8]~46_combout\ & ((\OutData[8]~47_combout\ & ((F1_ChannelBData[5]))) # (!\OutData[8]~47_combout\ & (\OutData[5]~110\)))) # (!\OutData[8]~46_combout\ & (((\OutData[8]~47_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f588",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[8]~46_combout\,
	datab => \OutData[5]~110\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(5),
	datad => \OutData[8]~47_combout\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~111\,
	regout => \Port4|DedicatedPort|ChannelBData\(5));

-- Location: LC_X4_Y5_N4
\Port4|GenericPort|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[5]~19\ = (((B1_Dir[5]) # (\DedicatedFunctionUsed~regout\)))
-- \Port4|GenericPort|Dir\(5) = DFFEAS(\Port4|GenericPort|IOPort[5]~19\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \DedicatedFunctionUsed~regout\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[5]~19\,
	regout => \Port4|GenericPort|Dir\(5));

-- Location: LC_X3_Y5_N9
\OutData[5]~230\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~230_combout\ = (!\FSMCAdd~combout\(2) & ((\FSMCAdd~combout\(0) & (\OutData[5]~111\ & \Port4|GenericPort|Dir\(5))) # (!\FSMCAdd~combout\(0) & (!\OutData[5]~111\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4101",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \FSMCAdd~combout\(0),
	datac => \OutData[5]~111\,
	datad => \Port4|GenericPort|Dir\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~230_combout\);

-- Location: LC_X3_Y5_N1
\OutData[5]~231\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~231_combout\ = (\DedicatedFunctionUsed~regout\ & (((\OutData[5]~111\)))) # (!\DedicatedFunctionUsed~regout\ & (\OutData[5]~230_combout\ & ((\IOPort[4][5]~32\) # (\OutData[5]~111\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f4a0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \DedicatedFunctionUsed~regout\,
	datab => \IOPort[4][5]~32\,
	datac => \OutData[5]~111\,
	datad => \OutData[5]~230_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~231_combout\);

-- Location: LC_X6_Y4_N5
\Gen_IOController1:2:PortX|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~106\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B4_Dir[5])))
-- \Gen_IOController1:2:PortX|Dir\(5) = DFFEAS(\OutData[5]~106\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[5]~5\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~106\,
	regout => \Gen_IOController1:2:PortX|Dir\(5));

-- Location: LC_X7_Y6_N7
\OutData[5]~107\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~107_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[5]~106\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[2][5]~50\) # (\OutData[5]~106\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "dd10",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(0),
	datac => \IOPort[2][5]~50\,
	datad => \OutData[5]~106\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~107_combout\);

-- Location: LC_X8_Y4_N4
\OutData[5]~108\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~108_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\OutData[5]~107_combout\)) # (!\IOPort[6][5]~14\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f700",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[6][5]~14\,
	datab => \OutData[5]~107_combout\,
	datac => \FSMCAdd~combout\(0),
	datad => \OutData[8]~31_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~108_combout\);

-- Location: LC_X9_Y5_N5
\Gen_IOController2:6:PortX|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~109\ = (!\FSMCAdd~combout\(2) & ((\OutData[5]~107_combout\ & ((!\OutData[5]~108_combout\))) # (!\OutData[5]~107_combout\ & (B7_Dir[5] & \OutData[5]~108_combout\))))
-- \Gen_IOController2:6:PortX|Dir\(5) = DFFEAS(\OutData[5]~109\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1022",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[5]~107_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \OutData[5]~108_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~109\,
	regout => \Gen_IOController2:6:PortX|Dir\(5));

-- Location: LC_X3_Y4_N6
\OutData[5]~112\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~112_combout\ = (\OutData[8]~50_combout\ & (((\OutData[5]~109\ & !\Equal0~0_combout\)))) # (!\OutData[8]~50_combout\ & ((\OutData[5]~231_combout\) # ((\Equal0~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fca",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[5]~231_combout\,
	datab => \OutData[5]~109\,
	datac => \OutData[8]~50_combout\,
	datad => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~112_combout\);

-- Location: LC_X11_Y4_N6
\Gen_IOController1:0:PortX|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~113\ = (\OutData[8]~41_combout\ & ((\OutData[5]~112_combout\ & (\OutData[5]~105_combout\)) # (!\OutData[5]~112_combout\ & ((B2_Dir[5]))))) # (!\OutData[8]~41_combout\ & (((\OutData[5]~112_combout\))))
-- \Gen_IOController1:0:PortX|Dir\(5) = DFFEAS(\OutData[5]~113\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bbc0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[5]~105_combout\,
	datab => \OutData[8]~41_combout\,
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \OutData[5]~112_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~113\,
	regout => \Gen_IOController1:0:PortX|Dir\(5));

-- Location: LC_X12_Y7_N5
\OutData[5]~220\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~220_combout\ = (\OutData[5]~113\ & ((\FSMCAdd~combout\(5)) # ((\FSMCAdd~combout\(4)) # (!\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fb00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCAdd~combout\(4),
	datad => \OutData[5]~113\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~220_combout\);

-- Location: PIN_8,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(5),
	combout => \FPGAData~combout\(5));

-- Location: LC_X12_Y7_N9
\ParPort|BufData[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~114\ = (\OutData[8]~53_combout\ & (((D1_BufData[5] & !\FSMCAdd~combout\(3))))) # (!\OutData[8]~53_combout\ & ((\OutData[5]~220_combout\) # ((\FSMCAdd~combout\(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33e2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \OutData[5]~220_combout\,
	datab => \OutData[8]~53_combout\,
	datac => \FPGAData~combout\(5),
	datad => \FSMCAdd~combout\(3),
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~114\,
	regout => \ParPort|BufData\(5));

-- Location: LC_X8_Y6_N7
\Gen_IOController1:1:PortX|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~101\ = (\FSMCAdd~combout\(5) & (((!\FSMCAdd~combout\(1))))) # (!\FSMCAdd~combout\(5) & (((B3_Dir[5] & \FSMCAdd~combout\(1)))))
-- \Gen_IOController1:1:PortX|Dir\(5) = DFFEAS(\OutData[5]~101\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "50aa",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~101\,
	regout => \Gen_IOController1:1:PortX|Dir\(5));

-- Location: LC_X8_Y6_N2
\OutData[5]~102\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~102_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[5]~101\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[1][5]~59\) # (\OutData[5]~101\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c0ce",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[1][5]~59\,
	datab => \OutData[5]~101\,
	datac => \FSMCAdd~combout\(0),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~102_combout\);

-- Location: LC_X12_Y3_N3
\OutData[5]~103\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~103_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\OutData[5]~102_combout\)) # (!\IOPort[5][5]~23\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[5][5]~23\,
	datab => \OutData[8]~31_combout\,
	datac => \OutData[5]~102_combout\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~103_combout\);

-- Location: LC_X12_Y3_N0
\Gen_IOController2:5:PortX|Dir[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~104\ = (!\FSMCAdd~combout\(2) & ((\OutData[5]~103_combout\ & (!\OutData[5]~102_combout\ & B6_Dir[5])) # (!\OutData[5]~103_combout\ & (\OutData[5]~102_combout\))))
-- \Gen_IOController2:5:PortX|Dir\(5) = DFFEAS(\OutData[5]~104\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0064",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[5]~103_combout\,
	datab => \OutData[5]~102_combout\,
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \FSMCAdd~combout\(2),
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~104\,
	regout => \Gen_IOController2:5:PortX|Dir\(5));

-- Location: LC_X12_Y7_N4
\OutData[5]~115\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~115_combout\ = (\OutData[5]~114\ & (((\OutData[5]~104\) # (!\OutData[8]~39_combout\)))) # (!\OutData[5]~114\ & (\OutData[5]~100\ & ((\OutData[8]~39_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e2cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[5]~100\,
	datab => \OutData[5]~114\,
	datac => \OutData[5]~104\,
	datad => \OutData[8]~39_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~115_combout\);

-- Location: LC_X11_Y7_N2
\CommTestVar[5]\ : maxii_lcell
-- Equation(s):
-- \OutData[5]~116\ = (\Equal10~1_combout\ & (((!CommTestVar[5])))) # (!\Equal10~1_combout\ & (\OutData[5]~115_combout\ & ((!\Equal9~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0a4e",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal10~1_combout\,
	datab => \OutData[5]~115_combout\,
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[5]~116\,
	regout => CommTestVar(5));

-- Location: LC_X7_Y5_N3
\Gen_IOController1:3:PortX|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[6]~6\ = (!\NE~combout\ & (((\FSMCData[6]~6\))))
-- \Gen_IOController1:3:PortX|Dir\(6) = DFFEAS(\FSMCCtrl|InData[6]~6\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datac => \FSMCData[6]~6\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[6]~6\,
	regout => \Gen_IOController1:3:PortX|Dir\(6));

-- Location: LC_X8_Y6_N5
\Gen_IOController1:1:PortX|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~121\ = (\FSMCAdd~combout\(5) & (((!\FSMCAdd~combout\(1))))) # (!\FSMCAdd~combout\(5) & (((B3_Dir[6] & \FSMCAdd~combout\(1)))))
-- \Gen_IOController1:1:PortX|Dir\(6) = DFFEAS(\OutData[6]~121\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "50aa",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~121\,
	regout => \Gen_IOController1:1:PortX|Dir\(6));

-- Location: LC_X8_Y6_N6
\OutData[6]~122\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~122_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[6]~121\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[1][6]~60\) # (\OutData[6]~121\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bb10",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(1),
	datac => \IOPort[1][6]~60\,
	datad => \OutData[6]~121\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~122_combout\);

-- Location: LC_X12_Y5_N1
\OutData[6]~123\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~123_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\OutData[6]~122_combout\)) # (!\IOPort[5][6]~24\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d0f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[5][6]~24\,
	datab => \FSMCAdd~combout\(0),
	datac => \OutData[8]~31_combout\,
	datad => \OutData[6]~122_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~123_combout\);

-- Location: LC_X12_Y5_N5
\Gen_IOController2:5:PortX|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~124\ = (!\FSMCAdd~combout\(2) & ((\OutData[6]~122_combout\ & ((!\OutData[6]~123_combout\))) # (!\OutData[6]~122_combout\ & (B6_Dir[6] & \OutData[6]~123_combout\))))
-- \Gen_IOController2:5:PortX|Dir\(6) = DFFEAS(\OutData[6]~124\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1044",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(2),
	datab => \OutData[6]~122_combout\,
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \OutData[6]~123_combout\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~124\,
	regout => \Gen_IOController2:5:PortX|Dir\(6));

-- Location: PIN_7,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(6),
	combout => \FPGAData~combout\(6));

-- Location: LC_X3_Y6_N7
\Port4|DedicatedPort|ChannelBBuf[6]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(6) = DFFEAS(((\Port4|DedicatedPort|ChannelBBuf\(5) & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ChannelBBuf\(5),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(6));

-- Location: LC_X2_Y6_N9
\Port4|DedicatedPort|ChannelABuf[6]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(6) = DFFEAS((!\GlobalReset~regout\ & (((\Port4|DedicatedPort|ChannelABuf\(5) & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datac => \Port4|DedicatedPort|ChannelABuf\(5),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(6));

-- Location: LC_X2_Y6_N2
\Port4|DedicatedPort|ChannelAData[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~130\ = ((!\FSMCAdd~combout\(2) & (F1_ChannelAData[6] & !\FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0030",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \FSMCAdd~combout\(2),
	datac => \Port4|DedicatedPort|ChannelABuf\(6),
	datad => \FSMCAdd~combout\(1),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~130\,
	regout => \Port4|DedicatedPort|ChannelAData\(6));

-- Location: LC_X2_Y6_N5
\Port4|DedicatedPort|ChannelBData[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~131\ = (\OutData[8]~46_combout\ & ((\OutData[8]~47_combout\ & (F1_ChannelBData[6])) # (!\OutData[8]~47_combout\ & ((\OutData[6]~130\))))) # (!\OutData[8]~46_combout\ & (\OutData[8]~47_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e6c4",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[8]~46_combout\,
	datab => \OutData[8]~47_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(6),
	datad => \OutData[6]~130\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~131\,
	regout => \Port4|DedicatedPort|ChannelBData\(6));

-- Location: LC_X4_Y5_N5
\Port4|GenericPort|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[6]~21\ = (((B1_Dir[6]) # (\DedicatedFunctionUsed~regout\)))
-- \Port4|GenericPort|Dir\(6) = DFFEAS(\Port4|GenericPort|IOPort[6]~21\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \DedicatedFunctionUsed~regout\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[6]~21\,
	regout => \Port4|GenericPort|Dir\(6));

-- Location: LC_X3_Y5_N5
\OutData[6]~228\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~228_combout\ = (!\FSMCAdd~combout\(2) & ((\FSMCAdd~combout\(0) & (\Port4|GenericPort|Dir\(6) & \OutData[6]~131\)) # (!\FSMCAdd~combout\(0) & ((!\OutData[6]~131\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4011",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \FSMCAdd~combout\(0),
	datac => \Port4|GenericPort|Dir\(6),
	datad => \OutData[6]~131\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~228_combout\);

-- Location: LC_X3_Y5_N6
\OutData[6]~229\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~229_combout\ = (\DedicatedFunctionUsed~regout\ & (\OutData[6]~131\)) # (!\DedicatedFunctionUsed~regout\ & (\OutData[6]~228_combout\ & ((\OutData[6]~131\) # (\IOPort[4][6]~33\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "dc88",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \DedicatedFunctionUsed~regout\,
	datab => \OutData[6]~131\,
	datac => \IOPort[4][6]~33\,
	datad => \OutData[6]~228_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~229_combout\);

-- Location: LC_X6_Y4_N9
\Gen_IOController1:2:PortX|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~126\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B4_Dir[6])))
-- \Gen_IOController1:2:PortX|Dir\(6) = DFFEAS(\OutData[6]~126\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[6]~6\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~126\,
	regout => \Gen_IOController1:2:PortX|Dir\(6));

-- Location: LC_X5_Y4_N6
\OutData[6]~127\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~127_combout\ = (\FSMCAdd~combout\(0) & (\OutData[6]~126\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[6]~126\) # (\IOPort[2][6]~51\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "88ba",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[6]~126\,
	datab => \FSMCAdd~combout\(0),
	datac => \IOPort[2][6]~51\,
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~127_combout\);

-- Location: LC_X8_Y4_N6
\OutData[6]~128\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~128_combout\ = (\OutData[8]~31_combout\ & ((\FSMCAdd~combout\(0)) # ((!\OutData[6]~127_combout\) # (!\IOPort[6][6]~15\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8aaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~31_combout\,
	datab => \FSMCAdd~combout\(0),
	datac => \IOPort[6][6]~15\,
	datad => \OutData[6]~127_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~128_combout\);

-- Location: LC_X9_Y5_N1
\Gen_IOController2:6:PortX|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~129\ = (!\FSMCAdd~combout\(2) & ((\OutData[6]~128_combout\ & (B7_Dir[6] & !\OutData[6]~127_combout\)) # (!\OutData[6]~128_combout\ & ((\OutData[6]~127_combout\)))))
-- \Gen_IOController2:6:PortX|Dir\(6) = DFFEAS(\OutData[6]~129\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1120",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[6]~128_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \OutData[6]~127_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~129\,
	regout => \Gen_IOController2:6:PortX|Dir\(6));

-- Location: LC_X4_Y6_N6
\OutData[6]~132\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~132_combout\ = (\Equal0~0_combout\ & (((!\OutData[8]~50_combout\)))) # (!\Equal0~0_combout\ & ((\OutData[8]~50_combout\ & ((\OutData[6]~129\))) # (!\OutData[8]~50_combout\ & (\OutData[6]~229_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0cfa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[6]~229_combout\,
	datab => \OutData[6]~129\,
	datac => \Equal0~0_combout\,
	datad => \OutData[8]~50_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~132_combout\);

-- Location: LC_X12_Y2_N8
\OutData[6]~125\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~125_combout\ = (((\IOPort[0][6]~69\ & !\FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \IOPort[0][6]~69\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~125_combout\);

-- Location: LC_X11_Y4_N5
\Gen_IOController1:0:PortX|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~133\ = (\OutData[6]~132_combout\ & ((\OutData[6]~125_combout\) # ((!\OutData[8]~41_combout\)))) # (!\OutData[6]~132_combout\ & (((B2_Dir[6] & \OutData[8]~41_combout\))))
-- \Gen_IOController1:0:PortX|Dir\(6) = DFFEAS(\OutData[6]~133\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d8aa",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[6]~132_combout\,
	datab => \OutData[6]~125_combout\,
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \OutData[8]~41_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~133\,
	regout => \Gen_IOController1:0:PortX|Dir\(6));

-- Location: LC_X12_Y7_N1
\OutData[6]~221\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~221_combout\ = (\OutData[6]~133\ & ((\FSMCAdd~combout\(5)) # ((\FSMCAdd~combout\(4)) # (!\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c8cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(5),
	datab => \OutData[6]~133\,
	datac => \FSMCAdd~combout\(4),
	datad => \FSMCAdd~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~221_combout\);

-- Location: LC_X12_Y7_N2
\ParPort|BufData[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~134\ = (\FSMCAdd~combout\(3) & (!\OutData[8]~53_combout\)) # (!\FSMCAdd~combout\(3) & ((\OutData[8]~53_combout\ & (D1_BufData[6])) # (!\OutData[8]~53_combout\ & ((\OutData[6]~221_combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7362",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \FSMCAdd~combout\(3),
	datab => \OutData[8]~53_combout\,
	datac => \FPGAData~combout\(6),
	datad => \OutData[6]~221_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~134\,
	regout => \ParPort|BufData\(6));

-- Location: LC_X4_Y4_N9
\OutData[6]~117\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~117_combout\ = (((\IOPort[7][6]~6\ & !\FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \IOPort[7][6]~6\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~117_combout\);

-- Location: LC_X5_Y6_N2
\OutData[6]~118\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~118_combout\ = ((\FSMCAdd~combout\(1) & (\Gen_IOController1:3:PortX|Dir\(6) & !\FSMCAdd~combout\(5))) # (!\FSMCAdd~combout\(1) & ((\FSMCAdd~combout\(5)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \Gen_IOController1:3:PortX|Dir\(6),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~118_combout\);

-- Location: LC_X5_Y6_N7
\OutData[6]~119\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~119_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[6]~118_combout\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[3][6]~42\) # (\OutData[6]~118_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cf02",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[3][6]~42\,
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(1),
	datad => \OutData[6]~118_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~119_combout\);

-- Location: LC_X11_Y5_N5
\Gen_IOController2:7:PortX|Dir[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~120\ = (\OutData[6]~119_combout\ & ((\OutData[6]~117_combout\) # ((!\OutData[8]~31_combout\)))) # (!\OutData[6]~119_combout\ & (((B8_Dir[6] & \OutData[8]~31_combout\))))
-- \Gen_IOController2:7:PortX|Dir\(6) = DFFEAS(\OutData[6]~120\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b8cc",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[6]~117_combout\,
	datab => \OutData[6]~119_combout\,
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \OutData[8]~31_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~120\,
	regout => \Gen_IOController2:7:PortX|Dir\(6));

-- Location: LC_X11_Y7_N1
\OutData[6]~135\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~135_combout\ = (\OutData[6]~134\ & ((\OutData[6]~124\) # ((!\OutData[8]~39_combout\)))) # (!\OutData[6]~134\ & (((\OutData[8]~39_combout\ & \OutData[6]~120\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bc8c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[6]~124\,
	datab => \OutData[6]~134\,
	datac => \OutData[8]~39_combout\,
	datad => \OutData[6]~120\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~135_combout\);

-- Location: LC_X11_Y7_N9
\CommTestVar[6]\ : maxii_lcell
-- Equation(s):
-- \OutData[6]~136\ = (\Equal10~1_combout\ & (((!CommTestVar[6])))) # (!\Equal10~1_combout\ & (\OutData[6]~135_combout\ & ((!\Equal9~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0a4e",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal10~1_combout\,
	datab => \OutData[6]~135_combout\,
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[6]~136\,
	regout => CommTestVar(6));

-- Location: LC_X7_Y5_N7
\Gen_IOController1:3:PortX|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[7]~7\ = (!\NE~combout\ & (((\FSMCData[7]~7\))))
-- \Gen_IOController1:3:PortX|Dir\(7) = DFFEAS(\FSMCCtrl|InData[7]~7\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datac => \FSMCData[7]~7\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[7]~7\,
	regout => \Gen_IOController1:3:PortX|Dir\(7));

-- Location: LC_X5_Y6_N4
\OutData[7]~138\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~138_combout\ = ((\FSMCAdd~combout\(1) & (\Gen_IOController1:3:PortX|Dir\(7) & !\FSMCAdd~combout\(5))) # (!\FSMCAdd~combout\(1) & ((\FSMCAdd~combout\(5)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \Gen_IOController1:3:PortX|Dir\(7),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~138_combout\);

-- Location: LC_X5_Y6_N5
\OutData[7]~139\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~139_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[7]~138_combout\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[3][7]~43\) # (\OutData[7]~138_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "af04",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \IOPort[3][7]~43\,
	datac => \FSMCAdd~combout\(1),
	datad => \OutData[7]~138_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~139_combout\);

-- Location: LC_X4_Y4_N1
\OutData[7]~137\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~137_combout\ = ((\IOPort[7][7]~7\ & ((!\FSMCAdd~combout\(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \IOPort[7][7]~7\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~137_combout\);

-- Location: LC_X8_Y5_N0
\Gen_IOController2:7:PortX|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~140\ = (\OutData[7]~139_combout\ & (((\OutData[7]~137_combout\)) # (!\OutData[8]~31_combout\))) # (!\OutData[7]~139_combout\ & (\OutData[8]~31_combout\ & (B8_Dir[7])))
-- \Gen_IOController2:7:PortX|Dir\(7) = DFFEAS(\OutData[7]~140\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea62",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[7]~139_combout\,
	datab => \OutData[8]~31_combout\,
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \OutData[7]~137_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~140\,
	regout => \Gen_IOController2:7:PortX|Dir\(7));

-- Location: LC_X9_Y6_N9
\Gen_IOController1:1:PortX|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~141\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B3_Dir[7])))
-- \Gen_IOController1:1:PortX|Dir\(7) = DFFEAS(\OutData[7]~141\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[7]~7\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~141\,
	regout => \Gen_IOController1:1:PortX|Dir\(7));

-- Location: LC_X11_Y6_N5
\OutData[7]~142\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~142_combout\ = (\FSMCAdd~combout\(0) & (\OutData[7]~141\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[7]~141\) # (\IOPort[1][7]~61\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a3a2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[7]~141\,
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCAdd~combout\(0),
	datad => \IOPort[1][7]~61\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~142_combout\);

-- Location: LC_X12_Y2_N6
\OutData[7]~143\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~143_combout\ = (\OutData[8]~31_combout\ & ((\FSMCAdd~combout\(0)) # ((!\IOPort[5][7]~25\) # (!\OutData[7]~142_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8aaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~31_combout\,
	datab => \FSMCAdd~combout\(0),
	datac => \OutData[7]~142_combout\,
	datad => \IOPort[5][7]~25\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~143_combout\);

-- Location: LC_X12_Y3_N6
\Gen_IOController2:5:PortX|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~144\ = (!\FSMCAdd~combout\(2) & ((\OutData[7]~142_combout\ & ((!\OutData[7]~143_combout\))) # (!\OutData[7]~142_combout\ & (B6_Dir[7] & \OutData[7]~143_combout\))))
-- \Gen_IOController2:5:PortX|Dir\(7) = DFFEAS(\OutData[7]~144\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1022",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[7]~142_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \OutData[7]~143_combout\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~144\,
	regout => \Gen_IOController2:5:PortX|Dir\(7));

-- Location: PIN_6,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(7),
	combout => \FPGAData~combout\(7));

-- Location: LC_X11_Y2_N8
\OutData[7]~145\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~145_combout\ = (\IOPort[0][7]~70\ & (((!\FSMCAdd~combout\(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0a0a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[0][7]~70\,
	datac => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~145_combout\);

-- Location: LC_X2_Y6_N3
\Port4|DedicatedPort|ChannelBBuf[7]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(7) = DFFEAS((!\GlobalReset~regout\ & (((\Port4|DedicatedPort|ChannelBBuf\(6) & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(6),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(7));

-- Location: LC_X2_Y6_N1
\Port4|DedicatedPort|ChannelABuf[7]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(7) = DFFEAS((!\GlobalReset~regout\ & (((\Port4|DedicatedPort|ChannelABuf\(6) & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datac => \Port4|DedicatedPort|ChannelABuf\(6),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(7));

-- Location: LC_X2_Y6_N8
\Port4|DedicatedPort|ChannelAData[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~150\ = ((!\FSMCAdd~combout\(2) & (F1_ChannelAData[7] & !\FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0030",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \FSMCAdd~combout\(2),
	datac => \Port4|DedicatedPort|ChannelABuf\(7),
	datad => \FSMCAdd~combout\(1),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~150\,
	regout => \Port4|DedicatedPort|ChannelAData\(7));

-- Location: LC_X2_Y6_N6
\Port4|DedicatedPort|ChannelBData[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~151\ = (\OutData[8]~46_combout\ & ((\OutData[8]~47_combout\ & (!F1_ChannelBData[7])) # (!\OutData[8]~47_combout\ & ((!\OutData[7]~150\))))) # (!\OutData[8]~46_combout\ & (\OutData[8]~47_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4c6e",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[8]~46_combout\,
	datab => \OutData[8]~47_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(7),
	datad => \OutData[7]~150\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~151\,
	regout => \Port4|DedicatedPort|ChannelBData\(7));

-- Location: LC_X4_Y5_N1
\Port4|GenericPort|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[7]~23\ = (((B1_Dir[7]) # (\DedicatedFunctionUsed~regout\)))
-- \Port4|GenericPort|Dir\(7) = DFFEAS(\Port4|GenericPort|IOPort[7]~23\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \DedicatedFunctionUsed~regout\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[7]~23\,
	regout => \Port4|GenericPort|Dir\(7));

-- Location: LC_X3_Y5_N7
\OutData[7]~226\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~226_combout\ = (!\FSMCAdd~combout\(2) & ((\FSMCAdd~combout\(0) & (\Port4|GenericPort|Dir\(7) & \OutData[7]~151\)) # (!\FSMCAdd~combout\(0) & ((!\OutData[7]~151\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4011",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(2),
	datab => \FSMCAdd~combout\(0),
	datac => \Port4|GenericPort|Dir\(7),
	datad => \OutData[7]~151\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~226_combout\);

-- Location: LC_X3_Y5_N8
\OutData[7]~227\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~227_combout\ = (\DedicatedFunctionUsed~regout\ & (((!\OutData[7]~151\)))) # (!\DedicatedFunctionUsed~regout\ & (\OutData[7]~226_combout\ & ((\IOPort[4][7]~34\) # (\OutData[7]~151\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33e0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[4][7]~34\,
	datab => \OutData[7]~151\,
	datac => \OutData[7]~226_combout\,
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~227_combout\);

-- Location: LC_X6_Y4_N8
\Gen_IOController1:2:PortX|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~146\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B4_Dir[7])))
-- \Gen_IOController1:2:PortX|Dir\(7) = DFFEAS(\OutData[7]~146\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[7]~7\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~146\,
	regout => \Gen_IOController1:2:PortX|Dir\(7));

-- Location: LC_X5_Y4_N4
\OutData[7]~147\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~147_combout\ = (\FSMCAdd~combout\(0) & (\OutData[7]~146\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[7]~146\) # (\IOPort[2][7]~52\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "88dc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \OutData[7]~146\,
	datac => \IOPort[2][7]~52\,
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~147_combout\);

-- Location: LC_X5_Y4_N7
\OutData[7]~148\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~148_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\IOPort[6][7]~16\)) # (!\OutData[7]~147_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f070",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[7]~147_combout\,
	datab => \IOPort[6][7]~16\,
	datac => \OutData[8]~31_combout\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~148_combout\);

-- Location: LC_X4_Y5_N2
\Gen_IOController2:6:PortX|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~149\ = (!\FSMCAdd~combout\(2) & ((\OutData[7]~147_combout\ & ((!\OutData[7]~148_combout\))) # (!\OutData[7]~147_combout\ & (B7_Dir[7] & \OutData[7]~148_combout\))))
-- \Gen_IOController2:6:PortX|Dir\(7) = DFFEAS(\OutData[7]~149\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1044",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(2),
	datab => \OutData[7]~147_combout\,
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \OutData[7]~148_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~149\,
	regout => \Gen_IOController2:6:PortX|Dir\(7));

-- Location: LC_X3_Y4_N9
\OutData[7]~152\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~152_combout\ = (\OutData[8]~50_combout\ & (((\OutData[7]~149\ & !\Equal0~0_combout\)))) # (!\OutData[8]~50_combout\ & ((\OutData[7]~227_combout\) # ((\Equal0~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "55e4",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~50_combout\,
	datab => \OutData[7]~227_combout\,
	datac => \OutData[7]~149\,
	datad => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~152_combout\);

-- Location: LC_X11_Y4_N8
\Gen_IOController1:0:PortX|Dir[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~153\ = (\OutData[7]~152_combout\ & ((\OutData[7]~145_combout\) # ((!\OutData[8]~41_combout\)))) # (!\OutData[7]~152_combout\ & (((B2_Dir[7] & \OutData[8]~41_combout\))))
-- \Gen_IOController1:0:PortX|Dir\(7) = DFFEAS(\OutData[7]~153\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b8cc",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[7]~145_combout\,
	datab => \OutData[7]~152_combout\,
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \OutData[8]~41_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~153\,
	regout => \Gen_IOController1:0:PortX|Dir\(7));

-- Location: LC_X12_Y4_N6
\OutData[7]~222\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~222_combout\ = (\OutData[7]~153\ & ((\FSMCAdd~combout\(4)) # ((\FSMCAdd~combout\(5)) # (!\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa8a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[7]~153\,
	datab => \FSMCAdd~combout\(4),
	datac => \FSMCAdd~combout\(2),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~222_combout\);

-- Location: LC_X12_Y6_N9
\ParPort|BufData[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~154\ = (\OutData[8]~53_combout\ & (!\FSMCAdd~combout\(3) & (D1_BufData[7]))) # (!\OutData[8]~53_combout\ & ((\FSMCAdd~combout\(3)) # ((\OutData[7]~222_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7564",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \OutData[8]~53_combout\,
	datab => \FSMCAdd~combout\(3),
	datac => \FPGAData~combout\(7),
	datad => \OutData[7]~222_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~154\,
	regout => \ParPort|BufData\(7));

-- Location: LC_X11_Y6_N9
\OutData[7]~155\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~155_combout\ = (\OutData[8]~39_combout\ & ((\OutData[7]~154\ & ((\OutData[7]~144\))) # (!\OutData[7]~154\ & (\OutData[7]~140\)))) # (!\OutData[8]~39_combout\ & (((\OutData[7]~154\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cfa0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[7]~140\,
	datab => \OutData[7]~144\,
	datac => \OutData[8]~39_combout\,
	datad => \OutData[7]~154\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~155_combout\);

-- Location: LC_X11_Y6_N4
\CommTestVar[7]\ : maxii_lcell
-- Equation(s):
-- \OutData[7]~156\ = (\Equal10~1_combout\ & (((!CommTestVar[7])))) # (!\Equal10~1_combout\ & (!\Equal9~0_combout\ & (\OutData[7]~155_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0f44",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal9~0_combout\,
	datab => \OutData[7]~155_combout\,
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \Equal10~1_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[7]~156\,
	regout => CommTestVar(7));

-- Location: LC_X7_Y5_N2
\Gen_IOController1:3:PortX|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[8]~8\ = (!\NE~combout\ & (((\FSMCData[8]~8\))))
-- \Gen_IOController1:3:PortX|Dir\(8) = DFFEAS(\FSMCCtrl|InData[8]~8\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Gen_IOController1:3:PortX|Dir[8]~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datad => \FSMCData[8]~8\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Gen_IOController1:3:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[8]~8\,
	regout => \Gen_IOController1:3:PortX|Dir\(8));

-- Location: LC_X2_Y6_N4
\Port4|DedicatedPort|ChannelBBuf[8]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(8) = DFFEAS((\Port4|DedicatedPort|ChannelBBuf\(7) & (!\Port4|DedicatedPort|Config_Reset~regout\ & ((!\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0022",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBBuf\(7),
	datab => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(8));

-- Location: LC_X2_Y7_N4
\Port4|DedicatedPort|ChannelABuf[8]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(8) = DFFEAS((!\GlobalReset~regout\ & (\Port4|DedicatedPort|ChannelABuf\(7) & ((!\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0044",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datab => \Port4|DedicatedPort|ChannelABuf\(7),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(8));

-- Location: LC_X2_Y7_N5
\Port4|DedicatedPort|ChannelAData[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~170\ = (!\FSMCAdd~combout\(2) & (((F1_ChannelAData[8] & !\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(2),
	datac => \Port4|DedicatedPort|ChannelABuf\(8),
	datad => \FSMCAdd~combout\(1),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~170\,
	regout => \Port4|DedicatedPort|ChannelAData\(8));

-- Location: LC_X2_Y6_N7
\Port4|DedicatedPort|ChannelBData[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~171\ = (\OutData[8]~46_combout\ & ((\OutData[8]~47_combout\ & (F1_ChannelBData[8])) # (!\OutData[8]~47_combout\ & ((\OutData[8]~170\))))) # (!\OutData[8]~46_combout\ & (\OutData[8]~47_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e6c4",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[8]~46_combout\,
	datab => \OutData[8]~47_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(8),
	datad => \OutData[8]~170\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~171\,
	regout => \Port4|DedicatedPort|ChannelBData\(8));

-- Location: LC_X4_Y5_N8
\Port4|GenericPort|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[8]~25\ = (((B1_Dir[8]) # (\DedicatedFunctionUsed~regout\)))
-- \Port4|GenericPort|Dir\(8) = DFFEAS(\Port4|GenericPort|IOPort[8]~25\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|Dir[0]~2_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \DedicatedFunctionUsed~regout\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|GenericPort|Dir[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[8]~25\,
	regout => \Port4|GenericPort|Dir\(8));

-- Location: LC_X2_Y5_N7
\OutData[8]~224\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~224_combout\ = (!\FSMCAdd~combout\(2) & ((\OutData[8]~171\ & (\FSMCAdd~combout\(0) & \Port4|GenericPort|Dir\(8))) # (!\OutData[8]~171\ & (!\FSMCAdd~combout\(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0091",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~171\,
	datab => \FSMCAdd~combout\(0),
	datac => \Port4|GenericPort|Dir\(8),
	datad => \FSMCAdd~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~224_combout\);

-- Location: LC_X2_Y5_N8
\OutData[8]~225\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~225_combout\ = (\DedicatedFunctionUsed~regout\ & (\OutData[8]~171\)) # (!\DedicatedFunctionUsed~regout\ & (\OutData[8]~224_combout\ & ((\OutData[8]~171\) # (\IOPort[4][8]~35\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aca8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~171\,
	datab => \OutData[8]~224_combout\,
	datac => \DedicatedFunctionUsed~regout\,
	datad => \IOPort[4][8]~35\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~225_combout\);

-- Location: LC_X6_Y4_N3
\Gen_IOController1:2:PortX|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~166\ = (\FSMCAdd~combout\(5) & (!\FSMCAdd~combout\(1))) # (!\FSMCAdd~combout\(5) & (\FSMCAdd~combout\(1) & (B4_Dir[8])))
-- \Gen_IOController1:2:PortX|Dir\(8) = DFFEAS(\OutData[8]~166\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Gen_IOController1:2:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "6262",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[8]~8\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:2:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~166\,
	regout => \Gen_IOController1:2:PortX|Dir\(8));

-- Location: LC_X5_Y4_N5
\OutData[8]~167\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~167_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[8]~166\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[2][8]~53\) # (\OutData[8]~166\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c0f2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[2][8]~53\,
	datab => \FSMCAdd~combout\(0),
	datac => \OutData[8]~166\,
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~167_combout\);

-- Location: LC_X5_Y4_N3
\OutData[8]~168\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~168_combout\ = (\OutData[8]~31_combout\ & ((\FSMCAdd~combout\(0)) # ((!\IOPort[6][8]~17\) # (!\OutData[8]~167_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8aaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~31_combout\,
	datab => \FSMCAdd~combout\(0),
	datac => \OutData[8]~167_combout\,
	datad => \IOPort[6][8]~17\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~168_combout\);

-- Location: LC_X4_Y5_N9
\Gen_IOController2:6:PortX|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~169\ = (!\FSMCAdd~combout\(2) & ((\OutData[8]~168_combout\ & (B7_Dir[8] & !\OutData[8]~167_combout\)) # (!\OutData[8]~168_combout\ & ((\OutData[8]~167_combout\)))))
-- \Gen_IOController2:6:PortX|Dir\(8) = DFFEAS(\OutData[8]~169\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Gen_IOController2:6:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1120",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~168_combout\,
	datab => \FSMCAdd~combout\(2),
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \OutData[8]~167_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:6:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~169\,
	regout => \Gen_IOController2:6:PortX|Dir\(8));

-- Location: LC_X4_Y6_N3
\OutData[8]~172\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~172_combout\ = (\Equal0~0_combout\ & (((!\OutData[8]~50_combout\)))) # (!\Equal0~0_combout\ & ((\OutData[8]~50_combout\ & ((\OutData[8]~169\))) # (!\OutData[8]~50_combout\ & (\OutData[8]~225_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "30ee",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~225_combout\,
	datab => \Equal0~0_combout\,
	datac => \OutData[8]~169\,
	datad => \OutData[8]~50_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~172_combout\);

-- Location: LC_X12_Y2_N1
\OutData[8]~165\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~165_combout\ = (((\IOPort[0][8]~71\ & !\FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \IOPort[0][8]~71\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~165_combout\);

-- Location: LC_X11_Y4_N7
\Gen_IOController1:0:PortX|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~173\ = (\OutData[8]~172_combout\ & ((\OutData[8]~165_combout\) # ((!\OutData[8]~41_combout\)))) # (!\OutData[8]~172_combout\ & (((B2_Dir[8] & \OutData[8]~41_combout\))))
-- \Gen_IOController1:0:PortX|Dir\(8) = DFFEAS(\OutData[8]~173\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Gen_IOController1:0:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d8aa",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~172_combout\,
	datab => \OutData[8]~165_combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \OutData[8]~41_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:0:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~173\,
	regout => \Gen_IOController1:0:PortX|Dir\(8));

-- Location: LC_X12_Y6_N2
\OutData[8]~223\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~223_combout\ = (\OutData[8]~173\ & ((\FSMCAdd~combout\(4)) # ((\FSMCAdd~combout\(5)) # (!\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ef00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(4),
	datab => \FSMCAdd~combout\(5),
	datac => \FSMCAdd~combout\(2),
	datad => \OutData[8]~173\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~223_combout\);

-- Location: PIN_5,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[8]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(8),
	combout => \FPGAData~combout\(8));

-- Location: LC_X12_Y6_N3
\ParPort|BufData[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~174\ = (\OutData[8]~53_combout\ & (((D1_BufData[8] & !\FSMCAdd~combout\(3))))) # (!\OutData[8]~53_combout\ & ((\OutData[8]~223_combout\) # ((\FSMCAdd~combout\(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33e2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \OutData[8]~223_combout\,
	datab => \OutData[8]~53_combout\,
	datac => \FPGAData~combout\(8),
	datad => \FSMCAdd~combout\(3),
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~174\,
	regout => \ParPort|BufData\(8));

-- Location: LC_X8_Y6_N1
\Gen_IOController1:1:PortX|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~161\ = (\FSMCAdd~combout\(5) & (((!\FSMCAdd~combout\(1))))) # (!\FSMCAdd~combout\(5) & (((B3_Dir[8] & \FSMCAdd~combout\(1)))))
-- \Gen_IOController1:1:PortX|Dir\(8) = DFFEAS(\OutData[8]~161\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Gen_IOController1:1:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "50aa",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(5),
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \FSMCAdd~combout\(1),
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController1:1:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~161\,
	regout => \Gen_IOController1:1:PortX|Dir\(8));

-- Location: LC_X8_Y6_N4
\OutData[8]~162\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~162_combout\ = (\FSMCAdd~combout\(0) & (\OutData[8]~161\)) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\OutData[8]~161\) # (\IOPort[1][8]~62\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "88dc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \OutData[8]~161\,
	datac => \IOPort[1][8]~62\,
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~162_combout\);

-- Location: LC_X11_Y6_N6
\OutData[8]~163\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~163_combout\ = (\OutData[8]~31_combout\ & (((\FSMCAdd~combout\(0)) # (!\OutData[8]~162_combout\)) # (!\IOPort[5][8]~26\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c4cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \IOPort[5][8]~26\,
	datab => \OutData[8]~31_combout\,
	datac => \FSMCAdd~combout\(0),
	datad => \OutData[8]~162_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~163_combout\);

-- Location: LC_X11_Y6_N7
\Gen_IOController2:5:PortX|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~164\ = (!\FSMCAdd~combout\(2) & ((\OutData[8]~163_combout\ & (!\OutData[8]~162_combout\ & B6_Dir[8])) # (!\OutData[8]~163_combout\ & (\OutData[8]~162_combout\))))
-- \Gen_IOController2:5:PortX|Dir\(8) = DFFEAS(\OutData[8]~164\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Gen_IOController2:5:PortX|Dir[8]~4_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0064",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~163_combout\,
	datab => \OutData[8]~162_combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \FSMCAdd~combout\(2),
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Gen_IOController2:5:PortX|Dir[8]~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~164\,
	regout => \Gen_IOController2:5:PortX|Dir\(8));

-- Location: LC_X4_Y6_N1
\OutData[8]~158\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~158_combout\ = ((\FSMCAdd~combout\(1) & (\Gen_IOController1:3:PortX|Dir\(8) & !\FSMCAdd~combout\(5))) # (!\FSMCAdd~combout\(1) & ((\FSMCAdd~combout\(5)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \Gen_IOController1:3:PortX|Dir\(8),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~158_combout\);

-- Location: LC_X4_Y6_N5
\OutData[8]~159\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~159_combout\ = (\FSMCAdd~combout\(0) & (((\OutData[8]~158_combout\)))) # (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & ((\IOPort[3][8]~44\) # (\OutData[8]~158_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "af04",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \IOPort[3][8]~44\,
	datac => \FSMCAdd~combout\(1),
	datad => \OutData[8]~158_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~159_combout\);

-- Location: LC_X4_Y4_N0
\OutData[8]~157\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~157_combout\ = (((\IOPort[7][8]~8\ & !\FSMCAdd~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \IOPort[7][8]~8\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~157_combout\);

-- Location: LC_X8_Y5_N9
\Gen_IOController2:7:PortX|Dir[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~160\ = (\OutData[8]~159_combout\ & (((\OutData[8]~157_combout\)) # (!\OutData[8]~31_combout\))) # (!\OutData[8]~159_combout\ & (\OutData[8]~31_combout\ & (B8_Dir[8])))
-- \Gen_IOController2:7:PortX|Dir\(8) = DFFEAS(\OutData[8]~160\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~3_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea62",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~159_combout\,
	datab => \OutData[8]~31_combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \OutData[8]~157_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	sload => VCC,
	ena => \Equal10~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~160\,
	regout => \Gen_IOController2:7:PortX|Dir\(8));

-- Location: LC_X11_Y6_N2
\OutData[8]~175\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~175_combout\ = (\OutData[8]~174\ & (((\OutData[8]~164\)) # (!\OutData[8]~39_combout\))) # (!\OutData[8]~174\ & (\OutData[8]~39_combout\ & ((\OutData[8]~160\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e6a2",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[8]~174\,
	datab => \OutData[8]~39_combout\,
	datac => \OutData[8]~164\,
	datad => \OutData[8]~160\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~175_combout\);

-- Location: LC_X11_Y6_N3
\CommTestVar[8]\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~176\ = (\Equal10~1_combout\ & (((!CommTestVar[8])))) # (!\Equal10~1_combout\ & (!\Equal9~0_combout\ & ((\OutData[8]~175_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1d0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Equal9~0_combout\,
	datab => \Equal10~1_combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \OutData[8]~175_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~176\,
	regout => CommTestVar(8));

-- Location: PIN_4,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[9]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(9),
	combout => \FPGAData~combout\(9));

-- Location: LC_X3_Y7_N0
\ParPort|BufData[9]\ : maxii_lcell
-- Equation(s):
-- \OutData[9]~180\ = (((D1_BufData[9] & !\Equal9~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	datac => \FPGAData~combout\(9),
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[9]~180\,
	regout => \ParPort|BufData\(9));

-- Location: LC_X5_Y7_N8
\OutData[14]~178\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~178_combout\ = \Equal9~0_combout\ $ (((\Equal10~1_combout\ $ (\Equal8~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a55a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datac => \Equal10~1_combout\,
	datad => \Equal8~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~178_combout\);

-- Location: LC_X9_Y7_N6
\Port4|DedicatedPort|InternalReset\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|InternalReset~combout\ = (\Port4|DedicatedPort|Config_Reset~regout\) # (((\GlobalReset~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ffaa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|InternalReset~combout\);

-- Location: LC_X9_Y7_N8
\Port4|DedicatedPort|SendData[15]~2\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData[15]~2_combout\ = (!\FSMCAdd~combout\(0) & (!\FSMCAdd~combout\(1) & (!\FSMCAdd~combout\(2) & \OutData[14]~184\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCAdd~combout\(2),
	datad => \OutData[14]~184\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|DedicatedPort|SendData[15]~2_combout\);

-- Location: LC_X8_Y7_N1
\Port4|DedicatedPort|SendData[9]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[9]~9\ = (!\NE~combout\ & (((\FSMCData[9]~9\))))
-- \Port4|DedicatedPort|SendData\(9) = DFFEAS(\FSMCCtrl|InData[9]~9\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datad => \FSMCData[9]~9\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[9]~9\,
	regout => \Port4|DedicatedPort|SendData\(9));

-- Location: LC_X5_Y7_N3
\OutData[14]~181\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~181_combout\ = (\Equal10~1_combout\ & ((\FSMCAdd~combout\(0)) # (\Equal8~1_combout\ $ (!\Equal9~0_combout\)))) # (!\Equal10~1_combout\ & (\FSMCAdd~combout\(0) & (\Equal8~1_combout\ $ (!\Equal9~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eb82",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Equal10~1_combout\,
	datab => \Equal8~1_combout\,
	datac => \Equal9~0_combout\,
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~181_combout\);

-- Location: LC_X5_Y7_N9
\CommTestVar[9]\ : maxii_lcell
-- Equation(s):
-- \OutData[9]~182\ = (\OutData[14]~178_combout\ & ((\OutData[14]~181_combout\ & ((!CommTestVar[9]))) # (!\OutData[14]~181_combout\ & (\OutData[9]~180\)))) # (!\OutData[14]~178_combout\ & (((\OutData[14]~181_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3f88",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[9]~180\,
	datab => \OutData[14]~178_combout\,
	datac => \FSMCCtrl|InData[9]~9\,
	datad => \OutData[14]~181_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[9]~182\,
	regout => CommTestVar(9));

-- Location: LC_X2_Y7_N8
\Port4|DedicatedPort|ChannelABuf[9]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(9) = DFFEAS((\Port4|DedicatedPort|ChannelABuf\(8) & (!\Port4|DedicatedPort|Config_Reset~regout\ & ((!\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0022",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelABuf\(8),
	datab => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(9));

-- Location: LC_X7_Y6_N9
\Port4|DedicatedPort|ChannelAData[9]\ : maxii_lcell
-- Equation(s):
-- \OutData[9]~177\ = (!\FSMCAdd~combout\(1) & (((F1_ChannelAData[9] & !\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelABuf\(9),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[9]~177\,
	regout => \Port4|DedicatedPort|ChannelAData\(9));

-- Location: LC_X3_Y6_N4
\Port4|DedicatedPort|ChannelBBuf[9]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(9) = DFFEAS(((\Port4|DedicatedPort|ChannelBBuf\(8) & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ChannelBBuf\(8),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(9));

-- Location: LC_X7_Y6_N2
\OutData[14]~179\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~179_combout\ = ((!\OutData[14]~178_combout\ & ((!\FSMCAdd~combout\(0)) # (!\FSMCAdd~combout\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0333",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \OutData[14]~178_combout\,
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCAdd~combout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~179_combout\);

-- Location: LC_X7_Y6_N3
\Port4|DedicatedPort|ChannelBData[9]\ : maxii_lcell
-- Equation(s):
-- \OutData[9]~183\ = (\OutData[9]~182\ & (((F1_ChannelBData[9]) # (!\OutData[14]~179_combout\)))) # (!\OutData[9]~182\ & (\OutData[9]~177\ & ((\OutData[14]~179_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e4aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[9]~182\,
	datab => \OutData[9]~177\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(9),
	datad => \OutData[14]~179_combout\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[9]~183\,
	regout => \Port4|DedicatedPort|ChannelBData\(9));

-- Location: LC_X7_Y6_N8
\OutData[9]~185\ : maxii_lcell
-- Equation(s):
-- \OutData[9]~185_combout\ = (\OutData[9]~183\ & ((\OutData[14]~178_combout\) # ((\OutData[14]~184\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa88",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[9]~183\,
	datab => \OutData[14]~178_combout\,
	datad => \OutData[14]~184\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[9]~185_combout\);

-- Location: LC_X7_Y7_N5
\Port4|DedicatedPort|ChannelABuf[10]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(10) = DFFEAS((!\GlobalReset~regout\ & (((\Port4|DedicatedPort|ChannelABuf\(9) & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \GlobalReset~regout\,
	datac => \Port4|DedicatedPort|ChannelABuf\(9),
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(10));

-- Location: LC_X7_Y6_N5
\Port4|DedicatedPort|ChannelAData[10]\ : maxii_lcell
-- Equation(s):
-- \OutData[10]~186\ = (!\FSMCAdd~combout\(1) & (((F1_ChannelAData[10] & !\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelABuf\(10),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[10]~186\,
	regout => \Port4|DedicatedPort|ChannelAData\(10));

-- Location: LC_X9_Y7_N0
\Port4|DedicatedPort|SendData[10]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[10]~10\ = (!\NE~combout\ & (\FSMCData[10]~10\))
-- \Port4|DedicatedPort|SendData\(10) = DFFEAS(\FSMCCtrl|InData[10]~10\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4444",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datab => \FSMCData[10]~10\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[10]~10\,
	regout => \Port4|DedicatedPort|SendData\(10));

-- Location: PIN_3,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[10]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(10),
	combout => \FPGAData~combout\(10));

-- Location: LC_X3_Y7_N6
\ParPort|BufData[10]\ : maxii_lcell
-- Equation(s):
-- \OutData[10]~187\ = (((D1_BufData[10] & !\Equal9~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	datac => \FPGAData~combout\(10),
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[10]~187\,
	regout => \ParPort|BufData\(10));

-- Location: LC_X5_Y7_N2
\CommTestVar[10]\ : maxii_lcell
-- Equation(s):
-- \OutData[10]~188\ = (\OutData[14]~181_combout\ & (\OutData[14]~178_combout\ & (!CommTestVar[10]))) # (!\OutData[14]~181_combout\ & (((\OutData[10]~187\)) # (!\OutData[14]~178_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5d19",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[14]~181_combout\,
	datab => \OutData[14]~178_combout\,
	datac => \FSMCCtrl|InData[10]~10\,
	datad => \OutData[10]~187\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[10]~188\,
	regout => CommTestVar(10));

-- Location: LC_X3_Y6_N3
\Port4|DedicatedPort|ChannelBBuf[10]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(10) = DFFEAS((\Port4|DedicatedPort|ChannelBBuf\(9) & (((!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBBuf\(9),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(10));

-- Location: LC_X7_Y6_N6
\Port4|DedicatedPort|ChannelBData[10]\ : maxii_lcell
-- Equation(s):
-- \OutData[10]~189\ = (\OutData[10]~188\ & ((\OutData[10]~186\) # ((!\OutData[14]~179_combout\)))) # (!\OutData[10]~188\ & (((F1_ChannelBData[10] & \OutData[14]~179_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b8cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[10]~186\,
	datab => \OutData[10]~188\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(10),
	datad => \OutData[14]~179_combout\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[10]~189\,
	regout => \Port4|DedicatedPort|ChannelBData\(10));

-- Location: LC_X7_Y6_N4
\OutData[10]~190\ : maxii_lcell
-- Equation(s):
-- \OutData[10]~190_combout\ = (\OutData[10]~189\ & (((\OutData[14]~178_combout\) # (\OutData[14]~184\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aaa0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \OutData[10]~189\,
	datac => \OutData[14]~178_combout\,
	datad => \OutData[14]~184\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[10]~190_combout\);

-- Location: LC_X7_Y7_N2
\Port4|DedicatedPort|ChannelABuf[11]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(11) = DFFEAS((\Port4|DedicatedPort|ChannelABuf\(10) & (((!\GlobalReset~regout\ & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelABuf\(10),
	datac => \GlobalReset~regout\,
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(11));

-- Location: LC_X6_Y7_N5
\Port4|DedicatedPort|ChannelAData[11]\ : maxii_lcell
-- Equation(s):
-- \OutData[11]~191\ = (!\FSMCAdd~combout\(1) & (((F1_ChannelAData[11] & !\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelABuf\(11),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[11]~191\,
	regout => \Port4|DedicatedPort|ChannelAData\(11));

-- Location: LC_X3_Y6_N6
\Port4|DedicatedPort|ChannelBBuf[11]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(11) = DFFEAS((\Port4|DedicatedPort|ChannelBBuf\(10) & (((!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBBuf\(10),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(11));

-- Location: LC_X8_Y7_N5
\Port4|DedicatedPort|SendData[11]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[11]~11\ = (!\NE~combout\ & (((\FSMCData[11]~11\))))
-- \Port4|DedicatedPort|SendData\(11) = DFFEAS(\FSMCCtrl|InData[11]~11\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datad => \FSMCData[11]~11\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[11]~11\,
	regout => \Port4|DedicatedPort|SendData\(11));

-- Location: PIN_2,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[11]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(11),
	combout => \FPGAData~combout\(11));

-- Location: LC_X3_Y7_N4
\ParPort|BufData[11]\ : maxii_lcell
-- Equation(s):
-- \OutData[11]~192\ = (((D1_BufData[11] & !\Equal9~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	datac => \FPGAData~combout\(11),
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[11]~192\,
	regout => \ParPort|BufData\(11));

-- Location: LC_X5_Y7_N4
\CommTestVar[11]\ : maxii_lcell
-- Equation(s):
-- \OutData[11]~193\ = (\OutData[14]~178_combout\ & ((\OutData[14]~181_combout\ & (!CommTestVar[11])) # (!\OutData[14]~181_combout\ & ((\OutData[11]~192\))))) # (!\OutData[14]~178_combout\ & (!\OutData[14]~181_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3b19",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[14]~178_combout\,
	datab => \OutData[14]~181_combout\,
	datac => \FSMCCtrl|InData[11]~11\,
	datad => \OutData[11]~192\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[11]~193\,
	regout => CommTestVar(11));

-- Location: LC_X6_Y7_N1
\Port4|DedicatedPort|ChannelBData[11]\ : maxii_lcell
-- Equation(s):
-- \OutData[11]~194\ = (\OutData[14]~179_combout\ & ((\OutData[11]~193\ & (\OutData[11]~191\)) # (!\OutData[11]~193\ & ((F1_ChannelBData[11]))))) # (!\OutData[14]~179_combout\ & (((\OutData[11]~193\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bbc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[11]~191\,
	datab => \OutData[14]~179_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(11),
	datad => \OutData[11]~193\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[11]~194\,
	regout => \Port4|DedicatedPort|ChannelBData\(11));

-- Location: LC_X7_Y6_N0
\OutData[11]~195\ : maxii_lcell
-- Equation(s):
-- \OutData[11]~195_combout\ = ((\OutData[11]~194\ & ((\OutData[14]~178_combout\) # (\OutData[14]~184\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0c0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \OutData[14]~178_combout\,
	datac => \OutData[11]~194\,
	datad => \OutData[14]~184\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[11]~195_combout\);

-- Location: PIN_1,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[12]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(12),
	combout => \FPGAData~combout\(12));

-- Location: LC_X3_Y7_N5
\ParPort|BufData[12]\ : maxii_lcell
-- Equation(s):
-- \OutData[12]~197\ = (((D1_BufData[12] & !\Equal9~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	datac => \FPGAData~combout\(12),
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[12]~197\,
	regout => \ParPort|BufData\(12));

-- Location: LC_X8_Y7_N7
\Port4|DedicatedPort|SendData[12]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[12]~12\ = (!\NE~combout\ & (((\FSMCData[12]~12\))))
-- \Port4|DedicatedPort|SendData\(12) = DFFEAS(\FSMCCtrl|InData[12]~12\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datad => \FSMCData[12]~12\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[12]~12\,
	regout => \Port4|DedicatedPort|SendData\(12));

-- Location: LC_X5_Y7_N5
\CommTestVar[12]\ : maxii_lcell
-- Equation(s):
-- \OutData[12]~198\ = (\OutData[14]~181_combout\ & (((!CommTestVar[12] & \OutData[14]~178_combout\)))) # (!\OutData[14]~181_combout\ & ((\OutData[12]~197\) # ((!\OutData[14]~178_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4e55",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[14]~181_combout\,
	datab => \OutData[12]~197\,
	datac => \FSMCCtrl|InData[12]~12\,
	datad => \OutData[14]~178_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[12]~198\,
	regout => CommTestVar(12));

-- Location: LC_X6_Y7_N2
\Port4|DedicatedPort|ChannelBBuf[12]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(12) = DFFEAS((!\Port4|DedicatedPort|Config_Reset~regout\ & (((!\GlobalReset~regout\ & \Port4|DedicatedPort|ChannelBBuf\(11))))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0500",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Config_Reset~regout\,
	datac => \GlobalReset~regout\,
	datad => \Port4|DedicatedPort|ChannelBBuf\(11),
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(12));

-- Location: LC_X6_Y7_N3
\Port4|DedicatedPort|ChannelABuf[12]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(12) = DFFEAS((!\Port4|DedicatedPort|Config_Reset~regout\ & (\Port4|DedicatedPort|ChannelABuf\(11) & (!\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0404",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Config_Reset~regout\,
	datab => \Port4|DedicatedPort|ChannelABuf\(11),
	datac => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(12));

-- Location: LC_X6_Y7_N8
\Port4|DedicatedPort|ChannelAData[12]\ : maxii_lcell
-- Equation(s):
-- \OutData[12]~196\ = (!\FSMCAdd~combout\(1) & (((F1_ChannelAData[12] & !\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelABuf\(12),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[12]~196\,
	regout => \Port4|DedicatedPort|ChannelAData\(12));

-- Location: LC_X6_Y7_N4
\Port4|DedicatedPort|ChannelBData[12]\ : maxii_lcell
-- Equation(s):
-- \OutData[12]~199\ = (\OutData[12]~198\ & (((\OutData[12]~196\)) # (!\OutData[14]~179_combout\))) # (!\OutData[12]~198\ & (\OutData[14]~179_combout\ & (F1_ChannelBData[12])))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea62",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[12]~198\,
	datab => \OutData[14]~179_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(12),
	datad => \OutData[12]~196\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[12]~199\,
	regout => \Port4|DedicatedPort|ChannelBData\(12));

-- Location: LC_X7_Y7_N6
\OutData[12]~200\ : maxii_lcell
-- Equation(s):
-- \OutData[12]~200_combout\ = ((\OutData[12]~199\ & ((\OutData[14]~184\) # (\OutData[14]~178_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \OutData[14]~184\,
	datac => \OutData[14]~178_combout\,
	datad => \OutData[12]~199\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[12]~200_combout\);

-- Location: PIN_144,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[13]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(13),
	combout => \FPGAData~combout\(13));

-- Location: LC_X3_Y7_N8
\ParPort|BufData[13]\ : maxii_lcell
-- Equation(s):
-- \OutData[13]~202\ = (((D1_BufData[13] & !\Equal9~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	datac => \FPGAData~combout\(13),
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[13]~202\,
	regout => \ParPort|BufData\(13));

-- Location: LC_X8_Y7_N2
\Port4|DedicatedPort|SendData[13]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[13]~13\ = (!\NE~combout\ & (((\FSMCData[13]~13\))))
-- \Port4|DedicatedPort|SendData\(13) = DFFEAS(\FSMCCtrl|InData[13]~13\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5500",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datad => \FSMCData[13]~13\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[13]~13\,
	regout => \Port4|DedicatedPort|SendData\(13));

-- Location: LC_X5_Y7_N0
\CommTestVar[13]\ : maxii_lcell
-- Equation(s):
-- \OutData[13]~203\ = (\OutData[14]~181_combout\ & (((!CommTestVar[13] & \OutData[14]~178_combout\)))) # (!\OutData[14]~181_combout\ & ((\OutData[13]~202\) # ((!\OutData[14]~178_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4e55",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[14]~181_combout\,
	datab => \OutData[13]~202\,
	datac => \FSMCCtrl|InData[13]~13\,
	datad => \OutData[14]~178_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[13]~203\,
	regout => CommTestVar(13));

-- Location: LC_X6_Y7_N6
\Port4|DedicatedPort|ChannelABuf[13]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(13) = DFFEAS((!\Port4|DedicatedPort|Config_Reset~regout\ & (((!\GlobalReset~regout\ & \Port4|DedicatedPort|ChannelABuf\(12))))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0500",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Config_Reset~regout\,
	datac => \GlobalReset~regout\,
	datad => \Port4|DedicatedPort|ChannelABuf\(12),
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(13));

-- Location: LC_X6_Y7_N9
\Port4|DedicatedPort|ChannelAData[13]\ : maxii_lcell
-- Equation(s):
-- \OutData[13]~201\ = (!\FSMCAdd~combout\(1) & (((F1_ChannelAData[13] & !\FSMCAdd~combout\(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelABuf\(13),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[13]~201\,
	regout => \Port4|DedicatedPort|ChannelAData\(13));

-- Location: LC_X6_Y7_N0
\Port4|DedicatedPort|ChannelBBuf[13]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(13) = DFFEAS(((\Port4|DedicatedPort|ChannelBBuf\(12) & (!\GlobalReset~regout\ & !\Port4|DedicatedPort|Config_Reset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ChannelBBuf\(12),
	datac => \GlobalReset~regout\,
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(13));

-- Location: LC_X6_Y7_N7
\Port4|DedicatedPort|ChannelBData[13]\ : maxii_lcell
-- Equation(s):
-- \OutData[13]~204\ = (\OutData[13]~203\ & ((\OutData[13]~201\) # ((!\OutData[14]~179_combout\)))) # (!\OutData[13]~203\ & (((F1_ChannelBData[13] & \OutData[14]~179_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d8aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[13]~203\,
	datab => \OutData[13]~201\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(13),
	datad => \OutData[14]~179_combout\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[13]~204\,
	regout => \Port4|DedicatedPort|ChannelBData\(13));

-- Location: LC_X7_Y6_N1
\OutData[13]~205\ : maxii_lcell
-- Equation(s):
-- \OutData[13]~205_combout\ = ((\OutData[13]~204\ & ((\OutData[14]~178_combout\) # (\OutData[14]~184\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ccc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \OutData[13]~204\,
	datac => \OutData[14]~178_combout\,
	datad => \OutData[14]~184\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[13]~205_combout\);

-- Location: PIN_143,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[14]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(14),
	combout => \FPGAData~combout\(14));

-- Location: LC_X3_Y7_N2
\ParPort|BufData[14]\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~207\ = (((D1_BufData[14] & !\Equal9~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	datac => \FPGAData~combout\(14),
	datad => \Equal9~0_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~207\,
	regout => \ParPort|BufData\(14));

-- Location: LC_X9_Y7_N2
\Port4|DedicatedPort|SendData[14]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[14]~14\ = (!\NE~combout\ & (((\FSMCData[14]~14\))))
-- \Port4|DedicatedPort|SendData\(14) = DFFEAS(\FSMCCtrl|InData[14]~14\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datac => \FSMCData[14]~14\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[14]~14\,
	regout => \Port4|DedicatedPort|SendData\(14));

-- Location: LC_X5_Y7_N1
\CommTestVar[14]\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~208\ = (\OutData[14]~181_combout\ & (((!CommTestVar[14] & \OutData[14]~178_combout\)))) # (!\OutData[14]~181_combout\ & ((\OutData[14]~207\) # ((!\OutData[14]~178_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4e55",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[14]~181_combout\,
	datab => \OutData[14]~207\,
	datac => \FSMCCtrl|InData[14]~14\,
	datad => \OutData[14]~178_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~208\,
	regout => CommTestVar(14));

-- Location: LC_X6_Y6_N4
\Port4|DedicatedPort|ChannelBBuf[14]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(14) = DFFEAS((\Port4|DedicatedPort|ChannelBBuf\(13) & (((!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBBuf\(13),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(14));

-- Location: LC_X6_Y6_N7
\Port4|DedicatedPort|ChannelABuf[14]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(14) = DFFEAS((\Port4|DedicatedPort|ChannelABuf\(13) & (((!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelABuf\(13),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(14));

-- Location: LC_X6_Y6_N1
\Port4|DedicatedPort|ChannelAData[14]\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~206\ = ((!\FSMCAdd~combout\(1) & (F1_ChannelAData[14] & !\FSMCAdd~combout\(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0030",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelABuf\(14),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~206\,
	regout => \Port4|DedicatedPort|ChannelAData\(14));

-- Location: LC_X6_Y6_N8
\Port4|DedicatedPort|ChannelBData[14]\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~209\ = (\OutData[14]~208\ & (((\OutData[14]~206\)) # (!\OutData[14]~179_combout\))) # (!\OutData[14]~208\ & (\OutData[14]~179_combout\ & (F1_ChannelBData[14])))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ea62",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[14]~208\,
	datab => \OutData[14]~179_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(14),
	datad => \OutData[14]~206\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~209\,
	regout => \Port4|DedicatedPort|ChannelBData\(14));

-- Location: LC_X6_Y6_N9
\OutData[14]~210\ : maxii_lcell
-- Equation(s):
-- \OutData[14]~210_combout\ = ((\OutData[14]~209\ & ((\OutData[14]~184\) # (\OutData[14]~178_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \OutData[14]~184\,
	datac => \OutData[14]~178_combout\,
	datad => \OutData[14]~209\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[14]~210_combout\);

-- Location: LC_X6_Y6_N6
\Port4|DedicatedPort|ChannelABuf[15]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelABuf\(15) = DFFEAS(((\Port4|DedicatedPort|ChannelABuf\(14) & (!\Port4|DedicatedPort|Config_Reset~regout\ & !\GlobalReset~regout\))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \Port4|DedicatedPort|ChannelABuf\(14),
	datac => \Port4|DedicatedPort|Config_Reset~regout\,
	datad => \GlobalReset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelABuf\(15));

-- Location: LC_X6_Y6_N3
\Port4|DedicatedPort|ChannelAData[15]\ : maxii_lcell
-- Equation(s):
-- \OutData[15]~211\ = ((!\FSMCAdd~combout\(1) & (F1_ChannelAData[15] & !\FSMCAdd~combout\(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0030",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	datab => \FSMCAdd~combout\(1),
	datac => \Port4|DedicatedPort|ChannelABuf\(15),
	datad => \FSMCAdd~combout\(2),
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[15]~211\,
	regout => \Port4|DedicatedPort|ChannelAData\(15));

-- Location: LC_X6_Y6_N5
\Port4|DedicatedPort|ChannelBBuf[15]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ChannelBBuf\(15) = DFFEAS((\Port4|DedicatedPort|ChannelBBuf\(14) & (((!\GlobalReset~regout\ & !\Port4|DedicatedPort|Config_Reset~regout\)))), !GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , 
-- \Port4|DedicatedPort|ChannelABuf[14]~18_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \Port4|DedicatedPort|ChannelBBuf\(14),
	datac => \GlobalReset~regout\,
	datad => \Port4|DedicatedPort|Config_Reset~regout\,
	aclr => GND,
	ena => \Port4|DedicatedPort|ChannelABuf[14]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ChannelBBuf\(15));

-- Location: PIN_142,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: Default
\FPGAData[15]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_FPGAData(15),
	combout => \FPGAData~combout\(15));

-- Location: LC_X5_Y7_N7
\ParPort|BufData[15]\ : maxii_lcell
-- Equation(s):
-- \OutData[15]~212\ = (!\Equal9~0_combout\ & (((D1_BufData[15]))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5050",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \ParPort|InternalClk~combout\,
	dataa => \Equal9~0_combout\,
	datac => \FPGAData~combout\(15),
	aclr => \GlobalReset~regout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[15]~212\,
	regout => \ParPort|BufData\(15));

-- Location: LC_X9_Y7_N4
\Port4|DedicatedPort|SendData[15]\ : maxii_lcell
-- Equation(s):
-- \FSMCCtrl|InData[15]~15\ = (!\NE~combout\ & (\FSMCData[15]~15\))
-- \Port4|DedicatedPort|SendData\(15) = DFFEAS(\FSMCCtrl|InData[15]~15\, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4444",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \NE~combout\,
	datab => \FSMCData[15]~15\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \FSMCCtrl|InData[15]~15\,
	regout => \Port4|DedicatedPort|SendData\(15));

-- Location: LC_X5_Y7_N6
\CommTestVar[15]\ : maxii_lcell
-- Equation(s):
-- \OutData[15]~213\ = (\OutData[14]~178_combout\ & ((\OutData[14]~181_combout\ & ((!CommTestVar[15]))) # (!\OutData[14]~181_combout\ & (\OutData[15]~212\)))) # (!\OutData[14]~178_combout\ & (((\OutData[14]~181_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5f88",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[14]~178_combout\,
	datab => \OutData[15]~212\,
	datac => \FSMCCtrl|InData[15]~15\,
	datad => \OutData[14]~181_combout\,
	aclr => \GlobalReset~regout\,
	sload => VCC,
	ena => \Equal10~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[15]~213\,
	regout => CommTestVar(15));

-- Location: LC_X6_Y6_N0
\Port4|DedicatedPort|ChannelBData[15]\ : maxii_lcell
-- Equation(s):
-- \OutData[15]~214\ = (\OutData[14]~179_combout\ & ((\OutData[15]~213\ & ((F1_ChannelBData[15]))) # (!\OutData[15]~213\ & (\OutData[15]~211\)))) # (!\OutData[14]~179_combout\ & (((\OutData[15]~213\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f388",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ALT_INV_ClkOut~regout\,
	dataa => \OutData[15]~211\,
	datab => \OutData[14]~179_combout\,
	datac => \Port4|DedicatedPort|ChannelBBuf\(15),
	datad => \OutData[15]~213\,
	aclr => GND,
	sload => VCC,
	ena => \Port4|DedicatedPort|ChannelAData[0]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[15]~214\,
	regout => \Port4|DedicatedPort|ChannelBData\(15));

-- Location: LC_X6_Y6_N2
\OutData[15]~215\ : maxii_lcell
-- Equation(s):
-- \OutData[15]~215_combout\ = ((\OutData[15]~214\ & ((\OutData[14]~178_combout\) # (\OutData[14]~184\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ccc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \OutData[15]~214\,
	datac => \OutData[14]~178_combout\,
	datad => \OutData[14]~184\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[15]~215_combout\);

-- Location: LC_X10_Y2_N8
\OutData[8]~216\ : maxii_lcell
-- Equation(s):
-- \OutData[8]~216_combout\ = (((\FSMCAdd~combout\(2)) # (\FSMCAdd~combout\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \FSMCAdd~combout\(2),
	datad => \FSMCAdd~combout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \OutData[8]~216_combout\);

-- Location: LC_X12_Y5_N2
\Gen_IOController1:0:PortX|OutputData[0]~0\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData[0]~0_combout\ = ((\FSMCAdd~combout\(0)) # ((\FSMCAdd~combout\(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fcfc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\);

-- Location: LC_X8_Y5_N2
\Gen_IOController2:7:PortX|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(0) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(0) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[0]~0\)))) # (!\Gen_IOController2:7:PortX|OutputData\(0) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[0]~0\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "de50",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \Gen_IOController2:7:PortX|OutputData\(0),
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(0));

-- Location: LC_X8_Y5_N4
\Gen_IOController2:7:PortX|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(1) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(1) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[1]~1\)))) # (!\Gen_IOController2:7:PortX|OutputData\(1) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[1]~1\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d5e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \Gen_IOController2:7:PortX|OutputData\(1),
	datad => \FSMCCtrl|InData[1]~1\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(1));

-- Location: LC_X8_Y5_N7
\Gen_IOController2:7:PortX|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(2) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(2) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[2]~2\)))) # (!\Gen_IOController2:7:PortX|OutputData\(2) 
-- & (!\OutData[8]~216_combout\ & (\FSMCCtrl|InData[2]~2\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "dc58",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController2:7:PortX|OutputData\(2),
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(2));

-- Location: LC_X11_Y5_N3
\Gen_IOController2:7:PortX|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(3) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(3) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[3]~3\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:7:PortX|OutputData\(3) 
-- & (\FSMCCtrl|InData[3]~3\ & ((!\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "de0a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[3]~3\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \OutData[8]~216_combout\,
	datad => \Gen_IOController2:7:PortX|OutputData\(3),
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(3));

-- Location: LC_X11_Y5_N4
\Gen_IOController2:7:PortX|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(4) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(4) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[4]~4\)))) # (!\Gen_IOController2:7:PortX|OutputData\(4) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[4]~4\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fa8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController2:7:PortX|OutputData\(4),
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[4]~4\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(4));

-- Location: LC_X11_Y5_N1
\Gen_IOController2:7:PortX|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(5) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(5) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[5]~5\)))) # (!\Gen_IOController2:7:PortX|OutputData\(5) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[5]~5\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController2:7:PortX|OutputData\(5),
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[5]~5\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(5));

-- Location: LC_X11_Y5_N7
\Gen_IOController2:7:PortX|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(6) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(6) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[6]~6\)))) # (!\Gen_IOController2:7:PortX|OutputData\(6) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[6]~6\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d5e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \Gen_IOController2:7:PortX|OutputData\(6),
	datad => \FSMCCtrl|InData[6]~6\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(6));

-- Location: LC_X11_Y5_N6
\Gen_IOController2:7:PortX|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(7) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(7) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[7]~7\)))) # (!\Gen_IOController2:7:PortX|OutputData\(7) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[7]~7\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fa8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController2:7:PortX|OutputData\(7),
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[7]~7\,
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(7));

-- Location: LC_X8_Y5_N8
\Gen_IOController2:7:PortX|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:7:PortX|OutputData\(8) = DFFEAS((\Gen_IOController2:7:PortX|OutputData\(8) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[8]~8\)))) # (!\Gen_IOController2:7:PortX|OutputData\(8) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[8]~8\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:7:PortX|InternalReset~combout\, , \Equal10~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "de50",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \Gen_IOController2:7:PortX|OutputData\(8),
	aclr => \Gen_IOController2:7:PortX|InternalReset~combout\,
	ena => \Equal10~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:7:PortX|OutputData\(8));

-- Location: LC_X10_Y2_N7
\Gen_IOController2:6:PortX|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(0) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(0) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[0]~0\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:6:PortX|OutputData\(0) 
-- & (\FSMCCtrl|InData[0]~0\ & ((!\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d0ea",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[0]~0\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \Gen_IOController2:6:PortX|OutputData\(0),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(0));

-- Location: LC_X10_Y2_N3
\Gen_IOController2:6:PortX|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(1) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(1) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[1]~1\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:6:PortX|OutputData\(1) 
-- & (((\FSMCCtrl|InData[1]~1\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8af8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController2:6:PortX|OutputData\(1),
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \FSMCCtrl|InData[1]~1\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(1));

-- Location: LC_X10_Y2_N9
\Gen_IOController2:6:PortX|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(2) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(2) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[2]~2\)))) # (!\Gen_IOController2:6:PortX|OutputData\(2) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[2]~2\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d5c8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController2:6:PortX|OutputData\(2),
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \FSMCCtrl|InData[2]~2\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(2));

-- Location: LC_X9_Y5_N3
\Gen_IOController2:6:PortX|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(3) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(3) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[3]~3\)))) # (!\Gen_IOController2:6:PortX|OutputData\(3) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[3]~3\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3a8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController2:6:PortX|OutputData\(3),
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \FSMCCtrl|InData[3]~3\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(3));

-- Location: LC_X9_Y5_N0
\Gen_IOController2:6:PortX|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(4) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(4) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[4]~4\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:6:PortX|OutputData\(4) 
-- & (((\FSMCCtrl|InData[4]~4\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b0ec",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \FSMCCtrl|InData[4]~4\,
	datac => \Gen_IOController2:6:PortX|OutputData\(4),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(4));

-- Location: LC_X9_Y5_N6
\Gen_IOController2:6:PortX|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(5) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(5) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[5]~5\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:6:PortX|OutputData\(5) 
-- & (((\FSMCCtrl|InData[5]~5\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b0ec",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \FSMCCtrl|InData[5]~5\,
	datac => \Gen_IOController2:6:PortX|OutputData\(5),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(5));

-- Location: LC_X9_Y5_N8
\Gen_IOController2:6:PortX|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(6) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(6) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[6]~6\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:6:PortX|OutputData\(6) 
-- & (\FSMCCtrl|InData[6]~6\ & (!\OutData[8]~216_combout\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f622",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[6]~6\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \Gen_IOController2:6:PortX|OutputData\(6),
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(6));

-- Location: LC_X9_Y5_N9
\Gen_IOController2:6:PortX|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(7) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(7) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[7]~7\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:6:PortX|OutputData\(7) 
-- & (((\FSMCCtrl|InData[7]~7\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8cf8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController2:6:PortX|OutputData\(7),
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(7));

-- Location: LC_X9_Y5_N4
\Gen_IOController2:6:PortX|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:6:PortX|OutputData\(8) = DFFEAS((\Gen_IOController2:6:PortX|OutputData\(8) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[8]~8\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:6:PortX|OutputData\(8) 
-- & (((\FSMCCtrl|InData[8]~8\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:6:PortX|InternalReset~combout\, , \Equal0~5_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b0ec",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \FSMCCtrl|InData[8]~8\,
	datac => \Gen_IOController2:6:PortX|OutputData\(8),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController2:6:PortX|InternalReset~combout\,
	ena => \Equal0~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:6:PortX|OutputData\(8));

-- Location: LC_X11_Y3_N2
\Gen_IOController2:5:PortX|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(0) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(0) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[0]~0\)))) # (!\Gen_IOController2:5:PortX|OutputData\(0) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[0]~0\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController2:5:PortX|OutputData\(0),
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(0));

-- Location: LC_X11_Y3_N6
\Gen_IOController2:5:PortX|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(1) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(1) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[1]~1\)))) # (!\Gen_IOController2:5:PortX|OutputData\(1) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[1]~1\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController2:5:PortX|OutputData\(1),
	datad => \FSMCCtrl|InData[1]~1\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(1));

-- Location: LC_X12_Y3_N8
\Gen_IOController2:5:PortX|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(2) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(2) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[2]~2\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:5:PortX|OutputData\(2) 
-- & (((\FSMCCtrl|InData[2]~2\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be0c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \FSMCCtrl|InData[2]~2\,
	datac => \OutData[8]~216_combout\,
	datad => \Gen_IOController2:5:PortX|OutputData\(2),
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(2));

-- Location: LC_X11_Y3_N4
\Gen_IOController2:5:PortX|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(3) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(3) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[3]~3\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:5:PortX|OutputData\(3) 
-- & (((\FSMCCtrl|InData[3]~3\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b0ec",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \FSMCCtrl|InData[3]~3\,
	datac => \Gen_IOController2:5:PortX|OutputData\(3),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(3));

-- Location: LC_X11_Y3_N5
\Gen_IOController2:5:PortX|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(4) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(4) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[4]~4\)))) # (!\Gen_IOController2:5:PortX|OutputData\(4) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[4]~4\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController2:5:PortX|OutputData\(4),
	datad => \FSMCCtrl|InData[4]~4\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(4));

-- Location: LC_X12_Y3_N9
\Gen_IOController2:5:PortX|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(5) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(5) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[5]~5\)))) # (!\Gen_IOController2:5:PortX|OutputData\(5) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[5]~5\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be30",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \Gen_IOController2:5:PortX|OutputData\(5),
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(5));

-- Location: LC_X11_Y3_N9
\Gen_IOController2:5:PortX|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(6) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(6) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[6]~6\)))) # (!\Gen_IOController2:5:PortX|OutputData\(6) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[6]~6\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController2:5:PortX|OutputData\(6),
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[6]~6\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(6));

-- Location: LC_X11_Y3_N3
\Gen_IOController2:5:PortX|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(7) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(7) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[7]~7\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController2:5:PortX|OutputData\(7) 
-- & (((\FSMCCtrl|InData[7]~7\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be0c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \FSMCCtrl|InData[7]~7\,
	datac => \OutData[8]~216_combout\,
	datad => \Gen_IOController2:5:PortX|OutputData\(7),
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(7));

-- Location: LC_X11_Y3_N8
\Gen_IOController2:5:PortX|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController2:5:PortX|OutputData\(8) = DFFEAS((\Gen_IOController2:5:PortX|OutputData\(8) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[8]~8\)))) # (!\Gen_IOController2:5:PortX|OutputData\(8) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[8]~8\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController2:5:PortX|InternalReset~combout\, , \Equal0~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController2:5:PortX|OutputData\(8),
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[8]~8\,
	aclr => \Gen_IOController2:5:PortX|InternalReset~combout\,
	ena => \Equal0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController2:5:PortX|OutputData\(8));

-- Location: LC_X1_Y5_N5
\Port4|GenericPort|IOPort[0]~10\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[0]~10_combout\ = ((\DedicatedFunctionUsed~regout\) # ((\Port4|GenericPort|Dir\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ffcc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \DedicatedFunctionUsed~regout\,
	datad => \Port4|GenericPort|Dir\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[0]~10_combout\);

-- Location: LC_X5_Y5_N0
\Port4|GenericPort|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(1) = DFFEAS((\FSMCCtrl|InData[1]~1\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[1]~1\ & (\Port4|GenericPort|OutputData\(1) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(0),
	datab => \Port4|GenericPort|OutputData\(1),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCCtrl|InData[1]~1\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(1));

-- Location: LC_X10_Y7_N3
\Port4|DedicatedPort|SendData[5]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(5) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[5]~5\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[5]~5\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(5));

-- Location: LC_X9_Y7_N5
\Port4|DedicatedPort|SendData[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(4) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[4]~4\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[4]~4\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(4));

-- Location: LC_X10_Y7_N2
\Port4|DedicatedPort|SendData[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(3) = DFFEAS((((\FSMCCtrl|InData[3]~3\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff00",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datad => \FSMCCtrl|InData[3]~3\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(3));

-- Location: LC_X9_Y7_N7
\Port4|DedicatedPort|SendData[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(0) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[0]~0\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[0]~0\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(0));

-- Location: LC_X10_Y7_N6
\Port4|DedicatedPort|SendBuf[0]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(0) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(0)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendBuf\(0))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0c0a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendBuf\(0),
	datab => \Port4|DedicatedPort|SendData\(0),
	datac => \Port4|DedicatedPort|InternalReset~combout\,
	datad => \Port4|DedicatedPort|Equal1~1_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(0));

-- Location: LC_X10_Y7_N5
\Port4|DedicatedPort|SendData[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(1) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[1]~1\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[1]~1\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(1));

-- Location: LC_X10_Y7_N4
\Port4|DedicatedPort|SendBuf[1]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(1) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(1)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendBuf\(0))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3022",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendBuf\(0),
	datab => \Port4|DedicatedPort|InternalReset~combout\,
	datac => \Port4|DedicatedPort|SendData\(1),
	datad => \Port4|DedicatedPort|Equal1~1_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(1));

-- Location: LC_X10_Y7_N7
\Port4|DedicatedPort|SendData[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(2) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[2]~2\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(2));

-- Location: LC_X10_Y7_N1
\Port4|DedicatedPort|SendBuf[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(2) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(2)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendBuf\(1))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3022",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendBuf\(1),
	datab => \Port4|DedicatedPort|InternalReset~combout\,
	datac => \Port4|DedicatedPort|SendData\(2),
	datad => \Port4|DedicatedPort|Equal1~1_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(2));

-- Location: LC_X10_Y7_N0
\Port4|DedicatedPort|SendBuf[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(3) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendData\(3))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendBuf\(2)))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0a0c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendData\(3),
	datab => \Port4|DedicatedPort|SendBuf\(2),
	datac => \Port4|DedicatedPort|InternalReset~combout\,
	datad => \Port4|DedicatedPort|Equal1~1_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(3));

-- Location: LC_X10_Y7_N9
\Port4|DedicatedPort|SendBuf[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(4) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendData\(4))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendBuf\(3)))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0b08",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendData\(4),
	datab => \Port4|DedicatedPort|Equal1~1_combout\,
	datac => \Port4|DedicatedPort|InternalReset~combout\,
	datad => \Port4|DedicatedPort|SendBuf\(3),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(4));

-- Location: LC_X10_Y7_N8
\Port4|DedicatedPort|SendBuf[5]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(5) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendData\(5))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendBuf\(4)))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0b08",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendData\(5),
	datab => \Port4|DedicatedPort|Equal1~1_combout\,
	datac => \Port4|DedicatedPort|InternalReset~combout\,
	datad => \Port4|DedicatedPort|SendBuf\(4),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(5));

-- Location: LC_X8_Y7_N9
\Port4|DedicatedPort|SendData[6]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(6) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[6]~6\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[6]~6\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(6));

-- Location: LC_X8_Y7_N6
\Port4|DedicatedPort|SendBuf[6]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(6) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(6)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendBuf\(5))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5404",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|InternalReset~combout\,
	datab => \Port4|DedicatedPort|SendBuf\(5),
	datac => \Port4|DedicatedPort|Equal1~1_combout\,
	datad => \Port4|DedicatedPort|SendData\(6),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(6));

-- Location: LC_X9_Y7_N1
\Port4|DedicatedPort|SendData[7]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(7) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[7]~7\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[7]~7\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(7));

-- Location: LC_X8_Y7_N4
\Port4|DedicatedPort|SendBuf[7]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(7) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(7)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendBuf\(6))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0e04",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Equal1~1_combout\,
	datab => \Port4|DedicatedPort|SendBuf\(6),
	datac => \Port4|DedicatedPort|InternalReset~combout\,
	datad => \Port4|DedicatedPort|SendData\(7),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(7));

-- Location: LC_X9_Y7_N9
\Port4|DedicatedPort|SendData[8]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendData\(8) = DFFEAS(GND, GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Port4|DedicatedPort|InternalReset~combout\, , \Port4|DedicatedPort|SendData[15]~2_combout\, \FSMCCtrl|InData[8]~8\, , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	aclr => \Port4|DedicatedPort|InternalReset~combout\,
	sload => VCC,
	ena => \Port4|DedicatedPort|SendData[15]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendData\(8));

-- Location: LC_X8_Y7_N3
\Port4|DedicatedPort|SendBuf[8]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(8) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(8)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendBuf\(7))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00ca",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendBuf\(7),
	datab => \Port4|DedicatedPort|SendData\(8),
	datac => \Port4|DedicatedPort|Equal1~1_combout\,
	datad => \Port4|DedicatedPort|InternalReset~combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(8));

-- Location: LC_X8_Y7_N8
\Port4|DedicatedPort|SendBuf[9]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(9) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(9)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendBuf\(8))))), 
-- GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3202",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendBuf\(8),
	datab => \Port4|DedicatedPort|InternalReset~combout\,
	datac => \Port4|DedicatedPort|Equal1~1_combout\,
	datad => \Port4|DedicatedPort|SendData\(9),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(9));

-- Location: LC_X8_Y7_N0
\Port4|DedicatedPort|SendBuf[10]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(10) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendData\(10))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & 
-- ((\Port4|DedicatedPort|SendBuf\(9)))))), GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3120",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Equal1~1_combout\,
	datab => \Port4|DedicatedPort|InternalReset~combout\,
	datac => \Port4|DedicatedPort|SendData\(10),
	datad => \Port4|DedicatedPort|SendBuf\(9),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(10));

-- Location: LC_X7_Y7_N3
\Port4|DedicatedPort|SendBuf[11]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(11) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(11)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & 
-- (\Port4|DedicatedPort|SendBuf\(10))))), GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00ca",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendBuf\(10),
	datab => \Port4|DedicatedPort|SendData\(11),
	datac => \Port4|DedicatedPort|Equal1~1_combout\,
	datad => \Port4|DedicatedPort|InternalReset~combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(11));

-- Location: LC_X7_Y7_N0
\Port4|DedicatedPort|SendBuf[12]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(12) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(12)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & 
-- (\Port4|DedicatedPort|SendBuf\(11))))), GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3202",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendBuf\(11),
	datab => \Port4|DedicatedPort|InternalReset~combout\,
	datac => \Port4|DedicatedPort|Equal1~1_combout\,
	datad => \Port4|DedicatedPort|SendData\(12),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(12));

-- Location: LC_X7_Y7_N9
\Port4|DedicatedPort|SendBuf[13]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(13) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(13)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & 
-- (\Port4|DedicatedPort|SendBuf\(12))))), GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00e4",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Equal1~1_combout\,
	datab => \Port4|DedicatedPort|SendBuf\(12),
	datac => \Port4|DedicatedPort|SendData\(13),
	datad => \Port4|DedicatedPort|InternalReset~combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(13));

-- Location: LC_X7_Y7_N7
\Port4|DedicatedPort|SendBuf[14]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(14) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & (\Port4|DedicatedPort|SendData\(14))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & 
-- ((\Port4|DedicatedPort|SendBuf\(13)))))), GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00ac",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|SendData\(14),
	datab => \Port4|DedicatedPort|SendBuf\(13),
	datac => \Port4|DedicatedPort|Equal1~1_combout\,
	datad => \Port4|DedicatedPort|InternalReset~combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(14));

-- Location: LC_X7_Y7_N4
\Port4|DedicatedPort|SendBuf[15]\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|SendBuf\(15) = DFFEAS((!\Port4|DedicatedPort|InternalReset~combout\ & ((\Port4|DedicatedPort|Equal1~1_combout\ & ((\Port4|DedicatedPort|SendData\(15)))) # (!\Port4|DedicatedPort|Equal1~1_combout\ & 
-- (\Port4|DedicatedPort|SendBuf\(14))))), GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00e4",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Equal1~1_combout\,
	datab => \Port4|DedicatedPort|SendBuf\(14),
	datac => \Port4|DedicatedPort|SendData\(15),
	datad => \Port4|DedicatedPort|InternalReset~combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|SendBuf\(15));

-- Location: LC_X7_Y7_N1
\Port4|DedicatedPort|ADC_SDI\ : maxii_lcell
-- Equation(s):
-- \Port4|DedicatedPort|ADC_SDI~regout\ = DFFEAS((\Port4|DedicatedPort|InternalReset~combout\ & (((\Port4|DedicatedPort|ADC_SDI~regout\)))) # (!\Port4|DedicatedPort|InternalReset~combout\ & (!\Port4|DedicatedPort|Equal1~1_combout\ & 
-- (\Port4|DedicatedPort|SendBuf\(15)))), GLOBAL(\Port4|DedicatedPort|ClkDiv|ClkOut~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "dc10",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	dataa => \Port4|DedicatedPort|Equal1~1_combout\,
	datab => \Port4|DedicatedPort|InternalReset~combout\,
	datac => \Port4|DedicatedPort|SendBuf\(15),
	datad => \Port4|DedicatedPort|ADC_SDI~regout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|DedicatedPort|ADC_SDI~regout\);

-- Location: LC_X4_Y4_N2
\Port4|GenericPort|IOPort[1]~11\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[1]~11_combout\ = ((\DedicatedFunctionUsed~regout\ & ((\Port4|DedicatedPort|ADC_SDI~regout\))) # (!\DedicatedFunctionUsed~regout\ & (\Port4|GenericPort|OutputData\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc30",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \DedicatedFunctionUsed~regout\,
	datac => \Port4|GenericPort|OutputData\(1),
	datad => \Port4|DedicatedPort|ADC_SDI~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[1]~11_combout\);

-- Location: LC_X1_Y4_N6
\Port4|GenericPort|Mux25~3\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|Mux25~3_combout\ = (((\Port4|GenericPort|Dir\(1)) # (\DedicatedFunctionUsed~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Port4|GenericPort|Dir\(1),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|Mux25~3_combout\);

-- Location: LC_X5_Y5_N3
\Port4|GenericPort|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(2) = DFFEAS((\FSMCCtrl|InData[2]~2\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[2]~2\ & (\Port4|GenericPort|OutputData\(2) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fa8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Port4|GenericPort|OutputData\(2),
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCCtrl|InData[2]~2\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(2));

-- Location: LC_X1_Y4_N9
\Port4|GenericPort|IOPort[2]~12\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[2]~12_combout\ = (((\Port4|GenericPort|OutputData\(2) & !\DedicatedFunctionUsed~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Port4|GenericPort|OutputData\(2),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[2]~12_combout\);

-- Location: LC_X5_Y5_N9
\Port4|GenericPort|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(3) = DFFEAS((\FSMCCtrl|InData[3]~3\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[3]~3\ & (\Port4|GenericPort|OutputData\(3) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3e30",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(0),
	datab => \FSMCAdd~combout\(1),
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \Port4|GenericPort|OutputData\(3),
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(3));

-- Location: LC_X1_Y4_N4
\Port4|GenericPort|IOPort[3]~14\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[3]~14_combout\ = (((\Port4|GenericPort|OutputData\(3) & !\DedicatedFunctionUsed~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Port4|GenericPort|OutputData\(3),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[3]~14_combout\);

-- Location: LC_X6_Y5_N6
\Port4|GenericPort|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(4) = DFFEAS((\FSMCCtrl|InData[4]~4\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[4]~4\ & (\Port4|GenericPort|OutputData\(4) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fa8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Port4|GenericPort|OutputData\(4),
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCCtrl|InData[4]~4\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(4));

-- Location: LC_X1_Y4_N2
\Port4|GenericPort|IOPort[4]~16\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[4]~16_combout\ = (((\Port4|GenericPort|OutputData\(4) & !\DedicatedFunctionUsed~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Port4|GenericPort|OutputData\(4),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[4]~16_combout\);

-- Location: LC_X5_Y5_N8
\Port4|GenericPort|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(5) = DFFEAS((\FSMCCtrl|InData[5]~5\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[5]~5\ & (\Port4|GenericPort|OutputData\(5) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5e0a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[5]~5\,
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(1),
	datad => \Port4|GenericPort|OutputData\(5),
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(5));

-- Location: LC_X1_Y5_N7
\Port4|GenericPort|IOPort[5]~18\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[5]~18_combout\ = ((\DedicatedFunctionUsed~regout\ & ((\Port4|DedicatedPort|ClkDiv|ClkOut~regout\))) # (!\DedicatedFunctionUsed~regout\ & (\Port4|GenericPort|OutputData\(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Port4|GenericPort|OutputData\(5),
	datac => \Port4|DedicatedPort|ClkDiv|ClkOut~regout\,
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[5]~18_combout\);

-- Location: LC_X5_Y5_N2
\Port4|GenericPort|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(6) = DFFEAS((\FSMCCtrl|InData[6]~6\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[6]~6\ & (\Port4|GenericPort|OutputData\(6) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5e0a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[6]~6\,
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCAdd~combout\(1),
	datad => \Port4|GenericPort|OutputData\(6),
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(6));

-- Location: LC_X1_Y5_N8
\Port4|GenericPort|IOPort[6]~20\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[6]~20_combout\ = (((\Port4|GenericPort|OutputData\(6) & !\DedicatedFunctionUsed~regout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \Port4|GenericPort|OutputData\(6),
	datad => \DedicatedFunctionUsed~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[6]~20_combout\);

-- Location: LC_X6_Y5_N7
\Port4|GenericPort|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(7) = DFFEAS((\FSMCCtrl|InData[7]~7\ & (((!\FSMCAdd~combout\(1))))) # (!\FSMCCtrl|InData[7]~7\ & (\Port4|GenericPort|OutputData\(7) & ((\FSMCAdd~combout\(0)) # (\FSMCAdd~combout\(1))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(0),
	datab => \Port4|GenericPort|OutputData\(7),
	datac => \FSMCAdd~combout\(1),
	datad => \FSMCCtrl|InData[7]~7\,
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(7));

-- Location: LC_X1_Y5_N9
\Port4|GenericPort|IOPort[7]~22\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[7]~22_combout\ = ((!\DedicatedFunctionUsed~regout\ & ((\Port4|GenericPort|OutputData\(7)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3300",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \DedicatedFunctionUsed~regout\,
	datad => \Port4|GenericPort|OutputData\(7),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[7]~22_combout\);

-- Location: LC_X6_Y5_N3
\Port4|GenericPort|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|OutputData\(8) = DFFEAS((\FSMCCtrl|InData[8]~8\ & (!\FSMCAdd~combout\(1))) # (!\FSMCCtrl|InData[8]~8\ & (\Port4|GenericPort|OutputData\(8) & ((\FSMCAdd~combout\(1)) # (\FSMCAdd~combout\(0))))), GLOBAL(\FSMCCtrl|InDataClk~combout\), 
-- !\Port4|GenericPort|InternalReset~combout\, , \Port4|GenericPort|OutputData[0]~2_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5e50",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCAdd~combout\(1),
	datab => \FSMCAdd~combout\(0),
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \Port4|GenericPort|OutputData\(8),
	aclr => \Port4|GenericPort|InternalReset~combout\,
	ena => \Port4|GenericPort|OutputData[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Port4|GenericPort|OutputData\(8));

-- Location: LC_X1_Y5_N4
\Port4|GenericPort|IOPort[8]~24\ : maxii_lcell
-- Equation(s):
-- \Port4|GenericPort|IOPort[8]~24_combout\ = ((!\DedicatedFunctionUsed~regout\ & ((\Port4|GenericPort|OutputData\(8)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3300",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \DedicatedFunctionUsed~regout\,
	datad => \Port4|GenericPort|OutputData\(8),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Port4|GenericPort|IOPort[8]~24_combout\);

-- Location: LC_X10_Y3_N3
\Gen_IOController1:3:PortX|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(0) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(0) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[0]~0\)))) # (!\Gen_IOController1:3:PortX|OutputData\(0) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[0]~0\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be30",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \FSMCCtrl|InData[0]~0\,
	datad => \Gen_IOController1:3:PortX|OutputData\(0),
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(0));

-- Location: LC_X10_Y3_N1
\Gen_IOController1:3:PortX|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(1) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(1) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[1]~1\)))) # (!\Gen_IOController1:3:PortX|OutputData\(1) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[1]~1\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController1:3:PortX|OutputData\(1),
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[1]~1\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(1));

-- Location: LC_X10_Y3_N8
\Gen_IOController1:3:PortX|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(2) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(2) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[2]~2\)))) # (!\Gen_IOController1:3:PortX|OutputData\(2) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[2]~2\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3a8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:3:PortX|OutputData\(2),
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \FSMCCtrl|InData[2]~2\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(2));

-- Location: LC_X7_Y5_N1
\Gen_IOController1:3:PortX|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(3) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(3) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[3]~3\)))) # (!\Gen_IOController1:3:PortX|OutputData\(3) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[3]~3\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "de50",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \Gen_IOController1:3:PortX|OutputData\(3),
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(3));

-- Location: LC_X7_Y5_N9
\Gen_IOController1:3:PortX|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(4) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(4) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[4]~4\)))) # (!\Gen_IOController1:3:PortX|OutputData\(4) 
-- & (!\OutData[8]~216_combout\ & (\FSMCCtrl|InData[4]~4\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "dc58",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \Gen_IOController1:3:PortX|OutputData\(4),
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(4));

-- Location: LC_X10_Y3_N7
\Gen_IOController1:3:PortX|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(5) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(5) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[5]~5\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:3:PortX|OutputData\(5) 
-- & (((\FSMCCtrl|InData[5]~5\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8cf8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController1:3:PortX|OutputData\(5),
	datac => \FSMCCtrl|InData[5]~5\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(5));

-- Location: LC_X7_Y5_N4
\Gen_IOController1:3:PortX|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(6) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(6) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[6]~6\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:3:PortX|OutputData\(6) 
-- & (\FSMCCtrl|InData[6]~6\ & ((!\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d0ea",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[6]~6\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \Gen_IOController1:3:PortX|OutputData\(6),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(6));

-- Location: LC_X7_Y5_N8
\Gen_IOController1:3:PortX|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(7) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(7) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[7]~7\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:3:PortX|OutputData\(7) 
-- & (\FSMCCtrl|InData[7]~7\ & ((!\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a2ec",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:3:PortX|OutputData\(7),
	datab => \FSMCCtrl|InData[7]~7\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(7));

-- Location: LC_X10_Y3_N0
\Gen_IOController1:3:PortX|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:3:PortX|OutputData\(8) = DFFEAS((\Gen_IOController1:3:PortX|OutputData\(8) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[8]~8\)))) # (!\Gen_IOController1:3:PortX|OutputData\(8) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[8]~8\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:3:PortX|InternalReset\, , \Equal0~1_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:3:PortX|OutputData\(8),
	datad => \FSMCCtrl|InData[8]~8\,
	aclr => \Gen_IOController1:3:PortX|InternalReset\,
	ena => \Equal0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:3:PortX|OutputData\(8));

-- Location: LC_X7_Y4_N0
\Gen_IOController1:2:PortX|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(0) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(0) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[0]~0\)))) # (!\Gen_IOController1:2:PortX|OutputData\(0) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[0]~0\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:2:PortX|OutputData\(0),
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(0));

-- Location: LC_X7_Y4_N4
\Gen_IOController1:2:PortX|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(1) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(1) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[1]~1\)))) # (!\Gen_IOController1:2:PortX|OutputData\(1) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[1]~1\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:2:PortX|OutputData\(1),
	datad => \FSMCCtrl|InData[1]~1\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(1));

-- Location: LC_X7_Y4_N5
\Gen_IOController1:2:PortX|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(2) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(2) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[2]~2\)))) # (!\Gen_IOController1:2:PortX|OutputData\(2) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[2]~2\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:2:PortX|OutputData\(2),
	datad => \FSMCCtrl|InData[2]~2\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(2));

-- Location: LC_X7_Y4_N9
\Gen_IOController1:2:PortX|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(3) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(3) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[3]~3\)))) # (!\Gen_IOController1:2:PortX|OutputData\(3) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[3]~3\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController1:2:PortX|OutputData\(3),
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[3]~3\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(3));

-- Location: LC_X7_Y4_N7
\Gen_IOController1:2:PortX|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(4) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(4) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[4]~4\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:2:PortX|OutputData\(4) 
-- & (((\FSMCCtrl|InData[4]~4\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b0ec",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \FSMCCtrl|InData[4]~4\,
	datac => \Gen_IOController1:2:PortX|OutputData\(4),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(4));

-- Location: LC_X6_Y4_N6
\Gen_IOController1:2:PortX|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(5) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(5) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[5]~5\)))) # (!\Gen_IOController1:2:PortX|OutputData\(5) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[5]~5\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:2:PortX|OutputData\(5),
	datad => \FSMCCtrl|InData[5]~5\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(5));

-- Location: LC_X6_Y4_N2
\Gen_IOController1:2:PortX|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(6) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(6) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[6]~6\)))) # (!\Gen_IOController1:2:PortX|OutputData\(6) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[6]~6\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be30",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \FSMCCtrl|InData[6]~6\,
	datad => \Gen_IOController1:2:PortX|OutputData\(6),
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(6));

-- Location: LC_X6_Y4_N4
\Gen_IOController1:2:PortX|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(7) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(7) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[7]~7\)))) # (!\Gen_IOController1:2:PortX|OutputData\(7) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[7]~7\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:2:PortX|OutputData\(7),
	datad => \FSMCCtrl|InData[7]~7\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(7));

-- Location: LC_X6_Y4_N1
\Gen_IOController1:2:PortX|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:2:PortX|OutputData\(8) = DFFEAS((\Gen_IOController1:2:PortX|OutputData\(8) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[8]~8\)))) # (!\Gen_IOController1:2:PortX|OutputData\(8) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[8]~8\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:2:PortX|InternalReset~combout\, , \Equal0~4_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:2:PortX|OutputData\(8),
	datad => \FSMCCtrl|InData[8]~8\,
	aclr => \Gen_IOController1:2:PortX|InternalReset~combout\,
	ena => \Equal0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:2:PortX|OutputData\(8));

-- Location: LC_X9_Y6_N3
\Gen_IOController1:1:PortX|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(0) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(0) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[0]~0\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:1:PortX|OutputData\(0) 
-- & (\FSMCCtrl|InData[0]~0\ & ((!\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a2ec",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:1:PortX|OutputData\(0),
	datab => \FSMCCtrl|InData[0]~0\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(0));

-- Location: LC_X9_Y6_N7
\Gen_IOController1:1:PortX|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(1) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(1) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[1]~1\)))) # (!\Gen_IOController1:1:PortX|OutputData\(1) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[1]~1\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:1:PortX|OutputData\(1),
	datad => \FSMCCtrl|InData[1]~1\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(1));

-- Location: LC_X9_Y6_N5
\Gen_IOController1:1:PortX|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(2) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(2) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[2]~2\)))) # (!\Gen_IOController1:1:PortX|OutputData\(2) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[2]~2\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be30",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \FSMCCtrl|InData[2]~2\,
	datad => \Gen_IOController1:1:PortX|OutputData\(2),
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(2));

-- Location: LC_X9_Y6_N8
\Gen_IOController1:1:PortX|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(3) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(3) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[3]~3\)))) # (!\Gen_IOController1:1:PortX|OutputData\(3) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[3]~3\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be30",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \FSMCCtrl|InData[3]~3\,
	datad => \Gen_IOController1:1:PortX|OutputData\(3),
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(3));

-- Location: LC_X8_Y6_N3
\Gen_IOController1:1:PortX|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(4) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(4) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[4]~4\)))) # (!\Gen_IOController1:1:PortX|OutputData\(4) 
-- & (!\OutData[8]~216_combout\ & (\FSMCCtrl|InData[4]~4\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ba38",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:1:PortX|OutputData\(4),
	datab => \OutData[8]~216_combout\,
	datac => \FSMCCtrl|InData[4]~4\,
	datad => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(4));

-- Location: LC_X8_Y6_N0
\Gen_IOController1:1:PortX|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(5) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(5) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[5]~5\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:1:PortX|OutputData\(5) 
-- & (\FSMCCtrl|InData[5]~5\ & ((!\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d0ea",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[5]~5\,
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \Gen_IOController1:1:PortX|OutputData\(5),
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(5));

-- Location: LC_X8_Y6_N8
\Gen_IOController1:1:PortX|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(6) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(6) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[6]~6\)))) # (!\Gen_IOController1:1:PortX|OutputData\(6) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[6]~6\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fa8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:1:PortX|OutputData\(6),
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[6]~6\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(6));

-- Location: LC_X9_Y6_N4
\Gen_IOController1:1:PortX|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(7) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(7) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[7]~7\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:1:PortX|OutputData\(7) 
-- & (((\FSMCCtrl|InData[7]~7\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8cf8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController1:1:PortX|OutputData\(7),
	datac => \FSMCCtrl|InData[7]~7\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(7));

-- Location: LC_X8_Y6_N9
\Gen_IOController1:1:PortX|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:1:PortX|OutputData\(8) = DFFEAS((\Gen_IOController1:1:PortX|OutputData\(8) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[8]~8\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:1:PortX|OutputData\(8) 
-- & (((\FSMCCtrl|InData[8]~8\ & !\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:1:PortX|InternalReset~combout\, , \Equal0~3_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8af8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:1:PortX|OutputData\(8),
	datab => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datac => \FSMCCtrl|InData[8]~8\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:1:PortX|InternalReset~combout\,
	ena => \Equal0~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:1:PortX|OutputData\(8));

-- Location: LC_X10_Y4_N4
\Gen_IOController1:0:PortX|OutputData[0]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(0) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(0) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[0]~0\)))) # (!\Gen_IOController1:0:PortX|OutputData\(0) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[0]~0\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3a8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData\(0),
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \FSMCCtrl|InData[0]~0\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(0));

-- Location: LC_X10_Y4_N3
\Gen_IOController1:0:PortX|OutputData[1]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(1) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(1) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[1]~1\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:0:PortX|OutputData\(1) 
-- & (\FSMCCtrl|InData[1]~1\ & (!\OutData[8]~216_combout\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f622",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[1]~1\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \Gen_IOController1:0:PortX|OutputData\(1),
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(1));

-- Location: LC_X10_Y4_N9
\Gen_IOController1:0:PortX|OutputData[2]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(2) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(2) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[2]~2\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:0:PortX|OutputData\(2) 
-- & (\FSMCCtrl|InData[2]~2\ & (!\OutData[8]~216_combout\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f622",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[2]~2\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \Gen_IOController1:0:PortX|OutputData\(2),
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(2));

-- Location: LC_X10_Y4_N8
\Gen_IOController1:0:PortX|OutputData[3]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(3) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(3) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[3]~3\)))) # (!\Gen_IOController1:0:PortX|OutputData\(3) 
-- & (!\OutData[8]~216_combout\ & ((\FSMCCtrl|InData[3]~3\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3a8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData\(3),
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \FSMCCtrl|InData[3]~3\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(3));

-- Location: LC_X10_Y4_N7
\Gen_IOController1:0:PortX|OutputData[4]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(4) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(4) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[4]~4\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:0:PortX|OutputData\(4) 
-- & (\FSMCCtrl|InData[4]~4\ & ((!\OutData[8]~216_combout\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c4ea",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[4]~4\,
	datab => \Gen_IOController1:0:PortX|OutputData\(4),
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \OutData[8]~216_combout\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(4));

-- Location: LC_X11_Y4_N9
\Gen_IOController1:0:PortX|OutputData[5]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(5) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(5) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[5]~5\)))) # (!\Gen_IOController1:0:PortX|OutputData\(5) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[5]~5\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8fc8",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \Gen_IOController1:0:PortX|OutputData\(5),
	datac => \OutData[8]~216_combout\,
	datad => \FSMCCtrl|InData[5]~5\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(5));

-- Location: LC_X11_Y4_N4
\Gen_IOController1:0:PortX|OutputData[6]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(6) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(6) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[6]~6\)))) # (!\Gen_IOController1:0:PortX|OutputData\(6) 
-- & (((!\OutData[8]~216_combout\ & \FSMCCtrl|InData[6]~6\)))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "b3e0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData\(6),
	datad => \FSMCCtrl|InData[6]~6\,
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(6));

-- Location: LC_X11_Y4_N3
\Gen_IOController1:0:PortX|OutputData[7]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(7) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(7) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\OutData[8]~216_combout\ $ (\FSMCCtrl|InData[7]~7\)))) # (!\Gen_IOController1:0:PortX|OutputData\(7) 
-- & (!\OutData[8]~216_combout\ & (\FSMCCtrl|InData[7]~7\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f644",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \OutData[8]~216_combout\,
	datab => \FSMCCtrl|InData[7]~7\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \Gen_IOController1:0:PortX|OutputData\(7),
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(7));

-- Location: LC_X11_Y4_N2
\Gen_IOController1:0:PortX|OutputData[8]\ : maxii_lcell
-- Equation(s):
-- \Gen_IOController1:0:PortX|OutputData\(8) = DFFEAS((\Gen_IOController1:0:PortX|OutputData\(8) & ((\Gen_IOController1:0:PortX|OutputData[0]~0_combout\) # (\FSMCCtrl|InData[8]~8\ $ (\OutData[8]~216_combout\)))) # (!\Gen_IOController1:0:PortX|OutputData\(8) 
-- & (\FSMCCtrl|InData[8]~8\ & (!\OutData[8]~216_combout\))), GLOBAL(\FSMCCtrl|InDataClk~combout\), !\Gen_IOController1:0:PortX|InternalReset~combout\, , \Equal8~0_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f622",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \FSMCCtrl|InDataClk~combout\,
	dataa => \FSMCCtrl|InData[8]~8\,
	datab => \OutData[8]~216_combout\,
	datac => \Gen_IOController1:0:PortX|OutputData[0]~0_combout\,
	datad => \Gen_IOController1:0:PortX|OutputData\(8),
	aclr => \Gen_IOController1:0:PortX|InternalReset~combout\,
	ena => \Equal8~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \Gen_IOController1:0:PortX|OutputData\(8));

-- Location: PIN_16,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 8mA
\FPGAClk~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \ParPort|IOClk~0_combout\,
	oe => VCC,
	padio => ww_FPGAClk);

-- Location: PIN_141,	 I/O Standard: 3.3-V LVCMOS,	 Current Strength: 4mA
\STM32Clk~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => STM32ClkDiv1(1),
	oe => VCC,
	padio => ww_STM32Clk);
END structure;


