//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#include <stdexcept>
#include "game/Portal2CommunityEdition.hpp"

Portal2CommunityEdition::Portal2CommunityEdition() {
	this->version = SourceGame_Portal2CommunityEdition;
}

auto Portal2CommunityEdition::LoadOffsets() noexcept(false) -> void {
	throw std::runtime_error("Portal 2: Community Edition is not yet supported!");
}

auto Portal2CommunityEdition::Version() -> const char* {
	return "Portal 2: Community Edition (8463)";
}

auto Portal2CommunityEdition::ProcessName() -> const char* {
	return "chaos.exe";
}