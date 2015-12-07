
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   23:28:59 07/27/2015
-- Design Name:   alu
-- Module Name:   E:/xilinxwork/CPU/alu_tb.vhd
-- Project Name:  CPU
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: alu
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

ENTITY alu_tb_vhd IS
END alu_tb_vhd;

ARCHITECTURE behavior OF alu_tb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT alu
	PORT(
		IR : IN std_logic_vector(15 downto 0);
		t1 : IN std_logic;
		rupdate : IN std_logic;
		raddr : IN std_logic_vector(3 downto 0);
		rdata : IN std_logic_vector(7 downto 0);
		rst : IN std_logic;          
		aluout : OUT std_logic_vector(7 downto 0);
		addr : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL t1 :  std_logic := '0';
	SIGNAL rupdate :  std_logic := '0';
	SIGNAL rst :  std_logic := '0';
	SIGNAL IR :  std_logic_vector(15 downto 0) := (others=>'0');
	SIGNAL raddr :  std_logic_vector(3 downto 0) := (others=>'0');
	SIGNAL rdata :  std_logic_vector(7 downto 0) := (others=>'0');

	--Outputs
	SIGNAL aluout :  std_logic_vector(7 downto 0);
	SIGNAL addr :  std_logic_vector(15 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: alu PORT MAP(
		IR => IR,
		t1 => t1,
		rupdate => rupdate,
		raddr => raddr,
		rdata => rdata,
		rst => rst,
		aluout => aluout,
		addr => addr
	);

	tb : PROCESS
	BEGIN
		--初始化
		rst<='1';
		t1<='1';
		ir<="0000000000000000";
		rupdate<='0';
		rdata<="00000000";
		raddr<="0000";
		
		--开始
		
		--MVI,R0,00001000
		wait for 10 ns;
		rst<='0';
		t1<='1';
		ir<="0100000000001000";
		rupdate<='0';
		rdata<="00000000";
		raddr<="0000";
	
		--MVI,R0,00001000
		wait for 10 ns;
		rst<='0';
		t1<='0';
		ir<="0100000000001000";
		rupdate<='1';
		rdata<="00001000";
		raddr<="0000";
		
		--MOV,R1,R0
		wait for 10 ns;
		rst<='0';
		t1<='1';
		ir<="0101000100000000";
		rupdate<='0';
		rdata<="00000000";
		raddr<="0000";
		
		--写入
		wait for 10 ns;
		rst<='0';
		t1<='0';
		ir<="0100000000001000";
		rupdate<='1';
		rdata<="00001000";
		raddr<="0001";
		
		--ADD,R1,R0
		wait for 10 ns;
		rst<='0';
		t1<='1';
		ir<="0011000100000000";
		rupdate<='0';
		rdata<="00000000";
		raddr<="0000";

		--更改寄存器的值(R1<-0111)&JZ,R1
		wait for 10 ns;
		rst<='0';
		t1<='1';
		ir<="0001000100101000";
		rupdate<='1';
		rdata<="00000111";
		raddr<="0001";
		
		--jz,r2(t1为0)
		wait for 10 ns;
		rst<='0';
		t1<='0';
		ir<="0001001000101000";
		rupdate<='0';
		rdata<="00000000";
		raddr<="0000";		
		
		--jz,r2&改R7
		wait for 10 ns;
		rst<='0';
		t1<='1';
		ir<="0001001000101000";
		rupdate<='1';
		rdata<="11100000";
		raddr<="0111";
				
		--STA,R1,00101000
		wait for 10 ns;
		rst<='0';
		t1<='1';
		ir<="0110000100101000";
		rupdate<='0';
		rdata<="00000000";
		raddr<="0000";

		wait; -- will wait forever
	END PROCESS;

END;
