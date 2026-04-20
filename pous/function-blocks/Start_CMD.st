FUNCTION_BLOCK Start_CMD
VAR_INPUT
	HOA_In_Hand : bool;
	HOA_In_Auto : bool;
END_VAR

VAR_OUTPUT
	Auto : bool;
	Hand : bool;
END_VAR

VAR
	Run_Mode0 : Run_Mode;
END_VAR

Auto := false;
Hand := false;

Run_Mode0 (
    HOA_Hand := HOA_In_Hand,
    HOA_Auto := HOA_In_Auto
);

if Run_Mode0.In_Auto then
  Auto := true;
  
elsif Run_Mode0.In_Hand then
  Hand := true;
  
end_if;

END_FUNCTION_BLOCK