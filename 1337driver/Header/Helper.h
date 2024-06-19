#pragma once

namespace Utility
{
    FORCEINLINE
        VOID DelayExecutionThread(
            DWORD Milliseconds
        )
    {
        ULONG64 ms = Milliseconds;
        ms = (ms * 1000) * 10;
        ms = ms * -1;
        KeDelayExecutionThread(KernelMode, 0, (PLARGE_INTEGER)&ms);
    }
}

class CRegistry
{
private:

    HANDLE hKey;

public:

    CRegistry()
    {
        UNICODE_STRING UnicodePath;
        RtlInitUnicodeString(&UnicodePath, Encrypt(REGISTRY_PATH_KERNEL));

        OBJECT_ATTRIBUTES ObjectAttributes;
        InitializeObjectAttributes(&ObjectAttributes, &UnicodePath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

        NTSTATUS Status = ZwOpenKey(&hKey, KEY_ALL_ACCESS, &ObjectAttributes);

        if (!NT_SUCCESS(Status))
        {
            LogPrint("Error Opening Handle: 0x%08X\r\n", Status);
        }
    }

    ~CRegistry()
    {
        ZwClose(hKey);
    }

    BOOLEAN ReadValue(LPCWSTR ValueName, PVOID OutputBuffer, ULONG BufferSize)
    {
        UNICODE_STRING UnicodeValueName;
        ULONG PartialInformationSize;
        PKEY_VALUE_PARTIAL_INFORMATION PartialInformation;
        ULONG ResultLength;
        NTSTATUS Status;
        BOOLEAN Result;

        RtlInitUnicodeString(&UnicodeValueName, ValueName);

        ResultLength = 0;
        PartialInformationSize = sizeof(KEY_VALUE_PARTIAL_INFORMATION) + BufferSize - 1;
        PartialInformation = (PKEY_VALUE_PARTIAL_INFORMATION)Memory::AllocPoolMemory(PartialInformationSize);
        Status = ZwQueryValueKey(hKey, &UnicodeValueName, KeyValuePartialInformation, PartialInformation, PartialInformationSize, &ResultLength);
        Result = FALSE;

        if (NT_SUCCESS(Status)) {

            RtlCopyMemory(OutputBuffer, PartialInformation->Data, PartialInformation->DataLength);
            Result = TRUE;

        }
        else if (Status == STATUS_BUFFER_OVERFLOW ||
            Status == STATUS_BUFFER_TOO_SMALL
            )
        {
            LogPrint("Buffer Overflow.\r\n");
        }

        Memory::FreePoolMemory(PartialInformation);
        return Result;
    }
    BOOLEAN WriteValue(LPWSTR ValueName, ULONG Type, PVOID Data, ULONG DataSize)
    {
        UNICODE_STRING UnicodeValueName;
        RtlInitUnicodeString(&UnicodeValueName, ValueName);
        if (ZwSetValueKey(hKey, &UnicodeValueName, 0, Type, Data, DataSize) == STATUS_SUCCESS)
            return TRUE;
        return FALSE;
    }

    template<typename T>
    T ReadValue(LPCWSTR Source)
    {
        T Result;
        RtlSecureZeroMemory(&Result, sizeof(Result));
        ReadValue(Source, &Result, sizeof(Result));
        return Result;
    }
    VOID WriteValue(LPWSTR ValueName, ULONG Data)
    {
        WriteValue(ValueName, REG_DWORD, &Data, sizeof(Data));
    }

    VOID DeleteValue(LPWSTR ValueName)
    {
        UNICODE_STRING UnicodeValueName;
        RtlInitUnicodeString(&UnicodeValueName, ValueName);
        ZwDeleteValueKey(hKey, &UnicodeValueName);
    }
};
