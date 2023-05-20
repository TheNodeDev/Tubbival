#pragma once
#include "Game.hpp"

class Portal2Linux : public Game {
public:
    Portal2Linux();
    auto LoadOffsets() noexcept(false) -> void override;
    auto Version() -> const char* override;
    static auto ProcessName() -> const char*;
};
