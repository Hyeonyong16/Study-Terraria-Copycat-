#include "pch.h"
#include "CCameraMoveScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CTransform.h>
#include <Engine/CCamera.h>

CCameraMoveScript::CCameraMoveScript()
	: CScript(CAMERAMOVESCRIPT)
	, m_CamSpeed(100.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::Tick()
{
	// 카메라 컴포넌트가 없으면 종료
	if (!Camera())
		return;

	PROJ_TYPE type = Camera()->GetProjType();

	if (PROJ_TYPE::PERSPECTIVE == type)
		Move_Perspective();
	else
		Move_OrthoGraphic();
}

void CCameraMoveScript::Move_Perspective()
{
	Vec3 vPos = Transform()->GetRelativePos();

	Vec3 vFront = Transform()->GetRelativeDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetRelativeDir(DIR::RIGHT);

	if (KEY_PRESSED(KEY::W))
		vPos += vFront * DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::S))
		vPos -= vFront * DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::A))
		vPos -= vRight * DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D))
		vPos += vRight * DT * m_CamSpeed;

	Transform()->SetRelativePos(vPos);


	if (!KEY_PRESSED(KEY::RBTN))
		return;

	Vec2 vDragDir = CKeyMgr::GetInst()->GetDragDir();
	Vec3 vRot = Transform()->GetRelativeRotation();
	vRot.x += vDragDir.y * DT * 1800.f;
	vRot.y += vDragDir.x * DT * 1800.f;
	Transform()->SetRelativeRotation(vRot);
}

void CCameraMoveScript::Move_OrthoGraphic()
{
	Vec3 vRot = Vec3(0.f, 0.f, 0.f);
	Transform()->SetRelativeRotation(vRot);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
		vPos.y += DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::S))
		vPos.y -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::A))
		vPos.x -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D))
		vPos.x += DT * m_CamSpeed;

	Transform()->SetRelativePos(vPos);
}

void CCameraMoveScript::SaveToFile(FILE* _File)
{
	fwrite(&m_CamSpeed, sizeof(float), 1, _File);
}

void CCameraMoveScript::LoadFromFile(FILE* _File)
{
	fread(&m_CamSpeed, sizeof(float), 1, _File);
}
