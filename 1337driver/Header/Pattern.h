#pragma once

namespace Utility
{
    BOOLEAN __DataCompare(
        LPCSTR pdata,
        LPCSTR bmask,
        LPCSTR szmask
        );

    ULONG64 __FindPattern(
        ULONG64 base,
        SIZE_T size,
        LPCSTR bmask,
        LPCSTR szmask
        );

    NTSTATUS BBSearchPattern(
        IN PCUCHAR pattern,
        IN UCHAR wildcard,
        IN ULONG64 len,
        IN const VOID* base,
        IN ULONG64 size,
        OUT PVOID* ppFound
        );

    NTSTATUS BBScanSection(IN PCCHAR section, IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, OUT PVOID* ppFound);

}