/*
 * This file is part of OpenPLC Runtime
 *
 * Copyright (C) 2023 Autonomy, GP Orcullo
 * Based on the work by GP Orcullo on Beremiz for uC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdbool.h>

// Include defines.h first for Arduino builds to set USE_*_BLOCKS macros
// before iec_std_FB.h processes its conditional includes
#ifdef ARDUINO
#include "../examples/Baremetal/defines.h"
#endif

#include "iec_types_all.h"
#include "POUS.h"

#define SAME_ENDIANNESS      0
#define REVERSE_ENDIANNESS   1

char plc_program_md5[] = "8b99214927b7d65c6c3039c67db49234";

uint8_t endianness;


extern MAIN RES0__INSTANCE0;

static const struct {
    void *ptr;
    __IEC_types_enum type;
} debug_vars[] = {
    {&(RES0__INSTANCE0.AUTO_MODE_EN), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.EN), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.ENO), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.HOA_IN_HAND), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.HOA_IN_AUTO), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.AUTO), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.HAND), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.EN), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.ENO), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.HOA_HAND), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.HOA_AUTO), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.IN_OFF), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.IN_HAND), BOOL_ENUM},
    {&(RES0__INSTANCE0.START_CMD0.RUN_MODE0.IN_AUTO), BOOL_ENUM},
    {&(RES0__INSTANCE0.HAND_MODE_EN), BOOL_ENUM},
    {&(RES0__INSTANCE0.AUTO_RELAY), BOOL_ENUM},
    {&(RES0__INSTANCE0.RUN_CMD), BOOL_ENUM},
    {&(RES0__INSTANCE0.HAND_RELAY), BOOL_ENUM},
    {&(RES0__INSTANCE0.STA_BUTT), BOOL_ENUM},
    {&(RES0__INSTANCE0.STP_BUTT), BOOL_ENUM},
    {&(RES0__INSTANCE0.RUN_PERM), BOOL_ENUM},
    {&(RES0__INSTANCE0.AUTO_REQ), BOOL_ENUM},
    {&(RES0__INSTANCE0.VFD_FAULT_LATCHED), BOOL_ENUM},
    {&(RES0__INSTANCE0.VFD_FAULT), BOOL_ENUM},
    {&(RES0__INSTANCE0.PRESS_FAULT_LATCHED), BOOL_ENUM},
    {&(RES0__INSTANCE0.HIGH_PRESS), BOOL_ENUM},
    {&(RES0__INSTANCE0.RESET_CMD), BOOL_ENUM},
    {&(RES0__INSTANCE0.RESET_BUTT), BOOL_ENUM},
    {&(RES0__INSTANCE0.HAND_REQ), BOOL_ENUM},
    {&(RES0__INSTANCE0.AUTO_INHIB), BOOL_ENUM},
    {&(RES0__INSTANCE0.TANK_LVL_HIGH), BOOL_ENUM},
    {&(RES0__INSTANCE0.TANK_LVL_LOW), BOOL_ENUM},
    {&(RES0__INSTANCE0.HIGH_LVL_SW), BOOL_ENUM},
    {&(RES0__INSTANCE0.LOW_LVL_SW), BOOL_ENUM},
};

#define VAR_COUNT               34

uint16_t get_var_count(void)
{
    return VAR_COUNT;
}

size_t get_var_size(size_t idx)
{
    if (idx >= VAR_COUNT)
    {
        return 0;
    }
    switch (debug_vars[idx].type) {
    case BOOL_ENUM:
        return sizeof(BOOL);
    default:
        return 0;
    }
}

void *get_var_addr(size_t idx)
{
    void *ptr = debug_vars[idx].ptr;

    switch (debug_vars[idx].type) {
    case BOOL_ENUM:
        return (void *)&((__IEC_BOOL_t *) ptr)->value;
    default:
        return 0;
    }
}

void force_var(size_t idx, bool forced, void *val)
{
    void *ptr = debug_vars[idx].ptr;

    if (forced) {
        size_t var_size = get_var_size(idx);
        switch (debug_vars[idx].type) {
        case BOOL_ENUM: {
            memcpy(&((__IEC_BOOL_t *) ptr)->value, val, var_size);
            ((__IEC_BOOL_t *) ptr)->flags |= __IEC_FORCE_FLAG;
            break;
        }
    
        default:
            break;
        }
    } else {
        switch (debug_vars[idx].type) {
        case BOOL_ENUM:
            ((__IEC_BOOL_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;
            break;
        default:
            break;
        }
    }
}

void swap_bytes(void *ptr, size_t size)
{
    uint8_t *bytePtr = (uint8_t *)ptr;
    size_t i;
    for (i = 0; i < size / 2; ++i)
    {
        uint8_t temp = bytePtr[i];
        bytePtr[i] = bytePtr[size - 1 - i];
        bytePtr[size - 1 - i] = temp;
    }
}

void trace_reset(void)
{
    for (size_t i=0; i < VAR_COUNT; i++)
    {
        force_var(i, false, 0);
    }
}

void set_trace(size_t idx, bool forced, void *val)
{
    if (idx >= 0 && idx < VAR_COUNT)
    {
        if (endianness == REVERSE_ENDIANNESS)
        {
            // Prevent swapping for STRING type
            if (debug_vars[idx].type == STRING_ENUM)
            {
                // Do nothing
                ;
            }
            else
            {
                swap_bytes(val, get_var_size(idx));
            }
        }

        force_var(idx, forced, val);
    }
}

void set_endianness(uint8_t value)
{
    if (value == SAME_ENDIANNESS || value == REVERSE_ENDIANNESS)
    {
        endianness = value;
    }
}
