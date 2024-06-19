#pragma once

typedef struct _HANDLE_TABLE
{
	ULONG       NextHandleNeedingPool;  //Uint4B
	LONG        ExtraInfoPages;         //Int4B
	ULONG64     TableCode;              //Uint8B 
	PEPROCESS   QuotaProcess;           //Ptr64 _EPROCESS
	_LIST_ENTRY HandleTableList;        //_LIST_ENTRY
	ULONG       UniqueProcessId;        //Uint4B
} HANDLE_TABLE, * PHANDLE_TABLE;

typedef struct _HANDLE_TABLE_ENTRY_INFO
{
	ULONG AuditMask;                //Uint4B
	ULONG MaxRelativeAccessMask;    //Uint4b
} HANDLE_TABLE_ENTRY_INFO, * PHANDLE_TABLE_ENTRY_INFO;

#pragma warning( push )
#pragma warning( disable : 4201 )
typedef struct _HANDLE_TABLE_ENTRY
{
	union                                           //that special class
	{
		ULONG64 VolatileLowValue;                   //Int8B
		ULONG64 LowValue;                           //Int8B
		ULONG64 RefCountField;                      //Int8B
		_HANDLE_TABLE_ENTRY_INFO* InfoTable;        //Ptr64 _HANDLE_TABLE_ENTRY_INFO
		struct
		{
			ULONG64 Unlocked : 1;        //1Bit
			ULONG64 RefCnt : 16;       //16Bits
			ULONG64 Attributes : 3;        //3Bits
			ULONG64 ObjectPointerBits : 44;       //44Bits
		};
	};
	union
	{
		ULONG64 HighValue;                          //Int8B
		_HANDLE_TABLE_ENTRY* NextFreeHandleEntry;   //Ptr64 _HANDLE_TABLE_ENTRY
	};
} HANDLE_TABLE_ENTRY, * PHANDLE_TABLE_ENTRY;
#pragma warning( pop )