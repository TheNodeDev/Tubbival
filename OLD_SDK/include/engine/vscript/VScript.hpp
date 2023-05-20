//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "engine/Math.hpp"
#include "engine/CUtl.hpp"
#include "Macros.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>

// TEMP
#include <stdio.h>

#define Q_ARRAYSIZE(p) ( sizeof(p) / sizeof(p[0]) )

#ifdef __GNUC__
    #include <string.h>
    #define _strdup strdup
#endif

#ifndef __int16
    #define __int16 int16_t
#endif

template <class T>
inline void Construct(T* pMemory) {
	::new (pMemory) T;
}

template <class T>
inline void CopyConstruct(T* pMemory, T const& src) {
	::new (pMemory) T(src);
}

template <class T>
inline void Destruct(T* pMemory) {
	pMemory->~T();
}



typedef enum _fieldtypes {
	FIELD_VOID = 0,
	FIELD_FLOAT,
	FIELD_STRING,
	FIELD_VECTOR,
	FIELD_QUATERNION,
	FIELD_INTEGER,
	FIELD_BOOLEAN,
	FIELD_SHORT,
	FIELD_CHARACTER,
	FIELD_COLOR32,
	FIELD_EMBEDDED,
	FIELD_CUSTOM,
	FIELD_CLASSPTR,
	FIELD_EHANDLE,
	FIELD_EDICT,
	FIELD_POSITION_VECTOR,
	FIELD_TIME,
	FIELD_TICK,
	FIELD_MODELNAME,
	FIELD_SOUNDNAME,
	FIELD_INPUT,
	FIELD_FUNCTION,
	FIELD_VMATRIX,
	FIELD_VMATRIX_WORLDSPACE,
	FIELD_MATRIX3X4_WORLDSPACE,
	FIELD_INTERVAL,
	FIELD_MODELINDEX,
	FIELD_MATERIALINDEX,
	FIELD_VECTOR2D,
	FIELD_INTEGER64,
	FIELD_VECTOR4D,
	FIELD_TYPECOUNT,
} fieldtype_t;

#define DECLARE_POINTER_HANDLE(name) \
    struct name##__ {                \
        int unused;                  \
    };                               \
    typedef struct name##__* name

class IScriptVM;

enum ScriptLanguage_t {
	SL_NONE,
	SL_GAMEMONKEY,
	SL_SQUIRREL,
	SL_LUA,
	SL_PYTHON,
	SL_DEFAULT = SL_SQUIRREL
};

DECLARE_POINTER_HANDLE(HSCRIPT);
#define INVALID_HSCRIPT ( (HSCRIPT) -1 )

enum ExtendedFieldType {
	FIELD_TYPEUNKNOWN = FIELD_TYPECOUNT,
	FIELD_CSTRING,
	FIELD_HSCRIPT,
	FIELD_VARIANT,
};

typedef int ScriptDataType_t;
struct ScriptVariant_t;

template <typename T>
struct ScriptDeducer { /*enum { FIELD_TYPE = FIELD_TYPEUNKNOWN };*/ };

#define DECLARE_DEDUCE_FIELDTYPE(fieldType, type) \
    template <>                                   \
    struct ScriptDeducer<type> {                  \
        enum { FIELD_TYPE = fieldType };          \
    };

DECLARE_DEDUCE_FIELDTYPE(FIELD_VOID, void);
DECLARE_DEDUCE_FIELDTYPE(FIELD_FLOAT, float);
DECLARE_DEDUCE_FIELDTYPE(FIELD_CSTRING, const char*);
DECLARE_DEDUCE_FIELDTYPE(FIELD_CSTRING, char*);
DECLARE_DEDUCE_FIELDTYPE(FIELD_VECTOR, Vector);
DECLARE_DEDUCE_FIELDTYPE(FIELD_VECTOR, const Vector&);
DECLARE_DEDUCE_FIELDTYPE(FIELD_INTEGER, int);
DECLARE_DEDUCE_FIELDTYPE(FIELD_BOOLEAN, bool);
DECLARE_DEDUCE_FIELDTYPE(FIELD_CHARACTER, char);
DECLARE_DEDUCE_FIELDTYPE(FIELD_HSCRIPT, HSCRIPT);
DECLARE_DEDUCE_FIELDTYPE(FIELD_VARIANT, ScriptVariant_t);

#define ScriptDeduceType(T) ScriptDeducer<T>::FIELD_TYPE

template <typename T>
inline const char* ScriptFieldTypeName() {
	return T::using_unknown_script_type();
}

#define DECLARE_NAMED_FIELDTYPE(fieldType, strName) \
    template <>                                     \
    inline const char* ScriptFieldTypeName<fieldType>() { return strName; }
DECLARE_NAMED_FIELDTYPE(void, "void");
DECLARE_NAMED_FIELDTYPE(float, "float");
DECLARE_NAMED_FIELDTYPE(const char*, "cstring");
DECLARE_NAMED_FIELDTYPE(char*, "cstring");
DECLARE_NAMED_FIELDTYPE(Vector, "vector");
DECLARE_NAMED_FIELDTYPE(const Vector&, "vector");
DECLARE_NAMED_FIELDTYPE(int, "integer");
DECLARE_NAMED_FIELDTYPE(bool, "boolean");
DECLARE_NAMED_FIELDTYPE(char, "character");
DECLARE_NAMED_FIELDTYPE(HSCRIPT, "hscript");
DECLARE_NAMED_FIELDTYPE(ScriptVariant_t, "variant");

inline const char* ScriptFieldTypeName(__int16 eType) {
	switch (eType) {
		case FIELD_VOID:
			return "void";
		case FIELD_FLOAT:
			return "float";
		case FIELD_CSTRING:
			return "cstring";
		case FIELD_VECTOR:
			return "vector";
		case FIELD_INTEGER:
			return "integer";
		case FIELD_BOOLEAN:
			return "boolean";
		case FIELD_CHARACTER:
			return "character";
		case FIELD_HSCRIPT:
			return "hscript";
		case FIELD_VARIANT:
			return "variant";
		default:
			return "unknown_script_type";
	}
}

struct ScriptFuncDescriptor_t {
	ScriptFuncDescriptor_t() {
		m_pszFunction = NULL;
		m_ReturnType = FIELD_TYPEUNKNOWN;
		m_pszDescription = NULL;
	}

	const char* m_pszScriptName;
	const char* m_pszFunction;
	const char* m_pszDescription;
	ScriptDataType_t m_ReturnType;
	CUtlVector<ScriptDataType_t> m_Parameters;
};

#define SCRIPT_HIDE "@"
#define SCRIPT_SINGLETON "!"
#define SCRIPT_ALIAS(alias, description) "#" alias ":" description

enum ScriptFuncBindingFlags_t {
	SF_MEMBER_FUNC = 0x01,
};

typedef bool (*ScriptBindingFunc_t)(void* pFunction, void* pContext, ScriptVariant_t* pArguments, int nArguments, ScriptVariant_t* pReturn);

struct ScriptFunctionBinding_t {
	ScriptFuncDescriptor_t m_desc;
	ScriptBindingFunc_t m_pfnBinding;
	void* m_pFunction;
	unsigned m_flags;
};

class IScriptInstanceHelper {
public:
	virtual void* GetProxied(void* p) { return p; }
	virtual bool ToString(void* p, char* pBuf, int bufSize) { return false; }
	virtual void* BindOnRead(HSCRIPT hInstance, void* pOld, const char* pszId) { return NULL; }
};

struct ScriptClassDesc_t {
	ScriptClassDesc_t()
			: m_pszScriptName(0)
			, m_pszClassname(0)
			, m_pszDescription(0)
			, m_pBaseDesc(0)
			, m_pfnConstruct(0)
			, m_pfnDestruct(0)
			, pHelper(NULL) { }

	const char* m_pszScriptName;
	const char* m_pszClassname;
	const char* m_pszDescription;
	ScriptClassDesc_t* m_pBaseDesc;
	CUtlVector<ScriptFunctionBinding_t> m_FunctionBindings;

	void* (*m_pfnConstruct)();
	void (*m_pfnDestruct)(void*);
	IScriptInstanceHelper* pHelper;
};

enum SVFlags_t {
	SV_FREE = 0x01,
};

struct ScriptVariant_t {
	ScriptVariant_t() : m_flags(0) , m_type(FIELD_VOID) {
		m_pVector = 0;
	}

	ScriptVariant_t(int val) : m_flags(0) , m_type(FIELD_INTEGER) {
		m_int = val;
	}

	ScriptVariant_t(float val) : m_flags(0) , m_type(FIELD_FLOAT) {
		m_float = val;
	}

	ScriptVariant_t(double val) : m_flags(0) , m_type(FIELD_FLOAT) {
		m_float = (float)val;
	}

	ScriptVariant_t(char val) : m_flags(0) , m_type(FIELD_CHARACTER) {
		m_char = val;
	}

	ScriptVariant_t(bool val) : m_flags(0) , m_type(FIELD_BOOLEAN) {
		m_bool = val;
	}

	ScriptVariant_t(HSCRIPT val) : m_flags(0) , m_type(FIELD_HSCRIPT) {
		m_hScript = val;
	}

	ScriptVariant_t(const Vector& val, bool bCopy = false) : m_flags(0) , m_type(FIELD_VECTOR) {
		if (!bCopy) {
			m_pVector = &val;
		} else {
			m_pVector = new Vector(val);
			m_flags |= SV_FREE;
		}
	}

	ScriptVariant_t(const Vector* val, bool bCopy = false) : m_flags(0) , m_type(FIELD_VECTOR) {
		if (!bCopy) {
			m_pVector = val;
		} else {
			m_pVector = new Vector(*val);
			m_flags |= SV_FREE;
		}
	}

	ScriptVariant_t(const char* val, bool bCopy = false) : m_flags(0) , m_type(FIELD_CSTRING) {
		if (!bCopy) {
			m_pszString = val;
		} else {
			m_pszString = _strdup(val);
			m_flags |= SV_FREE;
		}
	}

	bool IsNull() const { return (m_type == FIELD_VOID); }

	operator int() const {
		Assert(m_type == FIELD_INTEGER);
		return m_int;
	}

	operator float() const {
		Assert(m_type == FIELD_FLOAT);
		return m_float;
	}

	operator const char* () const {
		Assert(m_type == FIELD_CSTRING);
		return (m_pszString) ? m_pszString : "";
	}

	operator const Vector& () const {
		Assert(m_type == FIELD_VECTOR);
		static Vector vecNull = { 0, 0, 0 };
		return (m_pVector) ? *m_pVector : vecNull;
	}

	operator char() const {
		Assert(m_type == FIELD_CHARACTER);
		return m_char;
	}

	operator bool() const {
		Assert(m_type == FIELD_BOOLEAN);
		return m_bool;
	}

	operator HSCRIPT() const {
		Assert(m_type == FIELD_HSCRIPT);
		return m_hScript;
	}

	void operator=(int i) {
		m_type = FIELD_INTEGER;
		m_int = i;
	}

	void operator=(float f) {
		m_type = FIELD_FLOAT;
		m_float = f;
	}

	void operator=(double f) {
		m_type = FIELD_FLOAT;
		m_float = (float)f;
	}

	void operator=(const Vector& vec) {
		m_type = FIELD_VECTOR;
		m_pVector = &vec;
	}

	void operator=(const Vector* vec) {
		m_type = FIELD_VECTOR;
		m_pVector = vec;
	}

	void operator=(const char* psz) {
		m_type = FIELD_CSTRING;
		m_pszString = psz;
	}

	void operator=(char c) {
		m_type = FIELD_CHARACTER;
		m_char = c;
	}

	void operator=(bool b) {
		m_type = FIELD_BOOLEAN;
		m_bool = b;
	}

	void operator=(HSCRIPT h) {
		m_type = FIELD_HSCRIPT;
		m_hScript = h;
	}

	void Free() {
		if ( (m_flags & SV_FREE) && (m_type == FIELD_HSCRIPT || m_type == FIELD_VECTOR || m_type == FIELD_CSTRING) )
			delete m_pszString;
	}

	template <typename T>
	T Get() {
		T value;
		AssignTo(&value);
		return value;
	}

	template <typename T>
	bool AssignTo(T* pDest) {
		ScriptDataType_t destType = ScriptDeduceType(T);
		if (destType == FIELD_TYPEUNKNOWN) {
			//DevWarning("Unable to convert script variant to unknown type\n");
		}
		if (destType == m_type) {
			*pDest = *this;
			return true;
		}

		if (m_type != FIELD_VECTOR && m_type != FIELD_CSTRING && destType != FIELD_VECTOR && destType != FIELD_CSTRING) {
			switch (m_type) {
				case FIELD_VOID:
					*pDest = 0;
					break;
				case FIELD_INTEGER:
					*pDest = m_int;
					return true;
				case FIELD_FLOAT:
					*pDest = m_float;
					return true;
				case FIELD_CHARACTER:
					*pDest = m_char;
					return true;
				case FIELD_BOOLEAN:
					*pDest = m_bool;
					return true;
				case FIELD_HSCRIPT:
					*pDest = m_hScript;
					return true;
			}
		} else {
			/* DevWarning("No free conversion of %s script variant to %s right now\n",
				ScriptFieldTypeName(m_type), ScriptFieldTypeName<T>()); */
			if (destType != FIELD_VECTOR) {
				*pDest = 0;
			}
		}
		return false;
	}

	bool AssignTo(float* pDest) {
		switch (m_type) {
			case FIELD_VOID:
				*pDest = 0;
				return false;
			case FIELD_INTEGER:
				*pDest = (float)m_int;
				return true;
			case FIELD_FLOAT:
				*pDest = m_float;
				return true;
			case FIELD_BOOLEAN:
				*pDest = m_bool;
				return true;
			default:
				//DevWarning("No conversion from %s to float now\n", ScriptFieldTypeName(m_type));
				return false;
		}
	}

	bool AssignTo(int* pDest) {
		switch (m_type) {
			case FIELD_VOID:
				*pDest = 0;
				return false;
			case FIELD_INTEGER:
				*pDest = m_int;
				return true;
			case FIELD_FLOAT:
				*pDest = (int)m_float;
				return true;
			case FIELD_BOOLEAN:
				*pDest = m_bool;
				return true;
			default:
				//DevWarning("No conversion from %s to int now\n", ScriptFieldTypeName(m_type));
				return false;
		}
	}

	bool AssignTo(bool* pDest) {
		switch (m_type) {
			case FIELD_VOID:
				*pDest = 0;
				return false;
			case FIELD_INTEGER:
				*pDest = m_int;
				return true;
			case FIELD_FLOAT:
				*pDest = m_float;
				return true;
			case FIELD_BOOLEAN:
				*pDest = m_bool;
				return true;
			default:
				//DevWarning("No conversion from %s to bool now\n", ScriptFieldTypeName(m_type));
				return false;
		}
	}

	bool AssignTo(char** pDest) {
		//DevWarning("No free conversion of string or vector script variant right now\n");
		*pDest = (char*)"";
		return false;
	}

	bool AssignTo(ScriptVariant_t* pDest) {
		pDest->m_type = m_type;
		if (m_type == FIELD_VECTOR) {
			pDest->m_pVector = new Vector;
			*((Vector*)(pDest->m_pVector)) = Vector{ m_pVector->x, m_pVector->y, m_pVector->z };
			pDest->m_flags |= SV_FREE;
		} else if (m_type == FIELD_CSTRING) {
			pDest->m_pszString = _strdup(m_pszString);
			pDest->m_flags |= SV_FREE;
		} else {
			pDest->m_int = m_int;
		}
		return false;
	}

	union {
		int m_int;
		float m_float;
		const char* m_pszString;
		const Vector* m_pVector;
		char m_char;
		bool m_bool;
		HSCRIPT m_hScript;
	};

	__int16 m_type;
	__int16 m_flags;

private:
};

#define SCRIPT_VARIANT_NULL ScriptVariant_t()

#define FUNC_APPEND_PARAMS_0
#define FUNC_APPEND_PARAMS_1               \
    pDesc->m_Parameters.SetGrowSize(1);    \
    pDesc->m_Parameters.EnsureCapacity(1); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1));
#define FUNC_APPEND_PARAMS_2                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(2);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2));
#define FUNC_APPEND_PARAMS_3                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(3);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3));
#define FUNC_APPEND_PARAMS_4                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(4);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4));
#define FUNC_APPEND_PARAMS_5                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(5);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5));
#define FUNC_APPEND_PARAMS_6                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(6);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6));
#define FUNC_APPEND_PARAMS_7                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(7);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7));
#define FUNC_APPEND_PARAMS_8                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(8);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_8));
#define FUNC_APPEND_PARAMS_9                                          \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(9);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_8)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_9));
#define FUNC_APPEND_PARAMS_10                                         \
    pDesc->m_Parameters.SetGrowSize(1);                               \
    pDesc->m_Parameters.EnsureCapacity(10);                           \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_8)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_9)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_10));
#define FUNC_APPEND_PARAMS_11                                          \
    pDesc->m_Parameters.SetGrowSize(1);                                \
    pDesc->m_Parameters.EnsureCapacity(11);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_8));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_9));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_10)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_11));
#define FUNC_APPEND_PARAMS_12                                          \
    pDesc->m_Parameters.SetGrowSize(1);                                \
    pDesc->m_Parameters.EnsureCapacity(12);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_8));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_9));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_10)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_11)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_12));
#define FUNC_APPEND_PARAMS_13                                          \
    pDesc->m_Parameters.SetGrowSize(1);                                \
    pDesc->m_Parameters.EnsureCapacity(13);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_8));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_9));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_10)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_11)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_12)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_13));
#define FUNC_APPEND_PARAMS_14                                          \
    pDesc->m_Parameters.SetGrowSize(1);                                \
    pDesc->m_Parameters.EnsureCapacity(14);                            \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_1));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_2));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_3));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_4));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_5));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_6));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_7));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_8));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_9));  \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_10)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_11)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_12)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_13)); \
    pDesc->m_Parameters.AddToTail(ScriptDeduceType(FUNC_ARG_TYPE_14));

#define DEFINE_NONMEMBER_FUNC_TYPE_DEDUCER(N)                                                                                                    \
    template <typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                                           \
    inline void ScriptDeduceFunctionSignature(ScriptFuncDescriptor_t* pDesc, FUNCTION_RETTYPE (*pfnProxied)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N)) \
    {                                                                                                                                            \
        pDesc->m_ReturnType = ScriptDeduceType(FUNCTION_RETTYPE);                                                                                \
        FUNC_APPEND_PARAMS_##N                                                                                                                   \
    }

FUNC_GENERATE_ALL(DEFINE_NONMEMBER_FUNC_TYPE_DEDUCER);

#define DEFINE_MEMBER_FUNC_TYPE_DEDUCER(N)                                                                                                                                                \
    template <typename OBJECT_TYPE_PTR, typename FUNCTION_CLASS, typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                                 \
    inline void ScriptDeduceFunctionSignature(ScriptFuncDescriptor_t* pDesc, OBJECT_TYPE_PTR pObject, FUNCTION_RETTYPE (FUNCTION_CLASS::*pfnProxied)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N)) \
    {                                                                                                                                                                                     \
        pDesc->m_ReturnType = ScriptDeduceType(FUNCTION_RETTYPE);                                                                                                                         \
        FUNC_APPEND_PARAMS_##N                                                                                                                                                            \
    }

FUNC_GENERATE_ALL(DEFINE_MEMBER_FUNC_TYPE_DEDUCER);

#define DEFINE_CONST_MEMBER_FUNC_TYPE_DEDUCER(N)                                                                                                                                                \
    template <typename OBJECT_TYPE_PTR, typename FUNCTION_CLASS, typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                                       \
    inline void ScriptDeduceFunctionSignature(ScriptFuncDescriptor_t* pDesc, OBJECT_TYPE_PTR pObject, FUNCTION_RETTYPE (FUNCTION_CLASS::*pfnProxied)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N) const) \
    {                                                                                                                                                                                           \
        pDesc->m_ReturnType = ScriptDeduceType(FUNCTION_RETTYPE);                                                                                                                               \
        FUNC_APPEND_PARAMS_##N                                                                                                                                                                  \
    }

FUNC_GENERATE_ALL(DEFINE_CONST_MEMBER_FUNC_TYPE_DEDUCER);

#define ScriptInitMemberFuncDescriptor_(pDesc, class, func, scriptName)   \
    if (0) {                                                              \
    } else {                                                              \
        (pDesc)->m_pszScriptName = scriptName;                            \
        (pDesc)->m_pszFunction = #func;                                   \
        ScriptDeduceFunctionSignature(pDesc, (class*)(0), &class ::func); \
    }

#define ScriptInitFuncDescriptorNamed(pDesc, func, scriptName) \
    if (0) {                                                   \
    } else {                                                   \
        (pDesc)->m_pszScriptName = scriptName;                 \
        (pDesc)->m_pszFunction = #func;                        \
        ScriptDeduceFunctionSignature(pDesc, &func);           \
    }
#define ScriptInitFuncDescriptor(pDesc, func) ScriptInitFuncDescriptorNamed(pDesc, func, #func)
#define ScriptInitMemberFuncDescriptorNamed(pDesc, class, func, scriptName) ScriptInitMemberFuncDescriptor_(pDesc, class, func, scriptName)
#define ScriptInitMemberFuncDescriptor(pDesc, class, func) ScriptInitMemberFuncDescriptorNamed(pDesc, class, func, #func)

template <typename FUNCPTR_TYPE>
inline void* ScriptConvertFuncPtrToVoid(FUNCPTR_TYPE pFunc) {
	if ( ( sizeof(FUNCPTR_TYPE) == sizeof(void*) ) ) {
		union FuncPtrConvert {
			void* p;
			FUNCPTR_TYPE pFunc;
		};

		FuncPtrConvert convert;
		convert.pFunc = pFunc;
		return convert.p;
	}
#if MSVC
		else if ((sizeof(FUNCPTR_TYPE) == sizeof(void*) + sizeof(int))) {
        struct MicrosoftUnknownMFP {
            void* p;
            int m_delta;
        };

        union FuncPtrConvertMI {
            MicrosoftUnknownMFP mfp;
            FUNCPTR_TYPE pFunc;
        };

        FuncPtrConvertMI convert;
        convert.pFunc = pFunc;
        if (convert.mfp.m_delta == 0) {
            return convert.mfp.p;
        }
        AssertMsg(0, "Function pointer must be from primary vtable");
    }
    else if ((sizeof(FUNCPTR_TYPE) == sizeof(void*) + (sizeof(int) * 3))) {
        struct MicrosoftUnknownMFP {
            void* p;
            int m_delta;
            int m_vtordisp;
            int m_vtable_index;
        };

        union FuncPtrConvertMI {
            MicrosoftUnknownMFP mfp;
            FUNCPTR_TYPE pFunc;
        };

        FuncPtrConvertMI convert;
        convert.pFunc = pFunc;
        if (convert.mfp.m_delta == 0) {
            return convert.mfp.p;
        }
        AssertMsg(0, "Function pointer must be from primary vtable");
    }
#else
	else if ((sizeof(FUNCPTR_TYPE) == sizeof(void*) + sizeof(int))) {

        // AssertMsg(0, "Note: This path has not been verified yet. See comments below in #else case.");

        struct GnuMFP {
            union {
                void* funcadr;
                int vtable_index_2;
            };
            int delta;
        };

        GnuMFP* p = (GnuMFP*)&pFunc;
        if (p->vtable_index_2 & 1) {
            AssertMsg(0, "Please use the DEFINE_SCRIPTFUNC_VIRTUAL macro, because DEFINE_SCRIPTFUNC does not handle virtual methods on Linux");
            return NULL;
        }
        else {
            return p->funcadr;
        }
    }
#endif
	else
		AssertMsg(0, "Member function pointer not supported. Why on earth are you using virtual inheritance!?");
	return NULL;
}

#ifndef _WIN32
    template <typename FUNCPTR_TYPE, typename INSTANCE_TYPE> inline void* ScriptConvertFuncPtrToVoidVirtual(FUNCPTR_TYPE pFunc, INSTANCE_TYPE pInstance) {
        struct GnuMFP {
            int vti;
            int delta;
        };

        GnuMFP* mfp = (GnuMFP*)&pFunc;
        if(mfp->vti & 1)
            return *(void**)(*(uintptr_t*)((uintptr_t)pInstance + mfp->delta) + mfp->vti - 1);
        return NULL;
    }
#endif // _WIN32

template <typename FUNCPTR_TYPE>
inline FUNCPTR_TYPE ScriptConvertFuncPtrFromVoid(void* p) {
#ifndef _WIN32
    if(sizeof(FUNCPTR_TYPE) == 4) {
        union FuncPtrConvertMI {
			FUNCPTR_TYPE pFunc;
			void* stype;
		};

		FuncPtrConvertMI convert;
		convert.pFunc = 0;
		convert.stype = p;
		return convert.pFunc;
    } else {
        union FuncPtrConvertMI {
			FUNCPTR_TYPE pFunc;
			struct {
				void* stype;
				intptr_t iToc;
			} fn8;
		};

		FuncPtrConvertMI convert;
		convert.pFunc = 0;
		convert.fn8.stype = p;
		convert.fn8.iToc = 0;
		return convert.pFunc;
    }
#endif

	if ( ( sizeof(FUNCPTR_TYPE) == sizeof(void*) ) ) {
		union FuncPtrConvert {
			void* p;
			FUNCPTR_TYPE pFunc;
		};

		FuncPtrConvert convert;
		convert.p = p;
		return convert.pFunc;
	}

#if MSVC
		if ((sizeof(FUNCPTR_TYPE) == sizeof(void*) + sizeof(int))) {
        struct MicrosoftUnknownMFP {
            void* p;
            int m_delta;
        };

        union FuncPtrConvertMI {
            MicrosoftUnknownMFP mfp;
            FUNCPTR_TYPE pFunc;
        };

        FuncPtrConvertMI convert;
        convert.mfp.p = p;
        convert.mfp.m_delta = 0;
        return convert.pFunc;
    }
    if ((sizeof(FUNCPTR_TYPE) == sizeof(void*) + (sizeof(int) * 3))) {
        struct MicrosoftUnknownMFP {
            void* p;
            int m_delta;
            int m_vtordisp;
            int m_vtable_index;
        };

        union FuncPtrConvertMI {
            MicrosoftUnknownMFP mfp;
            FUNCPTR_TYPE pFunc;
        };

        FuncPtrConvertMI convert;
        convert.mfp.p = p;
        convert.mfp.m_delta = 0;
        return convert.pFunc;
    }
#elif defined(POSIX)
		AssertMsg(0, "Note: This path has not been implemented yet.");
#endif
	Assert(0);
	return NULL;
}

#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_0
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_1 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_1
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_2 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_2
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_3 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_3
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_4 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_4
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_5 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_5
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_6 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_6
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_7 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_7
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_8 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_8
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_9 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_9
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_10 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_10
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_11 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_11
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_12 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_12
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_13 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_13
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_14 , FUNC_BASE_TEMPLATE_FUNC_PARAMS_14

#define SCRIPT_BINDING_ARGS_0
#define SCRIPT_BINDING_ARGS_1 pArguments[0]
#define SCRIPT_BINDING_ARGS_2 pArguments[0], pArguments[1]
#define SCRIPT_BINDING_ARGS_3 pArguments[0], pArguments[1], pArguments[2]
#define SCRIPT_BINDING_ARGS_4 pArguments[0], pArguments[1], pArguments[2], pArguments[3]
#define SCRIPT_BINDING_ARGS_5 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4]
#define SCRIPT_BINDING_ARGS_6 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5]
#define SCRIPT_BINDING_ARGS_7 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6]
#define SCRIPT_BINDING_ARGS_8 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6], pArguments[7]
#define SCRIPT_BINDING_ARGS_9 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6], pArguments[7], pArguments[8]
#define SCRIPT_BINDING_ARGS_10 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6], pArguments[7], pArguments[8], pArguments[9]
#define SCRIPT_BINDING_ARGS_11 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6], pArguments[7], pArguments[8], pArguments[9], pArguments[10]
#define SCRIPT_BINDING_ARGS_12 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6], pArguments[7], pArguments[8], pArguments[9], pArguments[10], pArguments[11]
#define SCRIPT_BINDING_ARGS_13 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6], pArguments[7], pArguments[8], pArguments[9], pArguments[10], pArguments[11], pArguments[12]
#define SCRIPT_BINDING_ARGS_14 pArguments[0], pArguments[1], pArguments[2], pArguments[3], pArguments[4], pArguments[5], pArguments[6], pArguments[7], pArguments[8], pArguments[9], pArguments[10], pArguments[11], pArguments[12], pArguments[13]

#define DEFINE_SCRIPT_BINDINGS(N)                                                                                                                                     \
    template <typename FUNC_TYPE, typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                                            \
    class CNonMemberScriptBinding##N {                                                                                                                                \
    public:                                                                                                                                                           \
        static bool Call(void* pFunction, void* pContext, ScriptVariant_t* pArguments, int nArguments, ScriptVariant_t* pReturn)                                      \
        {                                                                                                                                                             \
            Assert(nArguments == N);                                                                                                                                  \
            Assert(pReturn);                                                                                                                                          \
            Assert(!pContext);                                                                                                                                        \
                                                                                                                                                                      \
            if (nArguments != N || !pReturn || pContext) {                                                                                                            \
                return false;                                                                                                                                         \
            }                                                                                                                                                         \
            *pReturn = ((FUNC_TYPE)pFunction)(SCRIPT_BINDING_ARGS_##N);                                                                                               \
            if (pReturn->m_type == FIELD_VECTOR)                                                                                                                      \
                pReturn->m_pVector = new Vector(*pReturn->m_pVector);                                                                                                 \
            return true;                                                                                                                                              \
        }                                                                                                                                                             \
    };                                                                                                                                                                \
                                                                                                                                                                      \
    template <typename FUNC_TYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                                                                       \
    class CNonMemberScriptBinding##N<FUNC_TYPE, void FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_##N> {                                                                   \
    public:                                                                                                                                                           \
        static bool Call(void* pFunction, void* pContext, ScriptVariant_t* pArguments, int nArguments, ScriptVariant_t* pReturn)                                      \
        {                                                                                                                                                             \
            Assert(nArguments == N);                                                                                                                                  \
            Assert(!pReturn);                                                                                                                                         \
            Assert(!pContext);                                                                                                                                        \
                                                                                                                                                                      \
            if (nArguments != N || pReturn || pContext) {                                                                                                             \
                return false;                                                                                                                                         \
            }                                                                                                                                                         \
            ((FUNC_TYPE)pFunction)(SCRIPT_BINDING_ARGS_##N);                                                                                                          \
            return true;                                                                                                                                              \
        }                                                                                                                                                             \
    };                                                                                                                                                                \
                                                                                                                                                                      \
    template <class OBJECT_TYPE_PTR, typename FUNC_TYPE, typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                     \
    class CMemberScriptBinding##N {                                                                                                                                   \
    public:                                                                                                                                                           \
        static bool Call(void* pFunction, void* pContext, ScriptVariant_t* pArguments, int nArguments, ScriptVariant_t* pReturn)                                      \
        {                                                                                                                                                             \
            Assert(nArguments == N);                                                                                                                                  \
            Assert(pReturn);                                                                                                                                          \
            Assert(pContext);                                                                                                                                         \
                                                                                                                                                                      \
            if (nArguments != N || !pReturn || !pContext) {                                                                                                           \
                return false;                                                                                                                                         \
            }                                                                                                                                                         \
            *pReturn = (((OBJECT_TYPE_PTR)(pContext))->*ScriptConvertFuncPtrFromVoid<FUNC_TYPE>(pFunction))(SCRIPT_BINDING_ARGS_##N);                                 \
            if (pReturn->m_type == FIELD_VECTOR)                                                                                                                      \
                pReturn->m_pVector = new Vector(*pReturn->m_pVector);                                                                                                 \
            return true;                                                                                                                                              \
        }                                                                                                                                                             \
    };                                                                                                                                                                \
                                                                                                                                                                      \
    template <class OBJECT_TYPE_PTR, typename FUNC_TYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                                                \
    class CMemberScriptBinding##N<OBJECT_TYPE_PTR, FUNC_TYPE, void FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_##N> {                                                     \
    public:                                                                                                                                                           \
        static bool Call(void* pFunction, void* pContext, ScriptVariant_t* pArguments, int nArguments, ScriptVariant_t* pReturn)                                      \
        {                                                                                                                                                             \
            Assert(nArguments == N);                                                                                                                                  \
            Assert(!pReturn);                                                                                                                                         \
            Assert(pContext);                                                                                                                                         \
                                                                                                                                                                      \
            if (nArguments != N || pReturn || !pContext) {                                                                                                            \
                return false;                                                                                                                                         \
            }                                                                                                                                                         \
            (((OBJECT_TYPE_PTR)(pContext))->*ScriptConvertFuncPtrFromVoid<FUNC_TYPE>(pFunction))(SCRIPT_BINDING_ARGS_##N);                                            \
            return true;                                                                                                                                              \
        }                                                                                                                                                             \
    };                                                                                                                                                                \
                                                                                                                                                                      \
    template <typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                                                                                \
    inline ScriptBindingFunc_t ScriptCreateBinding(FUNCTION_RETTYPE (*pfnProxied)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N))                                                \
    {                                                                                                                                                                 \
        typedef FUNCTION_RETTYPE (*Func_t)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N);                                                                                       \
        return &CNonMemberScriptBinding##N<Func_t, FUNCTION_RETTYPE FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_##N>::Call;                                               \
    }                                                                                                                                                                 \
                                                                                                                                                                      \
    template <typename OBJECT_TYPE_PTR, typename FUNCTION_CLASS, typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                             \
    inline ScriptBindingFunc_t ScriptCreateBinding(OBJECT_TYPE_PTR pObject, FUNCTION_RETTYPE (FUNCTION_CLASS::*pfnProxied)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N))       \
    {                                                                                                                                                                 \
        typedef FUNCTION_RETTYPE (FUNCTION_CLASS::*Func_t)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N);                                                                       \
        return &CMemberScriptBinding##N<OBJECT_TYPE_PTR, Func_t, FUNCTION_RETTYPE FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_##N>::Call;                                 \
    }                                                                                                                                                                 \
                                                                                                                                                                      \
    template <typename OBJECT_TYPE_PTR, typename FUNCTION_CLASS, typename FUNCTION_RETTYPE FUNC_TEMPLATE_FUNC_PARAMS_##N>                                             \
    inline ScriptBindingFunc_t ScriptCreateBinding(OBJECT_TYPE_PTR pObject, FUNCTION_RETTYPE (FUNCTION_CLASS::*pfnProxied)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N) const) \
    {                                                                                                                                                                 \
        typedef FUNCTION_RETTYPE (FUNCTION_CLASS::*Func_t)(FUNC_BASE_TEMPLATE_FUNC_PARAMS_##N);                                                                       \
        return &CMemberScriptBinding##N<OBJECT_TYPE_PTR, Func_t, FUNCTION_RETTYPE FUNC_BASE_TEMPLATE_FUNC_PARAMS_PASSTHRU_##N>::Call;                                 \
    }

FUNC_GENERATE_ALL(DEFINE_SCRIPT_BINDINGS);

#define ScriptInitFunctionBinding(pScriptFunction, func) ScriptInitFunctionBindingNamed(pScriptFunction, func, #func)
#define ScriptInitFunctionBindingNamed(pScriptFunction, func, scriptName)              \
    do {                                                                               \
        ScriptInitFuncDescriptorNamed((&(pScriptFunction)->m_desc), func, scriptName); \
        (pScriptFunction)->m_pfnBinding = ScriptCreateBinding(&func);                  \
        (pScriptFunction)->m_pFunction = (void*)&func;                                 \
    } while (0)

#define ScriptInitMemberFunctionBinding(pScriptFunction, class, func) ScriptInitMemberFunctionBinding_(pScriptFunction, class, func, #func)
#define ScriptInitMemberFunctionBindingNamed(pScriptFunction, class, func, scriptName) ScriptInitMemberFunctionBinding_(pScriptFunction, class, func, scriptName)
#define ScriptInitMemberFunctionBinding_(pScriptFunction, class, func, scriptName)              \
    do {                                                                                        \
        ScriptInitMemberFuncDescriptor_((&(pScriptFunction)->m_desc), class, func, scriptName); \
        (pScriptFunction)->m_pfnBinding = ScriptCreateBinding(((class*)0), &class ::func);      \
        (pScriptFunction)->m_pFunction = ScriptConvertFuncPtrToVoid(&class ::func);             \
        (pScriptFunction)->m_flags = SF_MEMBER_FUNC;                                            \
    } while (0)

#define ScriptInitMemberFunctionBindingNamedVirtual(pScriptFunction, class, func, scriptName) ScriptInitMemberFunctionBindingVirtual_(pScriptFunction, class, func, scriptName)
#define ScriptInitMemberFunctionBindingVirtual_(pScriptFunction, class, func, scriptName)              \
    do {                                                                                        \
        ScriptInitMemberFuncDescriptor_((&(pScriptFunction)->m_desc), class, func, scriptName); \
        (pScriptFunction)->m_pfnBinding = ScriptCreateBinding(((class*)0), &class ::func);      \
        (pScriptFunction)->m_pFunction = ScriptConvertFuncPtrToVoidVirtual(&class ::func, _instance);             \
        (pScriptFunction)->m_flags = SF_MEMBER_FUNC;                                            \
    } while (0)

#define ScriptInitClassDesc(pClassDesc, class, pBaseClassDesc) ScriptInitClassDescNamed(pClassDesc, class, pBaseClassDesc, #class)
#define ScriptInitClassDescNamed(pClassDesc, class, pBaseClassDesc, scriptName) ScriptInitClassDescNamed_(pClassDesc, class, pBaseClassDesc, scriptName)
#define ScriptInitClassDescNoBase(pClassDesc, class) ScriptInitClassDescNoBaseNamed(pClassDesc, class, #class)
#define ScriptInitClassDescNoBaseNamed(pClassDesc, class, scriptName) ScriptInitClassDescNamed_(pClassDesc, class, NULL, scriptName)
#define ScriptInitClassDescNamed_(pClassDesc, class, pBaseClassDesc, scriptName) \
    do {                                                                         \
        (pClassDesc)->m_pszScriptName = scriptName;                              \
        (pClassDesc)->m_pszClassname = #class;                                   \
        (pClassDesc)->m_pBaseDesc = pBaseClassDesc;                              \
    } while (0)

#define ScriptAddFunctionToClassDesc(pClassDesc, class, func, description) ScriptAddFunctionToClassDescNamed(pClassDesc, class, func, #func, description)
#define ScriptAddFunctionToClassDescNamed(pClassDesc, class, func, scriptName, description)                                    \
    do {                                                                                                                       \
        ScriptFunctionBinding_t* pBinding = &((pClassDesc)->m_FunctionBindings[(pClassDesc)->m_FunctionBindings.AddToTail()]); \
        pBinding->m_desc.m_pszDescription = description;                                                                       \
        ScriptInitMemberFunctionBindingNamed(pBinding, class, func, scriptName);                                               \
    } while (0)

#define ScriptAddFunctionToClassDescNamedVirtual(pClassDesc, class, func, scriptName, description) \
    do {                                                                                                                       \
        ScriptFunctionBinding_t* pBinding = &((pClassDesc)->m_FunctionBindings[(pClassDesc)->m_FunctionBindings.AddToTail()]); \
        pBinding->m_desc.m_pszDescription = description;                                                                       \
        ScriptInitMemberFunctionBindingNamedVirtual(pBinding, class, func, scriptName);                                               \
    } while (0)

#define ScriptRegisterFunction(pVM, func, description) ScriptRegisterFunctionNamed(pVM, func, #func, description)
#define ScriptRegisterFunctionNamed(pVM, func, scriptName, description) \
    do {                                                                \
        static ScriptFunctionBinding_t binding;                         \
        binding.m_desc.m_pszDescription = description;                  \
        binding.m_desc.m_Parameters.RemoveAll();                        \
        ScriptInitFunctionBindingNamed(&binding, func, scriptName);     \
        pVM->RegisterFunction(&binding);                                \
    } while (0)

#define ALLOW_SCRIPT_ACCESS() template <typename T> \
friend ScriptClassDesc_t* GetScriptDesc(T*);

#define BEGIN_SCRIPTDESC(className, baseClass, description) BEGIN_SCRIPTDESC_NAMED(className, baseClass, #className, description)
#define BEGIN_SCRIPTDESC_ROOT(className, description, instance) BEGIN_SCRIPTDESC_ROOT_NAMED(className, #className, description, instance)

#if defined(MSVC) && _MSC_VER < 1900
#define DEFINE_SCRIPTDESC_FUNCTION(className, baseClass) \
    ScriptClassDesc_t* GetScriptDesc(className*)
#else
#define DEFINE_SCRIPTDESC_FUNCTION(className, baseClass, instance) \
    template <>                                              \
    ScriptClassDesc_t* GetScriptDesc<baseClass>(baseClass*); \
    template <>                                              \
    ScriptClassDesc_t* GetScriptDesc<className>(className*)
#endif

#define BEGIN_SCRIPTDESC_NAMED(className, baseClass, scriptName, description, instance)           \
    ScriptClassDesc_t g_##className##_ScriptDesc;                                                 \
    DEFINE_SCRIPTDESC_FUNCTION(className, baseClass, instance)                                              \
    {                                                                                             \
        static bool bInitialized;                                                                 \
        if (bInitialized) {                                                                       \
            return &g_##className##_ScriptDesc;                                                   \
        }                                                                                         \
                                                                                                  \
        bInitialized = true;                                                                      \
                                                                                                  \
        typedef className _className;                                                             \
                                                                                                  \
        _className* _instance = &instance;                                                        \
                                                                                                  \
        ScriptClassDesc_t* pDesc = &g_##className##_ScriptDesc;                                   \
        pDesc->m_pszDescription = description;                                                    \
        ScriptInitClassDescNamed(pDesc, className, GetScriptDescForClass(baseClass), scriptName); \
        ScriptClassDesc_t* pInstanceHelperBase = pDesc->m_pBaseDesc;                              \
        while (pInstanceHelperBase) {                                                             \
            if (pInstanceHelperBase->pHelper) {                                                   \
                pDesc->pHelper = pInstanceHelperBase->pHelper;                                    \
                break;                                                                            \
            }                                                                                     \
            pInstanceHelperBase = pInstanceHelperBase->m_pBaseDesc;                               \
        }

#define BEGIN_SCRIPTDESC_ROOT_NAMED(className, scriptName, description, instance) \
    BEGIN_SCRIPTDESC_NAMED(className, ScriptNoBase_t, scriptName, description, instance)

#define END_SCRIPTDESC() \
    return pDesc;        \
    }

#define DEFINE_SCRIPTFUNC_D(func, description) DEFINE_SCRIPTFUNC_NAMED(func, #func, description)
#ifdef _WIN32
    #define DEFINE_SCRIPTFUNC_V(func, description) DEFINE_SCRIPTFUNC_NAMED(func, #func, description)
#else
    #define DEFINE_SCRIPTFUNC_V(func, description) DEFINE_SCRIPTFUNC_NAMED_VIRTUAL(func, #func, description)
#endif
#define DEFINE_SCRIPTFUNC_NAMED(func, scriptName, description) ScriptAddFunctionToClassDescNamed(pDesc, _className, func, scriptName, description);
#define DEFINE_SCRIPTFUNC_NAMED_VIRTUAL(func, scriptName, description) ScriptAddFunctionToClassDescNamedVirtual(pDesc, _className, func, scriptName, description);
#define DEFINE_SCRIPT_CONSTRUCTOR() ScriptAddConstructorToClassDesc(pDesc, _className);
#define DEFINE_SCRIPT_INSTANCE_HELPER(p) pDesc->pHelper = (p);

template <typename T>
ScriptClassDesc_t* GetScriptDesc(T*);

struct ScriptNoBase_t;
template <>
inline ScriptClassDesc_t* GetScriptDesc<ScriptNoBase_t>(ScriptNoBase_t*) { return NULL; }

#define GetScriptDescForClass(className) GetScriptDesc<className>( (className*) NULL )

template <typename T>
class CScriptConstructor {
public:
	static void* Construct() { return new T; }
	static void Destruct(void* p) { delete (T*)p; }
};

#define ScriptAddConstructorToClassDesc(pClassDesc, class)                    \
    do {                                                                      \
        (pClassDesc)->m_pfnConstruct = &CScriptConstructor<class>::Construct; \
        (pClassDesc)->m_pfnDestruct = &CScriptConstructor<class>::Destruct;   \
    } while (0)

enum ScriptErrorLevel_t {
	SCRIPT_LEVEL_WARNING = 0,
	SCRIPT_LEVEL_ERROR,
};

typedef void (*ScriptOutputFunc_t)(const char* pszText);
typedef bool (*ScriptErrorFunc_t)(ScriptErrorLevel_t eLevel, const char* pszText);

#ifdef RegisterClass
#undef RegisterClass
#endif

enum ScriptStatus_t {
	SCRIPT_ERROR = -1,
	SCRIPT_DONE,
	SCRIPT_RUNNING,
};

