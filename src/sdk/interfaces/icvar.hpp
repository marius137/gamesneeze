#pragma once
#include "../../core/menu/config.hpp"

#define FCVAR_NONE					0

#define FCVAR_UNREGISTERED			(1<<0)
#define FCVAR_DEVELOPMENTONLY		(1<<1)
#define FCVAR_GAMEDLL				(1<<2)
#define FCVAR_CLIENTDLL				(1<<3)
#define FCVAR_HIDDEN				(1<<4)

#define FCVAR_PROTECTED				(1<<5)
#define FCVAR_SPONLY				(1<<6)
#define FCVAR_ARCHIVE				(1<<7)
#define FCVAR_NOTIFY				(1<<8)
#define FCVAR_USERINFO				(1<<9)
#define FCVAR_CHEAT					(1<<14)

#define FCVAR_PRINTABLEONLY			(1<<10)
#define FCVAR_UNLOGGED				(1<<11)
#define FCVAR_NEVER_AS_STRING		(1<<12)
#define FCVAR_RELEASE				(1<<19)

#define FCVAR_REPLICATED			(1<<13)
#define FCVAR_DEMO					(1<<16)
#define FCVAR_DONTRECORD			(1<<17)

#define FCVAR_NOT_CONNECTED			(1<<22)
#define FCVAR_ARCHIVE_XBOX			(1<<24)
#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)

enum class ConVarType {
	INTEGER = 2,
	FLOAT = 4,
	STRING = 15,
};

// Fuzion/AimTux

struct CvarColorRGBA {
	CvarColorRGBA(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha = 255) {
		RGBA[0] = Red;
		RGBA[1] = Green;
		RGBA[2] = Blue;
		RGBA[3] = Alpha;
	}

	unsigned char RGBA[4];
};

class ConVar {
public:
	float GetFloat() {
		typedef float (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 15)(this);
	}

	int GetInt() {
		typedef int (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 16)(this);
	}

	void SetValue(const char* value) {
		if (CONFIGBOOL("Misc>Misc>Misc>Enable Setting Cvars")) {
			typedef void (*Fn)(void*, const char*);
			return getVirtualFunc<Fn>(this, 17)(this, value);
		}
	}

	void SetValue(float value) {
		if (CONFIGBOOL("Misc>Misc>Misc>Enable Setting Cvars")) {
			typedef void (*Fn)(void*, float);
			return getVirtualFunc<Fn>(this, 18)(this, value);
		}
	}

	void SetValue(int value) {
		if (CONFIGBOOL("Misc>Misc>Misc>Enable Setting Cvars")) {
			typedef void (*Fn)(void*, int);
			return getVirtualFunc<Fn>(this, 19)(this, value);
		}
	}

	void* vtable;
	ConVar* next; //0x0008
	bool isRegistered; //0x0009
	char pad_0011[7]; //0x0010
	char* name; //0x0018
	char* description; //0x0020
	int32_t flags; //0x0028
	char pad_0x0018[0x4]; //0x002C
	void* s_pAccessor; // 0x0030
	ConVar* pParent; // 0x0038
	char* strDefault;// 0x0040
	char* strValue;  // 0x0048
	int32_t strLength;
	ConVarType type; // 0x0050
	float fValue; //0x0054
	int32_t iValue;//0x0058
	bool hasMin; //0x005C
	char _padmin[3];
	float minVal; // 0x0060
	bool hasMax; //0x0064
	char _padmax[3];
	float maxVal; // 0x0068
    char _unkpad[4];
	void* someOtherClass;
    void* fnChangeCallback;
};

class ICvar {
public:
	ConVar* FindVar(const char *var) {
		typedef ConVar* (*Fn)(void*, const char*);
		return getVirtualFunc<Fn>(this, 15)(this, var);
	}

	template <typename... Values>
	void ConsoleColorPrintf(const CvarColorRGBA& MsgColor, const char* szMsgFormat, Values... Parameters) {
		typedef void (*Fn)(void*, const CvarColorRGBA&, const char*, ...);
		return getVirtualFunc<Fn>(this, 25)(this, MsgColor, szMsgFormat, Parameters...);
	}

	template <typename... Values>
	void ConsoleDPrintf(const char* szMsgFormat, Values... Parameters) {
		typedef void (*Fn)(void*, const char*, ...);
		return getVirtualFunc<Fn>(this, 27)(this, szMsgFormat, Parameters...);
	}
};
