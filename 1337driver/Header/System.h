#pragma once

namespace System
{
	PVOID GetSystemModuleBase(LPCWSTR ModuleName);
	NTSTATUS QuerySystemModule(const char* ModuleName, ULONG64* ModuleBase, SIZE_T* ModuleSize);

}