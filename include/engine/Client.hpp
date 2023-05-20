//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include "Math.hpp"

enum MotionBlurMode_t {
	MOTION_BLUR_DISABLE = 1,
	MOTION_BLUR_GAME = 2,
	MOTION_BLUR_SFM = 3
};

class CViewSetup {
public:
	int			x;
	int			y;
	int			width;
	int			height;
	bool		m_bOrtho;
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	bool		m_bCustomViewMatrix;
	matrix3x4_t	m_matCustomViewMatrix;
	float		fov;
	float		fovViewmodel;
	Vector		origin;
	QAngle		angles;
	float		zNear;
	float		zFar;
	float		zNearViewmodel;
	float		zFarViewmodel;
	float		m_flAspectRatio;
	float		m_flNearBlurDepth;
	float		m_flNearFocusDepth;
	float		m_flFarFocusDepth;
	float		m_flFarBlurDepth;
	float		m_flNearBlurRadius;
	float		m_flFarBlurRadius;
	int			m_nDoFQuality;
	MotionBlurMode_t	m_nMotionBlurMode;
	float	m_flShutterTime;
	Vector	m_vShutterOpenPosition;
	QAngle	m_shutterOpenAngles;
	Vector	m_vShutterClosePosition;
	QAngle	m_shutterCloseAngles;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	bool		m_bOffCenter : 1;
	bool		m_bRenderToSubrectOfLargerScreen : 1;
	bool		m_bDoBloomAndToneMapping : 1;
	bool		m_bDoDepthOfField : 1;
	bool		m_bHDRTarget : 1;
	bool		m_bDrawWorldNormal : 1;
	bool		m_bCullFrontFaces : 1;
	bool		m_bCacheFullSceneState : 1;
	bool		m_bRenderFlashlightDepthTranslucents : 1;
};