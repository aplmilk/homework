----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:05:42 07/27/2015 
-- Design Name: 
-- Module Name:    WriteBack - Behavioral 
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

entity WriteBack is
    Port ( IR : in  STD_LOGIC_VECTOR (15 downto 0);
           t3 : in  STD_LOGIC;
           addr : in  STD_LOGIC_VECTOR (15 downto 0);
           aluout : in  STD_LOGIC_VECTOR (7 downto 0);
           rtemp : in  STD_LOGIC_VECTOR (7 downto 0);
			  IODB: out std_logic_vector(7 downto 0);
           pc : in  STD_LOGIC_VECTOR (15 downto 0);
           pcupdate : out  STD_LOGIC;
           pcnew : out  STD_LOGIC_VECTOR (15 downto 0);
           rupdate : out  STD_LOGIC;
           rdata : out  STD_LOGIC_VECTOR (7 downto 0);
           raddr : out  STD_LOGIC_VECTOR (3 downto 0));
end WriteBack;

architecture Behavioral of WriteBack is

begin
process(t3,rtemp,aluout,rtemp,ir,pc)
begin
if(t3='1')	then 
	if(IR(15 downto 11)="01110")	then	--LDA,取数
		rdata<=rtemp;
		raddr<=('0'&IR(10 downto 8));
		rupdate<='1';
		pcupdate<='1';
		pcnew<=pc+1;
		IODB<="00000000";
	elsif(IR(15 downto 11)="00110" or IR(15 downto 11)="00100" or IR(15 downto 11)="01000" or IR(15 downto 11)="01010" OR IR(15 downto 11)="11000") then	--ADD\SUB\MV1\MOV
		rdata<=aluout;
		raddr<=('0'&IR(10 downto 8));
		rupdate<='1';	
		pcupdate<='1';
		pcnew<=pc+1;
		IODB<="00000000";
	elsif(IR(15 downto 11)="10000")	then --消CY
		rdata<=aluout;
		raddr<="1000";
		rupdate<='1';	
		pcupdate<='1';
		pcnew<=pc+1;	
		IODB<="00000000";
	elsif(IR(15 downto 11)="10000")	then --消0
		rdata<=aluout;
		raddr<="1100";
		rupdate<='1';	
		pcupdate<='1';
		pcnew<=pc+1;	
		IODB<="00000000";
--	elsif(IR(15 downto 11)="11000")	then --IN
--		rdata<="10001000";
--		raddr<=('0'&IR(10 downto 8));
--		rupdate<='1';	
--		pcupdate<='1';
--		pcnew<=pc+1;
--		IODB<="00000000";
	elsif(IR(15 downto 11)="11100")	then --OUT
		rdata<=aluout;
		raddr<="1100";
		rupdate<='0';	
		pcupdate<='1';
		pcnew<=pc+1;
		IODB<=ALUOUT;
	elsif(IR(15 downto 11)="00000" )	then --JMP
		pcupdate<='1';
		pcnew<=addr;
		rupdate<='0';
		IODB<="00000000";
	elsif(IR(15 downto 11)="00010" )	then --JZ
		if(aluout="00000000")	then 
			pcupdate<='1';
			pcnew<=addr;
			rupdate<='0';
			IODB<="00000000";
		else		--不为0执行pc+1
			pcupdate<='1';
			pcnew<=pc+1;	
			rupdate<='0';
			IODB<="00000000";			
		end if;
	else 	--其他
	rupdate<='0';
	pcupdate<='1';
	pcnew<=pc+1;
	IODB<="00000000";
	end if;

elsif(t3='0')	then
	pcupdate<='0';
	rupdate<='0';

end if;
	
end process;
end Behavioral;

