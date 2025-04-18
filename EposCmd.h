// EposCmd.h
#ifndef EPOSCMD_H
#define EPOSCMD_H

#include <windows.h>
// Déclarations des fonctions
extern "C" {
    __declspec(dllexport) bool VCS_MoveWithVelocity(void* keyHandle, unsigned short nodeId, int velocity, unsigned int* errorCode);
    __declspec(dllexport) bool VCS_HaltPositionMovement(void* keyHandle, unsigned short nodeId, unsigned int* errorCode);
    __declspec(dllexport) bool VCS_SetPositionMust(void* keyHandle, unsigned short nodeId, int position, unsigned int* errorCode);
    __declspec(dllexport) void* VCS_OpenDevice(const char* deviceName, const char* protocolStackName, const char* interfaceName, const char* portName, unsigned int* errorCode);
    __declspec(dllexport) void VCS_CloseDevice(void* keyHandle, unsigned int* errorCode);
}

#endif
#include "EposCmd.cpp"

// Implementation of VCS_HaltPositionMovement
bool VCS_HaltPositionMovement(void* keyHandle, unsigned short nodeId, unsigned int* errorCode) {
    if (keyHandle == nullptr || errorCode == nullptr) {
        if (errorCode) {
            *errorCode = 1; // Example error code for invalid parameters
        }
        return false;
    }

    // Simulate halting position movement
    // Replace this with actual device communication logic
    *errorCode = 0; // No error
    return true;    // Successfully halted position movement
}

// EposCmd.cpp