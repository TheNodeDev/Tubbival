//
// Created by ENDERZOMBI102 on 19/03/2022.
//

#pragma once

#include "PluginBase.hpp"

#define VERSION "0.1.0"
#define WEBSITE "https://gitlab.com/portal-sdk/portal-2-sdk"

class ExamplePlugin : public PluginBase {
public:
	ExamplePlugin() { };
	virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
	virtual void Unload();
	virtual void Pause();
	virtual void UnPause();
	virtual const char* GetPluginDescription();
	virtual void LevelInit(char const* pMapName);
	virtual void ServerActivate(void* pEdictList, int edictCount, int clientMax);
	virtual void GameFrame(bool simulating);
	virtual void LevelShutdown();
	virtual void ClientFullyConnect(void* pEdict);
	virtual void ClientActive(void* pEntity);
	virtual void ClientDisconnect(void* pEntity);
	virtual void ClientPutInServer(void* pEntity, char const* playerName);
	virtual void SetCommandClient(int index);
	virtual void ClientSettingsChanged(void* pEdict);
	virtual PLUGIN_RESULT ClientConnect(bool* bAllowConnect, void* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen);
	virtual PLUGIN_RESULT ClientCommand(void* pEntity, const CCommand &args);
	virtual PLUGIN_RESULT NetworkIDValidated(const char* pszUserName, const char* pszNetworkID);
	virtual void OnQueryCvarValueFinished(int iCookie, void* pPlayerEntity, int eStatus, const char* pCvarName, const char* pCvarValue);
	virtual void OnEdictAllocated(void* edict);
	virtual void OnEdictFreed(const void* edict);
	virtual void OnRegisterScripts();
	virtual const char* Version() { return VERSION; };
	virtual const char* Website() { return WEBSITE; };
	virtual void Cleanup();

	const char* GetPluginVersion() { return VERSION; };
	const char* GetPluginWebsite() { return WEBSITE; };
};

extern ExamplePlugin examplePlugin;
