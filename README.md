# Waste Water VFD Pump Control

This project is a PLC-style wastewater pump control program built with OpenPLC. It uses ladder logic, structured text, function blocks, HOA mode selection, permissives, fault latching, reset logic, and run command logic.

The main goal of this project is to practice real control system thinking. I wanted this to be more than just turning an output on and off. The logic is set up more like an industrial pump control circuit, where the final run command is only allowed when the mode, permissives, level conditions, and fault status are all correct.

## Project Goals

This project is meant to demonstrate a clean foundation for pump control logic using common automation concepts.

The controller is intended to show:

* Hand / Off / Auto mode selection
* Separate hand and auto mode enable logic
* Start and stop pushbutton behavior
* Run permissive logic
* Auto run request based on tank level
* Hand run request based on operator input
* VFD fault latching
* High-pressure fault latching
* Reset command behavior
* Auto inhibit behavior
* Final pump run command logic

This is currently a learning and portfolio project. It is not a finished certified control system for live wastewater equipment.

## System Overview

The basic control idea is simple:

1. The operator selects Hand, Off, or Auto.
2. The logic determines which mode is active.
3. The system checks that the stop button and active faults are not preventing operation.
4. In Hand mode, the operator can start the pump with the start button.
5. In Auto mode, the pump can start when the tank level reaches the high-level condition.
6. VFD and pressure faults latch in until reset.
7. The final `Run_CMD` is only true when either the hand request or auto request is true.

The structure is built around the idea of:

```text
Mode Selection → Permissives → Requests → Fault Logic → Run Command
```

## Current Features

* OpenPLC project structure
* Ladder logic main program
* Structured Text function blocks
* HOA mode selection
* Hand mode enable
* Auto mode enable
* Start command function block
* Run permissive logic
* Hand request latch
* Auto request logic
* Low-level and high-level tank conditions
* Auto inhibit logic
* VFD fault latch
* High-pressure fault latch
* Reset command logic
* Final pump / VFD run command

## Control Modes

### Hand Mode

Hand mode is intended for manual operator control.

When Hand mode is active:

* The hand mode enable bit turns on.
* The operator can press the start button to request pump operation.
* The hand request stays active as long as the system stays in Hand mode and the run permissive remains true.
* The stop button or an active fault removes the run permissive and drops the hand request.

This gives the hand circuit a more realistic latch-style behavior instead of requiring the start button to stay held down.

### Auto Mode

Auto mode is intended for level-based pump operation.

When Auto mode is active:

* The auto mode enable bit turns on.
* The pump can run when the tank level reaches the high-level condition.
* Auto operation is blocked if `Auto_Inhib` is active.
* Auto operation is also blocked if the run permissive is false.

The auto request is based on mode status, level status, inhibit status, and permissive status.

### Off Mode

Off mode is the safe default mode.

If neither Hand nor Auto is selected, or if both are selected at the same time, the mode logic defaults to Off.

This is intentional. If the mode input state is not clearly valid, the system should not assume it is safe to run.

## Sequence of Operation

### Normal Hand Operation

1. Operator selects Hand mode.
2. `Hand_Mode_En` turns on.
3. Operator presses the start button.
4. If `Run_Perm` is true, `Hand_Req` turns on.
5. `Run_CMD` turns on from `Hand_Req`.
6. Pump / VFD would be commanded to run.
7. Pressing stop, leaving Hand mode, or receiving a latched fault removes the run command.

### Normal Auto Operation

1. Operator selects Auto mode.
2. `Auto_Mode_En` turns on.
3. Tank level reaches the high-level condition.
4. If `Auto_Inhib` is false and `Run_Perm` is true, `Auto_Req` turns on.
5. `Run_CMD` turns on from `Auto_Req`.
6. Pump / VFD would be commanded to run.
7. A stop condition, fault, inhibit, or loss of auto request removes the run command.

### Fault Operation

1. A VFD fault or high-pressure condition becomes active.
2. The matching latched fault bit turns on.
3. `Run_Perm` turns off.
4. Hand and auto requests are blocked.
5. `Run_CMD` turns off.
6. The fault remains latched until reset logic clears it.

## Main Logic

The main program is written in ladder logic, with generated Structured Text available in the OpenPLC runtime output.

The main logic includes:

* Mode enable logic
* Run permissive logic
* Hand request logic
* Auto request logic
* Level condition logic
* Fault latch logic
* Reset logic
* Auto inhibit logic
* Final run command logic

Important control expression from the generated logic:

```pascal
Run_Perm := NOT(Press_Fault_Latched) AND NOT(VFD_Fault_Latched) AND NOT(STP_Butt);
```

That means the system is only permitted to run when:

* The pressure fault is not latched
* The VFD fault is not latched
* The stop button is not active

The final run command is based on either a hand request or an auto request:

```pascal
Run_CMD := Auto_Req OR Hand_Req;
```

This keeps the final output logic clean and easy to troubleshoot.

## Function Blocks

### `Run_Mode`

The `Run_Mode` function block reads the HOA hand and auto inputs and determines the active mode.

Inputs:

| Input      | Type   | Description     |
| ---------- | ------ | --------------- |
| `HOA_Hand` | `BOOL` | Hand mode input |
| `HOA_Auto` | `BOOL` | Auto mode input |

Outputs:

| Output    | Type   | Description            |
| --------- | ------ | ---------------------- |
| `In_Off`  | `BOOL` | System is in Off mode  |
| `In_Hand` | `BOOL` | System is in Hand mode |
| `In_Auto` | `BOOL` | System is in Auto mode |

The block only allows one valid mode at a time:

* Hand input on and Auto input off = Hand mode
* Auto input on and Hand input off = Auto mode
* Both off, or both on = Off mode

Defaulting to Off during an invalid HOA state is safer than allowing an unexpected run condition.

### `Start_CMD`

The `Start_CMD` function block uses the HOA mode status to determine which mode enable bit should be active.

Inputs:

| Input         | Type   | Description          |
| ------------- | ------ | -------------------- |
| `HOA_In_Hand` | `BOOL` | Hand selection input |
| `HOA_In_Auto` | `BOOL` | Auto selection input |

Outputs:

| Output | Type   | Description       |
| ------ | ------ | ----------------- |
| `Hand` | `BOOL` | Hand mode enabled |
| `Auto` | `BOOL` | Auto mode enabled |

This block builds on the `Run_Mode` function block and gives the main program cleaner hand and auto enable signals.

## Main Tags

| Tag                   | Type   | Description                                         |
| --------------------- | ------ | --------------------------------------------------- |
| `Hand_Relay`          | `BOOL` | Input showing HOA Hand selection                    |
| `Auto_Relay`          | `BOOL` | Input showing HOA Auto selection                    |
| `Hand_Mode_En`        | `BOOL` | Internal bit showing Hand mode is enabled           |
| `Auto_Mode_En`        | `BOOL` | Internal bit showing Auto mode is enabled           |
| `STA_Butt`            | `BOOL` | Start pushbutton input                              |
| `STP_Butt`            | `BOOL` | Stop pushbutton input                               |
| `Run_Perm`            | `BOOL` | Master run permissive                               |
| `Hand_Req`            | `BOOL` | Hand mode run request                               |
| `Auto_Req`            | `BOOL` | Auto mode run request                               |
| `Run_CMD`             | `BOOL` | Final pump / VFD run command                        |
| `High_Lvl_Sw`         | `BOOL` | High-level switch input                             |
| `Low_Lvl_Sw`          | `BOOL` | Low-level switch input                              |
| `Tank_Lvl_High`       | `BOOL` | Internal high-level condition                       |
| `Tank_Lvl_Low`        | `BOOL` | Internal low-level related condition                |
| `Auto_Inhib`          | `BOOL` | Blocks automatic operation after certain conditions |
| `VFD_Fault`           | `BOOL` | Raw VFD fault input                                 |
| `VFD_Fault_Latched`   | `BOOL` | Latched VFD fault                                   |
| `High_Press`          | `BOOL` | Raw high-pressure fault input                       |
| `Press_Fault_Latched` | `BOOL` | Latched high-pressure fault                         |
| `Reset_Butt`          | `BOOL` | Reset pushbutton input                              |
| `Reset_Cmd`           | `BOOL` | Internal reset command                              |

## Faults and Reset Logic

The project currently includes two latched faults:

* VFD fault
* High-pressure fault

The purpose of the latch is to make sure a fault does not disappear just because the raw input turns off. In real controls, operators and maintenance usually need to know that a fault happened, and the system should not restart automatically without a reset.

Example latch logic:

```pascal
VFD_Fault_Latched := NOT(Reset_Cmd) AND (VFD_Fault OR VFD_Fault_Latched);
Press_Fault_Latched := NOT(Reset_Cmd) AND (High_Press OR Press_Fault_Latched);
```

When reset is not active, the latched bit stays on if the fault is active or was already latched.

When reset is active, the latch can clear.

In a real system, reset should only clear the latched fault if the actual fault condition is no longer present.

## Level Logic

The project includes high-level and low-level logic for auto pump operation.

Current level-related tags include:

* `High_Lvl_Sw`
* `Low_Lvl_Sw`
* `Tank_Lvl_High`
* `Tank_Lvl_Low`

The high-level condition is used as part of the automatic run request.

One future improvement is to clean up the naming so the low-level logic is easier to read. For example, a name like `Above_Low_Lvl` may be clearer than `Tank_Lvl_Low` if the bit actually means the tank is above the low-level cutoff.

Clear tag names are important in controls because the logic should be easy to troubleshoot while looking at it online.

## Auto Inhibit

The `Auto_Inhib` bit is used to block automatic operation.

This is useful because a system may need to prevent automatic restart after certain faults or unsafe conditions. The operator would then need to investigate and reset before auto operation is allowed again.

This is a good control concept to keep building on.

## Project Files

The current repository includes these main files and folders:

```text
.
├── build/
│   └── OpenPLC Runtime v4/
│       └── src/
├── devices/
├── pous/
│   ├── function-blocks/
│   │   ├── Run_Mode.st
│   │   └── Start_CMD.st
│   └── programs/
├── README.md
├── plc.xml
├── plc_Codsey.xml
└── project.json
```

### Source Files

| File / Folder                       | Purpose                                                   |
| ----------------------------------- | --------------------------------------------------------- |
| `plc.xml`                           | Main OpenPLC project file                                 |
| `plc_Codsey.xml`                    | Additional/exported PLC project file                      |
| `project.json`                      | OpenPLC project metadata                                  |
| `pous/function-blocks/Run_Mode.st`  | Structured Text function block for HOA mode handling      |
| `pous/function-blocks/Start_CMD.st` | Structured Text function block for hand/auto enable logic |
| `pous/programs/`                    | Main program / ladder logic project files                 |
| `build/OpenPLC Runtime v4/src/`     | Generated OpenPLC runtime output                          |

The files inside the `build` folder are generated OpenPLC runtime files. They are useful for looking at generated Structured Text/C output, but the main hand-edited PLC logic should be kept in the OpenPLC project files and POU folders.

## How to Open the Project

This project is intended to be opened with OpenPLC Editor.

Basic workflow:

1. Download or clone the repository.
2. Open OpenPLC Editor.
3. Open the `plc.xml` project file.
4. Review the POU structure, function blocks, and main ladder program.
5. Build or export the project from OpenPLC as needed.
6. Use OpenPLC Runtime for testing if running it on supported hardware or a simulator.

## Suggested Testing Procedure

Before using this logic with real equipment, it should be tested in simulation or on a safe test setup.

Suggested test steps:

1. Open the project in OpenPLC Editor.
2. Verify the HOA mode inputs.
3. Test Hand mode only.
4. Confirm the start button latches `Hand_Req` when permissives are true.
5. Confirm the stop button drops `Run_Perm` and removes `Run_CMD`.
6. Test Auto mode only.
7. Simulate the high-level switch and confirm `Auto_Req` turns on.
8. Simulate a VFD fault and confirm `VFD_Fault_Latched` turns on.
9. Simulate a high-pressure fault and confirm `Press_Fault_Latched` turns on.
10. Confirm latched faults remove the run permissive.
11. Test reset behavior.
12. Confirm the pump does not run in Off mode.
13. Confirm the pump does not run if both Hand and Auto are active at the same time.

## Safety Notes

This project is for learning, testing, and controls practice.

If this type of logic were used with real wastewater equipment, the system would need proper safety design beyond the PLC code.

Important safety items would include:

* Proper motor overload protection
* Correct VFD wiring and parameter setup
* Lockout/tagout procedures
* Proper enclosure and grounding
* Fusing and circuit protection
* Emergency stop or safe stop design where required
* Float switch or level sensor validation
* Hardware-level protection for critical faults
* Manual disconnects and local controls
* Alarm indication for operators

Do not rely on software logic alone for critical equipment protection.

## What This Project Demonstrates

This project demonstrates:

* PLC project organization
* Ladder logic structure
* Structured Text function blocks
* HOA mode handling
* Hand and Auto separation
* Permissive-based control
* Request-based run logic
* Latched fault behavior
* Reset command behavior
* Auto inhibit logic
* Tank level control concepts
* Troubleshooting-focused thinking

This is the kind of foundation used in real pump, fan, conveyor, and process control systems.

## Current Project Status

Status: **In progress**

Completed so far:

* HOA mode enum created
* `Run_Mode` function block created
* `Start_CMD` function block created
* Hand mode enable logic added
* Auto mode enable logic added
* Run permissive logic added
* Hand request logic added
* Auto request logic added
* Run command logic added
* VFD fault latch added
* High-pressure fault latch added
* Reset command logic added
* Level condition logic started
* Auto inhibit logic started

## Future Improvements

Planned improvements and ideas:

* Add rung-by-rung documentation
* Add screenshots of the ladder logic
* Add a full tag list with addresses and descriptions
* Add an alarm table
* Add a clearer sequence of operation diagram
* Add HMI screen ideas
* Add fault reset conditions that only reset when the raw fault is clear
* Improve level tag naming
* Add pump run feedback logic
* Add VFD ready feedback
* Add VFD speed reference logic
* Add runtime/hour meter logic
* Add pump start counter
* Add lead/lag pump control in a future version
* Add simulation notes
* Add a license file if the project is shared publicly

## Notes

I built this project to keep learning controls and automation by working through practical logic. The goal is to keep making it cleaner, more realistic, and easier to troubleshoot.

This project is part of my continued learning in PLC programming, structured text, ladder logic, VFD control, and industrial automation.
