#include "pch.h"
#include <windows.h>
#include "EposCmd.h"  // Inclut le SDK d'EPOS4

extern "C" __declspec(dllexport) bool CalibrateMotorToZero(void* keyHandle, unsigned short nodeId, int limitSwitchPin, int velocity, unsigned int* errorCode) {
    // Code de ta fonction CalibrateMotorToZero
    // Tu peux ici utiliser les fonctions VCS_MoveWithVelocity, etc.
    return true; // Retourne un succès ou une erreur
}

extern "C" __declspec(dllexport) bool MoveWithVelocity(void* keyHandle, unsigned short nodeId, int velocity, unsigned int* errorCode) {
    // Code pour faire déplacer le moteur
    return true;
}

extern "C" __declspec(dllexport) bool HaltPositionMovement(void* keyHandle, unsigned short nodeId, unsigned int* errorCode) {
    // Code pour arrêter le mouvement
    return true;
}

extern "C" __declspec(dllexport) void* OpenEposDevice(const char* deviceName, const char* protocolStackName, const char* interfaceName, const char* portName, unsigned int* errorCode) {
    // Code pour ouvrir le device
    return nullptr; // Retourne un handle à utiliser pour interagir avec l'EPOS4
}

extern "C" __declspec(dllexport) void CloseEposDevice(void* keyHandle, unsigned int* errorCode) {
    // Code pour fermer le device
}

