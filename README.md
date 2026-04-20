# PLC Pump Control Logic Project

A PLC-style pump control project built in PLCopen XML using ladder logic and function blocks.

This project is focused on building a solid control foundation using real automation concepts such as HOA mode selection, hand/auto operation, run permissives, latched faults, reset behavior, and run command logic.

The goal of this project is to practice structured control logic and demonstrate practical controls thinking rather than just simple on/off output control.

---

## Project Overview

The logic currently includes:

- HOA mode handling
- hand and auto mode enable logic
- start command function block
- run permissive logic
- hand request logic
- auto request logic
- run command logic
- VFD fault latch
- pressure fault latch
- reset command logic
- low level and high level conditions
- auto inhibit logic

The project is written using a combination of:

- function blocks
- structured text inside function blocks
- ladder logic in the main program

---

## Current Features

### HOA mode handling
The project includes an `HOA_MODE` enum with:

- `HOA_HAND`
- `HOA_AUTO`
- `HOA_OFF`

A `Run_Mode` function block determines whether the system is in hand, auto, or off mode based on the HOA inputs. :contentReference[oaicite:1]{index=1}

### Start command logic
A `Start_CMD` function block uses the HOA mode status to determine whether hand mode or auto mode is enabled. :contentReference[oaicite:2]{index=2}

### Run permissive
The main ladder logic includes a run permissive condition that depends on stop status and fault status before operation is allowed. :contentReference[oaicite:3]{index=3}

### Hand mode request
The logic includes hand mode request behavior using run permissive, hand mode enable, and start button logic. :contentReference[oaicite:4]{index=4}

### Auto request
The logic includes auto request behavior based on run permissive, auto mode enable, auto inhibit status, and tank level conditions. :contentReference[oaicite:5]{index=5}

### Fault latching
The project includes latched fault logic for:

- VFD fault
- pressure fault

Reset behavior is included so the latched faults can be cleared through reset logic.

### Run command
The final run command is driven from either:

- hand request
- auto request

This makes the project feel more like a real control structure rather than a single direct output rung.

---

## Logic Structure

### Data Type
The project defines this custom data type:

- `HOA_MODE`

### Function Blocks
The project currently includes these function blocks:

- `Run_Mode`
- `Start_CMD`

### Main Program
The `main` program contains the ladder logic for:

- permissives
- requests
- fault latches
- reset logic
- level-related conditions
- run command generation

---

## Variables Used

Some of the key variables used in this project include:

- `Auto_Mode_En`
- `Hand_Mode_En`
- `Run_Perm`
- `Run_CMD`
- `Hand_Req`
- `Auto_Req`
- `Auto_Inhib`
- `Tank_Lvl_High`
- `Above_Low_Lvl`
- `VFD_Fault`
- `VFD_Fault_Latched`
- `High_Press`
- `Press_Fault_Latched`
- `Reset_Cmd`
- `Reset_Butt`
- `STA_Butt`
- `STP_Butt`
- `Hand_Relay`
- `Auto_Relay`

These variables help organize the control logic into a more realistic operating structure.

---

## What This Project Demonstrates

This project is meant to demonstrate:

- PLC-style control organization
- HOA mode handling
- function block use
- structured logic design
- permissive-based operation
- latched alarm/fault behavior
- manual and auto control concepts
- reset handling
- process-related thinking using level conditions
- a troubleshooting-focused controls mindset

---

## Why I Built This Project

I built this project to keep improving my skills in controls and automation by working through practical control logic instead of only studying theory.

I wanted to practice:

- how a pump control system should behave
- how hand and auto modes should be separated
- how permissives and inhibits affect operation
- how latched faults should work
- how reset logic should be handled
- how to structure a control project in a cleaner and more realistic way

This project is part of my continued growth in controls engineering, automation, electronics, and troubleshooting.

---

## File Format

This project is stored as a PLCopen XML file.

Current uploaded file:

- `plc(18).xml`

The project contains:

- custom data types
- function blocks
- a main program
- ladder logic structure
- task configuration

---

## Project Status

**Current status:** In progress

### Completed
- [x] HOA enum created
- [x] `Run_Mode` function block created
- [x] `Start_CMD` function block created
- [x] hand mode enable logic
- [x] auto mode enable logic
- [x] run permissive logic
- [x] hand request logic
- [x] auto request logic
- [x] run command logic
- [x] VFD fault latch logic
- [x] pressure fault latch logic
- [x] reset command logic

### Planned improvements
- [ ] add clearer documentation
- [ ] add rung-by-rung explanation
- [ ] add screenshots of ladder logic
- [ ] add sequence of operation
- [ ] add tag list
- [ ] add alarm description table
- [ ] add HMI concepts
- [ ] add more diagnostics
- [ ] expand pump control behavior
- [ ] build toward a more advanced version later

---

## Project Structure

```text
/project-folder
│
├── README.md
├── plc(18).xml
├── docs/
│   ├── sequence_of_operation.md
│   ├── tag_list.md
│   ├── alarm_notes.md
│   └── troubleshooting_notes.md
│
└── media/
    ├── ladder_screenshots
    └── project_images
