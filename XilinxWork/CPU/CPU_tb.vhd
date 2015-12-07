--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   15:13:31 07/28/2015
-- Design Name:   
-- Module Name:   E:/xilinxwork/test/CPU_tb.vhd
-- Project Name:  test
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: CPU
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
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY CPU_tb IS
END CPU_tb;
 
ARCHITECTURE behavior OF CPU_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT CPU
    PORT(
         RST : IN  std_logic;
         CLK : IN  std_logic;
         ABUS : OUT  std_logic_vector(15 downto 0);
         DBUS : INOUT  std_logic_vector(15 downto 0);
         nMREQ : OUT  std_logic;
         nRD : OUT  std_logic;
         nWR : OUT  std_logic;
         nBHE : OUT  std_logic;
         nBLE : OUT  std_logic;
         IOAD : OUT  std_logic_vector(1 downto 0);
         IODB : INOUT  std_logic_vector(7 downto 0);
         nPREQ : OUT  std_logic;
         nPRD : OUT  std_logic;
         nPWR : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal RST : std_logic := '0';
   signal CLK : std_logic := '0';

	--BiDirs
   signal DBUS : std_logic_vector(15 downto 0);
   signal IODB : std_logic_vector(7 downto 0);

 	--Outputs
   signal ABUS : std_logic_vector(15 downto 0);
   signal nMREQ : std_logic;
   signal nRD : std_logic;
   signal nWR : std_logic;
   signal nBHE : std_logic;
   signal nBLE : std_logic;
   signal IOAD : std_logic_vector(1 downto 0);
   signal nPREQ : std_logic;
   signal nPRD : std_logic;
   signal nPWR : std_logic;

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: CPU PORT MAP (
          RST => RST,
          CLK => CLK,
          ABUS => ABUS,
          DBUS => DBUS,
          nMREQ => nMREQ,
          nRD => nRD,
          nWR => nWR,
          nBHE => nBHE,
          nBLE => nBLE,
          IOAD => IOAD,
          IODB => IODB,
          nPREQ => nPREQ,
          nPRD => nPRD,
          nPWR => nPWR
        );

   -- Clock process definitions
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period/2;
		CLK <= '1';
		wait for CLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
	------------------------------------MVI,R0,00001000------------------------------------------
		--初始化清零
		rst<='1';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--取指
		wait for 20 ns;
		rst<='0';
		dbus<="0100000000001000";
		
		--运算
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--存储
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--回写
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
	------------------------------------MOV,R1,R0------------------------------------------
		
		--取指
		wait for 10 ns;
		rst<='0';
		dbus<="0101000100000000";
		--dbus<="0100000000111111";
		
		--运算
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--存储
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--回写
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
	------------------------------------ADD------------------------------------------
		
		--取指
		wait for 10 ns;
		rst<='0';
		dbus<="0011000100000000";
		
		--运算
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--存储
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--回写
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";


	----------------------------------STA,R1,01100010------------------------------------------
		
		--取指
		wait for 10 ns;
		rst<='0';
		dbus<="0110000101100010";
		
		--运算
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--存储
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--回写
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";

		------------------------------------LDA,r3,01010000------------------------------------------
		
		--取指
		wait for 10 ns;
		rst<='0';
		dbus<="0111001101010000";
		
		--运算
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--存储
		wait for 10 ns;
		rst<='0';
		dbus<="0000000000101111";
		
		--回写
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";


		------------------------------------JZ,R3,00000000------------------------------------------
		
		--取指
		wait for 10 ns;
		rst<='0';
		dbus<="0001001100000000";
		
		--运算
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--存储
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--回写
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";	
		
		
		------------------------------------JMP,000,00000000------------------------------------------
		
		--取指
		wait for 10 ns;
		rst<='0';
		dbus<="0000000000000000";
		
		--运算
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--存储
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		--回写
		wait for 10 ns;
		rst<='0';
		dbus<="ZZZZZZZZZZZZZZZZ";
		
		-----------------检验JMP---------------
		--取指
		wait for 10 ns;
		rst<='0';
		dbus<="0100000000001000";
		    wait;
   end process;

END;
