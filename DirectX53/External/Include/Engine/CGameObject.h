#pragma once

#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CScript;


class CGameObject :
    public CEntity
{
private:
    CComponent*             m_Com[COMPONENT_END];
    vector<CScript*>        m_vecScript;    
    CRenderComponent*       m_RenderCom; // ������ ������Ʈ ������

    CGameObject*            m_Parent;   // �θ� ������Ʈ
    vector<CGameObject*>    m_vecChild; // �ڽ� ������Ʈ

    int                     m_LayerIdx; // �Ҽ� ���̾� �ε���, -1 : ��� ���̾�� �ҼӵǾ����� �ʴ�.

    bool                    m_Dead;  // ������Ʈ�� �����Ǳ� ���� ���� üũ


public:
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_Com[_Type]; }
    CRenderComponent* GetRenderComponent() { return m_RenderCom; }

    bool IsDead() { return m_Dead; }

    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Child);

    CGameObject* GetParent() const { return m_Parent; }
    const vector<CGameObject*>& GetChild() const { return m_vecChild; } // �ڽ� ������Ʈ
    const vector<CScript*>& GetScripts() { return m_vecScript; }

    class CTransform* Transform() { return (CTransform*)GetComponent(TRANSFORM); }    
    class CCamera* Camera() { return (CCamera*)GetComponent(CAMERA); }
    class CCollider2D* Collider2D() { return (CCollider2D*)GetComponent(COLLIDER2D); }
    class CLight2D* Light2D() { return (CLight2D*)GetComponent(LIGHT2D); }

    class CMeshRender* MeshRender() { return (CMeshRender*)GetComponent(MESHRENDER); }
    class CSpriteRender* SpriteRender() { return (CSpriteRender*)GetComponent(SPRITERENDER); }
    class CFlipbookRender* FlipbookRender() { return (CFlipbookRender*)GetComponent(FLIPBOOKRENDER); }
    class CTileRender* TileRender() { return (CTileRender*)GetComponent(TILERENDER); }
    class CParticleRender* ParticleRender() { return (CParticleRender*)GetComponent(PARTICLERENDER); }

    void Destroy();


public:
    void Begin();
    void Tick();
    void FinalTick();
    void Render();

public:
    CLONE(CGameObject);
public:
    CGameObject();
    ~CGameObject();

    friend class CLayer;
    friend class CTaskMgr;
};

