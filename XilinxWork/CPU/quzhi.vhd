----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    23:47:22 07/26/2015 
-- Design Name: 
-- Module Name:    quzhi - Behavioral 
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

entity quzhi is
    Port ( t0 : in  STD_LOGIC;
           pcupdate : in  STD_LOGIC;
           pcnew : in  STD_LOGIC_VECTOR(15 downto 0);
           IRIN : in  STD_LOGIC_VECTOR (15 downto 0);
           rst : in  STD_LOGIC;
           IROUT : out  STD_LOGIC_VECTOR (15 downto 0);
           PCout : out  STD_LOGIC_VECTOR (15 downto 0));
end quzhi;

architecture Behavioral of quzhi is
signal pc:STD_LOGIC_VECTOR (15 downto 0);
begin

	process(t0,rst,pcnew,irin)
	variable ir:STD_LOGIC_VECTOR (15 downto 0);
	
	begin
	if(rst='1')	then	---复位
		pcout<="0000000000000000";					
		pc<="0000000000000000";	--初始化??
		ir:=IRIN;	
		IROUT<=IRIN;	
	else
		if(pcupdate='1')	then pc<=pcnew;	--pc更新
		end if;
		--if(t0='0' and t0'event)	then 
			if(t0='1')	then
			pcout<=pc;	--??主存发送16位pc地址
			ir:=IRIN;	--读入数??放在IR中
			IROUT<=IRIN;	--向各模块发出指令
		end if;
	end if;

	end process;
	
end Behavioral;

