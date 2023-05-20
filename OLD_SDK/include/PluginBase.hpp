#pragma once
#include <atomic>
#include <random>
#include <thread>
#include <vector>


#include "engine/PluginInterface.hpp"
#include "engine/Math.hpp"
#include "engine/vscript/VScript.hpp"
#include "module/Module.hpp"
#include "game/Game.hpp"
#include "Command.hpp"
#include "Plugin.hpp"
#include "Cheats.hpp"

/**
 * Base class for Portal 2 plugins, if you override a callback
 * that has functionality in this class, please call that callback
 * on this class as first thing ( unless stated otherwise )
 * with PluginBase::$CallbackName
 */
class PluginBase : public IServerPluginCallbacks {
public:
    Game* game;
    Plugin* plugin;
    Modules* modules;
    Cheats* cheats;

    std::vector<void*> clients;
    bool isPaused = false;
protected:
    const char* backupKey;
    bool backupKeyChanged = false;
public:
    PluginBase();

	/**
	 * Called on plugin load
     * Superclass MUST call this class's Cleanup method ( with PluginBase::Load() ) BEFORE own load is done.
	 * @param interfaceFactory
	 * @param gameServerFactory
	 * @return
	 */
    virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);

    /**
     * Called on plugin unload
     */
	virtual void Unload() = 0;

	/**
	 * Called when the server is paused
	 */
    virtual void Pause() = 0;

	/**
	 * Called when the server is unpaused
	 */
	virtual void UnPause() = 0;

	/**
	 * Called when Source ask for the plugin's description
	 */
	virtual const char* GetPluginDescription() = 0;

	/**
	 * Called any time a new level is started ( after GameInit() also on level transitions within a game )
	 */
	virtual void LevelInit(char const* pMapName) = 0;

	/**
	 * The server is about to activate
	 */
    virtual void ServerActivate(void* pEdictList, int edictCount, int clientMax) = 0;

	/**
	 * The server should run physics/think on all edicts
	 */
    virtual void GameFrame(bool simulating) = 0;

	/**
	 * Called when a level is shutdown (including changing levels)
	 */
    virtual void LevelShutdown();

	/**
	 * ???
	 */
	virtual void ClientFullyConnect(void* pEdict);

	/**
	 * Client is going active
	 */
    virtual void ClientActive(void* pEntity);

	/**
	 * Client is disconnecting from server
	 */
    virtual void ClientDisconnect(void* pEntity) = 0;

	/**
	 * Client is connected and should be put in the game
	 */
    virtual void ClientPutInServer(void* pEntity, char const* playerName) = 0;

	/**
	 * Sets the client index for the client who typed the command into their console
	 */
    virtual void SetCommandClient(int index) = 0;

	/**
	 * A player changed one/several replicated cvars (name etc)
	 */
    virtual void ClientSettingsChanged(void* pEdict) = 0;

	/**
	 *  Client is connecting to server
	 *	@param reject Message to reject the client with
	 *	@param bAllowConnect Set to false to refuse the connection
	 */
    virtual PLUGIN_RESULT ClientConnect(bool* bAllowConnect, void* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen) = 0;

	/**
	 * The client has typed a command at the console
	 */
	virtual PLUGIN_RESULT ClientCommand(void* pEntity, const CCommand &args) = 0;

	/**
	 * A user has had their network id setup and validated
	 */
    virtual PLUGIN_RESULT NetworkIDValidated(const char* pszUserName, const char* pszNetworkID) = 0;

	/**
	 * This is called when a query from IServerPluginHelpers::StartQueryCvarValue is finished.
	 * iCookie is the value returned by IServerPluginHelpers::StartQueryCvarValue.
	 * Added with version 2 of the interface.
	 */
	virtual void OnQueryCvarValueFinished(int iCookie, void* pPlayerEntity, int eStatus, const char* pCvarName, const char* pCvarValue) = 0;

	/**
	 * Added with version 3 of the interface.
	 * @param edict The edict that was allocated
	 */
	virtual void OnEdictAllocated(void* edict) = 0;

	/**
	 * added with version 3 of the interface.
	 * @param edict The edict that is about to get freed
	 */
    virtual void OnEdictFreed(const void* edict) = 0;

	/**
	 * Callback to register all script-related stuff
	 */
	virtual void OnRegisterScripts() = 0;

	/**
	 * Getter for the plugin's version
	 * @return A string representing the plugin's version
	 */
    virtual const char* Version() = 0;

	/**
	 * Getter for the plugin's build number.
	 * By default it is time and date of compilation.
	 * @return A string representing the plugin's build number
	 */
    virtual const char* Build() { return __TIME__ " " __DATE__; }

	/**
	 * Getter for the plugin's website.
	 */
    virtual const char* Website() = 0;

	/**
	 * Clean all managed resources and code here.
	 * Superclass MUST call this class's Cleanup method ( with PluginBase::Cleanup() ) after own cleanup is done.
	 */
    virtual void Cleanup();

	// ----- STUFF THAT I HAVE NO IDEA WHAT IT DOES -----

    void SetBackupKey(const char* key);
    const char* GetBackupKey();
	bool HasBackupKeyBeenChanged();
};