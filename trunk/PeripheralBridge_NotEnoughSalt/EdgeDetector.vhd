Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Entity EdgeDetector Is
	Port(
		Clk:In STD_LOGIC;
		DoubleClk:Buffer STD_LOGIC
	);
End Entity EdgeDetector;

Architecture Behavioral Of EdgeDetector Is
	Signal PostDivide:STD_LOGIC;
Begin

Process(Clk,PostDivide)
Begin
	DoubleClk<=Clk XOR PostDivide;
End Process;

Process(DoubleClk)
Begin
	IF rising_edge(DoubleClk) THEN
		PostDivide<=NOT PostDivide;
	End IF;
End Process;

End Behavioral;
