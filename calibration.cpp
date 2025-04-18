// calibration.cpp
#include "calibration.h"
#include <windows.h>
#include <iostream>
#include <stdexcept> 
#include <pch.h>

// Stub/mock of digitalRead for testing purposes.
// Replace this with actual GPIO reading if running on real hardware.
bool digitalRead(int pin) {
    // TODO: Replace with real GPIO read logic
    return false; // Change to simulate limit switch activation
}

// Function pointer typedefs for dynamically loaded DLL functions
typedef bool(__stdcall* VCS_MoveWithVelocity_t)(void*, unsigned short, int, unsigned int*);
typedef bool(__stdcall* VCS_HaltPositionMovement_t)(void*, unsigned short, unsigned int*);
typedef bool(__stdcall* VCS_SetPositionMust_t)(void*, unsigned short, int, unsigned int*);

// Helper class to manage DLL loading and function calls
class EposCmdHelper {
private:
    HMODULE hModule;
    VCS_MoveWithVelocity_t VCS_MoveWithVelocity;
    VCS_HaltPositionMovement_t VCS_HaltPositionMovement;
    VCS_SetPositionMust_t VCS_SetPositionMust;

public:
    EposCmdHelper(const char* dllPath)
        : hModule(nullptr),
        VCS_MoveWithVelocity(nullptr),
        VCS_HaltPositionMovement(nullptr),
        VCS_SetPositionMust(nullptr)
    {
        hModule = LoadLibraryA(dllPath);
        if (!hModule) {
            throw std::runtime_error("Failed to load DLL: " + std::string(dllPath));
        }

        VCS_MoveWithVelocity = reinterpret_cast<VCS_MoveWithVelocity_t>(GetProcAddress(hModule, "VCS_MoveWithVelocity"));
        VCS_HaltPositionMovement = reinterpret_cast<VCS_HaltPositionMovement_t>(GetProcAddress(hModule, "VCS_HaltPositionMovement"));
        VCS_SetPositionMust = reinterpret_cast<VCS_SetPositionMust_t>(GetProcAddress(hModule, "VCS_SetPositionMust"));

        if (!VCS_MoveWithVelocity || !VCS_HaltPositionMovement || !VCS_SetPositionMust) {
            FreeLibrary(hModule);
            throw std::runtime_error("Failed to load one or more functions from DLL.");
        }
    }

    ~EposCmdHelper() {
        if (hModule) {
            FreeLibrary(hModule);
        }
    }

    bool MoveWithVelocity(void* keyHandle, unsigned short nodeId, int velocity, unsigned int* errorCode) {
        return VCS_MoveWithVelocity(keyHandle, nodeId, velocity, errorCode);
    }

    bool HaltPositionMovement(void* keyHandle, unsigned short nodeId, unsigned int* errorCode) {
        return VCS_HaltPositionMovement(keyHandle, nodeId, errorCode);
    }

    bool SetPositionMust(void* keyHandle, unsigned short nodeId, int position, unsigned int* errorCode) {
        return VCS_SetPositionMust(keyHandle, nodeId, position, errorCode);
    }
};

// Function to calibrate the motor to zero position
bool CalibrateMotorToZero(void* keyHandle, unsigned short nodeId, int limitSwitchPin, int velocity, unsigned int* errorCode) {
    if (!keyHandle || !errorCode) {
        std::cerr << "Invalid input: keyHandle or errorCode is null." << std::endl;
        return false;
    }

    try {
        const char* dllPath = "EposCmd64.dll"; // Adjust if DLL is in a different location
        EposCmdHelper eposCmd(dllPath);

        // Keep moving the motor until the limit switch is activated
        while (!digitalRead(limitSwitchPin)) {
            if (!eposCmd.MoveWithVelocity(keyHandle, nodeId, -velocity, errorCode)) {
                std::cerr << "Failed to move motor with velocity. Error code: " << *errorCode << std::endl;
                return false;
            }
        }

        // Stop the motor
        if (!eposCmd.HaltPositionMovement(keyHandle, nodeId, errorCode)) {
            std::cerr << "Failed to halt motor movement. Error code: " << *errorCode << std::endl;
            return false;
        }

        // Set the current position to zero
        if (!eposCmd.SetPositionMust(keyHandle, nodeId, 0, errorCode)) {
            std::cerr << "Failed to set position to zero. Error code: " << *errorCode << std::endl;
            return false;
        }

        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception during calibration: " << ex.what() << std::endl;
        return false;
    }
}
