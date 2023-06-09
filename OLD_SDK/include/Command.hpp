#pragma once

#include <vector>
#include "engine/CVar.hpp"


class PluginBase;


class Command {
private:
    ConCommand* ptr;

    int version;

public:
    bool isRegistered;
    bool isReference;

public:
    Command();
    ~Command();
    Command(const char* name);
    Command(
		const char* pName,
		_CommandCallback callback,
		const char* pHelpString,
		int flags = 0,
        _CommandCompletionCallback completionFunc = nullptr
	);

    ConCommand* ThisPtr();

    void UniqueFor(int ver);
    void Register();
    void Unregister();

    bool operator!();

    static std::vector<Command*>& GetList();
    static int RegisterAll(PluginBase* plugin);
    static void UnregisterAll();
    static Command* Find(const char* name);

    static bool Hook(const char* name, _CommandCallback detour, _CommandCallback& original);
    static bool Unhook(const char* name, _CommandCallback original);
    static bool ActivateAutoCompleteFile(const char* name, _CommandCompletionCallback callback);
    static bool DectivateAutoCompleteFile(const char* name);
};

#define CON_COMMAND(name, description)                           \
    void name##_callback(const CCommand& args);                  \
    Command name = Command(#name, name##_callback, description); \
    void name##_callback(const CCommand& args)

#define CON_COMMAND_F(name, description, flags)                         \
    void name##_callback(const CCommand& args);                         \
    Command name = Command(#name, name##_callback, description, flags); \
    void name##_callback(const CCommand& args)

#define CON_COMMAND_F_COMPLETION(name, description, flags, completion)              \
    void name##_callback(const CCommand& args);                                     \
    Command name = Command(#name, name##_callback, description, flags, completion); \
    void name##_callback(const CCommand& args)

#define DECL_DECLARE_AUTOCOMPLETION_FUNCTION(command) \
    int command##_CompletionFunc(const char* partial, \
        char commands[COMMAND_COMPLETION_MAXITEMS][COMMAND_COMPLETION_ITEM_LENGTH])
#define DECLARE_AUTOCOMPLETION_FUNCTION(command, subdirectory, extension)            \
    CBaseAutoCompleteFileList command##Complete(#command, subdirectory, #extension); \
    int command##_CompletionFunc(const char* partial,                                \
        char commands[COMMAND_COMPLETION_MAXITEMS][COMMAND_COMPLETION_ITEM_LENGTH])  \
    {                                                                                \
        return command##Complete.AutoCompletionFunc(partial, commands);              \
    }

#define AUTOCOMPLETION_FUNCTION(command) \
    command##_CompletionFunc

#define CON_COMMAND_AUTOCOMPLETEFILE(name, description, flags, subdirectory, extension) \
    DECLARE_AUTOCOMPLETION_FUNCTION(name, subdirectory, extension)                      \
    CON_COMMAND_F_COMPLETION(name, description, flags, AUTOCOMPLETION_FUNCTION(name))

#define DECL_DETOUR_COMMAND(name)            \
    static _CommandCallback name##_callback; \
    static void name##_callback_hook(const CCommand& args);
#define DETOUR_COMMAND(name) \
    void name##_callback_hook(const CCommand& args)
