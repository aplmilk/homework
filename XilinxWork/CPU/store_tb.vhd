
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   17:43:06 07/27/2015
-- Design Name:   store
-- Module Name:   E:/xilinxwork/CPU/store_tb.vhd
-- Project Name:  CPU
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: store
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

ENTITY store_tb_vhd IS
END store_tb_vhd;

ARCHITECTURE behavior OF store_tb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT store
	PORT(
		IR : IN std_logic_vector(15 downto 0);
		t2 : IN std_logic;
		data : IN std_logic_vector(7 downto 0);          
		Rtemp : OUT std_logic_vector(7 downto 0);
		MREQ : OUT std_logic;
		BHE : OUT std_logic;
		BLE : OUT std_logic;
		RD : OUT std_logic;
		WR : OUT std_logic
		);
	END COMPONENT;

	--Inputs
	SIGNAL t2 :  std_logic := '0';
	SIGNAL IR :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL data :  std_logic_vector(7 downto 0) := (others=>'0');

	--Outputs
	SIGNAL Rtemp :  std_logic_vector(7 downto 0);
	SIGNAL MREQ :  std_logic:= '0';
	SIGNAL BHE :  std_logic:= '0';
	SIGNAL BLE :  std_logic:= '0';
	SIGNAL RD :  std_logic:= '0';
	SIGNAL WR :  std_logic:= '0';

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: store PORT MAP(
		IR => IR,
		t2 => t2,
		data => data,
		Rtemp => Rtemp,
		MREQ => MREQ,
		BHE => BHE,
		BLE => BLE,
		RD => RD,
		WR => WR
	);

	tb : PROCESS
	BEGIN

	--初始化
	wait for 10 ns;
	t2<='0';
	ir<="0000000000000000";
	data<="00000000";

	--取
	wait for 10 ns;
	t2<='1';
	ir<="0111000000000000";
	data<="00101000";
	
	--t2置0
	wait for 10 ns;
	t2<='0';
	ir<="0111000000000000";
	data<="00101000";
	
	--存
	wait for 10 ns;
	t2<='1';
	ir<="0110000000000000";
	data<="11111111";	
	
	--t2置0
	wait for 10 ns;
	t2<='0';
	ir<="0111000000000000";
	data<="00101000";
	
	--其他
	wait for 10 ns;
	t2<='1';
	ir<="0000000000000000";	--JMP
	data<="01010101";


		wait; -- will wait forever
	END PROCESS;

END;
