#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>
#include <Engine/CRenderMgr.h>

#include <Engine/CTransform.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CTaskMgr.h>
#include <Engine/CCollider2D.h>
#include <Engine/CMeshRender.h>
#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: CScript(PLAYERSCRIPT)
	, m_Speed(0.f)
	, m_PaperBurn(0.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Init()
{
	ADD_FLOAT("Speed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Missile", &m_Prefab);
}

void CPlayerScript::Begin()
{
	
}

void CPlayerScript::Tick()
{
	CTransform* pTrans = GetOwner()->Transform();

	Vec3 vPos = pTrans->GetRelativePos();

	// 키입력에 따라서 사각형이 움직이도록 한다.
	if (KEY_PRESSED(KEY::LEFT))
		vPos.x -= m_Speed * DT;
	if (KEY_PRESSED(KEY::RIGHT))
		vPos.x += m_Speed * DT;
	if (KEY_PRESSED(KEY::UP))
		vPos.y += m_Speed * DT;
	if (KEY_PRESSED(KEY::DOWN))
		vPos.y -= m_Speed * DT;

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = pTrans->GetRelativeRotation();
		vRot.z += DT * 180.f;
		pTrans->SetRelativeRotation(vRot);

		Vec3 vScale = Transform()->GetRelativeScale();
		vScale.x += DT * 10.f;
		vScale.y += DT * 10.f;
		Transform()->SetRelativeScale(vScale);
	}

	if (KEY_TAP(KEY::Y))
	{
		RenderComponent()->GetMaterial()->SetScalarParam(INT_3, 1);
	}
	if (KEY_RELEASED(KEY::Y))
	{
		RenderComponent()->GetMaterial()->SetScalarParam(INT_3, 0);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		if(nullptr != m_Prefab)
			Instantiate(m_Prefab, 4, Transform()->GetWorldPos());
	}

	pTrans->SetRelativePos(vPos);

	//m_PaperBurn += DT * 0.2f;
	RenderComponent()->GetMaterial()->SetScalarParam(FLOAT_0, m_PaperBurn);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider)
{

}

void CPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	fwrite(&m_PaperBurn, sizeof(float), 1, _File);
	SaveAssetRef(m_Prefab, _File);
}

void CPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	fread(&m_PaperBurn, sizeof(float), 1, _File);
	m_Prefab = LoadAssetRef<CPrefab>(_File);
}
