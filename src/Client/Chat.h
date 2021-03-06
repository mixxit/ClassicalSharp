#ifndef CC_CHAT_H
#define CC_CHAT_H
#include "Typedefs.h"
#include "Constants.h"
#include "Utils.h"
#include "NetworkEnums.h"
#include "GameStructs.h"
/* Manages sending and logging chat.
   Copyright 2014-2017 ClassicalSharp | Licensed under BSD-3
*/

typedef struct ChatLine_ { UInt8 Buffer[String_BufferSize(STRING_SIZE)]; DateTime Received; } ChatLine;
ChatLine Chat_Status[3], Chat_BottomRight[3], Chat_ClientStatus[3], Chat_Announcement;
StringsBuffer Chat_Log, Chat_InputLog;

IGameComponent Chat_MakeGameComponent(void);
void Chat_SetLogName(STRING_PURE String* name);
void Chat_Send(STRING_PURE String* text);
void Chat_Add(STRING_PURE String* text);
void Chat_AddOf(STRING_PURE String* text, Int32 messageType);
#define Chat_AddRaw(str, raw) String str = String_FromConst(raw); Chat_Add(&str);
#endif