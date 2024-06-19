#pragma once

namespace Process
{
    typedef struct _NT_KPROCESS {
        DISPATCHER_HEADER Header;
        LIST_ENTRY ProfileListHead;
        ULONG64 DirectoryTableBase;
        UCHAR Data[1];
    } NT_KPROCESS, * PNT_KPROCESS;

    ULONG64
        GetProcessDirectoryBase(
            PEPROCESS Process
        );

    BOOLEAN
        ReadProcessMemory(
            ULONG64 ProcessCR3,
            ULONG64 VirtualAddress,
            PVOID Destination,
            SIZE_T NumberOfBytes,
            PSIZE_T NumberOfBytesCopied
        );

    BOOLEAN
        WriteProcessMemory(
            ULONG64 ProcessCR3,
            ULONG64 VirtualAddress,
            PVOID Source,
            SIZE_T NumberOfBytes,
            PSIZE_T NumberOfBytesCopied
        );

}