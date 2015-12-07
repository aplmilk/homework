----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    00:09:00 07/27/2015 
-- Design Name: 
-- Module Name:    store - Behavioral 
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

entity store is
    Port ( IR : in  STD_LOGIC_VECTOR (15 downto 0);
           t2 : in  STD_LOGIC;
           data : in  STD_LOGIC_VECTOR (7 downto 0);
           Rtemp : out  STD_LOGIC_VECTOR (7 downto 0));
end store;

architecture Behavioral of store is
begin
process(t2,data)

variable rtep:std_logic_vector(7 downto 0);

begin
if(t2='1')	then
	if(IR(15 downto 11)="01100") then 	--STA,存（存的直接通过alu、控制端存储）
		rtemp<=data;
	elsif(IR(15 downto 11)="01110") then 	--LDA，取
		rtep:=data;
		rtemp<=data;
	else	--其他，不处理
		rtemp<=data;
		end if;
--rtemp<=rtep;

end if;
end process;
end Behavioral;

