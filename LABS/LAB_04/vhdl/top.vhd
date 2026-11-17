
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity top is
    Port (
        CLK100MHZ    : in  STD_LOGIC;
        CPU_RESETN   : in  STD_LOGIC;
        UART_TXD_IN  : in  STD_LOGIC;
        UART_RXD_OUT : out STD_LOGIC;
        LED          : out STD_LOGIC_VECTOR(15 downto 0)
    );
end top;

architecture Behavioral of top is

    signal rm_clk  : STD_LOGIC;
    signal din     : STD_LOGIC_VECTOR(15 downto 0);
    signal dout    : STD_LOGIC_VECTOR(15 downto 0);
    signal reset_h : STD_LOGIC;
    
    
component rm_a is
    port (
        clk  : in  STD_LOGIC;
        din  : in  STD_LOGIC_VECTOR(15 downto 0);
        dout : out STD_LOGIC_VECTOR(15 downto 0)
    );
end component;


begin

    -- Nexys A7 reset button is active-low.
    -- Convert it to active-high system reset.
    reset_h <= not CPU_RESETN;

    -- Static MicroBlaze system
    u_sys : entity work.design_1_wrapper
        port map (
            clk100          => CLK100MHZ,
            reset_rtl_0     => reset_h,
            rm_clk          => rm_clk,
            rm_din          => din,
            rm_dout         => dout,
            uart_rtl_0_rxd  => UART_TXD_IN,
            uart_rtl_0_txd  => UART_RXD_OUT
        );

    -- Reconfigurable Module A
    u_rm : rm_a
        port map (
            clk  => rm_clk,
            din  => din,
            dout => dout
        );

    -- Display module output using LEDs
    LED <= dout;

end Behavioral;
