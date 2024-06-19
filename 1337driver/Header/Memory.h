#pragma once

#define PHY_ADDRESS_MASK                0x000ffffffffff000ull
#define PHY_ADDRESS_MASK_1GB_PAGES      0x000fffffc0000000ull
#define PHY_ADDRESS_MASK_2MB_PAGES      0x000fffffffe00000ull

#define VADDR_ADDRESS_MASK_1GB_PAGES    0x000000003fffffffull
#define VADDR_ADDRESS_MASK_2MB_PAGES    0x00000000001fffffull
#define VADDR_ADDRESS_MASK_4KB_PAGES    0x0000000000000fffull

#define ENTRY_PRESENT_BIT               1
#define ENTRY_PAGE_SIZE_BIT             0x0000000000000080ull

#define PAGE_OFFSET_SIZE	            12
#define PMASK				            0xFFFFFF000

namespace Memory
{
    FORCEINLINE PVOID
        AllocPoolMemory(
            SIZE_T NumberOfBytes
        )
    {
        return ExAllocatePool2(POOL_FLAG_NON_PAGED_EXECUTE, NumberOfBytes, ALLOC_POOL_TAG);
    }

    FORCEINLINE VOID
        FreePoolMemory(
            PVOID Pointer
        )
    {
        ExFreePoolWithTag(Pointer, ALLOC_POOL_TAG);
    }

    FORCEINLINE PVOID
        MapPhysical(
            PHYSICAL_ADDRESS PhysicalAddress,
            SIZE_T NumberOfBytes,
            ULONG Protect
            )
    {
        return MmMapIoSpaceEx(PhysicalAddress, NumberOfBytes, Protect);
    }

    FORCEINLINE VOID
        UnmapPhysical(
            PVOID BaseVirtualAddress,
            SIZE_T NumberOfBytes
            )
    {
        MmUnmapIoSpace(BaseVirtualAddress, NumberOfBytes);
    }

    PHYSICAL_ADDRESS
        TranslateLinearAddress(
            ULONG64 CR3,
            ULONG64 VirtualAddress
            );

    BOOLEAN
        CopyMemory(
            ULONG64 Source,
            PVOID Destination,
            SIZE_T BytesToCopy,
            PSIZE_T BytesCopied
            );

    FORCEINLINE PVOID
        ResolveRelativeAddress(
            PVOID Instruction,
            ULONG Offsets,
            ULONG SizeOfInstruction
            )
    {
        ULONG64 Instr       = (ULONG64)Instruction;
        LONG RipOffset      = *(PLONG)(Instr + Offsets);
        PVOID ResolvedAddr  = (PVOID)(Instr + SizeOfInstruction + RipOffset);

        return ResolvedAddr;
    }
}