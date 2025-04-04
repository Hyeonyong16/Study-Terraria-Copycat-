#include "pch.h"
#include "CMissileScript.h"

#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>

CMissileScript::CMissileScript()
	: CScript(MISSILESCRIPT)
	, m_vDir(0.f, 1.f, 0.f)
	, m_Speed(100.f)
{
}

CMissileScript::~CMissileScript()
{
}


void CMissileScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos += m_vDir * m_Speed * DT;

	Transform()->SetRelativePos(vPos);
}

void CMissileScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider)
{
	if (L"Monster" == _Other->GetName())
	{
		_Other->Destroy();
	}
}

void CMissileScript::SaveToFile(FILE* _File)
{
	fwrite(&m_vDir, sizeof(Vec2), 1, _File);
	fwrite(&m_Speed, sizeof(float), 1, _File);
}

void CMissileScript::LoadFromFile(FILE* _File)
{
	fread(&m_vDir, sizeof(Vec2), 1, _File);
	fread(&m_Speed, sizeof(float), 1, _File);
}


