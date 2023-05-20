//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "Interface.hpp"
#include "CVar.hpp"

// #include "../util/KeyValues.hpp"
class KeyValues;

typedef enum {
	/**
	 * keep going (allow default behavior)
	 */
	PLUGIN_CONTINUE = 0,

	/**
	 * run the game dll function but use our return value instead
	 */
	PLUGIN_OVERRIDE,

	/**
	 * don't run the game dll function at all (prevent default behavior)
	 */
	PLUGIN_STOP,
} PLUGIN_RESULT;

class IServerPluginCallbacks {
public:
	/**
	 * Initialize the plugin to run
	 * Return false if there is an error during startup.
	 */
	virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) = 0;

	/**
	 * Called when the plugin should be shutdown
	 */
	virtual void Unload() = 0;

	/**
	 * called when a plugins execution is stopped but the plugin is not unloaded
	 */
	virtual void Pause() = 0;

	/**
	 * called when a plugin should start executing again (sometime after a Pause() call)
	 */
	virtual void UnPause() = 0;

	/**
	 * Returns string describing current plugin.  e.g., Admin-Mod.
	 */
	virtual const char* GetPluginDescription() = 0;

	/**
	 * Called any time a new level is started (after GameInit() also on level transitions within a game)
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
	virtual void LevelShutdown() = 0;

	/**
	 * ???
	 */
	virtual void ClientFullyConnect(void* pEdict) = 0;

	/**
	 * Client is going active
	 */
	virtual void ClientActive(void* pEntity) = 0;

	/**
	 * Client is disconnecting from server
	 */
	virtual void ClientDisconnect(void* pEntity) = 0;

	/**
	 * Client is connected and should be put in the game
	 */
	virtual void ClientPutInServer(void* pEntity, char const* playername) = 0;

	/**
	 * Sets the client index for the client who typed the command into their console
	 */
	virtual void SetCommandClient(int index) = 0;

	/**
	 * A player changed one/several replicated cvars (name etc)
	 */
	virtual void ClientSettingsChanged(void* pEdict) = 0;

	/**
	 *  Client is connecting to server ( set retVal to false to reject the connection )
	 *	You can specify a rejection message by writing it into reject
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
	 * added with version 3 of the interface.
	 */
	virtual void OnEdictAllocated(void* edict) = 0;

	/**
	 * added with version 3 of the interface.
	 */
	virtual void OnEdictFreed(const void* edict) = 0;
};

// DIALOGS STUFF

typedef enum {
	/**
	 * just an on screen message
	 */
	DIALOG_MSG = 0,

	/**
	 * an options menu
	 */
	DIALOG_MENU,

	/**
	 * a richtext dialog
	 */
	DIALOG_TEXT,

	/**
	 * an entry box
	 */
	DIALOG_ENTRY,

	/**
	 * Ask the client to connect to a specified IP address.
	 * Only the "time" and "title" keys are used.
	 */
	DIALOG_ASKCONNECT
} DIALOG_TYPE;

typedef int QueryCvarCookie_t;

class IServerPluginHelpers {
public:
	/**
	 * creates an onscreen menu with various option buttons
	 *	The keyvalues param can contain these fields:
	 *	"title" - (string) the title to show in the hud and in the title bar
	 *	"msg" - (string) a longer message shown in the GameUI
	 *  "color" - (color) the color to display the message in the hud (white by default)
	 *	"level" - (int) the priority of this message (closer to 0 is higher), only 1 message can be outstanding at a time
	 *	"time" - (int) the time in seconds this message should stay active in the GameUI (min 10 sec, max 200 sec)
	 *
	 * For DIALOG_MENU add sub keys for each option with these fields:
	 *  "command" - (string) client command to run if selected
	 *  "msg" - (string) button text for this option
	*/
	virtual void CreateMessage( void*& pEntity, DIALOG_TYPE type, KeyValues *data, IServerPluginCallbacks *plugin ) = 0;
	virtual void ClientCommand( void*& pEntity, const char *cmd ) = 0;

	/**
	 * Call this to find out the value of a cvar on the client.
	 *
	 * It is an asynchronous query, and it will call IServerPluginCallbacks::OnQueryCvarValueFinished when
	 * the value comes in from the client.
	 *
	 * Store the return value if you want to match this specific query to the OnQueryCvarValueFinished call.
	 * Returns InvalidQueryCvarCookie if the entity is invalid.
	 */
	virtual QueryCvarCookie_t StartQueryCvarValue( void*& pEntity, const char *pName ) = 0;
};

struct CPlugin {
	char m_szName[128]; //0
	bool m_bDisable; // 128
	IServerPluginCallbacks* m_pPlugin; // 132
	int m_iPluginInterfaceVersion; // 136
	void* m_pPluginModule; // 140
};