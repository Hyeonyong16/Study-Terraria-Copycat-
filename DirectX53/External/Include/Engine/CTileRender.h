#pragma once
#include "CRenderComponent.h"

#include "CSprite.h"
#include "CTexture.h"
#include "CStructuredBuffer.h"

struct tTileInfo
{
    Ptr<CSprite>    Sprite;
};

class CTileRender :
    public CRenderComponent
{
private:
    UINT                m_Col;          // ��
    UINT                m_Row;          // ��
    Vec2                m_TileSize;     // Ÿ�� 1���� ũ��
    vector<tTileInfo*>  m_vecTileInfo;  // �� Ÿ���� ����
    CStructuredBuffer*  m_GpuBuffer;    // Ÿ�� ������ �����ϰ� �ؽ��� �������ͷ� ���ε��ϱ� ����


public:
    void SetColRow(UINT _Col, UINT _Row);
    void SetTileSize(Vec2 _TileSize);
    void SetSprite(UINT _Col, UINT _Row, Ptr<CSprite> _Sprite);  

public:
    virtual void FinalTick() override;
    virtual void Render() override;

private:
    void CreateTileRenderMtrl();
    void UpdateBuffer();
    Ptr<CTexture> GetAtlasTex();



public:
    CLONE(CTileRender);
    CTileRender();
    ~CTileRender();
};

