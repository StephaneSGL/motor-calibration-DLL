# motor-calibration-DLL
C++ DLL to automatically calibrate EPOS4 motors to mechanical zero using limit switches.
# EPOS4 Motor Calibration DLL

This project provides a C++ dynamic link library (DLL) designed to calibrate EPOS4 motors to their mechanical zero using limit switches. The DLL is intended for integration with LabVIEW and supports industrial motion control setups.

##  Features

- Safe motor calibration to zero using limit switch detection
- EPOS4 command integration via `EposCmd64.dll`
- Designed for reuse in LabVIEW-based applications
- Avoids EPOS Studio/EtherCAT toolkit limitations

##  Folder Structure

- `src/`: C++ source files
- `include/`: Header files
- `lib/`: External dependencies (EPOS library files)
- `examples/`: Sample integration code
- `test/`: Optional unit tests

##  Requirements

- Windows
- Visual Studio
- EPOS Command Library (Maxon)
- LabVIEW (optional for integration)

##  How to Use

1. Clone the repo
2. Build the DLL using Visual Studio or CMake
3. Integrate the DLL in your LabVIEW VI or C++ application
4. Use the `InitCalibration()` and `MoveUntilLimit()` functions

##  License

This project is licensed under the MIT License.
