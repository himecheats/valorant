#include "includes.h"
#include "curl.h"

char dlldir[320];

DWORD64 ClientInputXD = 0;
void* DetourVTable(void** VTable, int Function, void* Detour)
{
	void* ret = VTable[Function];
	DWORD old;
	VirtualProtect(&(VTable[Function]), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
	VTable[Function] = Detour;
	VirtualProtect(&(VTable[Function]), sizeof(void*), old, &old);
	return ret;
}
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: // A process is loading the DLL.


		DisableThreadLibraryCalls(hModule);
		GetModuleFileName(hModule, (LPWSTR)dlldir, 512);
		for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
		CreateThread(NULL, 0, Start, NULL, 0, NULL);
		il2cpp::init();
		//ClientInputXD = GetModBase((L"GameAssembly.dll")) + 0x3045D0;
		//DetourAttach(&(LPVOID&)ClientInputXD, &ClientInput);

		break;
	case DLL_PROCESS_DETACH: // A process unloads the DLL.
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
		DetourTransactionCommit();
		break;
	}
	return TRUE;
}
