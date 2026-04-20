FUNCTION_BLOCK Run_Mode
VAR_INPUT
	HOA_Hand : bool;
	HOA_Auto : bool;
END_VAR

VAR_OUTPUT
	In_Off : bool;
	In_Hand : bool;
	In_Auto : bool;
END_VAR

VAR
	Mode : HOA_MODE;
END_VAR

In_Off := false;
In_Hand := false;
In_Auto := false;

if HOA_Hand and not HOA_Auto then 
  Mode := HOA_HAND;
  In_Hand := true;
elsif HOA_Auto and not HOA_Hand then 
  Mode := HOA_AUTO;
  In_Auto := true;
else
  Mode := HOA_OFF;
  In_Off := true;
end_if;

END_FUNCTION_BLOCK