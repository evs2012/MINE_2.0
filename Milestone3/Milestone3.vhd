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
signal onesDigit, tensDigit: integer := 0;

-- unsigned integer to hexfile
function hex_display (int: integer ) 
return std_logic_vector is
variable return_value : std_logic_vector(0 to 6) := "1001001";
begin
	case int  is
		when 0 => return_value :=  "1111110";
		when 1 => return_value :=  "0110000";
		when 2 => return_value :=  "1101101";
		when 3 => return_value :=  "1111001";
		when 4 => return_value :=  "0110011";
		when 5 => return_value :=  "1011011";
		when 6 => return_value :=  "1011111";
		when 7 => return_value :=  "1110000";
		when 8 => return_value :=  "1111111";
		when 9 => return_value :=  "1111011";
		when others => return_value := "1001001";
	end case;
	--invert because active low
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
	onesDigit <= to_integer(unsigned(counter2)) mod 10;
	tensDigit <= (to_integer(unsigned(counter2)) mod 100) / 10;

	HEX1 <= hex_display(tensDigit);
	HEX0 <= hex_display(onesDigit);	
end architecture; 