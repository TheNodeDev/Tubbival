#include <vector>
#include "module/Module.hpp"
#include "PluginBase.hpp"

Modules::Modules() : list() { }

auto Modules::InitAll(PluginBase* plugin) -> void {
    for ( const auto& mod : this->list ) {
        if (! mod->hasLoaded ) {
            mod->Init( plugin );
        }
    }
}

auto Modules::ShutdownAll() -> void {
    for ( const auto& mod : this->list ) {
        mod->Shutdown();
        mod->hasLoaded = false;
    }
}

auto Modules::DeleteAll() -> void {
    for ( auto& mod : this->list ) {
        if ( mod ) {
            delete mod;
        }
    }
}

auto Modules::TickAll() -> void {
	for ( const auto& mod : this->list ) {
		if ( mod->hasLoaded )
			mod->Tick();
	}
}

Modules::~Modules() {
    this->DeleteAll();
    this->list.clear();
}
