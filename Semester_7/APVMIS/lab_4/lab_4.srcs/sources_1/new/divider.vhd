----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 31.10.2019 22:56:35
-- Design Name: 
-- Module Name: DIVIDER - Behavioral
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity divider is
generic(div_value : integer := 20000000);
    Port ( CLK_IN : in STD_LOGIC;
           CLK_OUT : out STD_LOGIC);
end divider;

architecture Behavioral of divider is
    signal clk_counter_value : std_logic_vector (31 downto 0) := X"00000000";
    signal curr_clk_out : std_logic := '0'; 
begin
process(clk_in)
begin
    if (rising_edge(clk_in)) then
        if (clk_counter_value = (div_value - 1)) then
            clk_counter_value <= X"00000000";
            curr_clk_out <= not curr_clk_out;
        else
            clk_counter_value <= clk_counter_value + 1;
        end if;
    end if;
end process;
clk_out <= curr_clk_out;   
end Behavioral;
