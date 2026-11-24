library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- 16 pairs of signed INT8 inputs; one multiply-accumulate per accepted cycle.
-- start may only be asserted while busy='0'. A new dot product resets sum.
entity dot_product is
  generic (VECTOR_LENGTH : positive := 16);
  port (
    clk         : in  std_logic;
    rst         : in  std_logic;
    start       : in  std_logic;
    input_valid : in  std_logic;
    a_data      : in  signed(7 downto 0);
    b_data      : in  signed(7 downto 0);
    busy        : out std_logic;
    done        : out std_logic;
    result      : out signed(31 downto 0)
  );
end entity;

architecture rtl of dot_product is
  signal count     : natural range 0 to VECTOR_LENGTH := 0;
  signal active    : std_logic := '0';
  signal finished  : std_logic := '0';
  signal sum_reg   : signed(31 downto 0) := (others => '0');
begin
  busy   <= active;
  done   <= finished;
  result <= sum_reg;

  process(clk)
    variable product : signed(15 downto 0);
  begin
    if rising_edge(clk) then
      if rst = '1' then
        count <= 0;
        active <= '0';
        finished <= '0';
        sum_reg <= (others => '0');
      else
        finished <= '0';
        if active = '0' then
          if start = '1' then
            count <= 0;
            sum_reg <= (others => '0');
            active <= '1';
          end if;
        elsif input_valid = '1' then
          product := a_data * b_data;
          sum_reg <= sum_reg + resize(product, 32);
          if count = VECTOR_LENGTH - 1 then
            active <= '0';
            finished <= '1';
            count <= 0;
          else
            count <= count + 1;
          end if;
        end if;
      end if;
    end if;
  end process;
end architecture;
