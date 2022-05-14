----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:12:45 12/20/2021 
-- Design Name: 
-- Module Name:    PS2module - Behavioral 
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

entity PS2module is
    Port ( DO : in  STD_LOGIC_VECTOR (7 downto 0);
           DO_RDy : in  STD_LOGIC;
           CLK_XT : in  STD_LOGIC;
			  Reset : in STD_LOGIC;
           y : out  STD_LOGIC);
			 
end PS2module;

architecture Behavioral of PS2module is
	
	type state_type is(S0,S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12);
	signal state : state_type := S0;
	signal next_state : state_type := S0;
	
	
begin
	process1 : process( CLK_XT )
	begin
		if rising_edge( CLK_XT ) then
			if Reset = '1' then
				state <= S0;
		else
			state <= next_state;
			end if;
		end if;
	end process process1;
	
	process2 : process (state,DO,DO_RDy)
	begin
	next_state<=state;
	if do_rdy='1' then
		case state is
		when S0=>
			if DO=X"3B" then next_state<=S1;
			end if;
		when S1=>
			if DO=X"F0" then next_state<=S2;
			elsif DO=X"3B" then next_state<=S1;
			end if;
		when S2=>
			if DO=X"3B" then next_state<=S3;
			end if;
		when S3=>
			if DO=X"4D" then next_state<=S4;
			elsif DO=X"3B" then next_state<=S1;
			else next_state<=S0;
			end if;
		when S4=>
			if DO=X"F0" then next_state<=S5;
			end if;
		when S5=>
			if DO=X"4D" then next_state<=S6;
			end if;
		when S6=>
			if DO=X"3A" then next_state<=S7;
			elsif DO=X"3B" then next_state<=S1;
			else next_state<=S0;
			end if;
		when S7=>
			if DO=X"F0" then next_state<=S8;
			end if;
		when S8=>
			if DO=X"3A" then next_state<=S9;
			end if;
		when S9=>
			if DO=X"3C" then next_state<=S10;
			elsif DO=X"3B" then next_state<=S1;
			else next_state<=S0;
			end if;
		when S10=>
			if DO=X"F0" then next_state<=S11;
			end if;
		when S11=>
			if DO=X"3C" then next_state<=S12;
			end if;
		when S12=>
			if DO=X"3B" then next_state<=S1;
			elsif DO=X"3B" then next_state<=S1;
			else next_state<=S0;
			end if;
		end case;
		
		
	
	end if;
	
	
	
		
	
	
	end process process2;
	y<='1' when state= S12
		else '0';

end Behavioral;