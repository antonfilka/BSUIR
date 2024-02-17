----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.11.2023 21:13:58
-- Design Name: 
-- Module Name: top_tb - Behavioral
-- Project Name: 
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_textio.all;
use std.textio.all;

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

	function vec2string ( a: std_logic_vector) return string is
	variable b : string (1 to a'length) := (others => NUL);
	variable stri : integer := 1; 
	begin
	    for i in a'range loop
	        b(stri) := std_logic'image(a((i)))(2); -- (1) will return ''
	   		stri := stri+1;
	    end loop;
	return b;
	end function vec2string;


    procedure skipSpaces(line_data: inout line; numOfspaces: integer) is
    variable char : character;
    begin
    	space_loop: for i in 1 to numOfspaces loop
    		read(line_data, char);
    	end loop space_loop;

    end procedure skipSpaces;




	file test_input : text open read_mode is "F:/some.txt";
	SIGNAL G,R_C,RCK,ENP,ENT,RCO : STD_LOGIC := '0';
	SIGNAL CCLR,U_D,LOAD : STD_LOGIC := '1';
	SIGNAL INP, Q, Q_file : STD_LOGIC_VECTOR (3 DOWNTO 0);
	SIGNAL CCK : STD_LOGIC := '1';


begin

	DUT : top port map (G,R_C,RCK,CCLR,U_D,LOAD,ENP,ENT,CCK,INP,Q,RCO); -- device UNDER test


	INP <= "0110";
	CCK <= not CCK after PERIOD/10; -- freerun clk

	file_rd: process

	variable line_data: line;
	variable G_f,R_C_f,RCK_f,ENP_f,ENT_f,RCO_f : STD_LOGIC;
	variable CCLR_f,U_D_f,LOAD_f : STD_LOGIC;
	variable INP_f, Q_f : STD_LOGIC_VECTOR (3 DOWNTO 0);
	variable line_num : integer := 0;
	begin
		--write(line_data, G);
		--write(line_data, (R_C),right, 2);
		--write(line_data, (RCK),right, 2);
		--write(line_data, (CCLR),right, 2);
		--write(line_data, (U_D),right, 2);
		--write(line_data, (LOAD),right, 2);
		--write(line_data, (ENP),right, 2);
		--write(line_data, (ENT),right, 2);


		--write(line_data, (INP),right, 8);
		--write(line_data, (RCO),right, 2);
		--write(line_data, (Q),right, 8);

		--writeline(test_input, line_data);


        


		file_chill :  while not endfile(test_input) loop

		    line_num := line_num + 1;
		    readline(test_input, line_data);

		    if line_data.all'length = 0 or line_data.all(1) = '/' then
                next;
            end if;

		    read(line_data, G_f);
		    skipSpaces(line_data, 1);
		    read(line_data, R_C_f);
		    skipSpaces(line_data, 1);
		    read(line_data, RCK_f);

		    skipSpaces(line_data, 1);
		    read(line_data, CCLR_f);

		    skipSpaces(line_data, 1);
		    read(line_data, U_D_f);

		    skipSpaces(line_data, 1);
		    read(line_data, LOAD_f);
			

			skipSpaces(line_data, 1);
		    read(line_data, ENP_f);

		    skipSpaces(line_data, 1);
		    read(line_data, ENT_f);

		    skipSpaces(line_data, 4);
		    read(line_data, INP_f);

		    skipSpaces(line_data, 1);
		    read(line_data, RCO_f);

		    skipSpaces(line_data, 4);
		    read(line_data, Q_f);




		    G <= G_f;
		    R_C <= R_C_f;
		    RCK <= RCK_f;
		    CCLR <= CCLR_f;
		    U_D <= U_D_f;
		    LOAD <= LOAD_f;
		    ENP <= ENP_f;

		  	ENT <= ENT_f;
		  	INP <= INP_f;

		  	wait for PERIOD/2;


			assert (Q = Q_f)
                report "Q_f failed. "
                        & "Expected: " & vec2string(Q)
                        & ". Actual: " & vec2string(Q_f)
                        & ". Line: " & integer'image(line_num)
                severity ERROR;

            assert (RCO = RCO_f)
                report "RCO_f failed. "
                        & "Expected: " & std_logic'image(RCO)
                        & ". Actual: " & std_logic'image(RCO_f)
                        & ". Line: " & integer'image(line_num)
                severity ERROR;    

		end loop file_chill;
		file_close(test_input);





	end process file_rd;


end Behavioral;
