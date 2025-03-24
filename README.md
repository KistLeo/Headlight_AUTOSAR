---

# Headlight Automatics Project 

## Overview
The **Headlight Automatics** project is an AUTOSAR-compliant embedded system designed to control vehicle headlights automatically based on sensor inputs (speed, steering, ambient light, and camera data). It leverages an AUTOSAR OS to manage tasks, events, and alarms for real-time execution, ensuring reliable headlight operation under varying conditions.

---

## Project Structure
The project follows a modular AUTOSAR architecture, integrating **Basic Software (BSW)** and **Software Components (SWC)** with clearly defined tasks, events, and timing mechanisms:

- **Os.oil**: Configures the AUTOSAR OS with tasks, events, alarms, and counters for real-time scheduling.
- **Os.c**: Implements task execution and event handling, interfacing with the OS and RTE.
- **Runnables**: Defined within **SWCs**, mapped to tasks, and triggered by timing events (e.g., periodic alarms) or data-received events (e.g., sensor updates).
- **RTE (Runtime Environment)**: Facilitates seamless data flow and communication between **SWC runnables** and **BSW** modules.
- **BSW (Basic Software)**: Provides foundational services (e.g., OS, communication, diagnostics) and integrates with hardware, supporting **SWC** execution.
- **SWC (Software Components)**: Contain the application logic as runnables (e.g., `ReadSpeedAndSteering()`, `ComputeHeadlightLogic()`), interacting with the BSW via the RTE.


---

## Key Components
### 1. Tasks
Five tasks handle specific functionalities:
- **Task_SensorProcessing**: Processes speed and steering data.
- **Task_HeadlightInput**: Gathers ambient light and camera inputs.
- **Task_HeadlightLogic**: Computes headlight control logic.
- **Task_HeadlightControl**: Sends and receives headlight commands.
- **Task_HeadlightFeedback**: Monitors headlight state periodically.

### 2. Events
Events synchronize runnables:
- **Timing Events**: Trigger periodic actions (e.g., `Ev_SensorUpdate`).
- **Data Received Events**: Handle data-driven execution (e.g., `Ev_HeadlightInput`).

### 3. Alarms
Alarms ensure periodic task activation:
- `Alarm_SensorUpdate` (100ms): Triggers sensor reads.
- `Alarm_AmbientLightUpdate` (100ms): Updates ambient light data.
- `Alarm_HeadlightStateUpdate` (500ms): Monitors headlight feedback.

### 4. Configuration (Os.oil)
- Defines tasks with priorities (1–5), events, and alarms.
- Uses `SystemTimer` counter for timing precision.

### 5. Implementation (Os.c)
- Tasks wait for events, execute runnables, and clear events.
- Integrates with RTE for data exchange (e.g., `Rte_HeadlightAutomatics.h`).

---

## Detailed Workflow
1. **Sensor Data Collection**: `Task_SensorProcessing` reads speed/steering every 100ms and sends data.
2. **Input Processing**: `Task_HeadlightInput` collects ambient light (100ms) and camera data (event-driven).
3. **Logic Computation**: `Task_HeadlightLogic` processes inputs to determine headlight behavior.
4. **Command Execution**: `Task_HeadlightControl` sends/receives commands to adjust headlights.
5. **Feedback Loop**: `Task_HeadlightFeedback` checks headlight state every 500ms.

---

## Setup and Usage
- **Prerequisites**: AUTOSAR-compliant toolchain (e.g., Vector, EB tresos).
- **Configuration**: Edit `Os.oil` for task priorities or alarm timings as needed.
- **Build**: Compile `Os.c` with RTE and OS headers.
- **Deploy**: Flash to an ECU supporting AUTOSAR OS.

---