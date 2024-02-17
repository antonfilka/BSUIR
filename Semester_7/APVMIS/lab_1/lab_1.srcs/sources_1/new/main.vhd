----------------------------------------------------------------------------------
-- Company: KarinaCorp
-- Engineer: Cringineer
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity main is
    port (
        A       : in STD_LOGIC_VECTOR (4 DOWNTO 1);
        B       : in STD_LOGIC_VECTOR (4 DOWNTO 1);
        C       : in STD_LOGIC;

        SUM     : out STD_LOGIC_VECTOR (4 DOWNTO 1);
        C_OUT   : out STD_LOGIC
    );
end main;

architecture Behavioral of main is
    SIGNAL TEMP     : STD_LOGIC_VECTOR (4 DOWNTO 1 );
    SIGNAL A_TEMP   : STD_LOGIC_VECTOR (4 DOWNTO 1 );
    SIGNAL B_TEMP   : STD_LOGIC_VECTOR (4 DOWNTO 1 );

begin

    process(A)
    begin
        for i in A_TEMP'range loop
            A_TEMP(i) <= not (A(i) or B(i));
            B_TEMP(i) <= not (A(i) and B(i));
        end loop;

    end process;


    TEMP(4) <= not ((B_TEMP(3) and A_TEMP(2)) or (A_TEMP(1) and B_TEMP(2) and B_TEMP(3)) or (B_TEMP(3) and B_TEMP(2) and B_TEMP(1) and (not C) ) or A_TEMP(3)
    );

    TEMP(3) <= not ((B_TEMP(2) and A_TEMP(1)) or (B_TEMP(2) and B_TEMP(1) and (not C)) or A_TEMP(2)
    );

    TEMP(2) <= not ((B_TEMP(1) and (not C)) or A_TEMP(1)
    );

    TEMP(1) <=  C;

    process(all)
    begin
        for i in TEMP'range loop
            SUM(i) <= ((B_TEMP(i) and (not A_TEMP(i))) xor TEMP(i));
        end loop;
    end process;
    
    C_OUT <= not (A_TEMP(4) or (A_TEMP(3) and B_TEMP(4)) or (A_TEMP(2) and B_TEMP(4) and B_TEMP(3)) or (
    	A_TEMP(1) and B_TEMP(4) and B_TEMP(3) and B_TEMP(2)) or (B_TEMP(4) and B_TEMP(3) and B_TEMP(2) and B_TEMP(1) and (not C))
    );


end Behavioral;
