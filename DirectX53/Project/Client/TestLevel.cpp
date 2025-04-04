#include "pch.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CCollisionMgr.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CTaskMgr.h>

#include <Lecture/Scripts/CPlayerScript.h>
#include <Lecture/Scripts/CMissileScript.h>
#include <Lecture/Scripts/CCameraMoveScript.h>



void CreateTestLevel()
{
	Ptr<CSound> pSound = CAssetMgr::GetInst()->FindAsset<CSound>(L"Sound\\BGM_Stage1.wav");
	if(pSound.Get())
		pSound->Play(0, 0.2f, false);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Background");
	pCurLevel->GetLayer(2)->SetName(L"Tile");
	pCurLevel->GetLayer(3)->SetName(L"Player");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"Enermy");
	pCurLevel->GetLayer(6)->SetName(L"EnermyProjectile");

	// 카메라 역할 오브젝트 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Transform()->SetRelativePos(0.f, 0.f, -100.f);

	pCamObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	//pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetPriority(0); // 메인 카메라로 설정
	pCamObj->Camera()->CheckLayerAll();
	pCamObj->Camera()->CheckLayer(31);

	SpawnGameObject(pCamObj, 0);

	// 광원 설치
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Light");

	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Transform()->SetRelativePos(-200.f, 0.f, 0.f);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light2D()->SetLightColor(Vec3(0.8f, 0.2f, 0.3f));
	pLight->Light2D()->SetRadius(300.f);

	SpawnGameObject(pLight, 0);


	pLight = new CGameObject;
	pLight->SetName(L"Light");

	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Transform()->SetRelativePos(200.f, 0.f, 0.f);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light2D()->SetLightColor(Vec3(0.2f, 0.8f, 0.3));
	pLight->Light2D()->SetRadius(300.f);

	SpawnGameObject(pLight, 0);


	// Parent Object
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Player");

	pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CFlipbookRender);
	//pObject->AddComponent(new CPlayerScript);

	pObject->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	pObject->Transform()->SetRelativeScale(300.f, 300.f, 1.f);

	//pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObject->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pObject->Collider2D()->SetIndependentScale(true);
	pObject->Collider2D()->SetScale(Vec2(110.f, 110.f));
	pObject->Collider2D()->SetOffset(Vec2(0.f, 0.f));

	pObject->FlipbookRender()->AddFlipbook(0, CAssetMgr::GetInst()->Load<CFlipbook>(L"Flipbook\\LinkFlipbook.flip", L"Flipbook\\LinkFlipbook.flip"));
	pObject->FlipbookRender()->Play(0, 20, true);


	// Child Object
	CGameObject* pChild = new CGameObject;
	pChild->SetName(L"Child");
	pChild->AddComponent(new CTransform);
	pChild->AddComponent(new CMeshRender);
	pChild->AddComponent(new CCollider2D);

	pChild->Transform()->SetIndependentScale(true);
	pChild->Transform()->SetRelativePos(150.f, 0.f, 0.f);
	pChild->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pChild->Collider2D()->SetNotifyParent(true);
	pChild->Collider2D()->SetOffset(Vec2(0.f, 0.f));
	pChild->Collider2D()->SetScale(Vec2(1.1f, 1.1f));

	pChild->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
	pChild->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	// 부모 자식 연결
	pObject->AddChild(pChild);

	// 레벨에 부모 오브젝트만 추가
	SpawnGameObject(pObject, 3);

	// ========
	// Particle
	// ========
	pObject = new CGameObject;
	pObject->SetName(L"Particle");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CParticleRender);

	pObject->Transform()->SetRelativePos(-500.f, 300.f, 50.f);
	pObject->Transform()->SetRelativeScale(300.f, 300.f, 1.f);

	CParticleRender* pRender = pObject->ParticleRender();

	// 파티클 용 텍스쳐 지정
	Ptr<CTexture> pParticleTex = CAssetMgr::GetInst()->Load<CTexture>(L"Texture\\particle\\ray.png");
	pRender->SetParticleTex(pParticleTex);

	pRender->SetSpawnRate(20.f);
	pRender->SetSpawnShape(0);
	pRender->SetSpawnShapeScale(Vec3(500.f, 500.f, 500.f));
	pRender->SetMinLife(1.f);
	pRender->SetMaxLife(3.f);
	pRender->SetMinScale(Vec3(100.f, 30.f, 10.f));
	pRender->SetMaxScale(Vec3(200.f, 60.f, 20.f));

	pRender->SetSpaceType(0);

	// AddVelocity 기능 On
	pRender->SetModlue(PARTICLE_MODULE::ADD_VELOCITY, true);
	pRender->SetAddVelocityType(3);
	pRender->SetMinSpeed(100.f);
	pRender->SetMaxSpeed(500.f);
	pRender->SetFixedVelocity(Vec3(0.f, -1.f, 0.f));

	// SpawnBurst 기능
	pRender->SetModlue(PARTICLE_MODULE::SPAWN_BURST, true);
	pRender->SetBurstParticleCount(100);
	pRender->SetBurstRepeatCount(10);
	pRender->SetBurstTerm(2.f);

	// Scale 
	pRender->SetModlue(PARTICLE_MODULE::SCALE, true);
	pRender->SetStartScale(2.f);
	pRender->SetEndScale(2.f);

	// Drag
	//pRender->SetModlue(PARTICLE_MODULE::DRAG, true);
	//pRender->SetDragDestNormalizeAge(0.6f);  // 수명 끝
	//pRender->SetDragLimitSpeed(100.f);		// 속력 0

	// NoiseForce
	pRender->SetModlue(PARTICLE_MODULE::NOISE_FORCE, true);
	pRender->SetNoiseForceTerm(0.2f);
	pRender->SetNoiseForceScale(300.f);

	// Render
	pRender->SetModlue(PARTICLE_MODULE::RENDER, true);
	pRender->SetStartColor(Vec4(1.f, 0.f, 0.f, 1.f));
	pRender->SetEndColor(Vec4(0.f, 0.f, 1.f, 1.f));

	pRender->SetFadeOut(true);
	pRender->SetFadOutStartRatio(0.8f);

	pRender->SetVelocityAlignment(true, true);

	// 오브젝트를 0번 레이어에 추가
	SpawnGameObject(pObject, 0);


	// TileRender Object
	pObject = new CGameObject;
	pObject->SetName(L"TileRender");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CTileRender);

	pObject->Transform()->SetRelativePos(-200.f, 300.f, 500.f);
	pObject->Transform()->SetRelativeScale(300.f, 300.f, 1.f);

	pObject->TileRender()->SetColRow(10, 10);
	pObject->TileRender()->SetTileSize(Vec2(64.f, 64.f));

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			pObject->TileRender()->SetSprite(i, j, CAssetMgr::GetInst()->Load<CSprite>(L"Sprite\\TileSprite_0.sprite"));
		}
	}
	SpawnGameObject(pObject, 0);

	// 충돌 레이어 지정
	CCollisionMgr::GetInst()->CollisionLayerCheck(3, 5);
	CCollisionMgr::GetInst()->CollisionLayerCheck(4, 5);
	CCollisionMgr::GetInst()->CollisionLayerCheck(3, 6);	
}
