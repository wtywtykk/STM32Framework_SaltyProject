Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Entity ParPortController Is
	Port(
		Rst:In STD_LOGIC;
		
		IOPort:In STD_LOGIC_VECTOR(15 DownTo 0);
		IOClk:Out STD_LOGIC;
		
		RD_Data:Out STD_LOGIC_VECTOR(15 DownTo 0);
		RD_Enable:In STD_LOGIC;
		RD_Clk:In STD_LOGIC
	);
End Entity ParPortController;

Architecture Behavioral Of ParPortController Is

Signal BufData:STD_LOGIC_VECTOR(15 DownTo 0);
Signal InternalClk:STD_LOGIC;

Begin

Process(RD_Clk,RD_Enable)
Begin
	InternalClk<=RD_Clk AND RD_Enable;
End Process;

Process(InternalClk,IOPort,BufData,Rst)
Begin
	If Rst='1' Then
		IOClk<='0';
		BufData<="0000000000000000";
	Else
		IOClk<=InternalClk;
		If rising_edge(InternalClk) Then
			BufData<=IOPort;
		End If;
	End If;
	RD_Data<=BufData;
End Process;

End Behavioral;
