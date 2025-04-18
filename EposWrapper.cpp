#include "pch.h"
#include <windows.h>
#include <iostream>
#include "EposWrapper.h"

typedef void* (__stdcall* VCS_OpenDevice_t)(const char*, const char*, const char*, const char*, unsigned int*);
typedef bool(__stdcall* VCS_MoveWithVelocity_t)(void*, unsigned short, int, unsigned int*);
typedef bool(__stdcall* VCS_HaltPositionMovement_t)(void*, unsigned short, unsigned int*);
typedef bool(__stdcall* VCS_SetPositionMust_t)(void*, unsigned short, int, unsigned int*);
typedef bool(__stdcall* VCS_CloseDevice_t)(void*, unsigned int*);

HMODULE dllHandle = nullptr;

extern "C" __declspec(dllexport) bool __stdcall CalibrateMotorToZero(const char* deviceName, const char* interfaceName, unsigned short nodeId, int velocity) {
    unsigned int errorCode = 0;

    if (!dllHandle) dllHandle = LoadLibraryA("EposCmd64.dll");
    if (!dllHandle) return false;

    VCS_OpenDevice_t VCS_OpenDevice = (VCS_OpenDevice_t)GetProcAddress(dllHandle, "VCS_OpenDevice");
    VCS_CloseDevice_t VCS_CloseDevice = (VCS_CloseDevice_t)GetProcAddress(dllHandle, "VCS_CloseDevice");
    VCS_MoveWithVelocity_t VCS_MoveWithVelocity = (VCS_MoveWithVelocity_t)GetProcAddress(dllHandle, "VCS_MoveWithVelocity");
    VCS_HaltPositionMovement_t VCS_HaltPositionMovement = (VCS_HaltPositionMovement_t)GetProcAddress(dllHandle, "VCS_HaltPositionMovement");
    VCS_SetPositionMust_t VCS_SetPositionMust = (VCS_SetPositionMust_t)GetProcAddress(dllHandle, "VCS_SetPositionMust");

    if (!VCS_OpenDevice || !VCS_CloseDevice || !VCS_MoveWithVelocity || !VCS_HaltPositionMovement || !VCS_SetPositionMust)
        return false;

    void* keyHandle = VCS_OpenDevice(deviceName, "MAXON_USB", interfaceName, "USB0", &errorCode);
    if (!keyHandle) return false;

    // Simule le déplacement vers le zéro pendant quelques ms
    for (int i = 0; i < 100; ++i) {
        VCS_MoveWithVelocity(keyHandle, nodeId, -velocity, &errorCode);
        Sleep(20);
    }

    VCS_HaltPositionMovement(keyHandle, nodeId, &errorCode);
    VCS_SetPositionMust(keyHandle, nodeId, 0, &errorCode);
    VCS_CloseDevice(keyHandle, &errorCode);

    return true;
}
