//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "VScript.hpp"

class CUtlBuffer;

class IScriptVM {
public:
	virtual bool Init() = 0; // 0
	virtual void Shutdown() = 0; // 1
	virtual bool ConnectDebugger() = 0; // 2
	virtual void DisconnectDebugger() = 0; // 3
	/**
	 * @return the language this vm is running
	 */
	virtual ScriptLanguage_t GetLanguage() = 0; // 4
	/**
	 * @return the name of the language this vm is running
	 */
	virtual const char* GetLanguageName() = 0; // 5
	virtual void AddSearchPath(const char* pszSearchPath) = 0; // 6
	virtual bool Frame(float simTime) = 0; // 7
#ifdef _WIN32
	virtual ScriptStatus_t Run(HSCRIPT hScript, HSCRIPT hScope = NULL, bool bWait = true) = 0; // 8
	virtual ScriptStatus_t Run(HSCRIPT hScript, bool bWait) = 0; // 9
	virtual ScriptStatus_t Run(const char* pszScript, bool bWait = true) = 0; // 10
	inline ScriptStatus_t Run(const unsigned char* pszScript, bool bWait = true) { return Run((char*)pszScript, bWait); }
	virtual HSCRIPT CompileScript(const char* pszScript, const char* pszId = NULL) = 0; // 11
	inline HSCRIPT CompileScript(const unsigned char* pszScript, const char* pszId = NULL) { return CompileScript((char*)pszScript, pszId); }
	virtual void ReleaseScript(HSCRIPT) = 0; // 12
#else
	virtual ScriptStatus_t Run(const char* pszScript, bool bWait = true) = 0; // 8
    inline ScriptStatus_t Run(const unsigned char* pszScript, bool bWait = true) { return Run((char*)pszScript, bWait); }
    virtual HSCRIPT CompileScript(const char* pszScript, const char* pszId = NULL) = 0; // 9
    inline HSCRIPT CompileScript(const unsigned char* pszScript, const char* pszId = NULL) { return CompileScript((char*)pszScript, pszId); }
    virtual void ReleaseScript(HSCRIPT) = 0; // 10
    virtual ScriptStatus_t Run(HSCRIPT hScript, HSCRIPT hScope = NULL, bool bWait = true) = 0; // 11
    virtual ScriptStatus_t Run(HSCRIPT hScript, bool bWait) = 0; // 12
#endif
	virtual HSCRIPT CreateScope(const char* pszScope, HSCRIPT hParent = NULL) = 0; // 13
	virtual void ReleaseScope(HSCRIPT hScript) = 0; // 14
	virtual HSCRIPT LookupFunction(const char* pszFunction, HSCRIPT hScope = NULL) = 0; // 15
	virtual void ReleaseFunction(HSCRIPT hScript) = 0; // 16
	virtual ScriptStatus_t ExecuteFunction(HSCRIPT hFunction, ScriptVariant_t* pArgs, int nArgs, ScriptVariant_t* pReturn, HSCRIPT hScope, bool bWait) = 0; // 17
	virtual void RegisterFunction(ScriptFunctionBinding_t* pScriptFunction) = 0; // 18
	virtual bool RegisterClass(ScriptClassDesc_t* pClassDesc) = 0; // 19
	virtual HSCRIPT RegisterInstance(ScriptClassDesc_t* pDesc, void* pInstance) = 0; // 20
	virtual void SetInstanceUniqeId(HSCRIPT hInstance, const char* pszId) = 0; // 21
	template <typename T>
	HSCRIPT RegisterInstance(T* pInstance) { return RegisterInstance(GetScriptDesc(pInstance), pInstance); }
	template <typename T>
	HSCRIPT RegisterInstance(T* pInstance, const char* pszInstance, HSCRIPT hScope = NULL) {
		HSCRIPT hInstance = RegisterInstance(GetScriptDesc(pInstance), pInstance);
		SetValue(hScope, pszInstance, hInstance);
		return hInstance;
	}
	virtual void RemoveInstance(HSCRIPT) = 0; // 22
	void RemoveInstance(HSCRIPT hInstance, const char* pszInstance, HSCRIPT hScope = NULL) {
		ClearValue(hScope, pszInstance);
		RemoveInstance(hInstance);
	}
	void RemoveInstance(const char* pszInstance, HSCRIPT hScope = NULL) {
		ScriptVariant_t val;
		if (GetValue(hScope, pszInstance, &val)) {
			if (val.m_type == FIELD_HSCRIPT) {
				RemoveInstance(val, pszInstance, hScope);
			}
			ReleaseValue(val);
		}
	}
	virtual void* GetInstanceValue(HSCRIPT hInstance, ScriptClassDesc_t* pExpectedType = NULL) = 0; // 23
	virtual bool GenerateUniqueKey(const char* pszRoot, char* pBuf, int nBufSize) = 0; // 24
	virtual bool ValueExists(HSCRIPT hScope, const char* pszKey) = 0; // 25
	bool ValueExists(const char* pszKey) { return ValueExists(NULL, pszKey); }
	virtual bool SetValue(HSCRIPT hScope, const char* pszKey, const char* pszValue) = 0; // 26
	virtual bool SetValue(HSCRIPT hScope, const char* pszKey, const ScriptVariant_t& value) = 0; // 27
	bool SetValue(const char* pszKey, const ScriptVariant_t& value) { return SetValue(NULL, pszKey, value); }
	virtual void CreateTable(ScriptVariant_t& Table) = 0; // 28
	virtual int GetNumTableEntries(HSCRIPT hScope) = 0; // 29
	virtual int GetKeyValue(HSCRIPT hScope, int nIterator, ScriptVariant_t* pKey, ScriptVariant_t* pValue) = 0; // 30
	virtual bool GetValue(HSCRIPT hScope, const char* pszKey, ScriptVariant_t* pValue) = 0; // 31
	bool GetValue(const char* pszKey, ScriptVariant_t* pValue) { return GetValue(NULL, pszKey, pValue); }
	virtual void ReleaseValue(ScriptVariant_t& value) = 0; // 32
	virtual bool ClearValue(HSCRIPT hScope, const char* pszKey) = 0; // 33
	bool ClearValue(const char* pszKey) { return ClearValue(NULL, pszKey); }
	virtual void WriteState(CUtlBuffer* pBuffer) = 0; // 34
	virtual void ReadState(CUtlBuffer* pBuffer) = 0; // 35
	virtual void RemoveOrphanInstances() = 0; // 36
	virtual void DumpState() = 0; // 37
	virtual void SetOutputCallback(ScriptOutputFunc_t pFunc) = 0; // 38
	virtual void SetErrorCallback(ScriptErrorFunc_t pFunc) = 0; // 39
	virtual bool RaiseException(const char* pszExceptionText) = 0; // 40

	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope = NULL, bool bWait = true, ScriptVariant_t* pReturn = NULL) {
		return ExecuteFunction(hFunction, NULL, 0, pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1) {
		ScriptVariant_t args[1];
		args[0] = arg1;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2) {
		ScriptVariant_t args[2];
		args[0] = arg1;
		args[1] = arg2;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3) {
		ScriptVariant_t args[3];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4) {
		ScriptVariant_t args[4];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5) {
		ScriptVariant_t args[5];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6) {
		ScriptVariant_t args[6];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7) {
		ScriptVariant_t args[7];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7, ARG_TYPE_8 arg8) {
		ScriptVariant_t args[8];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		args[7] = arg8;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7, ARG_TYPE_8 arg8, ARG_TYPE_9 arg9) {
		ScriptVariant_t args[9];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		args[7] = arg8;
		args[8] = arg9;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7, ARG_TYPE_8 arg8, ARG_TYPE_9 arg9, ARG_TYPE_10 arg10) {
		ScriptVariant_t args[10];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		args[7] = arg8;
		args[8] = arg9;
		args[9] = arg10;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7, ARG_TYPE_8 arg8, ARG_TYPE_9 arg9, ARG_TYPE_10 arg10, ARG_TYPE_11 arg11) {
		ScriptVariant_t args[11];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		args[7] = arg8;
		args[8] = arg9;
		args[9] = arg10;
		args[10] = arg11;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7, ARG_TYPE_8 arg8, ARG_TYPE_9 arg9, ARG_TYPE_10 arg10, ARG_TYPE_11 arg11, ARG_TYPE_12 arg12) {
		ScriptVariant_t args[12];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		args[7] = arg8;
		args[8] = arg9;
		args[9] = arg10;
		args[10] = arg11;
		args[11] = arg12;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12, typename ARG_TYPE_13>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7, ARG_TYPE_8 arg8, ARG_TYPE_9 arg9, ARG_TYPE_10 arg10, ARG_TYPE_11 arg11, ARG_TYPE_12 arg12, ARG_TYPE_13 arg13) {
		ScriptVariant_t args[13];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		args[7] = arg8;
		args[8] = arg9;
		args[9] = arg10;
		args[10] = arg11;
		args[11] = arg12;
		args[12] = arg13;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}

	template <typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12, typename ARG_TYPE_13, typename ARG_TYPE_14>
	ScriptStatus_t Call(HSCRIPT hFunction, HSCRIPT hScope, bool bWait, ScriptVariant_t* pReturn, ARG_TYPE_1 arg1, ARG_TYPE_2 arg2, ARG_TYPE_3 arg3, ARG_TYPE_4 arg4, ARG_TYPE_5 arg5, ARG_TYPE_6 arg6, ARG_TYPE_7 arg7, ARG_TYPE_8 arg8, ARG_TYPE_9 arg9, ARG_TYPE_10 arg10, ARG_TYPE_11 arg11, ARG_TYPE_12 arg12, ARG_TYPE_13 arg13, ARG_TYPE_14 arg14) {
		ScriptVariant_t args[14];
		args[0] = arg1;
		args[1] = arg2;
		args[2] = arg3;
		args[3] = arg4;
		args[4] = arg5;
		args[5] = arg6;
		args[6] = arg7;
		args[7] = arg8;
		args[8] = arg9;
		args[9] = arg10;
		args[10] = arg11;
		args[11] = arg12;
		args[12] = arg13;
		args[13] = arg14;
		return ExecuteFunction(hFunction, args, Q_ARRAYSIZE(args), pReturn, hScope, bWait);
	}
};