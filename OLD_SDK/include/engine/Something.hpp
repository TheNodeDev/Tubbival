#pragma once
#include <cmath>
#include <cstring>


struct CGlobalVarsBase {
    float realtime; // 0
    int framecount; // 4
    float absoluteframetime; // 8
    float curtime; // 12
    float frametime; // 16
    int maxClients; // 20
    int tickcount; // 24
    float interval_per_tick; // 28
    float interpolation_amount; // 32
    int simTicksThisFrame; // 36
    int network_protocol; // 40
    void* pSaveData; // 44
    bool m_bClient; // 48
    int nTimestampNetworkingBase; // 52
    int nTimestampRandomizeWindow; // 56
};

struct CEntInfo {
    void* m_pEntity; // 0
    int m_SerialNumber; // 4
    CEntInfo* m_pPrev; // 8
    CEntInfo* m_pNext; // 12
};

struct CEntInfo2 : CEntInfo {
    void* unk1; // 16
    void* unk2; // 20
};

enum MapLoadType_t {
    MapLoad_NewGame = 0,
    MapLoad_LoadGame = 1,
    MapLoad_Transition = 2,
    MapLoad_Background = 3
};

struct CGlobalVars : CGlobalVarsBase {
    char* mapname; // 60
    int mapversion; // 64
    char* startspot; // 68
    MapLoadType_t eLoadType; // 72
    bool bMapLoadFailed; // 76
    bool deathmatch; // 80
    bool coop; // 84
    bool teamplay; // 88
    int maxEntities; // 92
};





// Particle system stuff



