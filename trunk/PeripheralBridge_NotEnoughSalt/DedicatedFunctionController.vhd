Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;
Use IEEE.STD_LOGIC_ARITH.ALL;
Use IEEE.STD_LOGIC_UNSIGNED.ALL;

Entity DedicatedFunctionController Is
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
End Entity DedicatedFunctionController;

Architecture Behavioral Of DedicatedFunctionController Is

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

Signal ADC_RD_CONVST:STD_LOGIC;
Signal ADC_SDI:STD_LOGIC;
Signal ADC_SDOB:STD_LOGIC;
Signal ADC_SDOA:STD_LOGIC;
Signal ADC_BUSY:STD_LOGIC;
Signal ADC_CLOCK:STD_LOGIC;
Signal ADC_M0:STD_LOGIC;
Signal ADC_CS:STD_LOGIC;
Signal ADC_M1:STD_LOGIC;

Signal InternalReset:STD_LOGIC;

Signal Config_Reset:STD_LOGIC;

Signal ConvertCounter:UNSIGNED(4 DownTo 0);
Signal Convert:STD_LOGIC;

Signal TransferCounter:UNSIGNED(4 DownTo 0);
Signal SendBuf:STD_LOGIC_VECTOR(15 DownTo 0);
Signal ChannelABuf:STD_LOGIC_VECTOR(15 DownTo 0);
Signal ChannelBBuf:STD_LOGIC_VECTOR(15 DownTo 0);

Signal SendData:STD_LOGIC_VECTOR(15 DownTo 0);
Signal ChannelAData:STD_LOGIC_VECTOR(15 DownTo 0);
Signal ChannelBData:STD_LOGIC_VECTOR(15 DownTo 0);

Begin

ClkDiv:FreqDivider
	Generic Map(
		MaxDivision=>7
	)
	Port Map(
		Divider=>5,
		ClkIn=>Clk,
		ClkOut=>ADC_CLOCK
	);

Process(ADC_RD_CONVST,ADC_SDI,ADC_CLOCK,ADC_M0,ADC_CS,ADC_M1,InPort)
Begin
	OutMask<="111100011";
	OutPort<=(Others=>'0');
	OutPort(0)<=ADC_RD_CONVST;
	OutPort(1)<=ADC_SDI;
	ADC_SDOB<=InPort(2);
	ADC_SDOA<=InPort(3);
	ADC_BUSY<=InPort(4);
	OutPort(5)<=ADC_CLOCK;
	OutPort(6)<=ADC_M0;
	OutPort(7)<=ADC_CS;
	OutPort(8)<=ADC_M1;
End Process;

ADC_M0<='0';
ADC_M1<='0';
ADC_CS<='0';

Process(Rst,Config_Reset)
Begin
	InternalReset<=Rst OR Config_Reset;
End Process;

Process(ADC_CLOCK,InternalReset)
Begin
	If falling_edge(ADC_CLOCK) Then
		If InternalReset='1' Then
			ConvertCounter<=(Others=>'0');
			Convert<='0';
		Else
			If ConvertCounter/=19 Then
				ConvertCounter<=ConvertCounter+1;
				Convert<='0';
			Else
				ConvertCounter<=(Others=>'0');
				Convert<='1';
			End If;
		End If;
	End If;
End Process;

Process(Clk,Convert)
Begin
	If falling_edge(Clk) Then
		ADC_RD_CONVST<=Convert;
	End If;
End Process;

Process(ADC_CLOCK,ADC_RD_CONVST,InternalReset)
Begin
	If rising_edge(ADC_CLOCK) Then
		If InternalReset='1' Then
			SendBuf<=(Others=>'0');
		Else
			If TransferCounter/=16 Then
				ADC_SDI<=SendBuf(15);
				SendBuf(15 DownTo 1)<=SendBuf(14 DownTo 0);
			Else
				ADC_SDI<='0';
				SendBuf<=SendData;
			End If;
		End If;
	End If;
End Process;

Process(ADC_CLOCK,ADC_RD_CONVST,InternalReset)
Begin
	If falling_edge(ADC_CLOCK) Then
		If InternalReset='1' Then
			TransferCounter<=(Others=>'0');
			ChannelABuf<=(Others=>'0');
			ChannelBBuf<=(Others=>'0');
		Else
			If ADC_RD_CONVST='1' Then
				TransferCounter<=(Others=>'0');
			Else
				If TransferCounter/=16 Then
					ChannelABuf<=ChannelABuf(14 DownTo 0) & ADC_SDOA;
					ChannelBBuf<=ChannelBBuf(14 DownTo 0) & ADC_SDOB;
					TransferCounter<=TransferCounter+1;
				Else
					ChannelAData<=ChannelABuf;
					ChannelBData<=ChannelBBuf;
				End If;
			End If;
		End If;
	End If;
End Process;

Process(WR_Clk,WR_Enable,FuncSel,WR_Data)
Begin
	If WR_Enable='1' Then
		If rising_edge(WR_Clk) Then
			If FuncSel=4 Then--SetConfig
				Config_Reset<=WR_Data(0);
			End If;
		End If;
	End If;
End Process;

Process(WR_Clk,WR_Enable,FuncSel,WR_Data,InternalReset)
Begin
	If InternalReset='1' Then
		SendData<=(Others=>'0');
	Else
		If WR_Enable='1' Then
			If rising_edge(WR_Clk) Then
				Case FuncSel Is
					When 0=>--Send
						SendData<=WR_Data;
					When 1=>
					When 2=>
					When 3=>
					When 4=>--SetConfig
						--Reset is controled separately
						--because we need to ensure that reset bit can be cleared even under reset.
					When Others=>
				End Case;
			End If;
		End If;
	End If;
End Process;

Process(FuncSel,ChannelAData,ChannelBData,ConvertCounter,ADC_BUSY,Config_Reset)
Begin
	Case FuncSel Is
		When 0=>
			RD_Data<=ChannelAData;
		When 1=>
			RD_Data<=ChannelBData;
		When 2=>
			RD_Data(0)<=Not (ConvertCounter(4) Or ConvertCounter(3));
			RD_Data(15 DownTo 1)<="000000000000000";
		When 3=>
			RD_Data<="1000001101100011";
		When 4=>
			RD_Data(0)<=Config_Reset;
			RD_Data(15 DownTo 1)<="000000000000000";
		When Others=>
			RD_Data<="0000000000000000";
	End Case;
End Process;

End Behavioral;
