// calibration.h

#pragma once

#ifdef CALIBRATIONDLL_EXPORTS
#define CALIBRATION_API __declspec(dllexport)
#else
#define CALIBRATION_API __declspec(dllimport)
#endif

extern "C" {
    CALIBRATION_API bool CalibrateMotorToZero(void* keyHandle,
        unsigned short nodeId,
        int limitSwitchPin,
        int velocity,
        unsigned int* errorCode);
}

