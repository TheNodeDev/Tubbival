#include "game/Game.hpp"
#include "util/Memory.hpp"
#include "game/Portal2.hpp"
#include "game/Portal2Linux.hpp"
#include "game/Portal2CommunityEdition.hpp"

const char* Game::Version() {
    return "Unknown";
}

bool Game::IsPortal2Engine() {
    return this->version == SourceGame_Portal2Engine;
}

bool Game::IsChaosSourceEngine() {
	return this->version == SourceGame_ChaosSourceEngine;
}

Game* Game::CreateNew() {
	if ( Memory::GetProcessName() == Portal2::ProcessName() ) {
        return new Portal2();
    } else if ( Memory::GetProcessName() == Portal2Linux::ProcessName() ) {
        return new Portal2Linux();
    } else if ( Memory::GetProcessName() == Portal2CommunityEdition::ProcessName() ) {
        return new Portal2CommunityEdition();
    }
    return nullptr;
}
