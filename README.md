🌐 [English](README.md) | [中文](README_zh.md)

# Welcome to DragoPass EC Group!!!
```
 git clone this repo for template files
```

#### Policies
This assignment allows collaboration, online searching, generative AI. But please cite the origin of those content in your solution with comment. 

:black_medium_square: Citing others' work will not affect the result.

:x: Using other sources without citing will cause punishment.

#### File Description
This repository contains the following files and directories:  

```
orientation-2026/
├── Task 1/
│   └── referee.c # Referee system communication parsing (reference file for Task 1)
├── Task 2/
│   ├── chassis.c # Chassis control main logic implementation
│   └── chassis.h # Chassis control header file (struct and function declarations)
├── README.md # English documentation
└── README_zh.md # Chinese documentation
```

---

# Questions
## Task1: Referee(Judge) System Communication (50 Points)

### Descriptions
In RoboMaster matches, every robot communicates with the **Referee System** (a.k.a. Judge System) via a serial protocol (UART).  
The Judge System sends data packets that contain information such as robot HP, shooter cooling limits, power limit, etc.  
It is the responsibility of the **Electrical Control (EC) Group** to parse these data packets and store them into structured variables for use by higher-level code.

In this task, you will implement **UART packet parsing** for a simplified Judge System.

### Protocol (Simplified Version)
A packet from the Judge System has the following structure (all values are in **little-endian**):

| Byte Offset | Length | Field         | Description                          |
|-------------|--------|---------------|--------------------------------------|
| 0           | 2      | SOF (0xA5)    | Start of Frame, fixed to 0xA5 0x00   |
| 2           | 2      | Data Length   | Length of the payload (N)            |
| 4           | 1      | Seq           | Sequence number (increments each pkt)|
| 5           | 2      | CRC16         | CRC16 of header (Bytes 0–4)          |
| 7           | N      | Data Payload  | Content of the packet                |
| 7+N         | 2      | CRC16         | CRC16 of whole packet                |

**Example Payload (Robot Status)**  
| Byte Offset | Length | Field          | Description             |
|-------------|--------|----------------|-------------------------|
| 0           | 2      | robot_id       | Unique ID for each robot|
| 2           | 2      | current_HP     | Current robot HP        |
| 4           | 2      | max_HP         | Maximum robot HP        |

### Tasks
1. Implement a **UART receive handler** that stores incoming bytes into a ring buffer.  
2. Implement a **Packet_Decode()** function that:  
   - Finds the header (SOF = 0xA5 0x00)  
   - Checks both CRC16 (header + full packet)  
   - Extracts payload if valid  
3. Define a struct `RobotStatus_t` to store `robot_id`, `current_HP`, and `max_HP`.  
4. Write the logic in C to decode the packet and update a global variable `robot_status`.

### Useful Tools
- CRC16 algorithm is provided in `crc.c` (you just need to call it).  
- UART low-level driver is already initialized for you (`HAL_UART_Receive_IT`).  
- You may use `#define JUDGE_SOF 0xA5` to simplify the implementation.  

### Grading
- 40% for correctly implementing ring buffer and UART receive logic.  
- 40% for correct packet parsing and CRC validation.  
- 10% for struct definition and variable update.  
- 10% for coding style.  

---

## Task2: Implementing Chassis Control (50 Points)
### Descriptions
Your are asked to implement the chassis control program.
I understand this sounds difficult, don't worry, I have constructed many helper functions for you.

### Hint
You may want to know these facts before solving this task:

The controller use CAN bus to communicate with motors. There are 2 CAN buses on a Robomaster Development Board C, denoted as CAN1, CAN2. Chassis motors are connected to CAN1. The motor distinguish signals on the bus with IDs. You may use arbitrary ID between [0,8] for this task as long as they are different from each other.

The chassis uses mecanum wheels to operate omni-directional movement. Feel free to search for it online.

### Useful Tools
Check chassis.h to see typedefs. Don't worry about undefined structs.
Helper functions are described in chassis.c

### Tasks
The program will run Chassis_Init once then run Chassis_Task repeatedly with 1ms delay every iteration.

The expect speed for the robot are stored in vx, vy, vw.

Chassis_Init: Initialize everything.
Chassis_Task:
1. Get motor data
2. Calculate the target speed for each motor.
3. Use PID to control the motor with currents
4. Send motor command

Check [Dev Standard](https://github.com/RM-DragoPass-EC-Group/.github/blob/main/profile/Development%20Standard/Development%20Standard.md) for info about dev standard.

### Grading
50% for implementing the program (Because you are not able to test whether the program will run, minor mistakes are accepted.)

10% each for implementing helper functions (PID_Init, Basic_PID_Controller, forward_kinematic, backward_kinematic)

9% for coding style (loose standard)
