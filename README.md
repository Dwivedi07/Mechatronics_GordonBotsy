# ME 210: Gordon Botsy
This repository contains all the code for our bot Gordan Botsy!

# Checkoff Code Repository

This repository contains the final code for the Mechatronics_GordonBotsy project. The main `.ino` file, `checkoffcode.ino`, handles all state bifurcations and checks conditions within each module, including motor control, beacon detection, and sensor readings.

## Repository Structure

```
📦 checkoff_code
├── 📄 checkoffcode.ino    # Main Arduino file managing state bifurcations and module conditions
├── 📄 beacon.cpp          # Implementation of beacon-related functions
├── 📄 beacon.h            # Header file for beacon module
├── 📄 global.h            # Global definitions and variables
├── 📄 linefollow.cpp      # Implementation of line-following algorithm
├── 📄 linefollow.h        # Header file for line-following module
├── 📄 motor_drive.cpp     # Motor control functions implementation
├── 📄 motor_drive.h       # Header file for motor drive module
├── 📄 pot_movement.cpp    # Implementation of pot-based movement
├── 📄 pot_movement.h      # Header file for pot movement
├── 📄 servo.cpp           # Servo motor control functions
├── 📄 servo.h             # Header file for servo control
├── 📄 ultrasonic.cpp      # Ultrasonic sensor functions implementation
└── 📄 ultrasonic.h        # Header file for ultrasonic sensor
```

## Description

- **checkoffcode.ino**: The core Arduino program that manages different states and ensures proper functioning by interacting with all modules.
- **Motor, Beacon, Sensor Modules**: Each module has a corresponding `.cpp` file for implementation and a `.h` file for declarations.
- **Global Definitions**: `global.h` contains shared variables and definitions used across different modules.

## How to Use
1. Clone this repository to your local machine.
2. Open `checkoffcode.ino` in the Arduino IDE.
3. Ensure all required dependencies and libraries are installed.
4. Compile and upload the code to your microcontroller.
5. Verify functionality by checking motor movement, beacon detection, and sensor responses.

## Contribution
Feel free to contribute by improving the code, optimizing algorithms, or fixing bugs. Submit a pull request with a detailed explanation of changes.

---
For any issues or questions, please open an issue in the repository. 🚀

##  Contact

For questions, issues, or feedback, please reach out to the following:

### Varun Pathak
Email: vpathak@stanford.edu

### Arpit Dwivedi
Email: dwivedi7@stanford.edu

### Nachiketh Karthik
Email: karthi24@stanford.edu

### Danish M
Email: danishm@stanford.edu
