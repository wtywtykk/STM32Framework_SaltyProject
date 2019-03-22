Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Entity RDWRController Is
	Port(
		Rst:In STD_LOGIC;
		
		WR_Enable:In STD_LOGIC;
		WR_Clk:In STD_LOGIC;
		WR_Clk_Out:OUT STD_LOGIC;
		
		RD_Enable:In STD_LOGIC;
		RD_Clk:In STD_LOGIC;
		RD_Clk_Out:OUT STD_LOGIC
	);
End Entity RDWRController;

Architecture Behavioral Of RDWRController Is

Begin

Process(WR_Enable,WR_Clk,Rst)
Begin
	If Rst='1' Then
		WR_Clk_Out<='0';
	Else
		If WR_Enable='1' Then
			WR_Clk_Out<=WR_Clk;
		End If;
	End If;
End Process;

Process(RD_Enable,RD_Clk,Rst)
Begin
	If Rst='1' Then
		RD_Clk_Out<='0';
	Else
		If RD_Enable='1' Then
			RD_Clk_Out<=RD_Clk;
		End If;
	End If;
End Process;

End Behavioral;
