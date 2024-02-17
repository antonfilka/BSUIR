----------------------------------------------------------------------------------
-- Company: KarinaCorp
-- Engineer: ChinChanChon
-- 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;




entity main_tb is

end main_tb;

architecture Behavioral of main_tb is
	component main is
	    port (
        A       : in STD_LOGIC_VECTOR (4 DOWNTO 1);
        B       : in STD_LOGIC_VECTOR (4 DOWNTO 1);
        C       : in STD_LOGIC;

        SUM     : out STD_LOGIC_VECTOR (4 DOWNTO 1);
        C_OUT   : out STD_LOGIC
    );
	end component main;
	SIGNAL C,C_OUT : STD_LOGIC := '0';
	SIGNAL A,B,SUM : STD_LOGIC_VECTOR (4 DOWNTO 1) := "0000";

begin
	UUT: main port map (A =>A, B=>B, C=> C, SUM =>SUM, C_OUT =>C_OUT);

	C <= not C after 160 ns; -- получено эмпирическим путём :3
	
	A(1) <= not A(1) after 10 ns;
	A(3) <= A(1);
	A(2) <= not A(4) after 40 ns;
	A(4) <= A(2);


	B(1) <= not B(1) after 20 ns;
	B(3) <= B(1);
	B(2) <= not B(4) after 80 ns;
	B(4) <= B(2);


end Behavioral;
