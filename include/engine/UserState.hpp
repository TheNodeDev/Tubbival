//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "Math.hpp"
#include "Color.hpp"

enum SignonState {
	None = 0,
	Challenge = 1,
	Connected = 2,
	New = 3,
	Prespawn = 4,
	Spawn = 5,
	Full = 6,
	Changelevel = 7
};

struct CUserCmd {
	void* VMT; // 0
	int command_number; // 4
	int tick_count; // 8
	QAngle viewangles; // 12, 16, 20
	float forwardmove; // 24
	float sidemove; // 28
	float upmove; // 32
	int buttons; // 36
	unsigned char impulse; // 40
	int weaponselect; // 44
	int weaponsubtype; // 48
	int random_seed; // 52
	short mousedx; // 56
	short mousedy; // 58
	bool hasbeenpredicted; // 60
};

class CMoveData {
public:
	bool m_bFirstRunOfFunctions : 1; // 0
	bool m_bGameCodeMovedPlayer : 1; // 2
	void* m_nPlayerHandle; // 4
	int m_nImpulseCommand; // 8
	QAngle m_vecViewAngles; // 12, 16, 20
	QAngle m_vecAbsViewAngles; // 24, 28, 32
	int m_nButtons; // 36
	int m_nOldButtons; // 40
	float m_flForwardMove; // 44
	float m_flSideMove; // 48
	float m_flUpMove; // 52
	float m_flMaxSpeed; // 56
	float m_flClientMaxSpeed; // 60
	Vector m_vecVelocity; // 64, 68, 72
	QAngle m_vecAngles; // 76, 80, 84
	QAngle m_vecOldAngles; // 88, 92, 96
	float m_outStepHeight; // 100
	Vector m_outWishVel; // 104, 108, 112
	Vector m_outJumpVel; // 116, 120, 124
	Vector m_vecConstraintCenter; // 128, 132, 136
	float m_flConstraintRadius; // 140
	float m_flConstraintWidth; // 144
	float m_flConstraintSpeedFactor; // 148
	float m_unknown;
	Vector m_vecAbsOrigin; // 156
};

class CHLMoveData : public CMoveData {
public:
	bool m_bIsSprinting;
};

#define IN_ATTACK (1 << 0)
#define IN_JUMP (1 << 1)
#define IN_DUCK (1 << 2)
#define IN_FORWARD (1 << 3)
#define IN_BACK (1 << 4)
#define IN_USE (1 << 5)
#define IN_MOVELEFT (1 << 9)
#define IN_MOVERIGHT (1 << 10)
#define IN_ATTACK2 (1 << 11)
#define IN_RELOAD (1 << 13)
/**
 * Player is holding the speed key
 */
#define IN_SPEED (1 << 17)

/**
 * At rest / on the ground
 */
#define FL_ONGROUND (1 << 0)
/**
 * Player flag -- Player is fully crouched
 */
#define FL_DUCKING (1 << 1)
/**
 * Player is frozen for 3rd person camera
 */
#define FL_FROZEN (1 << 5)
/**
 * Player can't move, but keeps key inputs for controlling another entity
 */
#define FL_ATCONTROLS (1 << 6)

#define WL_Feet 1
#define WL_Waist 2

typedef enum {
	/**
	 * never moves
	 */
	MOVETYPE_NONE = 0,
	/**
	 * For players -- in TF2 commander view, etc.
	 */
	MOVETYPE_ISOMETRIC = 1,
	/**
	 * Player only - moving on the ground
	 */
	MOVETYPE_WALK = 2,
	/**
	 * gravity, special edge handling -- monsters use this
	 */
	MOVETYPE_STEP = 3,
	/**
	 * No gravity, but still collides with stuff
	 */
	MOVETYPE_FLY = 4,
	/**
	 * flies through the air + is affected by gravity
	 */
	MOVETYPE_FLYGRAVITY = 5,
	/**
	 * uses VPHYSICS for simulation
	 */
	MOVETYPE_VPHYSICS = 6,
	/**
	 * no clip to world, push and crush
	 */
	MOVETYPE_PUSH = 7,
	/**
	 * No gravity, no collisions, still do velocity/avelocity
	 */
	MOVETYPE_NOCLIP = 8,
	/**
	 * Used by players only when going onto a ladder
	 */
	MOVETYPE_LADDER = 9,
	/**
	 * Observer movement, depends on player's observer mode
	 */
	MOVETYPE_OBSERVER = 10,
	/**
	 * Allows the entity to describe its own physics
	 */
	MOVETYPE_CUSTOM = 11,

	// should always be defined as the last item in the list
	MOVETYPE_LAST = MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS = 4
} MoveType_t;

typedef enum {
	HS_NEW_GAME = 0,
	HS_LOAD_GAME = 1,
	HS_CHANGE_LEVEL_SP = 2,
	HS_CHANGE_LEVEL_MP = 3,
	HS_RUN = 4,
	HS_GAME_SHUTDOWN = 5,
	HS_SHUTDOWN = 6,
	HS_RESTART = 7
} HOSTSTATES;

struct CHostState {
	HOSTSTATES m_currentState; // 0
	HOSTSTATES m_nextState; // 4
	Vector m_vecLocation; // 8, 12, 16
	QAngle m_angLocation; // 20, 24, 28
	char m_levelName[256]; // 32
	char m_landmarkName[256]; // 288
	char m_saveName[256]; // 544
	float m_flShortFrameTime; // 800
	bool m_activeGame; // 804
	bool m_bRememberLocation; // 805
	bool m_bBackgroundLevel; // 806
	bool m_bWaitingForConnection; // 807
};