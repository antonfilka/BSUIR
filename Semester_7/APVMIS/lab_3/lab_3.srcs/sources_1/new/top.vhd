----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.11.2023 17:48:28
-- Design Name: 
-- Module Name: top - Behavioral
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity top is
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
end top;

architecture Behavioral of top is
    component d_ff is
        port (
                D 	 : in 	STD_LOGIC;
                C 	 : in 	STD_LOGIC;
                NOT_R: in 	STD_LOGIC;
                Q	 : out 	STD_LOGIC;
                NOT_Q: out 	STD_LOGIC
            );
     end component d_ff;	




    SIGNAL CNT_LINE_D	: STD_LOGIC_VECTOR (3 DOWNTO 0);
    SIGNAL CNT_LINE_QN	: STD_LOGIC_VECTOR (3 DOWNTO 0);
    SIGNAL CNT_LINE_Q 	: STD_LOGIC_VECTOR (3 DOWNTO 0);

    SIGNAL REG_LINE_QN	: STD_LOGIC_VECTOR (3 DOWNTO 0);

    SIGNAL BUF_LINE		: STD_LOGIC_VECTOR (3 DOWNTO 0);
    SIGNAL BUF_ENP		: STD_LOGIC;

    SIGNAL BUF_Q		: STD_LOGIC_VECTOR (3 DOWNTO 0);
    SIGNAL DUMMY		: STD_LOGIC;

    constant VCC		: STD_LOGIC := '1';
    SIGNAL not_UD,not_RC : STD_LOGIC;




        procedure and2nor(
    	SIGNAL in_1: in  STD_LOGIC; 
    	signal in_2: in  STD_LOGIC;
    	signal in_3: in  STD_LOGIC; 
    	SIGNAL in_4: in  STD_LOGIC;
    	signal out_NOR	: out STD_LOGIC) is
    begin
    	out_NOR <= ((in_1 and in_2) nor (in_3 and in_4));
    end procedure and2nor;
begin

	main: process (all) 
	begin 
		
		some: for i in BUF_LINE'range loop
			not_UD <= not(U_D);
			and2nor(not_UD,CNT_LINE_Q(i),U_D,CNT_LINE_QN(i),BUF_LINE(i));
		end loop some;
	end process main;

	BUF_ENP <= (LOAD and (not (ENP)) and (not (ENT)));


	CNT_LINE_D(0) <= not ( 
		(CNT_LINE_Q(0) and BUF_ENP) or 
		(not(BUF_ENP) and LOAD and CNT_LINE_QN(0)) or
		(INP(0) nor LOAD )
	);


	CNT_LINE_D(1) <= not ( 
		(CNT_LINE_Q(1) and BUF_ENP and BUF_LINE(0)) or 
		((not(BUF_ENP) or (not(BUF_LINE(0)))) and LOAD and CNT_LINE_QN(1)) or
		(INP(1) nor LOAD )
	);




	CNT_LINE_D(2) <= not ( 
		(CNT_LINE_Q(2) and BUF_ENP and BUF_LINE(0) and BUF_LINE(1)) or 
		((not(BUF_ENP) or (not(BUF_LINE(0))) or (not(BUF_LINE(1)))) and LOAD and CNT_LINE_QN(2)) or
		(INP(2) nor LOAD )
	);



	CNT_LINE_D(3) <= not ( 
		(CNT_LINE_Q(3) and BUF_ENP and BUF_LINE(0) and BUF_LINE(1) and BUF_LINE(2)) or 
		((not(BUF_ENP) or (not(BUF_LINE(0))) or (not(BUF_LINE(1))) or (not(BUF_LINE(2))) ) and LOAD and CNT_LINE_QN(3)) or
		(INP(3) nor LOAD )
	);



	RCO <= not (BUF_LINE(0) and BUF_LINE(1) and BUF_LINE(2) and BUF_LINE(3) and (not(ENT)));







	lines: for i in 0 to 3 generate
		first: d_ff port map (
			D =>CNT_LINE_D(i), 
			C=>CCK, 
			NOT_R=>CCLR, 
			Q=>CNT_LINE_Q(i), 
			NOT_Q=>CNT_LINE_QN(i)
		);
		second: d_ff port map (
			D =>CNT_LINE_Q(i), 
			C=>RCK, 
			NOT_R=>VCC, 
			Q=>DUMMY, 
			NOT_Q=>REG_LINE_QN(i)
		);
	end generate lines;


		--first1: d_ff port map (
		--	D =>CNT_LINE_D(0), 
		--	C=>CCK, 
		--	NOT_R=>CCLR, 
		--	Q=>CNT_LINE_Q(0), 
		--	NOT_Q=>CNT_LINE_QN(0)
		--);

		--first2: d_ff port map (
		--	D =>CNT_LINE_D(1), 
		--	C=>CCK, 
		--	NOT_R=>CCLR, 
		--	Q=>CNT_LINE_Q(1), 
		--	NOT_Q=>CNT_LINE_QN(1)
		--);

		--first3: d_ff port map (	
		--	D =>CNT_LINE_D(2), 
		--	C=>CCK, 
		--	NOT_R=>CCLR, 
		--	Q=>CNT_LINE_Q(2), 
		--	NOT_Q=>CNT_LINE_QN(2)
		--);

		--first4: d_ff port map (
		--	D =>CNT_LINE_D(3), 
		--	C=>CCK, 
		--	NOT_R=>CCLR, 
		--	Q=>CNT_LINE_Q(3), 
		--	NOT_Q=>CNT_LINE_QN(3)
		--);


		--second1: d_ff port map (
		--	D =>CNT_LINE_Q(0), 
		--	C=>RCK, 
		--	NOT_R=>VCC, 
		--	Q=>DUMMY, 
		--	NOT_Q=>REG_LINE_QN(0)
		--);

		--second2: d_ff port map (
		--	D =>CNT_LINE_Q(1), 
		--	C=>RCK, 
		--	NOT_R=>VCC, 
		--	Q=>DUMMY, 
		--	NOT_Q=>REG_LINE_QN(1)
		--);


		--second3: d_ff port map (
		--	D =>CNT_LINE_Q(2), 
		--	C=>RCK, 
		--	NOT_R=>VCC, 
		--	Q=>DUMMY, 
		--	NOT_Q=>REG_LINE_QN(2)
		--);

		--second4: d_ff port map (
		--	D =>CNT_LINE_Q(3), 
		--	C=>RCK, 
		--	NOT_R=>VCC, 
		--	Q=>DUMMY, 
		--	NOT_Q=>REG_LINE_QN(3)
		--);


	q_maker: process(all)
	begin 
		not_RC <= not(R_C);
		some_2: for i in 0 to 3 loop
			and2nor(R_C,REG_LINE_QN(i),not_RC,CNT_LINE_QN(i),BUF_Q(i));
		end loop some_2;
	end process q_maker;


	tri_state_buf: process (BUF_Q,G)
	begin
		for i in 0 to 3 loop
			if (G = '0') then
				Q(i) <= BUF_Q(i);
			else 
				Q(i) <= 'Z';
			end if;
		end loop;
	end process tri_state_buf;



end Behavioral;
