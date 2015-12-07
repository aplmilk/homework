library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity RAM is
    Port ( A : in  STD_LOGIC_VECTOR (9 downto 0); --地址输入端
           IOIN : in  STD_LOGIC_VECTOR (3 downto 0); --数据输入 输出端
			  IOOUT:OUT std_logic_vector(3 downto 0);

           CS : in  STD_LOGIC; --片选信号 低电平有效
           WE : in  STD_LOGIC; -- 写允许信号 0为写 1为读
           VCC : in  STD_LOGIC; --电源
           GUD : in  STD_LOGIC); --接地端
end RAM;

architecture Behavioral of RAM is
	TYPE INTEL is array (0 to 63) of std_logic_vector(63 downto 0);
	signal sram:INTEL ; --64*64阵列
	--signal i : integer range 0 to 63;
	signal Arow:std_logic_vector(5 downto 0) := "000000";
	signal Acol :std_logic_vector(3 downto 0):= "0000";
	signal tmp :std_logic;
	signal row:integer:=0;
	signal col:integer:=0;
begin

tmp <= (not CS) and WE; --判断读有效 还是 写有效
-----------译码器 六位的地址线 四位的数据线 写法很巧妙哦 我想了老半天才想到的orz--------
process(A)
begin
--------地址线 行row------
	Arow(0) <= A(3);
	Arow(1) <= A(4);
	Arow(2) <= A(5);
	Arow(3) <= A(6);
	Arow(4) <= A(7);
	Arow(5) <= A(8);
--------数据线 列col------
	Acol(0) <= A(0);
	Acol(1) <= A(1);
	Acol(2) <= A(2);
	Acol(3) <= A(9); 

	row <= conv_integer(Arow);
	col <= conv_integer(Acol);
end process;

process(tmp)
begin
----------写操作
if(conv_integer(tmp) = 0)
then 
	sram(row)(col) <= IOIN(0);
	sram(row)(col + 16) <= IOIN(1);
	sram(row)(col + 32) <= IOIN(2);
	sram(row)(col + 48) <= IOIN(3);
	-------读操作------
elsif(conv_integer(tmp) = 1)
then
	IOOUT(0) <= sram(row)(col);
	IOOUT(1) <= sram(row)(col + 16);
	IOOUT(2) <= sram(row)(col + 32);
	IOOUT(3) <= sram(row)(col + 48);
end if;
end process;

end Behavioral;

