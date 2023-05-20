//
// Created by ENDERZOMBI102 on 19/03/2022.
//

#include "ExamplePlugin.hpp"
#include "module/Console.hpp"
#include "module/VScript.hpp"

ExamplePlugin examplePlugin;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(ExamplePlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, examplePlugin);

BEGIN_SCRIPTDESC_ROOT(ExamplePlugin, "The ExamplePlugin instance.", examplePlugin);
	// DEFINE_SCRIPTFUNC_D is the default macro
	// to expose a function in a class, used for non-virtual functions
	DEFINE_SCRIPTFUNC_D(GetPluginVersion, "Get the plugin's version.");
	// DEFINE_SCRIPTFUNC_V is used in cases where the function exposed
	// is declared with the `virtual` keyword
	DEFINE_SCRIPTFUNC_V(GetPluginDescription, "Get the plugin's description.");
	DEFINE_SCRIPTFUNC_D(GetPluginWebsite, "Get the plugin's webite.");
END_SCRIPTDESC();

void ExamplePlugin::OnRegisterScripts() {
	vscript->g_pScriptVM->RegisterClass( GetScriptDescForClass(ExamplePlugin) );
	vscript->g_pScriptVM->RegisterInstance( &examplePlugin, "ExamplePlugin" );
}

bool ExamplePlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) {
	auto loaded = PluginBase::Load( interfaceFactory, gameServerFactory );
	if ( loaded ) {
		console->Msg("Example Plugin loaded!\n");
	}
	return loaded;
}

void ExamplePlugin::Unload() {
	console->Msg( "Event: Unload\n" );
	this->Cleanup();
}

void ExamplePlugin::Pause() {
	console->Msg( "Event: Pause\n" );
}

void ExamplePlugin::UnPause() {
	console->Msg( "Event: UnPause\n" );
}

const char* ExamplePlugin::GetPluginDescription() {
	return "Examples for everyone!\n";
}

void ExamplePlugin::LevelInit(const char *pMapName) {
	console->Msg( "Event: LevelInit Params: %s\n", pMapName );
}

void ExamplePlugin::ServerActivate(void *pEdictList, int edictCount, int clientMax) {
	console->Msg( "Event: ServerActivate\n" );
}

void ExamplePlugin::GameFrame(bool simulating) {
	// commented out to prevent console spam
//	console->Msg( "Event: GameFrame Params: %d\n", simulating );
	PluginBase::GameFrame(simulating);
}

void ExamplePlugin::LevelShutdown() {
	console->Msg( "Event: LevelShutdown\n" );
	PluginBase::LevelShutdown();
}

void ExamplePlugin::ClientFullyConnect(void *pEdict) {
	console->Msg( "Event: ClientFullyConnect Params: %p\n", pEdict );
	PluginBase::ClientFullyConnect(pEdict);
}

void ExamplePlugin::ClientActive(void *pEntity) {
	console->Msg( "Event: ClientActive Params: %p\n", pEntity );
	PluginBase::ClientActive(pEntity);
}

void ExamplePlugin::ClientDisconnect(void *pEntity) {
	console->Msg( "Event: ClientDisconnect Params: %p\n", pEntity );
}

void ExamplePlugin::ClientPutInServer(void *pEntity, const char *playerName) {
	console->Msg( "Event: ClientPutInServer Params: %p - %s\n", pEntity, playerName );
}

void ExamplePlugin::SetCommandClient(int index) {
	console->Msg( "Event: SetCommandClient Params: %d\n", index );
}

void ExamplePlugin::ClientSettingsChanged(void *pEdict) {
	console->Msg( "Event: ClientSettingsChanged Params: %p\n", pEdict );
}

PLUGIN_RESULT
ExamplePlugin::ClientConnect(bool *bAllowConnect, void *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxRejectLen) {
	console->Msg( "Event: ClientConnect Params: %d - %p - %s - %s - %s - %d\n", *bAllowConnect, pEntity, pszName, pszAddress, reject, maxRejectLen );
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT ExamplePlugin::ClientCommand(void *pEntity, const CCommand &args) {
	console->Msg( "Event: ClientCommand Params: %p - %s\n", pEntity, args.m_ppArgv );
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT ExamplePlugin::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID) {
	console->Msg( "Event: NetworkIdValidated Params: %s - %s\n", pszUserName, pszNetworkID );
	return PLUGIN_CONTINUE;
}

void ExamplePlugin::OnQueryCvarValueFinished(int iCookie, void *pPlayerEntity, int eStatus, const char *pCvarName, const char *pCvarValue) {
	console->Msg( "Event: OnQueryCvarValueFinished Params: %d - %p - %d - %s - %s\n", iCookie, pPlayerEntity, eStatus, pCvarName, pCvarValue );
}

void ExamplePlugin::OnEdictAllocated(void *edict) {
	console->Msg( "Event: OnEdictAllocated Params: %p\n", edict );
}

void ExamplePlugin::OnEdictFreed(const void *edict) {
	console->Msg( "Event: OnEdictFreed Params: %p\n", edict );
}

void ExamplePlugin::Cleanup() {
	if ( console )
		console->Msg( "Event: Cleanup\n" );
	PluginBase::Cleanup();
}
