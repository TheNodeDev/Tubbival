#include <chrono>
#include "PluginBase.hpp"
#include "module/Console.hpp"
#include "module/Engine.hpp"
#include "module/Client.hpp"
#include "module/Server.hpp"
#include "module/VScript.hpp"
#include "module/Surface.hpp"
#include "module/VGui.hpp"

PluginBase::PluginBase()
    : game( Game::CreateNew() )
    , plugin( new Plugin() )
    , modules( new Modules() )
    , cheats( new Cheats() )
    , clients() { }

// Used callbacks
bool PluginBase::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) {
	console = new Console();
	if (! console->Init( this ) )
		return false;

	if ( this->game ) {
		try {
			this->game->LoadOffsets();
		} catch ( std::runtime_error exc ) {
			console->Warning( ( std::string( "Portal 2 SDK: Failed to load offsets! message is \"" ) + exc.what() + "\"\n" ).c_str() );
			return false;
		}

		this->modules->AddModule<Tier1>(&tier1);
		this->modules->InitAll( this );

		if ( tier1 && tier1->hasLoaded ) {
			this->cheats->Init( this );

			this->modules->AddModule<Engine>(&engine);
			this->modules->AddModule<Client>(&client);
			this->modules->AddModule<Server>(&server);
			this->modules->AddModule<VScript>(&vscript);
			this->modules->AddModule<Surface>(&surface);
			this->modules->AddModule<VGui>(&vgui);
			this->modules->InitAll( this );

			if ( engine && client && engine->hasLoaded && client->hasLoaded && server->hasLoaded ) {
				console->Print( "Portal 2 SDK: all modules loaded\n" );
				return true;
			} else {
				console->Warning( "Portal 2 SDK: Failed to load engine and client modules!\n" );
			}
		} else {
			console->Warning( "Portal 2 SDK: Failed to load tier1 module!\n" );
		}
	} else {
		console->Warning( "Portal 2 SDK: Game not supported!\n" );
	}

	console->Warning( "Portal 2 SDK: Aborting modules load!\n" );
	return false;
}

void PluginBase::LevelShutdown() {
    console->DevMsg("Portal2SDK::LevelShutdown\n");

	#ifdef EXAMPLES_COMPILE
        staminaHud->SetStaminaColor( Color(0, 0, 0, 0) );
	#endif
	this->SetBackupKey("0");

    // Make sure to clear the list after sending any client-side shutdown commands
    this->clients.clear();
}

void PluginBase::ClientActive(void* pEntity) {
    console->DevMsg("Portal2SDK::ClientActive -> pEntity: %p\n", pEntity);
    client->SetPortalGunIndicatorColor(Vector(0, 0, 0));
}

void PluginBase::ClientFullyConnect(void* pEdict) {
    this->clients.push_back(pEdict);
}

void PluginBase::Cleanup() {
    if ( console )
        console->Print("Portal 2 SDK disabled.\n");

    if ( this->cheats )
        this->cheats->Shutdown();

    if ( this->modules )
        this->modules->ShutdownAll();

    SAFE_UNLOAD(this->cheats);
    SAFE_UNLOAD(this->game);
    SAFE_UNLOAD(this->plugin);
    SAFE_UNLOAD(this->modules);
    SAFE_UNLOAD(console);
}

void PluginBase::SetBackupKey(const char* key) {
    backupKey = key;
    this->backupKeyChanged = true;
}

const char* PluginBase::GetBackupKey() {
    return this->backupKey;
}

bool PluginBase::HasBackupKeyBeenChanged() {
    bool changed = this->backupKeyChanged;
    if ( changed )
		this->backupKeyChanged = false;
    return changed;
}

void PluginBase::GameFrame(bool simulating) {
	isPaused = !simulating;
}
