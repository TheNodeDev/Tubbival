//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "Game.hpp"

class Portal2CommunityEdition : public Game {
public:
	Portal2CommunityEdition();
	auto LoadOffsets() noexcept(false) -> void override;
	auto Version() -> const char* override;
	static auto ProcessName() -> const char*;
};