#pragma once
#include "CRenderComponent.h"
#include "CParticleTickCS.h"

class CStructuredBuffer;

class CParticleRender :
    public CRenderComponent
{
private:
    CStructuredBuffer*      m_ParticleBuffer;
    CStructuredBuffer*      m_SpawnBuffer;
    CStructuredBuffer*      m_ModuleBuffer;

    Ptr<CParticleTickCS>    m_TickCS;
    UINT                    m_MaxParticle;      // ��ƼŬ �ִ� ����

    tParticleModule         m_Module;           // ��ƼŬ ���� ������
    bool                    m_ModuleChanged;    // ��� ������ ������ ����
    float                   m_AccTime;          // �����ð� üũ


public:    
    void SetSpawnRate(float _Rate) { m_Module.SpawnRate = _Rate; m_ModuleChanged = true; }
    float GetSpawnRate() { return m_Module.SpawnRate;m_ModuleChanged = true; }
    void SetStartColor(Vec4 _Color) { m_Module.StartColor = _Color; m_ModuleChanged = true;}
    void SetEndColor(Vec4 _Color) { m_Module.EndColor = _Color; m_ModuleChanged = true;}
    void SetMinScale(Vec3 _Scale) { m_Module.MinScale = _Scale;m_ModuleChanged = true; }
    void SetMaxScale(Vec3 _Scale) { m_Module.MaxScale = _Scale; m_ModuleChanged = true;}
    void SetMinLife(float _MinLife) { m_Module.MinLife = _MinLife; m_ModuleChanged = true;}
    void SetMaxLife(float _MaxLife) { m_Module.MaxLife = _MaxLife; m_ModuleChanged = true;}
    // 0 : Box, 1 : Sphere
    void SetSpawnShape(int _Shape) { m_Module.SpawnShape = _Shape; m_ModuleChanged = true;}
    void SetSpawnShapeScale(Vec3 _Scale) { m_Module.SpawnShapeScale = _Scale; m_ModuleChanged = true;}
    // 0 : Local, 1 : World;
    void SetSpaceType(int _Type) { m_Module.SpaceType = _Type; m_ModuleChanged = true;}






public:
    virtual void FinalTick() override;
    virtual void Render() override;

private:
    void CreateMtrl();
    void CalcSpawnCount();


public:
    CLONE(CParticleRender);
    CParticleRender();
    ~CParticleRender();
};

