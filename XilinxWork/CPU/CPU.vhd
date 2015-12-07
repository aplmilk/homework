----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:54:56 07/27/2015 
-- Design Name: 
-- Module Name:    CPU - Behavioral 
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
library UNISIM;
use UNISIM.VComponents.all;

entity CPU is
    Port ( RST : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           ABUS : out  STD_LOGIC_VECTOR (15 downto 0);
           DBUS : inout  STD_LOGIC_VECTOR (15 downto 0);
           nMREQ : out  STD_LOGIC;
           nRD : out  STD_LOGIC;
           nWR : out  STD_LOGIC;
           nBHE : out  STD_LOGIC;
           nBLE : out  STD_LOGIC;
			  --外设
           IOAD : out  STD_LOGIC_VECTOR (1 downto 0);
			  IODK	: IN  STD_LOGIC_VECTOR (7 downto 0);
           IODB : out  STD_LOGIC_VECTOR (7 downto 0);
           nPREQ : out  STD_LOGIC;
           nPRD : out  STD_LOGIC;
           nPWR : out  STD_LOGIC;
			  --FPGA输出
			  fdata:out  STD_LOGIC_VECTOR (15 downto 0);
			  faddr:out  STD_LOGIC_VECTOR (15 downto 0);
			  fir:out  STD_LOGIC_VECTOR (15 downto 0);
			  fclk:out  STD_LOGIC_VECTOR (3 downto 0)
			  );
end CPU;

architecture Behavioral of CPU is

component bufgp port
(
	i:in std_logic;
	o:out std_logic
);
end component;

signal clkgp:std_logic;

component clock is
	Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           t : out  STD_LOGIC_VECTOR (3 downto 0));
end component ;

component quzhi is
    Port ( t0 : in  STD_LOGIC;
           pcupdate : in  STD_LOGIC;
           pcnew : in  STD_LOGIC_VECTOR(15 downto 0);
           IRIN : in  STD_LOGIC_VECTOR (15 downto 0);
           rst : in  STD_LOGIC;
           IROUT : out  STD_LOGIC_VECTOR (15 downto 0);
           PCout : out  STD_LOGIC_VECTOR (15 downto 0)
			  );
end component ;

component store is
    Port ( IR : in  STD_LOGIC_VECTOR (15 downto 0);
           t2 : in  STD_LOGIC;
           data : in  STD_LOGIC_VECTOR (7 downto 0);
           Rtemp : out  STD_LOGIC_VECTOR (7 downto 0)
			  );
end component ;

component alu is
    Port ( IR : in  STD_LOGIC_VECTOR (15 downto 0);
           t1 : in  STD_LOGIC;
           rupdate : in  STD_LOGIC;
           raddr : in  STD_LOGIC_VECTOR (3 downto 0);
           rdata : in  STD_LOGIC_VECTOR (7 downto 0);
			  rst: in STD_LOGIC;
			  kdata: in std_logic_vector(7 downto 0);
           aluout : out  STD_LOGIC_VECTOR (7 downto 0);
           addr : out  STD_LOGIC_VECTOR (15 downto 0)
			  );
end component ;

component WriteBack is
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
           raddr : out  STD_LOGIC_VECTOR (3 downto 0)
			  );
end component ;

component VisitCtrl is
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
           WR : out  STD_LOGIC
			  );
end component ;

signal  	t0,t1,t2,t3:std_logic;
signal	pcupdate,rupdate:std_logic;
signal	pcnew,ir,pcout,addr,quzhidata,addrbus:std_logic_vector(15 downto 0);
signal 	storedata,aluout,rtemp,rdata:std_logic_vector(7 downto 0);
signal 	raddr:std_logic_vector(3 downto 0);

--signal 	wr,rd,bhe,ble,cs:std_logic;

--^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^信号表

begin

u1:bufgp port map(
	i=>clk,
	o=>clkgp
);

clockpart:clock port map(
	clk=>clkgp,
	rst=>rst,
	t(0)=>t0,
	t(1)=>t1,
	t(2)=>t2,
	t(3)=>t3
);

quzhipart:quzhi port map(

	rst=>rst,
	t0=>t0,
	pcupdate=>pcupdate,
	pcnew=>pcnew,
	irin=>quzhidata,
	irout=>ir,
	pcout=>pcout
);

alupart:alu port map(
	t1=>t1,
	ir=>ir,
	rupdate=>rupdate,
	raddr=>raddr,
	rdata=>rdata,
	rst=>rst,
	kdata=>IODK,
	aluout=>aluout,
	addr=>addr

);

storepart:store port map(
	ir=>ir,
	t2=>t2,
	data=>storedata,	
	rtemp=>rtemp

);

writebackpart:WriteBack port map(

	t3=>t3,
	ir=>ir,
	addr=>addr,
	aluout=>aluout,
	rtemp=>rtemp,
	IODB=>IODB,
	pc=>pcout,
	pcupdate=>pcupdate,
	pcnew=>pcnew,
	rupdate=>rupdate,
	rdata=>rdata,
	raddr=>raddr
);

visitctrlpart:VisitCtrl port map(
	t0=>t0,
	t2=>t2,
	pc=>pcout,
	addr=>addr,
	ir=>ir,
	aluout=>aluout,
	qudata=>quzhidata,
	cundata=>storedata,
	dbus=>dbus,
	abus=>addrbus,
	npreq=>npreq,
	nprd=>nprd,
	npwr=>npwr,
	rd=>nrd,
	wr=>nwr,
	mreq=>nmreq,
	bhe=>nbhe,
	ble=>nble
);


IOAD<=IR(1 downto 0);
abus<=addrbus;
fdata<=dbus;
faddr<=addrbus;
fir<=ir;
fclk(0)<=t0;
fclk(1)<=t1;
fclk(2)<=t2;
fclk(3)<=t3;

--nmreq<=cs;
--nrd<=rd;
--nwr<=wr;
--nbhe<=bhe;
--nble<=ble;


end Behavioral;

