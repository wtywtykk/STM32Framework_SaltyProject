Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Entity FreqDivider Is
	Generic(
		MaxDivision:INTEGER:=63
	);
	Port(
		Divider:INTEGER Range 0 To MaxDivision;
		ClkIn:In STD_LOGIC;
		ClkOut:Buffer STD_LOGIC
	);
End Entity FreqDivider;

Architecture Behavioral Of FreqDivider Is

Component EdgeDetector Is
	Port(
		Clk:In STD_LOGIC;
		DoubleClk:Buffer STD_LOGIC
	);
End Component EdgeDetector;

Signal DoubleClk:STD_LOGIC;

Begin

FreqDoubler:EdgeDetector
	Port Map(
		Clk=>ClkIn,DoubleClk=>DoubleClk
	);

Process(DoubleClk)
	Variable Counter:INTEGER Range 0 To MaxDivision;
Begin
	If rising_edge(DoubleClk) Then
		Counter:=Counter+1;
		If Counter>=Divider Then
			ClkOut<=NOT ClkOut;
			Counter:=0;
		End If;
	End If;
End Process;

End Behavioral;
