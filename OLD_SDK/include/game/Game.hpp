#pragma once

enum SourceGameVersion {
    SourceGame_Unknown = 0,

    SourceGame_Portal2 = (1 << 0),
    SourceGame_Portal2CommunityEdition = (1 << 1),

    SourceGame_Portal2Engine = SourceGame_Portal2,
    SourceGame_ChaosSourceEngine = SourceGame_Portal2CommunityEdition
};

class Game {
public:
    SourceGameVersion version;
public:
    virtual ~Game() = default;
    virtual auto LoadOffsets() noexcept(false) -> void = 0;
    virtual auto Version() -> const char*;

    auto IsPortal2Engine() -> bool;
    auto IsChaosSourceEngine() -> bool;

    static auto CreateNew() -> Game*;
};
