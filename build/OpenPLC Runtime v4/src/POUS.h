#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(HOA_MODE,
  HOA_MODE__HOA_HAND,
  HOA_MODE__HOA_AUTO,
  HOA_MODE__HOA_OFF
)
// FUNCTION_BLOCK RUN_MODE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,HOA_HAND)
  __DECLARE_VAR(BOOL,HOA_AUTO)
  __DECLARE_VAR(BOOL,IN_OFF)
  __DECLARE_VAR(BOOL,IN_HAND)
  __DECLARE_VAR(BOOL,IN_AUTO)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(HOA_MODE,MODE)

} RUN_MODE;

void RUN_MODE_init__(RUN_MODE *data__, BOOL retain);
// Code part
void RUN_MODE_body__(RUN_MODE *data__);
// FUNCTION_BLOCK START_CMD
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,HOA_IN_HAND)
  __DECLARE_VAR(BOOL,HOA_IN_AUTO)
  __DECLARE_VAR(BOOL,AUTO)
  __DECLARE_VAR(BOOL,HAND)

  // FB private variables - TEMP, private and located variables
  RUN_MODE RUN_MODE0;

} START_CMD;

void START_CMD_init__(START_CMD *data__, BOOL retain);
// Code part
void START_CMD_body__(START_CMD *data__);
// PROGRAM MAIN
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,AUTO_MODE_EN)
  START_CMD START_CMD0;
  __DECLARE_VAR(BOOL,HAND_MODE_EN)
  __DECLARE_VAR(BOOL,AUTO_RELAY)
  __DECLARE_VAR(BOOL,RUN_CMD)
  __DECLARE_VAR(BOOL,HAND_RELAY)
  __DECLARE_VAR(BOOL,STA_BUTT)
  __DECLARE_VAR(BOOL,STP_BUTT)
  __DECLARE_VAR(BOOL,RUN_PERM)
  __DECLARE_VAR(BOOL,AUTO_REQ)
  __DECLARE_VAR(BOOL,VFD_FAULT_LATCHED)
  __DECLARE_VAR(BOOL,VFD_FAULT)
  __DECLARE_VAR(BOOL,PRESS_FAULT_LATCHED)
  __DECLARE_VAR(BOOL,HIGH_PRESS)
  __DECLARE_VAR(BOOL,RESET_CMD)
  __DECLARE_VAR(BOOL,RESET_BUTT)
  __DECLARE_VAR(BOOL,HAND_REQ)
  __DECLARE_VAR(BOOL,AUTO_INHIB)
  __DECLARE_VAR(BOOL,TANK_LVL_HIGH)
  __DECLARE_VAR(BOOL,TANK_LVL_LOW)
  __DECLARE_VAR(BOOL,HIGH_LVL_SW)
  __DECLARE_VAR(BOOL,LOW_LVL_SW)

} MAIN;

void MAIN_init__(MAIN *data__, BOOL retain);
// Code part
void MAIN_body__(MAIN *data__);
#endif //__POUS_H
