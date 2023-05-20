//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "Math.hpp"
#include "CUtl.hpp"

struct CParticleControlPoint {
	Vector m_Position;
	Vector m_PrevPosition;

	// orientation
	Vector m_ForwardVector;
	Vector m_UpVector;
	Vector m_RightVector;

	// reference to entity or whatever this control point comes from
	void* m_pObject;

	// parent for hierarchies
	int m_nParent;

	// CParticleSnapshot which particles can read data from or write data to:
	void* m_pSnapshot;
};

struct CModelHitBoxesInfo {
	float m_flLastUpdateTime;
	float m_flPrevLastUpdateTime;
	int m_nNumHitBoxes;
	int m_nNumPrevHitBoxes;
	void* m_pHitBoxes;
	void* m_pPrevBoxes;
};

struct CParticleCPInfo {
	CParticleControlPoint m_ControlPoint;
	CModelHitBoxesInfo m_CPHitBox;
};

struct CParticleAttributeAddressTable {
	float* m_pAttributes[24];
	size_t m_nFloatStrides[24];
};

// Alien Swarm SDK definition is used, but it doesn't work properly
// TODO: figure out all members of this struct

class CParticleCollection {
public:
	//CUtlReference< void > m_Sheet; // CSheet
	//fltx4 m_fl4CurTime;
	//int m_nPaddedActiveParticles;
	//float m_flCurTime;
	//float m_flPrevSimTime;
	//float m_flTargetDrawTime;
	//int m_nActiveParticles;
	//float m_flDt;
	//float m_flPreviousDt;
	//float m_flNextSleepTime;
	//CUtlReference< void > m_pDef; //CParticleSystemDefinition
	//int m_nAllocatedParticles;
	//int m_nMaxAllowedParticles;
	//bool m_bDormant;
	//bool m_bEmissionStopped;
	//bool m_bPendingRestart;
	//bool m_bQueuedStartEmission;
	//bool m_bFrozen;
	//bool m_bInEndCap;
	//int m_LocalLightingCP;
	//Color m_LocalLighting;
	unsigned char unknown001[100];

	int m_nNumControlPointsAllocated;
	CParticleCPInfo* m_pCPInfo;
	unsigned char* m_pOperatorContextData;
	CParticleCollection* m_pNext;
	CParticleCollection* m_pPrev;
	struct CWorldCollideContextData* m_pCollisionCacheData[4];
	CParticleCollection* m_pParent;
	CUtlIntrusiveDList<CParticleCollection>  m_Children;
	Vector m_Center;
	void* m_pRenderable;
	bool m_bBoundsValid;
	Vector m_MinBounds;
	Vector m_MaxBounds;
	int m_nHighestCP;
	//int m_nAttributeMemorySize;
	//unsigned char* m_pParticleMemory;
	//unsigned char* m_pParticleInitialMemory;
	//unsigned char* m_pConstantMemory;
	//unsigned char* m_pPreviousAttributeMemory;
	//int m_nPerParticleInitializedAttributeMask;
	//int m_nPerParticleUpdatedAttributeMask;
	//int m_nPerParticleReadInitialAttributeMask;
	//CParticleAttributeAddressTable m_ParticleAttributes;
	//CParticleAttributeAddressTable m_ParticleInitialAttributes;
	//CParticleAttributeAddressTable m_PreviousFrameAttributes;
	//float* m_pConstantAttributes;
	//unsigned long long m_nControlPointReadMask;
	//unsigned long long m_nControlPointNonPositionalMask;
	//int m_nParticleFlags;
	//bool m_bIsScrubbable : 1;
	//bool m_bIsRunningInitializers : 1;
	//bool m_bIsRunningOperators : 1;
	//bool m_bIsTranslucent : 1;
	//bool m_bIsTwoPass : 1;
	//bool m_bAnyUsesPowerOfTwoFrameBufferTexture : 1;
	//bool m_bAnyUsesFullFrameBufferTexture : 1;
	//bool m_bIsBatchable : 1;
	//bool m_bIsOrderImportant : 1;
	//bool m_bRunForParentApplyKillList : 1;
	//bool m_bUsesPowerOfTwoFrameBufferTexture;
	//bool m_bUsesFullFrameBufferTexture;
	//int m_nDrawnFrames;
	//int m_nUniqueParticleId;
	//int m_nRandomQueryCount;
	//int m_nRandomSeed;
	//int m_nOperatorRandomSampleOffset;
	//float m_flMinDistSqr;
	//float m_flMaxDistSqr;
	//float m_flOOMaxDistSqr;
	//Vector m_vecLastCameraPos;
	//float m_flLastMinDistSqr;
	//float m_flLastMaxDistSqr;
	//int m_nNumParticlesToKill;
	//void* m_pParticleKillList; // KillListItem_t
	//CParticleCollection* m_pNextDef;
	//CParticleCollection* m_pPrevDef;
	//void* m_pRenderOp; //CParticleOperatorInstance
};

struct CNewParticleEffect {
	/**
	 * wtf is this property
	 * */
	void* valveYouAbsoluteDumbFucksIWishYouAllGetHitByAnIcecreamTruck[4];
	CParticleCollection collection;
};