#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) bool __stdcall CalibrateMotorToZero(const char* deviceName, const char* interfaceName, unsigned short nodeId, int velocity);

#ifdef __cplusplus
}
#endif

