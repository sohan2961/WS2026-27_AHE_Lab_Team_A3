library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_dot_product is end entity;

architecture test of tb_dot_product is
  signal clk, rst, start, input_valid, busy, done : std_logic := '0';
  signal a_data, b_data : signed(7 downto 0) := (others => '0');
  signal result : signed(31 downto 0);
  type test_vector is array (0 to 15) of integer;
  constant aa : test_vector := (1, 2, 3, 4, others => 0);
  constant bb : test_vector := (2, 1, 0, 3, others => 0);
begin
  clk <= not clk after 5 ns;
  dut : entity work.dot_product
    generic map(VECTOR_LENGTH => 16)
    port map(clk => clk, rst => rst, start => start,
      input_valid => input_valid, a_data => a_data, b_data => b_data,
      busy => busy, done => done, result => result);

  process
  begin
    rst <= '1'; wait until rising_edge(clk); wait for 1 ns;
    rst <= '0'; start <= '1';
    wait until rising_edge(clk); wait for 1 ns;
    start <= '0';
    assert busy = '1' report "DUT did not start" severity failure;
    for i in 0 to 15 loop
      a_data <= to_signed(aa(i), 8);
      b_data <= to_signed(bb(i), 8);
      input_valid <= '1';
      wait until rising_edge(clk); wait for 1 ns;
    end loop;
    input_valid <= '0';
    assert done = '1' report "Missing completion pulse" severity failure;
    assert busy = '0' report "DUT still busy" severity failure;
    assert result = to_signed(16, 32) report "Incorrect dot product" severity failure;
    report "PASS: dot product = 16" severity note;
    wait;
  end process;
end architecture;
