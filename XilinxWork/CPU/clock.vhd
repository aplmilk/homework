----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    23:02:42 07/26/2015 
-- Design Name: 
-- Module Name:    clock - Behavioral 
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clock is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           t : out  STD_LOGIC_VECTOR (3 downto 0));
end clock;

architecture Behavioral of clock is
signal q:std_logic_vector(3 downto 0);	
begin

process(clk,rst)
	--variable a:std_logic_vector(3 downto 0);
	begin
	if(rst='1')	then
		t<="0001";
		q<="0010";	
		--a:="0000";
		
	elsif(clk='1' and clk'event) then
--		if(q="1000")	then	
--			q<="0010";
--			t<="0001";
--		else
			q(0)<=q(3);	--×óÒÆ
			q(1)<=q(0);
			q(2)<=q(1);
			q(3)<=q(2);	
			t<=q;	--¸³Öµ
	--	end if;
		
		
		
	end if;
	end process;

end Behavioral;

