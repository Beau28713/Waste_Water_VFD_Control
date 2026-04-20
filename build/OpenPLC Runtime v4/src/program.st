TYPE
  HOA_MODE : (HOA_HAND, HOA_AUTO, HOA_OFF);
END_TYPE

FUNCTION_BLOCK Run_Mode
  VAR_INPUT
    HOA_Hand : BOOL;
    HOA_Auto : BOOL;
  END_VAR
  VAR_OUTPUT
    In_Off : BOOL;
    In_Hand : BOOL;
    In_Auto : BOOL;
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

FUNCTION_BLOCK Start_CMD
  VAR_INPUT
    HOA_In_Hand : BOOL;
    HOA_In_Auto : BOOL;
  END_VAR
  VAR_OUTPUT
    Auto : BOOL;
    Hand : BOOL;
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

PROGRAM main
  VAR
    Auto_Mode_En : BOOL;
    START_CMD0 : Start_CMD;
    Hand_Mode_En : BOOL;
    Auto_Relay : BOOL;
    Run_CMD : BOOL;
    Hand_Relay : BOOL;
    STA_Butt : BOOL;
    STP_Butt : BOOL;
    Run_Perm : BOOL;
    Auto_Req : BOOL;
    VFD_Fault_Latched : BOOL;
    VFD_Fault : BOOL;
    Press_Fault_Latched : BOOL;
    High_Press : BOOL;
    Reset_Cmd : BOOL;
    Reset_Butt : BOOL;
    Hand_Req : BOOL;
    Auto_Inhib : BOOL;
    Tank_Lvl_High : BOOL;
    Tank_Lvl_Low : BOOL;
    High_Lvl_Sw : BOOL;
    Low_Lvl_Sw : BOOL;
  END_VAR

  START_CMD0(EN := TRUE, HOA_In_Hand := Hand_Relay, HOA_In_Auto := Auto_Relay);
  IF START_CMD0.ENO THEN
      Auto_Mode_En := START_CMD0.Auto;
  END_IF;
  IF START_CMD0.ENO THEN
      Hand_Mode_En := START_CMD0.Hand;
  END_IF;
  Run_Perm := NOT(Press_Fault_Latched) AND NOT(VFD_Fault_Latched) AND NOT(STP_Butt);
  Hand_Req := (Hand_Req OR STA_Butt) AND Hand_Mode_En AND Run_Perm;
  Tank_Lvl_High := Tank_Lvl_Low AND (High_Lvl_Sw OR Tank_Lvl_High);
  Tank_Lvl_Low := NOT(Low_Lvl_Sw);
  Auto_Req := Tank_Lvl_High AND NOT(Auto_Inhib) AND Auto_Mode_En AND Run_Perm;
  VFD_Fault_Latched := NOT(Reset_Cmd) AND (VFD_Fault OR VFD_Fault_Latched);
  Press_Fault_Latched := NOT(Reset_Cmd) AND (High_Press OR Press_Fault_Latched);
  Reset_Cmd := Reset_Butt;
  Auto_Inhib := Auto_Mode_En AND (Auto_Inhib OR Press_Fault_Latched OR VFD_Fault_Latched);
  Run_CMD := Auto_Req OR Hand_Req;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 1);
    PROGRAM instance0 WITH task0 : main;
  END_RESOURCE
END_CONFIGURATION

(*DBG:char md5[] = "8b99214927b7d65c6c3039c67db49234";*)
(*DBG:/**)
(*DBG: * This file is part of OpenPLC Runtime*)
(*DBG: **)
(*DBG: * Copyright (C) 2023 Autonomy, GP Orcullo*)
(*DBG: * Based on the work by GP Orcullo on Beremiz for uC*)
(*DBG: **)
(*DBG: * This program is free software; you can redistribute it and/or*)
(*DBG: * modify it under the terms of the GNU General Public License*)
(*DBG: * as published by the Free Software Foundation; either version 2*)
(*DBG: * of the License, or (at your option) any later version.*)
(*DBG: **)
(*DBG: * This program is distributed in the hope that it will be useful,*)
(*DBG: * but WITHOUT ANY WARRANTY; without even the implied warranty of*)
(*DBG: * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the*)
(*DBG: * GNU General Public License for more details.*)
(*DBG: **)
(*DBG: * You should have received a copy of the GNU General Public License*)
(*DBG: * along with this program; If not, see <http://www.gnu.org/licenses/>.*)
(*DBG: **)
(*DBG: */*)
(*DBG:*)
(*DBG:#include <stdbool.h>*)
(*DBG:*)
(*DBG:// Include defines.h first for Arduino builds to set USE_*_BLOCKS macros*)
(*DBG:// before iec_std_FB.h processes its conditional includes*)
(*DBG:#ifdef ARDUINO*)
(*DBG:#include "../examples/Baremetal/defines.h"*)
(*DBG:#endif*)
(*DBG:*)
(*DBG:#include "iec_types_all.h"*)
(*DBG:#include "POUS.h"*)
(*DBG:*)
(*DBG:#define SAME_ENDIANNESS      0*)
(*DBG:#define REVERSE_ENDIANNESS   1*)
(*DBG:*)
(*DBG:char plc_program_md5[] = "8b99214927b7d65c6c3039c67db49234";*)
(*DBG:*)
(*DBG:uint8_t endianness;*)
(*DBG:*)
(*DBG:*)
(*DBG:extern MAIN RES0__INSTANCE0;*)
(*DBG:*)
(*DBG:static const struct {*)
(*DBG:    void *ptr;*)
(*DBG:    __IEC_types_enum type;*)
(*DBG:} debug_vars[] = {*)
(*DBG:    {&(RES0__INSTANCE0.AUTO_MODE_EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.HOA_IN_HAND), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.HOA_IN_AUTO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.AUTO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.HAND), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.HOA_HAND), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.HOA_AUTO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.IN_OFF), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.IN_HAND), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.IN_AUTO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.HAND_MODE_EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.AUTO_RELAY), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.RUN_CMD), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.HAND_RELAY), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.STA_BUTT), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.STP_BUTT), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.RUN_PERM), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.AUTO_REQ), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.VFD_FAULT_LATCHED), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.VFD_FAULT), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.PRESS_FAULT_LATCHED), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.HIGH_PRESS), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.RESET_CMD), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.RESET_BUTT), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.HAND_REQ), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.AUTO_INHIB), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.TANK_LVL_HIGH), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.TANK_LVL_LOW), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.HIGH_LVL_SW), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.LOW_LVL_SW), BOOL_ENUM},*)
(*DBG:};*)
(*DBG:*)
(*DBG:#define VAR_COUNT               34*)
(*DBG:*)
(*DBG:uint16_t get_var_count(void)*)
(*DBG:{*)
(*DBG:    return VAR_COUNT;*)
(*DBG:}*)
(*DBG:*)
(*DBG:size_t get_var_size(size_t idx)*)
(*DBG:{*)
(*DBG:    if (idx >= VAR_COUNT)*)
(*DBG:    {*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:    switch (debug_vars[idx].type) {*)
(*DBG:    case BOOL_ENUM:*)
(*DBG:        return sizeof(BOOL);*)
(*DBG:    default:*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void *get_var_addr(size_t idx)*)
(*DBG:{*)
(*DBG:    void *ptr = debug_vars[idx].ptr;*)
(*DBG:*)
(*DBG:    switch (debug_vars[idx].type) {*)
(*DBG:    case BOOL_ENUM:*)
(*DBG:        return (void *)&((__IEC_BOOL_t *) ptr)->value;*)
(*DBG:    default:*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void force_var(size_t idx, bool forced, void *val)*)
(*DBG:{*)
(*DBG:    void *ptr = debug_vars[idx].ptr;*)
(*DBG:*)
(*DBG:    if (forced) {*)
(*DBG:        size_t var_size = get_var_size(idx);*)
(*DBG:        switch (debug_vars[idx].type) {*)
(*DBG:        case BOOL_ENUM: {*)
(*DBG:            memcpy(&((__IEC_BOOL_t *) ptr)->value, val, var_size);*)
(*DBG:            ((__IEC_BOOL_t *) ptr)->flags |= __IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:    *)
(*DBG:        default:*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:    } else {*)
(*DBG:        switch (debug_vars[idx].type) {*)
(*DBG:        case BOOL_ENUM:*)
(*DBG:            ((__IEC_BOOL_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        default:*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void swap_bytes(void *ptr, size_t size)*)
(*DBG:{*)
(*DBG:    uint8_t *bytePtr = (uint8_t *)ptr;*)
(*DBG:    size_t i;*)
(*DBG:    for (i = 0; i < size / 2; ++i)*)
(*DBG:    {*)
(*DBG:        uint8_t temp = bytePtr[i];*)
(*DBG:        bytePtr[i] = bytePtr[size - 1 - i];*)
(*DBG:        bytePtr[size - 1 - i] = temp;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void trace_reset(void)*)
(*DBG:{*)
(*DBG:    for (size_t i=0; i < VAR_COUNT; i++)*)
(*DBG:    {*)
(*DBG:        force_var(i, false, 0);*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void set_trace(size_t idx, bool forced, void *val)*)
(*DBG:{*)
(*DBG:    if (idx >= 0 && idx < VAR_COUNT)*)
(*DBG:    {*)
(*DBG:        if (endianness == REVERSE_ENDIANNESS)*)
(*DBG:        {*)
(*DBG:            // Prevent swapping for STRING type*)
(*DBG:            if (debug_vars[idx].type == STRING_ENUM)*)
(*DBG:            {*)
(*DBG:                // Do nothing*)
(*DBG:                ;*)
(*DBG:            }*)
(*DBG:            else*)
(*DBG:            {*)
(*DBG:                swap_bytes(val, get_var_size(idx));*)
(*DBG:            }*)
(*DBG:        }*)
(*DBG:*)
(*DBG:        force_var(idx, forced, val);*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void set_endianness(uint8_t value)*)
(*DBG:{*)
(*DBG:    if (value == SAME_ENDIANNESS || value == REVERSE_ENDIANNESS)*)
(*DBG:    {*)
(*DBG:        endianness = value;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)