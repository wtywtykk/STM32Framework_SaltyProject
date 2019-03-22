Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Entity PortController Is
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
End Entity PortController;

Architecture Behavioral Of PortController Is

Signal InternalReset:STD_LOGIC;
Signal Dir:STD_LOGIC_VECTOR(8 DownTo 0);
Signal OutputData:STD_LOGIC_VECTOR(8 DownTo 0);

Signal Config_Reset:STD_LOGIC;
--Signal Config_HiZ:STD_LOGIC;

Begin

Process(Rst,Config_Reset)
Begin
	InternalReset<=Rst OR Config_Reset;
End Process;

Process(WR_Clk,WR_Enable,FuncSel,WR_Data)
Begin
	If WR_Enable='1' Then
		If rising_edge(WR_Clk) Then
			If FuncSel=4 Then--SetConfig
				Config_Reset<=Wr_Data(0);
			End If;
		End If;
	End If;
End Process;

Process(WR_Clk,WR_Enable,FuncSel,WR_Data,InternalReset)
Begin
	If InternalReset='1' Then
		OutPutData<="000000000";
		Dir<="000000000";
		--Config_HiZ<='0';
	Else
		If WR_Enable='1' Then
			If rising_edge(WR_Clk) Then
				Case FuncSel Is
					When 0=>--IOData
						OutPutData<=WR_Data(8 DownTo 0);
					When 1=>--SetBit
						OutPutData<=OutPutData OR WR_Data(8 DownTo 0);
					When 2=>--ClearBit
						OutPutData<=OutPutData AND (NOT WR_Data(8 DownTo 0));
					When 3=>--SetDirection
						Dir<=WR_Data(8 DownTo 0);
					When 4=>--SetConfig
						--Reset is controled separately
						--because we need to ensure that reset bit can be cleared even under reset.
						--Config_HiZ<=Wr_Data(1);
					When Others=>
				End Case;
			End If;
		End If;
	End If;
End Process;

Process(FuncSel,IOPort,Dir,Config_Reset)--,Config_HiZ
Begin
	Case FuncSel Is
		When 0=>--IOData
			RD_Data(8 DownTo 0)<=IOPort;
			RD_Data(15 DownTo 9)<="0000000";
		When 1 | 2=>--SetBit,ClearBit
			RD_Data<="0000000000000000";
		When 3=>--SetDirection
			RD_Data(8 DownTo 0)<=Dir;
			RD_Data(15 DownTo 9)<="0000000";
		When 4=>--SetConfig
			RD_Data(0)<=Config_Reset;
			--RD_Data(1)<=Config_HiZ;
			--RD_Data(15 DownTo 2)<="00000000000000";
			RD_Data(15 DownTo 1)<="000000000000000";
		When Others=>
			RD_Data<="0000000000000000";
	End Case;
End Process;

Process(DedicatedFunctionUsed,IOPort,DedicatedOutMask,DedicatedOutPort,Dir,OutputData)--,Config_HiZ
Begin
	DedicatedInPort<=IOPort;
	If DedicatedFunctionUsed='1' Then
		For I In 0 To 8 Loop
			If DedicatedOutMask(I)='1' Then
				IOPort(I)<=DedicatedOutPort(I);
			Else
				IOPort(I)<='Z';
			End If;
		End Loop;
	Else
		--If Config_HiZ='1' Then
			--IOPort<="ZZZZZZZZZ";
		--Else
			For I In 0 To 8 Loop
				If Dir(I)='1' Then
					IOPort(I)<=OutPutData(I);
				Else
					IOPort(I)<='Z';
				End If;
			End Loop;
		--End If;
	End If;
End Process;

End Behavioral;
