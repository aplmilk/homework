
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   09:33:52 07/27/2015
-- Design Name:   quzhi
-- Module Name:   E:/xilinxwork/CPU/quzhi_tb.vhd
-- Project Name:  CPU
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: quzhi
--
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends 
-- that these types always be used for the top-level I/O of a design in order 
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;

ENTITY quzhi_tb_vhd IS
END quzhi_tb_vhd;

ARCHITECTURE behavior OF quzhi_tb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT quzhi
	PORT(
		t0 : IN std_logic;
		pcupdate : IN std_logic;
		pcnew : IN std_logic_vector(15 downto 0);
		IRIN : IN std_logic_vector(15 downto 0);
		rst : IN std_logic;          
		IROUT : OUT std_logic_vector(15 downto 0);
		PCout : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL t0 :  std_logic := '0';
	SIGNAL pcupdate :  std_logic := '0';
	SIGNAL rst :  std_logic := '0';
	SIGNAL pcnew :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL IRIN :  std_logic_vector(15 downto 0) := (others=>'0');

	--Outputs
	SIGNAL IROUT :  std_logic_vector(15 downto 0);
	SIGNAL PCout :  std_logic_vector(15 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: quzhi PORT MAP(
		t0 => t0,
		pcupdate => pcupdate,
		pcnew => pcnew,
		IRIN => IRIN,
		rst => rst,
		IROUT => IROUT,
		PCout => PCout
	);

	tb : PROCESS
	BEGIN

		--初始化
		rst<='1';	
		t0<='0';
		pcupdate<='0';
		pcnew<="0000000000000001";
		--irin<="0000000000000010";
		
		--开始
		wait for 10 ns;
		rst<='0';
		t0<='1';
		pcupdate<='1';		--pc更新
		pcnew<="0000000000000001";
		irin<="0000000000000011";
		--PC更新&过渡
		wait for 10 ns;
		rst<='0';
		t0<='0';
		pcupdate<='0';		--pc不更新
		pcnew<="0000000000001101";
		irin<="0000000000000010";
		
		--PC不更新
		wait for 10 ns;
		rst<='0';
		t0<='1';
		pcupdate<='1';		--pc更新
		pcnew<="0000000000001111";
		irin<="0000000000000110";
		-- Place stimulus here

		wait; -- will wait forever
	END PROCESS;

END;
