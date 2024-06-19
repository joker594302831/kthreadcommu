#pragma once

#ifndef NATIVE_IMPORT_H
#define NATIVE_IMPORT_H

#ifdef __cplusplus
extern "C" {
#endif

	NTSYSCALLAPI PLIST_ENTRY PsLoadedModuleList;
	NTSYSCALLAPI POBJECT_TYPE* IoDriverObjectType;

	typedef struct _SYSTEM_MODULE_ENTRY {
		HANDLE Section;
		PVOID MappedBase;
		PVOID ImageBase;
		ULONG ImageSize;
		ULONG Flags;
		USHORT LoadOrderIndex;
		USHORT InitOrderIndex;
		USHORT LoadCount;
		USHORT OffsetToFileName;
		UCHAR FullPathName[256];
	} SYSTEM_MODULE_ENTRY, * PSYSTEM_MODULE_ENTRY;

	typedef struct _SYSTEM_MODULE_INFORMATION {
		ULONG Count;
		SYSTEM_MODULE_ENTRY Module[1];
	} SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

	typedef struct _LDR_DATA_TABLE_ENTRY
	{
		LIST_ENTRY64	InLoadOrderLinks;
		LIST_ENTRY64	InMemoryOrderLinks;
		LIST_ENTRY64	InInitializationOrderLinks;
		UINT64			DllBase;
		UINT64			EntryPoint;
		ULONG			SizeOfImage;
		UNICODE_STRING	FullDllName;
		UNICODE_STRING 	BaseDllName;
		ULONG			Flags;
		USHORT			LoadCount;
		USHORT			TlsIndex;
		PVOID			SectionPointer;
		ULONG			CheckSum;
		PVOID			LoadedImports;
		PVOID			EntryPointActivationContext;
		PVOID			PatchInformation;
		LIST_ENTRY64	ForwarderLinks;
		LIST_ENTRY64	ServiceTagLinks;
		LIST_ENTRY64	StaticLinks;
		PVOID			ContextInformation;
		ULONG64			OriginalBase;
		LARGE_INTEGER	LoadTime;
	} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

	NTSYSCALLAPI PIMAGE_NT_HEADERS
		RtlImageNtHeader(
			IN PVOID ModuleAddress
			);

	NTSYSCALLAPI PVOID
		PsGetProcessSectionBaseAddress(
			IN PEPROCESS Process
			);

	NTSYSCALLAPI PPEB
		PsGetProcessPeb(
			IN PEPROCESS Process
			);

	NTSYSCALLAPI NTSTATUS
		MmCopyVirtualMemory(
			PEPROCESS SourceProcess,
			PVOID SourceAddress,
			PEPROCESS TargetProcess,
			PVOID TargetAddress,
			SIZE_T BufferSize,
			KPROCESSOR_MODE PreviousMode,
			PSIZE_T ReturnSize
			);

	NTSYSCALLAPI NTSTATUS
		ObReferenceObjectByName(
			__in PUNICODE_STRING ObjectName,
			__in ULONG Attributes,
			__in_opt PACCESS_STATE AccessState,
			__in_opt ACCESS_MASK DesiredAccess,
			__in POBJECT_TYPE ObjectType,
			__in KPROCESSOR_MODE AccessMode,
			__inout_opt PVOID ParseContext,
			__out PVOID* Object
			);

	NTSYSCALLAPI NTSTATUS
		ZwQuerySystemInformation(
			ULONG	SystemInformationClass,
			PVOID	SystemInformation,
			ULONG	SystemInformationLength,
			PULONG	ReturnLength
			);

#ifdef __cplusplus
}
#endif

#endif // !NATIVE_IMPORT_H
