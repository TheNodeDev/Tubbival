#pragma once

#include <vector>

#include "engine/CVar.hpp"


class PluginBase;

/**
 * Represents a variable
 */
class Variable {
private:
    ConVar* ptr;

    int version;
    int originalFlags;

    union {
        void* originalfnChangeCallback;
        int originalSize;
    };

public:
    bool isRegistered;
    bool isReference;

public:
    Variable();
    ~Variable();
    Variable( const char* name );
    Variable( const char* name, const char* value, const char* helpstr, int flags = FCVAR_NEVER_AS_STRING );
    Variable( const char* name, const char* value, float min, const char* helpstr, int flags = FCVAR_NEVER_AS_STRING );
    Variable( const char* name, const char* value, float min, float max, const char* helpstr, int flags = FCVAR_NEVER_AS_STRING );

    void Create(
			const char* name,
			const char* value,
			int flags = 0,
			const char* helpstr = "",
			bool hasmin = false,
			float min = 0,
	        bool hasmax = false,
			float max = 0
	);
    void PostInit( PluginBase* plugin );

    ConVar* ThisPtr();
    ConVar2* ThisPtr2();

    bool GetBool();
    int GetInt();
    float GetFloat();
    const char* GetString();
    const int GetFlags();

    void SetValue( const char* value );
    void SetValue( float value );
    void SetValue( int value );

    void SetFlags( int value );
    void AddFlag( int value );
    void RemoveFlag( int value );

    void Modify( int flagsToRemove = 0, int flagsToAdd = 0 );
    void Restore();

    void DisableChange( PluginBase* plugin );
    void EnableChange( PluginBase* plugin );

    void UniqueFor( int version );
    void Register( PluginBase* plugin );
    void Unregister();

    bool operator!();

    static std::vector<Variable*>& GetList();
    static int RegisterAll( PluginBase* plugin );
    static void UnregisterAll();
    static Variable* Find( const char* name );
};
