library ieee ;
use ieee.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use ieee.numeric_std.all;

---------------------------------------------

entity Milestone3 is
port(	  
	CLOCK_50  :		in std_logic;
	KEY		 :		in std_logic_vector(3 downto 0); 									--pushbuttons
	SW		 	 :		in std_logic_vector(17 downto 0);									--switch
	LEDR	 	 :		out std_logic_vector(17 downto 0) := (others => '0');			-- and gate result
	LEDG	 	 :		inout std_logic_vector(8 downto 0) := (others => '0');			-- led 8 bit counter
	HEX0 	 	 : 	OUT STD_logic_vector (0 TO 6);										-- Seven segment
	HEX1 	 	 : 	OUT STD_logic_vector (0 TO 6)											-- Seven segment
);
end Milestone3;

architecture Behavioral of Milestone3 is
signal counter1, counter2: std_logic_vector(7 downto 0) := x"00";

-- 4 bits to hexfile
function hex_display (nibble: std_logic_vector(3 downto 0)) 
return std_logic_vector is
variable return_value : std_logic_vector(0 to 6) := "1001001";
begin
	case nibble  is
		when x"0" => return_value :=  "1111110";
		when x"1" => return_value :=  "0110000";
		when x"2" => return_value :=  "1101101";
		when x"3" => return_value :=  "1111001";
		when x"4" => return_value :=  "0110011";
		when x"5" => return_value :=  "1011011";
		when x"6" => return_value :=  "1011111";
		when x"7" => return_value :=  "1110000";
		when x"8" => return_value :=  "1111111";
		when x"9" => return_value :=  "1111011";
		when x"A" => return_value :=  "1110111";
		when x"B" => return_value :=  "0011111";
		when x"C" => return_value :=  "1001110";
		when x"D" => return_value :=  "0111101";
		when x"E" => return_value :=  "1001111";
		when x"F" => return_value :=  "1000111";
		when others => return_value := "1001001";
	end case;

	return not return_value;
	
end hex_display;

begin	
	--Switches 0 and 1 to LED(0)
	LEDR(0) <= SW(0) and SW(1);
	
	--8-bit counter 
	process (Key(0))
	begin
		if falling_edge(Key(0)) then 
			counter1 <= std_logic_vector(to_unsigned(to_integer(unsigned(counter1)) +1,8)); 
		end if;
	end process;  
	
	-- Map output to Green LEDS	  
	LEDG(7 downto 0) <= counter1(7 downto 0);
	
	-- Counter based on key 1
	process (Key(1))
	begin
		if falling_edge(Key(1)) then 
			counter2 <= std_logic_vector(to_unsigned(to_integer(unsigned(counter2)) +1,8)); 
		end if;
	end process;
	
	-- output results to hex displays
	HEX1 <= hex_display(std_logic_vector(counter2(7 downto 4)));
	HEX0 <= hex_display(std_logic_vector(counter2(3 downto 0)));	
end architecture; 