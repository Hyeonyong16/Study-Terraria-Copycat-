#pragma once

#include "CTexture.h"

class CCamera;
class CGameObject;
class CLight2D;
class CStructuredBuffer;

class CRenderMgr
	: public singleton<CRenderMgr>
{
	SINGLE(CRenderMgr);
private:
	vector<CCamera*>		m_vecCam;
	vector<CLight2D*>		m_vecLight2D;
	CStructuredBuffer*		m_Light2DBuffer;



	CGameObject*			m_DebugObject;
	vector<tDebugShapeInfo> m_vecDebugInfo;

	Ptr<CTexture>			m_PostProcessTex;


public:
	void RegisterCamera(CCamera* _Cam, int _Priority);	
	void RegisterLight2D(CLight2D* _Light2D) { m_vecLight2D.push_back(_Light2D); }
	void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_vecDebugInfo.push_back(_info); }
	void CopyRenderTarget();
	Ptr<CTexture> GetPostProcessTex() { return m_PostProcessTex; }

public:
	void Init();
	void Tick();

private:
	void Binding();
	void Render();
	void Clear();
	void DebugRender();
};

