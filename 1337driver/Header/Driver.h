#pragma once


#include <ntifs.h>
#include <ntstrsafe.h>
#include <ntimage.h>
#include <dontuse.h>

#include "Native.h"

#pragma warning( disable : 4309 )
#include "skCrypt.h"

#ifndef DBG
#define LogPrint(Text, ...)
#else
#define LogPrint(Text, ...)     DbgPrint(Encrypt(Text), __VA_ARGS__)
#endif // !_DBG

#include "System.h"
#include "Pattern.h"
#include "Spoof.h"
#include "Memory.h"
#include "Process.h"
#include "Helper.h"
#include "Mouse.h"