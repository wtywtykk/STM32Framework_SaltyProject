Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Entity FSMCController Is
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
End Entity FSMCController;

Architecture Behavioral Of FSMCController Is

Signal Selected:STD_LOGIC;

Begin

Add<=FSMCAdd;

Process(NE,NOE,OutData)
Begin
	If NE='0' AND NOE='0' Then
		OutDataClk<='1';
		FSMCData<=OutData;
	Else
		OutDataClk<='0';
		FSMCData<="ZZZZZZZZZZZZZZZZ";
	End If;
End Process;

Process(NE,NWE,FSMCData)
Begin
	If NE='0' Then
		InDataClk<=NWE;
		InDATA<=FSMCData;
	Else
		InDataClk<='1';
		InData<="0000000000000000";
	End If;
End Process;

End Behavioral;
