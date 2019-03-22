Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;
Use IEEE.STD_LOGIC_ARITH.ALL;
Use IEEE.STD_LOGIC_UNSIGNED.ALL;
Library PeripBirdgeTypes;
Use WORK.PeripBirdgeTypes.ALL;

Entity PeripheralBridge Is
	Port(
		--=========================FSMC Data and control lines=========================
		NE:In STD_LOGIC;
		NOE:In STD_LOGIC;
		NWE:In STD_LOGIC;
		FSMCAdd:In STD_LOGIC_VECTOR(5 DownTo 0);
		FSMCData:InOut STD_LOGIC_VECTOR(15 DownTo 0);
		--=========================GPIO Ports=========================
		IOPort:InOut IOPortType;
		--=========================FPGA Ports=========================
		FPGAData:In STD_LOGIC_VECTOR(15 DownTo 0);
		FPGAClk:Out STD_LOGIC;
		--=========================Clock=========================
		SysClk:In STD_LOGIC;
		STM32Clk:Out STD_LOGIC
	);
End Entity PeripheralBridge;

Architecture Behavioral Of PeripheralBridge Is

Component FreqDivider Is
	Generic(
		MaxDivision:INTEGER:=63
	);
	Port(
		Divider:INTEGER Range 0 To MaxDivision;
		ClkIn:In STD_LOGIC;
		ClkOut:Buffer STD_LOGIC
	);
End Component FreqDivider;

Component FSMCController Is
	Port(
		Add:Out STD_LOGIC_VECTOR(5 DownTo 0);
		InDataClk:Out STD_LOGIC;
		InData:Out STD_LOGIC_VECTOR(15 DownTo 0);
		OutDataClk:Out STD_LOGIC;
		OutData:In STD_LOGIC_VECTOR(15 DownTo 0);
		
		NE:In STD_LOGIC;
		NOE:In STD_LOGIC;
		NWE:In STD_LOGIC;
		FSMCAdd:In STD_LOGIC_VECTOR(5 DownTo 0);
		FSMCData:InOut STD_LOGIC_VECTOR(15 DownTo 0)
	);
End Component FSMCController;

Component Port0Mux Is
	Port(
		Clk:In STD_LOGIC;
		Rst:In STD_LOGIC;
		
		IOPort:InOut STD_LOGIC_VECTOR(8 DownTo 0);
		
		FuncSel:In INTEGER RANGE 0 To 4;
		RD_Data:Out STD_LOGIC_VECTOR(15 DownTo 0);
		WR_Clk:In STD_LOGIC;
		WR_Enable:In STD_LOGIC;
		WR_Data:In STD_LOGIC_VECTOR(15 DownTo 0);
		
		DedicatedFunctionUsed:In STD_LOGIC
	);
End Component Port0Mux;

Component PortController Is
	Port(
		Clk:In STD_LOGIC;
		Rst:In STD_LOGIC;
		
		IOPort:InOut STD_LOGIC_VECTOR(8 DownTo 0);
		
		FuncSel:In INTEGER RANGE 0 To 4;
		RD_Data:Out STD_LOGIC_VECTOR(15 DownTo 0);
		WR_Clk:In STD_LOGIC;
		WR_Enable:In STD_LOGIC;
		WR_Data:In STD_LOGIC_VECTOR(15 DownTo 0);
		
		DedicatedInPort:Out STD_LOGIC_VECTOR(8 DownTo 0);
		DedicatedOutPort:In STD_LOGIC_VECTOR(8 DownTo 0);
		DedicatedOutMask:In STD_LOGIC_VECTOR(8 DownTo 0);
		DedicatedFunctionUsed:In STD_LOGIC
	);
End Component PortController;

Component ParPortController Is
	Port(
		Rst:In STD_LOGIC;
		
		IOPort:In STD_LOGIC_VECTOR(15 DownTo 0);
		IOClk:Out STD_LOGIC;
		
		RD_Data:Out STD_LOGIC_VECTOR(15 DownTo 0);
		RD_Enable:In STD_LOGIC;
		RD_Clk:In STD_LOGIC
	);
End Component ParPortController;

Signal RegAddr:STD_LOGIC_VECTOR(5 DownTo 0);
Signal InClk:STD_LOGIC;
Signal InData:STD_LOGIC_VECTOR(15 DownTo 0);
Signal OutClk:STD_LOGIC;
Signal OutData:STD_LOGIC_VECTOR(15 DownTo 0);

Signal GPIOFuncSelect:INTEGER Range 0 To 6;
Signal GPIOReadValue:IOControllerDataBundleType;
Signal GPIOWriteEnable:STD_LOGIC_VECTOR(7 DownTo 0);

Signal FPGAReadEnable:STD_LOGIC;
Signal FPGAReadValue:STD_LOGIC_VECTOR(15 DownTo 0);

Signal PeripConfigEnable:STD_LOGIC;
Signal GlobalReset:STD_LOGIC;
Signal DedicatedFunctionUsed:STD_LOGIC;

Signal CommTestEnable:STD_LOGIC;
Signal CommTestVar:STD_LOGIC_VECTOR(15 DownTo 0);

Begin

--Clock output for stm32
--ClkDiv:FreqDivider
--	Generic Map(
--		MaxDivision=>7
--	)
--	Port Map(
--		Divider=>4,
--		ClkIn=>SysClk,
--		ClkOut=>STM32Clk
--	);
Process(SysClk)
	Variable STM32ClkDiv1:UNSIGNED(1 DownTo 0);
Begin
	If rising_edge(SysClk) Then
		STM32ClkDiv1:=STM32ClkDiv1+1;
	End If;
	STM32Clk<=STM32ClkDiv1(1);
End Process;

FSMCCtrl:FSMCController
	Port Map(
		Add=>RegAddr,
		InDataClk=>InClk,
		InData=>InData,
		OutDataClk=>OutClk,
		OutData=>OutData,
		NE=>NE,
		NOE=>NOE,
		NWE=>NWE,
		FSMCAdd=>FSMCAdd,
		FSMCData=>FSMCData
	);
Port4:Port0Mux
	Port Map(
		Clk=>SysClk,
		Rst=>GlobalReset,
		IOPort=>IOPort(4),
		FuncSel=>GPIOFuncSelect,
		RD_Data=>GPIOReadValue(4),
		WR_Clk=>InClk,
		WR_Enable=>GPIOWriteEnable(4),
		WR_Data=>InData,
		DedicatedFunctionUsed=>DedicatedFunctionUsed
	);
--Generate port controller instances for other ports
Gen_IOController1:For I In 0 To 3 Generate
		PortX:PortController
			Port Map(
				Clk=>SysClk,
				Rst=>GlobalReset,
				IOPort=>IOPort(I),
				FuncSel=>GPIOFuncSelect,
				RD_Data=>GPIOReadValue(I),
				WR_Clk=>InClk,
				WR_Enable=>GPIOWriteEnable(I),
				WR_Data=>InData,
				DedicatedInPort=>Open,
				DedicatedOutPort=>(Others=>'0'),
				DedicatedOutMask=>(Others=>'0'),
				DedicatedFunctionUsed=>'0'
			);
End Generate;
Gen_IOController2:For I In 5 To 7 Generate
		PortX:PortController
			Port Map(
				Clk=>SysClk,
				Rst=>GlobalReset,
				IOPort=>IOPort(I),
				FuncSel=>GPIOFuncSelect,
				RD_Data=>GPIOReadValue(I),
				WR_Clk=>InClk,
				WR_Enable=>GPIOWriteEnable(I),
				WR_Data=>InData,
				DedicatedInPort=>Open,
				DedicatedOutPort=>(Others=>'0'),
				DedicatedOutMask=>(Others=>'0'),
				DedicatedFunctionUsed=>'0'
			);
End Generate;

ParPort:ParPortController
	Port Map(
		Rst=>GlobalReset,
		IOPort=>FPGAData,
		IOClk=>FPGAClk,
		RD_Data=>FPGAReadValue,
		RD_Enable=>FPGAReadEnable,
		RD_Clk=>OutClk
	);

Process(InClk,PeripConfigEnable)
Begin
	If PeripConfigEnable='1' Then
		If rising_edge(InClk) Then
			GlobalReset<=InData(0);
			DedicatedFunctionUsed<=InData(1);
		End If;
	End If;
End Process;

Process(InClk,CommTestEnable,GlobalReset)
Begin
	If GlobalReset='1' Then
		CommTestVar<="0000000000000000";
	Else
		If CommTestEnable='1' Then
			If rising_edge(InClk) Then
				CommTestVar<=InData;
			End If;
		End If;
	End If;
End Process;

Process(RegAddr,InClk,OutClk,GPIOReadValue,FPGAReadValue,GlobalReset,DedicatedFunctionUsed,CommTestVar)
	Variable IntegerAddr:INTEGER Range 0 To 63;
Begin
	IntegerAddr:=conv_integer(RegAddr);
	
	GPIOWriteEnable<="00000000";
	FPGAReadEnable<='0';
	PeripConfigEnable<='0';
	CommTestEnable<='0';
	OutData<="0000000000000000";
	
	--GPIO Controllers
	--Address 0-4,8-12,16-20,24-28,32-36,40-44,48-52,56-60 Used
	GPIOFuncSelect<=IntegerAddr MOD 8;
	For I In 0 To 7 Loop
		If IntegerAddr/8=I Then
			GPIOWriteEnable(I)<='1';
			OutData<=GPIOReadValue(I);
		End If;
	End Loop;
	--FPGA Read
	If IntegerAddr=5 Then
		FPGAReadEnable<='1';
		OutData<=FPGAReadValue;
	End If;
	--Peripheral bridge Configure
	If IntegerAddr=6 Then
		PeripConfigEnable<='1';
		OutData(0)<=GlobalReset;
		OutData(1)<=DedicatedFunctionUsed;
		OutData(15 DownTo 2)<="00000000000000";
	End If;
	--Communication Test Register
	If IntegerAddr=63 Then
		CommTestEnable<='1';
		OutData<=NOT CommTestVar;
	End If;
End Process;

End Behavioral;
