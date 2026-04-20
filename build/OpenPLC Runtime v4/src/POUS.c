void RUN_MODE_init__(RUN_MODE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->HOA_HAND,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HOA_AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_OFF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_HAND,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MODE,HOA_MODE__HOA_HAND,retain)
}

// Code part
void RUN_MODE_body__(RUN_MODE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,IN_OFF,,__BOOL_LITERAL(FALSE));
  __SET_VAR(data__->,IN_HAND,,__BOOL_LITERAL(FALSE));
  __SET_VAR(data__->,IN_AUTO,,__BOOL_LITERAL(FALSE));
  if ((__GET_VAR(data__->HOA_HAND,) && !(__GET_VAR(data__->HOA_AUTO,)))) {
    __SET_VAR(data__->,MODE,,__GET_VAR(data__->HOA_HAND,));
    __SET_VAR(data__->,IN_HAND,,__BOOL_LITERAL(TRUE));
  } else if ((__GET_VAR(data__->HOA_AUTO,) && !(__GET_VAR(data__->HOA_HAND,)))) {
    __SET_VAR(data__->,MODE,,__GET_VAR(data__->HOA_AUTO,));
    __SET_VAR(data__->,IN_AUTO,,__BOOL_LITERAL(TRUE));
  } else {
    __SET_VAR(data__->,MODE,,HOA_MODE__HOA_OFF);
    __SET_VAR(data__->,IN_OFF,,__BOOL_LITERAL(TRUE));
  };

  goto __end;

__end:
  return;
} // RUN_MODE_body__() 





void START_CMD_init__(START_CMD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->HOA_IN_HAND,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HOA_IN_AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HAND,__BOOL_LITERAL(FALSE),retain)
  RUN_MODE_init__(&data__->RUN_MODE0,retain);
}

// Code part
void START_CMD_body__(START_CMD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,AUTO,,__BOOL_LITERAL(FALSE));
  __SET_VAR(data__->,HAND,,__BOOL_LITERAL(FALSE));
  __SET_VAR(data__->RUN_MODE0.,HOA_HAND,,__GET_VAR(data__->HOA_IN_HAND,));
  __SET_VAR(data__->RUN_MODE0.,HOA_AUTO,,__GET_VAR(data__->HOA_IN_AUTO,));
  RUN_MODE_body__(&data__->RUN_MODE0);
  if (__GET_VAR(data__->RUN_MODE0.IN_AUTO,)) {
    __SET_VAR(data__->,AUTO,,__BOOL_LITERAL(TRUE));
  } else if (__GET_VAR(data__->RUN_MODE0.IN_HAND,)) {
    __SET_VAR(data__->,HAND,,__BOOL_LITERAL(TRUE));
  };

  goto __end;

__end:
  return;
} // START_CMD_body__() 





void MAIN_init__(MAIN *data__, BOOL retain) {
  __INIT_VAR(data__->AUTO_MODE_EN,__BOOL_LITERAL(FALSE),retain)
  START_CMD_init__(&data__->START_CMD0,retain);
  __INIT_VAR(data__->HAND_MODE_EN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AUTO_RELAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RUN_CMD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HAND_RELAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STA_BUTT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STP_BUTT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RUN_PERM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AUTO_REQ,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->VFD_FAULT_LATCHED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->VFD_FAULT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PRESS_FAULT_LATCHED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HIGH_PRESS,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESET_CMD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESET_BUTT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HAND_REQ,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AUTO_INHIB,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TANK_LVL_HIGH,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TANK_LVL_LOW,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HIGH_LVL_SW,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LOW_LVL_SW,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void MAIN_body__(MAIN *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->START_CMD0.,EN,,__BOOL_LITERAL(TRUE));
  __SET_VAR(data__->START_CMD0.,HOA_IN_HAND,,__GET_VAR(data__->HAND_RELAY,));
  __SET_VAR(data__->START_CMD0.,HOA_IN_AUTO,,__GET_VAR(data__->AUTO_RELAY,));
  START_CMD_body__(&data__->START_CMD0);
  if (__GET_VAR(data__->START_CMD0.ENO,)) {
    __SET_VAR(data__->,AUTO_MODE_EN,,__GET_VAR(data__->START_CMD0.AUTO,));
  };
  if (__GET_VAR(data__->START_CMD0.ENO,)) {
    __SET_VAR(data__->,HAND_MODE_EN,,__GET_VAR(data__->START_CMD0.HAND,));
  };
  __SET_VAR(data__->,RUN_PERM,,((!(__GET_VAR(data__->PRESS_FAULT_LATCHED,)) && !(__GET_VAR(data__->VFD_FAULT_LATCHED,))) && !(__GET_VAR(data__->STP_BUTT,))));
  __SET_VAR(data__->,HAND_REQ,,(((__GET_VAR(data__->HAND_REQ,) || __GET_VAR(data__->STA_BUTT,)) && __GET_VAR(data__->HAND_MODE_EN,)) && __GET_VAR(data__->RUN_PERM,)));
  __SET_VAR(data__->,TANK_LVL_HIGH,,(__GET_VAR(data__->TANK_LVL_LOW,) && (__GET_VAR(data__->HIGH_LVL_SW,) || __GET_VAR(data__->TANK_LVL_HIGH,))));
  __SET_VAR(data__->,TANK_LVL_LOW,,!(__GET_VAR(data__->LOW_LVL_SW,)));
  __SET_VAR(data__->,AUTO_REQ,,(((__GET_VAR(data__->TANK_LVL_HIGH,) && !(__GET_VAR(data__->AUTO_INHIB,))) && __GET_VAR(data__->AUTO_MODE_EN,)) && __GET_VAR(data__->RUN_PERM,)));
  __SET_VAR(data__->,VFD_FAULT_LATCHED,,(!(__GET_VAR(data__->RESET_CMD,)) && (__GET_VAR(data__->VFD_FAULT,) || __GET_VAR(data__->VFD_FAULT_LATCHED,))));
  __SET_VAR(data__->,PRESS_FAULT_LATCHED,,(!(__GET_VAR(data__->RESET_CMD,)) && (__GET_VAR(data__->HIGH_PRESS,) || __GET_VAR(data__->PRESS_FAULT_LATCHED,))));
  __SET_VAR(data__->,RESET_CMD,,__GET_VAR(data__->RESET_BUTT,));
  __SET_VAR(data__->,AUTO_INHIB,,(__GET_VAR(data__->AUTO_MODE_EN,) && ((__GET_VAR(data__->AUTO_INHIB,) || __GET_VAR(data__->PRESS_FAULT_LATCHED,)) || __GET_VAR(data__->VFD_FAULT_LATCHED,))));
  __SET_VAR(data__->,RUN_CMD,,(__GET_VAR(data__->AUTO_REQ,) || __GET_VAR(data__->HAND_REQ,)));

  goto __end;

__end:
  return;
} // MAIN_body__() 





