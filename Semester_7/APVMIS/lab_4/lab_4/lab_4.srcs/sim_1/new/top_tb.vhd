----------------------------------------------------------------------------------
-- Company: Los Pollos Hermanos
-- Engineer: Gustavo
-- 
-- Create Date: 08.11.2023 21:13:58
-- Design Name: 
-- Module Name: top_tb - Behavioral
-- Project Name: 
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity top_tb is
	generic (PERIOD : time := 20 ns);
end top_tb;



architecture Behavioral of top_tb is
	component top is
	port (
			G 	 	 : in 	STD_LOGIC; -- negative
			R_C  	 : in 	STD_LOGIC; -- C - negative
			RCK  	 : in 	STD_LOGIC;
			CCLR	 : in 	STD_LOGIC; -- negative
			U_D  	 : in 	STD_LOGIC; -- D - negative
			LOAD	 : in	STD_LOGIC; -- negative
			ENP		 : in 	STD_LOGIC; -- negative
			ENT  	 : in 	STD_LOGIC; -- negative
			CCK 	 : in 	STD_LOGIC;

			INP		 : in  	STD_LOGIC_VECTOR (3 DOWNTO 0);
			Q		 : out  STD_LOGIC_VECTOR (3 DOWNTO 0);
			RCO		 : out 	STD_LOGIC -- negative
		);
	end component top;


	SIGNAL G,R_C,RCK,ENP,ENT,RCO : STD_LOGIC := '0';
	SIGNAL CCLR,U_D,LOAD : STD_LOGIC := '1';
	SIGNAL INP, Q : STD_LOGIC_VECTOR (3 DOWNTO 0);
	SIGNAL CCK : STD_LOGIC := '1';


begin

	DUT : top port map (G,R_C,RCK,CCLR,U_D,LOAD,ENP,ENT,CCK,INP,Q,RCO); -- device UNDER test


	INP <= "0110";
	CCK <= not CCK after PERIOD/10; -- freerun clk


	main_tb: process
	begin
		CCLR <= '0';
		wait for PERIOD/10;
		CCLR <= '1';
		wait for PERIOD/2;
		LOAD <= '1';
		wait for PERIOD/2;
		LOAD <= '0';
		wait for PERIOD/2;
		LOAD <= '1';
		wait for PERIOD*2;
		wait for PERIOD/10;
		RCK <= '1';
		wait for PERIOD/5;

		-- REGISTER CHECK
		R_C <= '1';


		wait for PERIOD/5;
		RCK <= '0';
		wait for PERIOD/5;
		RCK <= '1';
		wait for PERIOD/5;
		RCK <= '0';
		wait for PERIOD/5;
		RCK <= '1';
		wait for PERIOD/5;
		RCK <= '0';
		wait for PERIOD/5;
		RCK <= '1';
		wait for PERIOD/5;
		RCK <= '0';

		-- AGAIN TO CNTR
		wait for PERIOD/5;
		R_C <= '0';
		wait for PERIOD/2;

		--RESET'ISH
		CCLR <= '0';
		wait for PERIOD/20;
		CCLR <= '1';
		wait for PERIOD/2;



		-- DOWN CNTR
		U_D <= '0';
		wait for PERIOD*2;
		U_D <= '1';


		-- ENP CHECK
		wait for PERIOD/2;
		ENP <= '1';
		wait for PERIOD*2;
		ENP <= '0';



		-- ENT CHECK
		wait for PERIOD/2;
		ENT <= '1';
		wait for PERIOD*2;
		ENT <= '0';		


		-- TRI_STATE CHEECK
		wait for PERIOD/2;
		G <= '1';
		wait for PERIOD;
		ENT <= '0';		

		-- PEREKUS TAKSISTA CHEECK
		wait;




	end process main_tb;





end Behavioral;
