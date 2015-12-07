LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY inteltb IS
END inteltb;
 
ARCHITECTURE behavior OF inteltb IS 
 
    COMPONENT RAM
    PORT(
         A : IN  std_logic_vector(9 downto 0);
         IOIN : IN  std_logic_vector(3 downto 0);
			IOOUT:OUT std_logic_vector(3 downto 0);
         CS : IN  std_logic;
         WE : IN  std_logic;
         VCC : IN  std_logic;
         GUD : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic_vector(9 downto 0) := (others => '0');
   signal CS : std_logic := '1';
   signal WE : std_logic := '0';
   signal VCC : std_logic := '0';
   signal GUD : std_logic := '0';

	--BiDirs
   signal IOIN : std_logic_vector(3 downto 0) := "0000"; 
	signal IOOUT:std_logic_vector(3 downto 0) :="0000";
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: RAM PORT MAP (
          A => A,
          IOIN => IOIN,
			 IOOUT => IOOUT,
          CS => CS,
          WE => WE,
          VCC => VCC,
          GUD => GUD
        );



   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
 		wait for 100 ns;	
		A <= "0000000000";
		IOIN<="1010";
		CS<='0';
		WE<='0';
		  wait for 100 ns;	
		A <= "0000000000";
		IOIN<="0000";
		CS<='0';
		WE<='1';
		  wait for 100 ns;	
	A <= "0000000001";
		IOIN<="1110";
		CS<='0';
		WE<='0';  
		
		 wait for 100 ns;	
		A <= "0000000001";
		IOIN<="0000";
		CS<='0';
		WE<='1';  
		
		 wait for 100 ns;	
	A <= "0000000011";
		IOIN<="0100";
		CS<='0';
		WE<='0';  
		
		 wait for 100 ns;	
		A <= "0000000011";
		IOIN<="0000";
		CS<='0';
		WE<='1';  
		
		
		 wait for 100 ns;	
	A <= "1000100011";
		IOIN<="0110";
		CS<='0';
		WE<='0';  
		
		 wait for 100 ns;	
		A <= "1000100011";
		IOIN<="0000";
		CS<='0';
		WE<='1';  
		
		wait for 100 ns;	
		A <= "1111111111";
		IOIN<="1100";
		CS<='0';
		WE<='0';  
		
		 wait for 100 ns;	
		A <= "1111111111";
		IOIN<="0000";
		CS<='0';
		WE<='1';  
		
		wait;
		
   end process;

END;
