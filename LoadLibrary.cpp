#include "pch.h"
#include <windows.h>
#include <iostream>

// Typedef pour les fonctions de la DLL
typedef bool(__stdcall* VCS_MoveWithVelocity_t)(void*, unsigned short, int, unsigned int*);
typedef bool(__stdcall* VCS_HaltPositionMovement_t)(void*, unsigned short, unsigned int*);
typedef bool(__stdcall* VCS_SetPositionMust_t)(void*, unsigned short, int, unsigned int*);
typedef void* (__stdcall* VCS_OpenDevice_t)(const char*, const char*, const char*, const char*, unsigned int*);
typedef void(__stdcall* VCS_CloseDevice_t)(void*, unsigned int*);

int main() {
    HMODULE hModule = LoadLibraryA("EposCmd64.dll");
    if (!hModule) {
        std::cerr << "Erreur de chargement de la DLL !" << std::endl;
        return -1;
    }

    // Récupérer les adresses des fonctions
    VCS_MoveWithVelocity_t VCS_MoveWithVelocity = (VCS_MoveWithVelocity_t)GetProcAddress(hModule, "VCS_MoveWithVelocity");
    VCS_HaltPositionMovement_t VCS_HaltPositionMovement = (VCS_HaltPositionMovement_t)GetProcAddress(hModule, "VCS_HaltPositionMovement");
    VCS_SetPositionMust_t VCS_SetPositionMust = (VCS_SetPositionMust_t)GetProcAddress(hModule, "VCS_SetPositionMust");
    VCS_OpenDevice_t VCS_OpenDevice = (VCS_OpenDevice_t)GetProcAddress(hModule, "VCS_OpenDevice");
    VCS_CloseDevice_t VCS_CloseDevice = (VCS_CloseDevice_t)GetProcAddress(hModule, "VCS_CloseDevice");

    // Vérifier que toutes les fonctions ont été récupérées
    if (!VCS_MoveWithVelocity || !VCS_HaltPositionMovement || !VCS_SetPositionMust || !VCS_OpenDevice || !VCS_CloseDevice) {
        std::cerr << "Erreur de récupération des fonctions !" << std::endl;
        FreeLibrary(hModule);
        return -1;
    }

    // Exemple d'utilisation
    unsigned int errorCode = 0;
    void* keyHandle = VCS_OpenDevice("EPOS4", "MAXON_USB", "USB", "USB0", &errorCode);
    if (!keyHandle) {
        std::cerr << "Erreur d'ouverture du device !" << std::endl;
        FreeLibrary(hModule);
        return -1;
    }

    // Appel d'une fonction par exemple pour déplacer le moteur avec une certaine vitesse
    if (!VCS_MoveWithVelocity(keyHandle, 1, 1000, &errorCode)) {
        std::cerr << "Erreur de déplacement !" << std::endl;
        VCS_CloseDevice(keyHandle, &errorCode);
        FreeLibrary(hModule);
        return -1;
    }

    // Fermer le device
    VCS_CloseDevice(keyHandle, &errorCode);
    FreeLibrary(hModule);

    return 0;
}
