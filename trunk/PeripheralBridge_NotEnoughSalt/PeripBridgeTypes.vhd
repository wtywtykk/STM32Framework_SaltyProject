Library IEEE;
Use IEEE.STD_LOGIC_1164.ALL;

Package PeripBirdgeTypes Is
	Type IOPortType Is Array(0 To 7) Of STD_LOGIC_VECTOR(8 DownTo 0);
	Type IOControllerDataBundleType Is Array(0 To 7) Of STD_LOGIC_VECTOR(15 DownTo 0);
End Package;
