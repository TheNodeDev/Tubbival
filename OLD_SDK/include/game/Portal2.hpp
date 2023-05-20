#pragma once
#include "Game.hpp"

class Portal2 : public Game {
public:
    Portal2();
    auto LoadOffsets() noexcept(false) -> void override;
    auto Version() -> const char* override;
    static auto ProcessName() -> const char*;
};
