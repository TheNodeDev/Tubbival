#pragma once
#include "Utils.hpp"
#include "engine/PluginInterface.hpp"

// CServerPlugin
#define CServerPlugin_m_Size 16
#define CServerPlugin_m_Plugins 4

class Plugin {
public:
    CPlugin* ptr;
    int index;
public:
    Plugin();
};
