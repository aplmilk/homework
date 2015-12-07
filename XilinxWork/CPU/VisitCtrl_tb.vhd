
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   21:32:39 07/27/2015
-- Design Name:   VisitCtrl
-- Module Name:   E:/xilinxwork/CPU/VisitCtrl_tb.vhd
-- Project Name:  CPU
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: VisitCtrl
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

ENTITY VisitCtrl_tb_vhd IS
END VisitCtrl_tb_vhd;

ARCHITECTURE behavior OF VisitCtrl_tb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT VisitCtrl
	PORT(
		t0 : IN std_logic;
		t2 : IN std_logic;
		PC : IN std_logic_vector(15 downto 0);
		IR : IN std_logic_vector(15 downto 0);
		addr : IN std_logic_vector(15 downto 0);
		aluout : IN std_logic_vector(7 downto 0);    
		DBUS : INOUT std_logic_vector(15 downto 0);      
		qudata : OUT std_logic_vector(15 downto 0);
		cundata : OUT std_logic_vector(7 downto 0);
		ABUS : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL t0 :  std_logic := '0';
	SIGNAL t2 :  std_logic := '0';
	SIGNAL PC :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL IR :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL addr :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL aluout :  std_logic_vector(7 downto 0) := (others=>'0');

	--BiDirs
	SIGNAL DBUS :  std_logic_vector(15 downto 0);

	--Outputs
	SIGNAL qudata :  std_logic_vector(15 downto 0);
	SIGNAL cundata :  std_logic_vector(7 downto 0);
	SIGNAL ABUS :  std_logic_vector(15 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: VisitCtrl PORT MAP(
		t0 => t0,
		t2 => t2,
		PC => PC,
		IR => IR,
		addr => addr,
		aluout => aluout,
		qudata => qudata,
		cundata => cundata,
		DBUS => DBUS,
		ABUS => ABUS
	);

	tb : PROCESS
	BEGIN
--		--初始化
--		t0<='0';
--		t2<='0';
--		pc<="0000000000000000";
--		aluout<="00000000";
--		ir<="0000000000000000";
--		DBUS<="0000000000000000";
		
		--取指周期
		wait for 10 ns;
		t0<='1';
		t2<='0';
		pc<="0000000010101010";
		aluout<="00000000";
		ir<="0000000000000000";
		DBUS<="0011000101000000";

		--存储周期(LDA)
		wait for 10 ns;
		t0<='0';
		t2<='1';
		pc<="0000000010101010";
		aluout<="10111111";
		ir<="0111000111001100";
		DBUS<="0100110011110000";

		--t2置0
		wait for 10 ns;
		t0<='0';
		t2<='0';
		pc<="0000000010101010";
		aluout<="10111111";
		ir<="0111000111001100";
		DBUS<="ZZZZZZZZZZZZZZZZ";
		
		--存储周期(STA)
		wait for 10 ns;
		t0<='0';
		t2<='1';
		pc<="0000000010101010";
		aluout<="10111111";
		ir<="0110000111001100";
		DBUS<="ZZZZZZZZZZZZZZZZ";
	
		--t2置0
		wait for 10 ns;
		t0<='0';
		t2<='0';
		pc<="0000000010101010";
		aluout<="10111111";
		ir<="0110000111001100";
		DBUS<="ZZZZZZZZZZZZZZZZ";
		
		--存储周期(其他)
		wait for 10 ns;
		t0<='0';
		t2<='1';
		pc<="0000000010101010";
		aluout<="10111111";
		ir<="0011000111001100";
		DBUS<="ZZZZZZZZZZZZZZZZ";
		
		wait; -- will wait forever
	END PROCESS;

END;
