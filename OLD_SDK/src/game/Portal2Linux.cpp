#include "../../include/game/Portal2Linux.hpp"
#include "../../include/Offsets.hpp"

Portal2Linux::Portal2Linux() {
    this->version = SourceGame_Portal2;
}

auto Portal2Linux::LoadOffsets() -> void {
    using namespace Offsets;

    // engine.so

	InternalSetValue = 19;                 // ConVar
	InternalSetFloatValue = 20;            // ConVar
	InternalSetIntValue = 21;              // ConVar
	GetScreenSize = 5;                     // CEngineClient
	ClientCmd = 7;                         // CEngineClient
	GetClientStateFunction = 16;           // CEngineClient::ClientCmd
	Cbuf_AddText = 45;                     // CEngineClient::ClientCmd
	CCommandBufferSize = 9556;             // Cbuf_AddText
	m_bWaitEnabled = 8265;                 // CCommandBuffer::AddText
	GetActiveSplitScreenPlayerSlot = 127;  // CEngineClient
	SetSignonState = 3;                    // CDemoRecorder
	Paint = 15;                            // CEngineVGui
	HostState_OnClientConnected = 1503;    // CClientState::SetSignonState
	hoststate = 9;                         // HostState_OnClientConnected
	PrecacheModel = 61;                    // CEngineTool::PrecacheModel
	AutoCompletionFunc = 46;               // listdemo_CompletionFunc

    // client.so

    GetHud = 146; // cc_leaderboard_enable
    FindElement = 161; // cc_leaderboard_enable
    ChatPrintf = 25; // CBaseHudChat
    RenderView = 26;

    // server.so
    m_hActiveWeapon = 2164; // CBaseEntity
    m_bCanFirePortal1 = 1524; // CBaseEntity
    UTIL_PlayerByIndex = 70; // CServerGameDLL::Think
    Think = 31; // CServerGameDLL
    m_hGroundEntity = 352; // CBaseEntity
    GetIServerEntity = 2; // CServerTools
    m_EntPtrArray = 48; // CServerTools::GetIServerEntity
    //CBaseEntityActivate = ;

    // libvstdlib.so

    RegisterConCommand = 9; // CCVar
    UnregisterConCommand = 10; // CCvar
    FindCommandBase = 13; // CCVar
    m_pConCommandList = 48; // CCvar

    // vscript.so

    CreateVM = 8;

    // vgui2.so

    GetIScheme = 9; // CSchemeManager
    GetFont = 4; // CScheme

    // vguimatsurface.so

    DrawSetColor = 13; // CMatSystemSurface
    DrawFilledRect = 15; // CMatSystemSurface
    DrawLine = 18; // CMatSystemSurface
    DrawSetTextFont = 22; // CMatSystemSurface
    DrawSetTextColor = 24; // CMatSystemSurface
    GetFontTall = 72; // CMatSystemSurface
    PaintTraverseEx = 117; // CMatSystemSurface
    StartDrawing = 559; // CMatSystemSurface::PaintTraverseEx
    FinishDrawing = 430; // CMatSystemSurface::PaintTraverseEx
    DrawColoredText = 160; // CMatSystemSurface
    DrawTextLen = 163; // CMatSystemSurface
    DisableClipping = 156; // CMatSystemSurface
    Paint = 15; // CEngineVGui

    DrawSetTextureFile = 35; // CMatSystemSurface
    DrawSetTextureRGBA = 36; // CMatSystemSurface
    DrawSetTexture = 37; // CMatSystemSurface
    DrawGetTextureSize = 38; // CMatSystemSurface
    DrawTexturedRect = 39; // CMatSystemSurface
    IsTextureIDValid = 40; // CMatSystemSurface
    CreateNewTextureID = 41; // CMatSystemSurface
}

auto Portal2Linux::Version() -> const char* {
    return "Portal 2 (8491)";
}

auto Portal2Linux::ProcessName() -> const char* {
    return "portal2_linux";
}
