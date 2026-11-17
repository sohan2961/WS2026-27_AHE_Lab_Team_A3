
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity rm_c is
    Port (
        clk  : in  STD_LOGIC;
        din  : in  STD_LOGIC_VECTOR(15 downto 0);
        dout : out STD_LOGIC_VECTOR(15 downto 0)
    );
end rm_c;

architecture rtl of rm_c is
begin
    process(clk)
    begin
        if rising_edge(clk) then
            dout <= din(7 downto 0) &
                    din(15 downto 8);
        end if;
    end process;
end rtl;
