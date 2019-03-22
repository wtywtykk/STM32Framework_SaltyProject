Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Entity Port0Mux Is
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
End Entity Port0Mux;

Architecture Behavioral Of Port0Mux Is

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

Component DedicatedFunctionController Is
	Port(
		Clk:In STD_LOGIC;
		Rst:In STD_LOGIC;
		
		InPort:In STD_LOGIC_VECTOR(8 DownTo 0);
		OutPort:Out STD_LOGIC_VECTOR(8 DownTo 0);
		OutMask:Out STD_LOGIC_VECTOR(8 DownTo 0);
		
		FuncSel:In INTEGER RANGE 0 To 4;
		RD_Data:Out STD_LOGIC_VECTOR(15 DownTo 0);
		WR_Clk:In STD_LOGIC;
		WR_Enable:In STD_LOGIC;
		WR_Data:In STD_LOGIC_VECTOR(15 DownTo 0)
	);
End Component DedicatedFunctionController;

Signal GenericRD_Data:STD_LOGIC_VECTOR(15 DownTo 0);
Signal GenericWR_Enable:STD_LOGIC;
Signal DedicatedInPort:STD_LOGIC_VECTOR(8 DownTo 0);
Signal DedicatedOutPort:STD_LOGIC_VECTOR(8 DownTo 0);
Signal DedicatedOutMask:STD_LOGIC_VECTOR(8 DownTo 0);
Signal DedicatedRD_Data:STD_LOGIC_VECTOR(15 DownTo 0);
Signal DedicatedWR_Enable:STD_LOGIC;

Begin

GenericPort:PortController
	Port Map(
		Clk=>Clk,
		Rst=>Rst,
		IOPort=>IOPort,
		FuncSel=>FuncSel,
		RD_Data=>GenericRD_Data,
		WR_Clk=>WR_Clk,
		WR_Enable=>GenericWR_Enable,
		WR_Data=>WR_Data,
		DedicatedInPort=>DedicatedInPort,
		DedicatedOutPort=>DedicatedOutPort,
		DedicatedOutMask=>DedicatedOutMask,
		DedicatedFunctionUsed=>DedicatedFunctionUsed
	);
	
DedicatedPort:DedicatedFunctionController
	Port Map(
		Clk=>Clk,
		Rst=>Rst,
		InPort=>DedicatedInPort,
		OutPort=>DedicatedOutPort,
		OutMask=>DedicatedOutMask,
		FuncSel=>FuncSel,
		RD_Data=>DedicatedRD_Data,
		WR_Clk=>WR_Clk,
		WR_Enable=>DedicatedWR_Enable,
		WR_Data=>WR_Data
	);

Process(DedicatedFunctionUsed,GenericRD_Data,DedicatedRD_Data,WR_Enable)
Begin
	If DedicatedFunctionUsed='0' Then
		RD_Data<=GenericRD_Data;
		GenericWR_Enable<=WR_Enable;
		DedicatedWR_Enable<='0';
	Else
		GenericWR_Enable<='0';
		RD_Data<=DedicatedRD_Data;
		DedicatedWR_Enable<=WR_Enable;
	End If;
End Process;

End Behavioral;
