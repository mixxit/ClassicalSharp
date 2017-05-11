#include "Platform.h"
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

HANDLE heap;
void Platform_Init() {
	heap = GetProcessHeap(); // TODO: HeapCreate instead? probably not
}

void Platform_Free() {
	HeapDestroy(heap);
}

void* Platform_MemAlloc(UInt32 numBytes) {
	return HeapAlloc(heap, 0, numBytes);
}

void Platform_MemFree(void* mem) {
	HeapFree(heap, 0, mem);
}

void Platform_MemSet(void* dst, UInt8 value, UInt32 numBytes) {
	UInt8* dstByte = (UInt8*)dst;
	// TODO: massively slow
	for (UInt32 i = 0; i < numBytes; i++) {
		*dstByte++ = value;
	}
}

void Platform_MemCpy(void* dst, void* src, UInt32 numBytes) {
	UInt8* dstByte = (UInt8*)dst;
	UInt8* srcByte = (UInt8*)src;
	// TODO: massively slow
	for (UInt32 i = 0; i < numBytes; i++) {
		*dstByte++ = *srcByte++;
	}
}


void Platform_Log(String message) {
	// TODO: log to console
}


bool Platform_FileExists(String path) {
	UInt32 attribs = GetFileAttributesA(path.buffer);
	return attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY);
}

ReturnCode Platform_FileOpen(void** file, String path, bool readOnly) {
	UINT32 access = GENERIC_READ;
	if (!readOnly) access |= GENERIC_WRITE;
	HANDLE handle = CreateFileA(path.buffer, access, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	*file = (void*)handle;

	return handle != INVALID_HANDLE_VALUE ? 0 : GetLastError();
}

ReturnCode Platform_FileCreate(void** file, String path) {
	UINT32 access = GENERIC_READ | GENERIC_WRITE;
	HANDLE handle = CreateFileA(path.buffer, access, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	*file = (void*)handle;

	return handle != INVALID_HANDLE_VALUE ? 0 : GetLastError();
}

ReturnCode Platform_FileRead(void* file, UInt8* buffer, UInt32 count, UInt32* bytesRead) {
	BOOL success = ReadFile((HANDLE)file, buffer, count, bytesRead, NULL);
	return success ? 0 : GetLastError();
}

ReturnCode Platform_FileWrite(void* file, UInt8* buffer, UInt32 count, UInt32* bytesWritten) {
	BOOL success = WriteFile((HANDLE)file, buffer, count, bytesWritten, NULL);
	return success ? 0 : GetLastError();
}

ReturnCode Platform_FileClose(void* file) {
	BOOL success = CloseHandle((HANDLE)file);
	return success ? 0 : GetLastError();
}