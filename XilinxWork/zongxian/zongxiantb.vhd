--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   10:30:02 06/25/2015
-- Design Name:   
-- Module Name:   E:/xilinxwork/zongxian/zongxiantb.vhd
-- Project Name:  zongxian
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: zongxian
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
 
ENTITY zongxiantb IS
END zongxiantb;
 
ARCHITECTURE behavior OF zongxiantb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT zongxian
    PORT(
         BS : OUT  std_logic;
         BR : OUT  std_logic_vector(3 downto 0);
         BG : IN  std_logic_vector(3 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal BG : std_logic_vector(3 downto 0) := (others => '0');

 	--Outputs
   signal BS : std_logic;
   signal BR : std_logic_vector(3 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: zongxian PORT MAP (
          BS => BS,
          BR => BR,
          BG => BG
        );

 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	
		BG<="1000";
      wait for 100 ns;	
		BG<="1010";
		      wait for 100 ns;	
		BG<="0010";
      -- insert stimulus here 

      wait;
   end process;

END;
