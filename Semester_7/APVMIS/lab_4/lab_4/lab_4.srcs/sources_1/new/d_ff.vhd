----------------------------------------------------------------------------------
-- Engineer: Pudge
-- Company: AssweCan
-- Create Date: 26.09.2023 21:44:13

----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity d_ff is
	port (
			D 	 : in 	STD_LOGIC;
			C 	 : in 	STD_LOGIC;
			NOT_R: in 	STD_LOGIC;
			Q	 : out 	STD_LOGIC;
			NOT_Q: out 	STD_LOGIC
		);
end d_ff;

architecture Behavioral of d_ff is

begin
	process (C,NOT_R)
	begin
		if (NOT_R = '0') then
		case (NOT_R) is
			when '0' => Q <= '0'; NOT_Q <= '1';
			when others => null;
		end case;
		else
		if rising_edge(C) then
			Q <= D;
			NOT_Q <= not D;
		end if;
		end if;
	end process;

end Behavioral;