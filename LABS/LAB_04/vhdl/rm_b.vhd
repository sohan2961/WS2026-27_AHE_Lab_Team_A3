
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity rm_b is
    Port (
        clk  : in  STD_LOGIC;
        din  : in  STD_LOGIC_VECTOR(15 downto 0);
        dout : out STD_LOGIC_VECTOR(15 downto 0)
    );
end rm_b;

architecture rtl of rm_b is
begin
    process(clk)
    begin
        if rising_edge(clk) then
            dout <= not din;
        end if;
    end process;
end rtl;

