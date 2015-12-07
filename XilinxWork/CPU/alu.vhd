----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    23:58:23 07/26/2015 
-- Design Name: 
-- Module Name:    alu - Behavioral 
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

entity alu is
    Port ( IR : in  STD_LOGIC_VECTOR (15 downto 0);
           t1 : in  STD_LOGIC;
           rupdate : in  STD_LOGIC;
           raddr : in  STD_LOGIC_VECTOR (3 downto 0);
           rdata : in  STD_LOGIC_VECTOR (7 downto 0);
			  rst: in STD_LOGIC;
			  kdata: in std_logic_vector(7 downto 0);
           aluout : out  STD_LOGIC_VECTOR (7 downto 0);
           addr : out  STD_LOGIC_VECTOR (15 downto 0));
end alu;

architecture Behavioral of alu is
signal CF,ZF:std_logic;
signal cy,zy:std_logic;		--进位中间量
begin

process(ir,t1,rupdate,raddr,rdata,rst,kdata)
variable a:std_logic_vector(7 downto 0);	--寄存器 a,ad1 b,ad2 addr,d7//x
variable b:std_logic_vector(7 downto 0);


TYPE Reg is array (0 to 7) of std_logic_vector(7 downto 0);	--R0~R7
variable R:Reg ; 

variable ad1:integer;
variable ad2:integer;
variable ad:std_logic_vector(7 downto 0);
variable regaddr:integer;

variable c,d,result:std_logic_vector(8 downto 0);

begin
if(rst='1')	then 
	R(0):="00000000";	--??????
	R(1):="00000000";
	R(2):="00000000";
	R(3):="00000000";
	R(4):="00000000";
	R(5):="00000000";
	R(6):="00000000";
	R(7):="00000000";
	CF<='0';
	ZF<='0';
else

	ad1:=conv_integer(IR(10 downto 8));
	ad2:=conv_integer(IR(2 downto 0));		
	ad:=IR(7 downto 0);
	regaddr:=conv_integer(raddr);
	
	--数据传送
	if(rupdate='1' and IR(15 downto 11)="10000")	then --消CY
		CF<='0';
	elsif(rupdate='1' and IR(15 downto 11)="11000")	then 	--消0
		ZF<='0';
	elsif(rupdate='1')	then 
		R(regaddr):=rdata;
	end if;
	
	if(t1='1')	then 
	--操作数&地址准备&运算
	case IR(15 downto 11) is

		when "00000"=>			--JMP
			a:=R(ad1);
			b:=ad;
			addr<=(R(7)&b);
		
		when "00010"=>			--JZ
			a:=R(ad1);
			b:=ad;
			addr<=(R(7)&b);
			aluout<=a;
			
		when "00100"=>			--SUB
			a:=R(ad1);
			b:=R(ad2);
			aluout<=a-b-("0000000"&CF);
			if(a=b)	then Zy<='1';
			else
				Zy<='0';
			end if;
			
		when "00110"=>			--ADD
			a:=R(ad1);
			b:=R(ad2);
			c:=('0'&a);
			d:=('0'&b);
			result:=c+d+("0000000"&CF);
			aluout<=result(7 downto 0);
			Cy<=result(8);
			
		when "01000"=>			--MVI
			a:=R(ad1);
			b:=ad;
			aluout<=b;	
			
		when "01010"=>			--MOV
			a:=R(ad1);
			b:=R(ad2);
			aluout<=b;				
			
		when "01100"=>			--STA
			a:=R(ad1);
			b:=ad;
			addr<=(R(7)&b);
			aluout<=a;
			
		when "01110"=>			--LDA
			a:=R(ad1);
			b:=ad;
			addr<=(R(7)&b);
			
		when "10000"=>			--消CY
			a:=R(ad1);
			b:=ad;		
				
		when"11000"=>			--IN
			a:=R(ad1);
			b:=ad;
			aluout<=kdata;
			
		when"11100"=>			--OUT
			a:=R(ad1);
			b:=ad;
			aluout<=a;
			
		when others=>			--消0		(衔薮砦笫淙?
			a:=R(ad1);
			b:=ad;
	end case;
	
	elsif(t1='0') then	--其他时刻传进位标志
		CF<=cy;
		ZF<=zy;
end if;
end if;
end process;
end Behavioral;

