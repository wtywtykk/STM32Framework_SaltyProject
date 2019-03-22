-- Copyright (C) 1991-2016 Altera Corporation. All rights reserved.
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, the Altera Quartus Prime License Agreement,
-- the Altera MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Altera and sold by Altera or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- ***************************************************************************
-- This file contains a Vhdl test bench template that is freely editable to   
-- suit user's needs .Comments are provided in each section to help the user  
-- fill out necessary details.                                                
-- ***************************************************************************
-- Generated on "05/26/2017 01:29:56"
                                                            
-- Vhdl Test Bench template for design  :  PeripheralBridge
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

PACKAGE PeripheralBridge_data_type IS 
TYPE IOPort_8_0_type IS ARRAY (8 DOWNTO 0) OF STD_LOGIC;
TYPE IOPort_8_0_0_7_type IS ARRAY (0 TO 7) OF IOPort_8_0_type;
SUBTYPE IOPort_type IS IOPort_8_0_0_7_type;
END PeripheralBridge_data_type;

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

library work;
use work.PeripheralBridge_data_type.all;

ENTITY PeripheralBridge_vhd_tst IS
END PeripheralBridge_vhd_tst;
ARCHITECTURE PeripheralBridge_arch OF PeripheralBridge_vhd_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL FPGAClk : STD_LOGIC;
SIGNAL FPGAData : STD_LOGIC_VECTOR(15 DOWNTO 0);
SIGNAL FSMCAdd : STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL FSMCData : STD_LOGIC_VECTOR(15 DOWNTO 0);
SIGNAL IOPort : IOPort_type;
SIGNAL NE : STD_LOGIC;
SIGNAL NOE : STD_LOGIC;
SIGNAL NWE : STD_LOGIC;
SIGNAL STM32Clk : STD_LOGIC;
SIGNAL SysClk : STD_LOGIC;
COMPONENT PeripheralBridge
	PORT (
	FPGAClk : BUFFER STD_LOGIC;
	FPGAData : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
	FSMCAdd : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
	FSMCData : BUFFER STD_LOGIC_VECTOR(15 DOWNTO 0);
	IOPort : BUFFER IOPort_type;
	NE : IN STD_LOGIC;
	NOE : IN STD_LOGIC;
	NWE : IN STD_LOGIC;
	STM32Clk : BUFFER STD_LOGIC;
	SysClk : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : PeripheralBridge
	PORT MAP (
-- list connections between master ports and signals
	FPGAClk => FPGAClk,
	FPGAData => FPGAData,
	FSMCAdd => FSMCAdd,
	FSMCData => FSMCData,
	IOPort => IOPort,
	NE => NE,
	NOE => NOE,
	NWE => NWE,
	STM32Clk => STM32Clk,
	SysClk => SysClk
	);
init : PROCESS                                               
-- variable declarations                                     
BEGIN                                                        
        -- code that executes only once                      
WAIT;                                                       
END PROCESS init;                                           
always : PROCESS                                              
-- optional sensitivity list                                  
-- (        )                                                 
-- variable declarations                                      
BEGIN                                                         
        -- code executes for every event on sensitivity list  
WAIT;                                                        
END PROCESS always;                          
CLKGEN:Process
Begin
	Wait For 20ns;
	SysClk<='1';
	Wait For 20ns;
	SysClk<='0';
End Process;                
END PeripheralBridge_arch;
