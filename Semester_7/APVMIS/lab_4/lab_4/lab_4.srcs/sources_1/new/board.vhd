----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01.11.2019 00:24:51
-- Design Name: 
-- Module Name: schema - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.vcomponents.all;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.ALL;

entity board is
    Port ( 
        ledsmain: out std_logic_vector(3 downto 0);
        ledsboard: out std_logic_vector(3 downto 0);
        pushbuttons: in std_logic_vector(4 downto 0);
        dipswitch: in std_logic_vector(3 downto 0);
        --clock diff pair
        sysclk_p: in std_logic;
        sysclk_n: in std_logic
    );
end board;

architecture Behavioral of board is
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
    end component;
    
    component divider is
        port ( 
            CLK_IN : in STD_LOGIC;
            CLK_OUT : out STD_LOGIC
        );
    end component;

    signal CLOCK, NOT_CLOCK: std_logic;
    signal Q : std_logic_vector (7 DOWNTO 0);
    signal CLK_NO_DIV,RCO,RCKEN,RCLK_int,G : std_logic;
begin


  IBUFDS_inst : IBUFDS

    port map (
       O =>  CLK_NO_DIV,  -- Buffer output
       I =>  sysclk_p,  -- Diff_p buffer input (connect directly to top-level port)
       IB => sysclk_n -- Diff_n buffer input (connect directly to top-level port)
    );

    
    RCLK_EN: process(RCKEN) begin
        if (RCKEN = '1') then
            RCLK_int <= NOT_CLOCK;
         else 
            RCLK_int <= '0';
         end if;
        
    end process RCLK_EN;
    
    G         <= '0';
    NOT_CLOCK <= not(CLOCK);

    counter: top port map (
        G 	 	 => G, -- negative
        R_C  	 => not pushbuttons(0), -- C - negative
        RCK  	 => NOT_CLOCK,
        CCLR	 => not pushbuttons(1), -- negative
        U_D  	 => not pushbuttons(2), -- D - negative
        LOAD	 => not pushbuttons(3), -- negative
        ENP		 => G, -- negative
        ENT  	 => pushbuttons(4), -- negative
        CCK 	 => CLOCK,

        INP		 => dipswitch,
        Q		 => ledsmain,
        RCO		 => RCO
    );
    
    ledsboard(0) <= not RCO;


    
    div: divider port map (
        CLK_IN => CLK_NO_DIV, 
        CLK_OUT => CLOCK
    );
    
end Behavioral;