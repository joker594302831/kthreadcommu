#pragma once

//
//https://learn.microsoft.com/en-us/windows/win32/api/ntddmou/ns-ntddmou-mouse_input_data?redirectedfrom=MSDN
//

//
//Parameters
//DeviceObject[in]
//Pointer to the class device object.
//
//InputDataStart[in]
//Pointer to the first mouse input data packet in the input buffer of the port device.
//
//InputDataEnd[in]
//Pointer to the mouse input data packet that immediately follows the last data packet in the input data buffer of the port device.
//
//InputDataConsumed[in, out]
//Pointer to the number of mouse input data packets that are transferred by the routine.
//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct tagPOINT
	{
		LONG  x;
		LONG  y;

	} POINT, * PPOINT;

#pragma warning( push )
#pragma warning( disable : 4201 )
#define NAMELESS_DUMMY_UNION
	typedef struct _MOUSE_INPUT_DATA {
		USHORT UnitId;
		USHORT Flags;
		union {
			ULONG Buttons;
			struct {
				USHORT ButtonFlags;
				USHORT ButtonData;
			} NAMELESS_DUMMY_UNION;
		} NAMELESS_DUMMY_UNION;
		ULONG  RawButtons;
		LONG   LastX;
		LONG   LastY;
		ULONG  ExtraInformation;
	} MOUSE_INPUT_DATA, * PMOUSE_INPUT_DATA;
#pragma warning( pop )

	typedef VOID
	(*MouseClassServiceCallbackFn)(
		PDEVICE_OBJECT DeviceObject,
		PMOUSE_INPUT_DATA InputDataStart,
		PMOUSE_INPUT_DATA InputDataEnd,
		PULONG InputDataConsumed
		);

	typedef struct _MOUSE_OBJECT
	{
		PDEVICE_OBJECT              DeviceObject;
		MouseClassServiceCallbackFn ServiceCallback;
		BOOLEAN                     UseMouse;
	} MOUSE_OBJECT, * PMOUSE_OBJECT;

	//
	// Forward ASM Function
	// 

	VOID MouseClassServiceCallback(
		PDEVICE_OBJECT DeviceObject,
		PMOUSE_INPUT_DATA InputDataStart,
		PMOUSE_INPUT_DATA InputDataEnd,
		PULONG InputDataConsumed
	);

#define KeMRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

	VOID RSSetCursorPosition(LONG DeltaX, LONG DeltaY);
	VOID RSSetCursorRelative(LONG DeltaX, LONG DeltaY);

	VOID InitializeMouseControl(VOID);
	BOOLEAN OpenMouse(VOID);
	VOID MoveMouse(LONG DeltaX, LONG DeltaY, USHORT ButtonFlags);

#ifdef __cplusplus
}
#endif // __cplusplus