----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:40:17 06/25/2015 
-- Design Name: 
-- Module Name:    zongxian - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity zongxian is
port(BS:out STD_LOGIC;
	BR: out STD_LOGIC_VECTOR(3 downto 0);
	BG: in STD_LOGIC_VECTOR(3 downto 0));
end zongxian;

architecture Behavioral of zongxian is
signal a1 : STD_LOGIC; 
signal a2 : STD_LOGIC; 
signal a3 : STD_LOGIC; 
signal a4 : STD_LOGIC; 

begin

a1<=BG(0);
a2<=BG(1);
a3<=BG(2);
a4<=BG(3);

process(a1,a2,a3,a4)
begin
if (a1='1')
	then BR<="1000";
			BS<='1';	
elsif(a1='0' and a2='1')
		then BR<="0100";
			  BS<='1';
elsif(a1='0' and a2='0' and a3='1')
			then BR<="0010";
			BS<='1';
elsif(a1='0' and a2='0' and a3='0' and a4='1')
				then BR<="0001";
				BS<='1';
elsif(a1='0' and a2='0' and a3='0' and a4='0')
				then BR<="0000";
					BS<='0';	
end if;
end process;
end Behavioral;

