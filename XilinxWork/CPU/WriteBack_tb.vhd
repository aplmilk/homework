
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   20:30:52 07/27/2015
-- Design Name:   WriteBack
-- Module Name:   E:/xilinxwork/CPU/WriteBack_tb.vhd
-- Project Name:  CPU
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: WriteBack
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

ENTITY WriteBack_tb_vhd IS
END WriteBack_tb_vhd;

ARCHITECTURE behavior OF WriteBack_tb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT WriteBack
	PORT(
		IR : IN std_logic_vector(15 downto 0);
		t3 : IN std_logic;
		addr : IN std_logic_vector(15 downto 0);
		aluout : IN std_logic_vector(7 downto 0);
		rtemp : IN std_logic_vector(7 downto 0);
		IODB: out std_logic_vector(7 downto 0);
		pc : IN std_logic_vector(15 downto 0);          
		pcupdate : OUT std_logic;
		pcnew : OUT std_logic_vector(15 downto 0);
		rupdate : OUT std_logic;
		rdata : OUT std_logic_vector(7 downto 0);
		raddr : OUT std_logic_vector(3 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL t3 :  std_logic := '0';
	SIGNAL IR :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL addr :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL aluout :  std_logic_vector(7 downto 0) := (others=>'0');
	SIGNAL rtemp :  std_logic_vector(7 downto 0) := (others=>'0');
	SIGNAL pc :  std_logic_vector(15 downto 0) := (others=>'0');

	--Outputs
	SIGNAL pcupdate :  std_logic:= '0';
	SIGNAL pcnew :  std_logic_vector(15 downto 0);
	SIGNAL rupdate :  std_logic:= '0';
	signal iodb:  std_logic_vector(7 downto 0);
	SIGNAL rdata :  std_logic_vector(7 downto 0);
	SIGNAL raddr :  std_logic_vector(3 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: WriteBack PORT MAP(
		IR => IR,
		t3 => t3,
		addr => addr,
		aluout => aluout,
		rtemp => rtemp,
		pc => pc,
		pcupdate => pcupdate,
		pcnew => pcnew,
		rupdate => rupdate,
		rdata => rdata,
		raddr => raddr
	);

	tb : PROCESS
	BEGIN

		--≥ı ºªØ
		t3<='0';
		ir<="0000000000000000";
		aluout<="00000000";
		rtemp<="00000000";
		addr<="0000000000000000";
		pc<="0000000000000000";
		
		--LDA
		wait for 10 ns;
		t3<='1';
		ir<="0111000100000000";
		aluout<="00000010";
		rtemp<="00000111";
		addr<="0000000000001010";
		pc<="0000000000000010";
		
		--t3÷√0
		wait for 10 ns;
		t3<='0';
		ir<="0111000000000000";
		aluout<="00000010";
		rtemp<="00000111";
		addr<="0000000000001010";
		pc<="0000000000000010";
		
		--ADD
		wait for 10 ns;
		t3<='1';
		ir<="0011000100000000";
		aluout<="00000010";
		rtemp<="00000111";
		addr<="0000000000001010";
		pc<="0000000000000010";
		
		--t3÷√0
		wait for 10 ns;
		t3<='0';
		ir<="0111000000000000";
		aluout<="00000010";
		rtemp<="00000111";
		addr<="0000000000001010";
		pc<="0000000000000010";
		
		--JMP
		wait for 10 ns;
		t3<='1';
		ir<="0000000001010101";
		aluout<="00000010";
		rtemp<="00000111";
		addr<="0000000000001010";
		pc<="0000000000000010";
		

		wait; -- will wait forever
	END PROCESS;

END;
