//
// Created by ENDERZOMBI102 on 01/03/2022.
//
#pragma once

// -------------------------
// CVAR flags
// -------------------------

/**
 *
 * \applicable_to CVARs, ConCommands
 *
 * Default, no flags at all
 */
#define FCVAR_NONE 0

// Command to ConVars and ConCommands
// ConVar Systems
/**
 *
 * \applicable_to CVARs, ConCommands
 *
 * If this is set, don't add to linked list, etc.
 */
#define FCVAR_UNREGISTERED (1<<0)
/**
 *
 * \applicable_to CVARs, ConCommands
 *
 * Hidden in released products.
 * Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
 */
#define FCVAR_DEVELOPMENTONLY (1 << 1)
/**
 * \applicable_to CVARs, ConCommands
 *
 * defined by the game DLL (not for use in plugins)
 */
#define FCVAR_GAMEDLL (1<<2)
/**
 * \applicable_to CVARs, ConCommands
 *
 * defined by the client DLL (not for use in plugins)
 */
#define FCVAR_CLIENTDLL	(1<<3)
/**
 * \applicable_to CVARs, ConCommands
 *
 * Hidden. Doesn't appear in find or autocomplete.
 * Like FCVAR_DEVELOPMENTONLY, but can't be compiled out.
 */
#define FCVAR_HIDDEN (1 << 4)

// cvar only
/**
 * \applicable_to CVARs
 *
 * It's a server cvar, but we don't send the data since it's a password, etc.
 * Sends 1 if it's not bland/zero, 0 otherwise as value
 */
#define FCVAR_PROTECTED	(1<<5)
/**
 * \applicable_to CVARs
 *
 * This cvar cannot be changed by clients connected to a multiplayer server.
 */
#define FCVAR_SPONLY (1<<6)
/**
 * \applicable_to CVARs
 *
 * set to cause it to be saved to vars.rc
 */
#define	FCVAR_ARCHIVE (1<<7)
/**
 * \applicable_to CVARs
 *
 * notifies players when changed.
 */
#define FCVAR_NOTIFY (1 << 8)
/**
 * \applicable_to CVARs
 *
 * changes the client's info string
 */
#define	FCVAR_USERINFO (1<<9)
/**
 * \applicable_to CVARs
 *
 * Marks a CVAR as a cheat.
 * Marked cvars requires sv_cheats to be 1 to be used.
 */
#define FCVAR_CHEAT (1 << 14)

/**
 * \applicable_to CVARs
 *
 * This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
 */
#define FCVAR_PRINTABLEONLY	(1<<10)
/**
 * \applicable_to CVARs
 *
 * If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
 */
#define FCVAR_UNLOGGED (1<<11)
/**
 * \applicable_to CVARs
 *
 * never try to print a cvar marked with this.
 */
#define FCVAR_NEVER_AS_STRING (1 << 12)


#define COMMAND_COMPLETION_MAXITEMS 64
#define COMMAND_COMPLETION_ITEM_LENGTH 64


#ifdef _WIN32
	#define __funcc __thiscall
#else
	#define __funcc __attribute__((__cdecl__))
#endif


struct CCommand;
class ConCommandBase;

using _CommandCallback = void (*)(const CCommand& args);
using _CommandCompletionCallback = int (*)(const char* partial, char commands[COMMAND_COMPLETION_MAXITEMS][COMMAND_COMPLETION_ITEM_LENGTH]);
using _InternalSetValue = void(__funcc*)(void* thisptr, const char* value);
using _InternalSetFloatValue = void(__funcc*)(void* thisptr, float value);
using _InternalSetIntValue = void(__funcc*)(void* thisptr, int value);
using _RegisterConCommand = void(__funcc*)(void* thisptr, ConCommandBase* pCommandBase);
using _UnregisterConCommand = void(__funcc*)(void* thisptr, ConCommandBase* pCommandBase);
using _FindCommandBase = void*(__funcc*)(void* thisptr, const char* name);
using _AutoCompletionFunc = int(__funcc*)(void* thisptr, char const* partial, char commands[COMMAND_COMPLETION_MAXITEMS][COMMAND_COMPLETION_ITEM_LENGTH]);

/**
 * Base class for console commands and variables
 */
class ConCommandBase {
public:
	void* ConCommandBase_VTable; // 0
	ConCommandBase* m_pNext; // 4
	bool m_bRegistered; // 8
	const char* m_pszName; // 12
	const char* m_pszHelpString; // 16
	int m_nFlags; // 20

public:
	ConCommandBase()
			: ConCommandBase_VTable(nullptr)
			, m_pNext(nullptr)
			, m_bRegistered(false)
			, m_pszName(nullptr)
			, m_pszHelpString(nullptr)
			, m_nFlags(0)
	{
	}
};

/**
 * Represents a command
 */
struct CCommand {
	enum {
		COMMAND_MAX_ARGC = 64,
		COMMAND_MAX_LENGTH = 512
	};
	int m_nArgc;
	int m_nArgv0Size;
	char m_pArgSBuffer[COMMAND_MAX_LENGTH];
	char m_pArgvBuffer[COMMAND_MAX_LENGTH];
	const char* m_ppArgv[COMMAND_MAX_ARGC];

	int ArgC() const {
		return this->m_nArgc;
	}

	const char* Arg(int nIndex) const {
		return this->m_ppArgv[nIndex];
	}

	const char* operator[](int nIndex) const {
		return Arg(nIndex);
	}
};

/**
 * Represents a Console Command
 */
class ConCommand : public ConCommandBase {
public:
	union {
		void* m_fnCommandCallbackV1;
		_CommandCallback m_fnCommandCallback;
		void* m_pCommandCallback;
	};

	union {
		_CommandCompletionCallback m_fnCompletionCallback;
		void* m_pCommandCompletionCallback;
	};

	bool m_bHasCompletionCallback : 1;
	bool m_bUsingNewCommandCallback : 1;
	bool m_bUsingCommandCallbackInterface : 1;

public:
	ConCommand() : ConCommandBase() ,
		m_fnCommandCallbackV1(nullptr), m_fnCompletionCallback(nullptr) { }
};

/**
 * Represents a registered Console Variable
 */
class ConVar : public ConCommandBase {
public:
	void* ConVar_VTable; // 24
	ConVar* m_pParent; // 28
	const char* m_pszDefaultValue; // 32
	char* m_pszString; // 36
	int m_StringLength; // 40
	float m_fValue; // 44
	int m_nValue; // 48
	bool m_bHasMin; // 52
	float m_fMinVal; // 56
	bool m_bHasMax; // 60
	float m_fMaxVal; // 64
	void* m_fnChangeCallback; // 68

public:
	ConVar()
			: ConCommandBase()
			, ConVar_VTable(nullptr)
			, m_pParent(nullptr)
			, m_pszDefaultValue(nullptr)
			, m_pszString(nullptr)
			, m_StringLength(0)
			, m_fValue(0)
			, m_nValue(0)
			, m_bHasMin(0)
			, m_fMinVal(0)
			, m_bHasMax(0)
			, m_fMaxVal(0)
			, m_fnChangeCallback(nullptr) { }
	~ConVar() {
		if (this->m_pszString) {
			delete[] this->m_pszString;
			this->m_pszString = nullptr;
		}
	}
};

/**
 * Represents a Console Variable
 */
class ConVar2 : public ConVar {
public:
	// CUtlVector<FnChangeCallback_t> m_fnChangeCallback
	// CUtlMemory<FnChangeCallback_t> m_Memory
	int m_nAllocationCount; // 72
	int m_nGrowSize; // 76
	int m_Size; // 80
	void* m_pElements; // 84

public:
	ConVar2()
			: ConVar()
			, m_nAllocationCount(0)
			, m_nGrowSize(0)
			, m_Size(0)
			, m_pElements(nullptr) { }
};
