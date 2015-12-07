----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:27:17 07/27/2015 
-- Design Name: 
-- Module Name:    VisitCtrl - Behavioral 
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

entity VisitCtrl is
    Port ( t0:in STD_LOGIC;
			  t2:in STD_LOGIC;
			  PC : in  STD_LOGIC_VECTOR (15 downto 0);
           IR : in  STD_LOGIC_VECTOR (15 downto 0);
			  addr : in  STD_LOGIC_VECTOR (15 downto 0);
           aluout : in  STD_LOGIC_VECTOR (7 downto 0);
           qudata : out  STD_LOGIC_VECTOR (15 downto 0);
           cundata : out  STD_LOGIC_VECTOR (7 downto 0);
           DBUS : inout  STD_LOGIC_VECTOR (15 downto 0);
           ABUS : out  STD_LOGIC_VECTOR (15 downto 0);
			  npreq: out  STD_LOGIC;
			  nprd: out  STD_LOGIC;
			  npwr: out  STD_LOGIC;
			  MREQ: out  STD_LOGIC;
			  BHE: out  STD_LOGIC;
			  BLE: out  STD_LOGIC;
           RD : out  STD_LOGIC;
           WR : out  STD_LOGIC);
end VisitCtrl;

architecture Behavioral of VisitCtrl is

begin

	PROCESS(t0,t2,pc)
	begin

	if(t0='1')	then --取指周期
		RD<='0';
		WR<='1';
		MREQ<='0';
		BHE<='0';
		BLE<='0';
		npreq<='1';
		nprd<='1';
		npwr<='1';
		ABUS<=pc;
		qudata<=DBUS;	--取的是指令（16位）
		DBUS<="ZZZZZZZZZZZZZZZZ";
	
	elsif(t2='1') then --存储周期
	
		if(IR(15 downto 11)="01100") then --STA
			RD<='1';
			WR<='0';
			MREQ<='0';
			BHE<='0';
			BLE<='0';
			npreq<='1';
			nprd<='1';
			npwr<='1';
			DBUS<=("00000000"&aluout);									
			ABUS<=addr;
			
		elsif(IR(15 downto 11)="01110")	then --LDA
			RD<='0';
			WR<='1';
			MREQ<='0';
			BHE<='0';
			BLE<='0';
			npreq<='1';
			nprd<='1';
			npwr<='1';
			DBUS<="ZZZZZZZZZZZZZZZZ";	
			cundata<=DBUS(7 downto 0);
			ABUS<=addr;
			
		elsif(IR(15 downto 11)="11000")	then --IN
		RD<='1';
		WR<='1';
		MREQ<='1';
		BHE<='1';
		BLE<='1';
		npreq<='0';
		nprd<='1';
		npwr<='0';
		DBUS<="ZZZZZZZZZZZZZZZZ";		
		elsif(IR(15 downto 11)="11100")	then --OUT
		RD<='1';
		WR<='1';
		MREQ<='1';
		BHE<='1';
		BLE<='1';
		npreq<='0';
		nprd<='0';
		npwr<='1';
		DBUS<="ZZZZZZZZZZZZZZZZ";
		
			else
		RD<='1';
		WR<='1';
		MREQ<='1';
		BHE<='1';
		BLE<='1';
		npreq<='1';
		nprd<='1';
		npwr<='1';
		DBUS<="ZZZZZZZZZZZZZZZZ";
		end if;	
  else
  		RD<='1';
		WR<='1';
		MREQ<='1';
		BHE<='1';
		BLE<='1';
		npreq<='1';
		nprd<='1';
		npwr<='1';
		DBUS<="ZZZZZZZZZZZZZZZZ";
	end if;
	end process;

end Behavioral;

