#include "pch.h"
#include "CSprite.h"

#include "CAssetMgr.h"

CSprite::CSprite(bool _EngineAsset)
    : CAsset(ASSET_TYPE::SPRITE, _EngineAsset)
{
}

CSprite::~CSprite()
{
}

void CSprite::SetLeftTop(Vec2 _LeftTopPixel)
{
    if (nullptr == m_Atlas)
    {
        m_LeftTop = Vec2(0.f, 0.f);
        m_Slice = Vec2(0.f, 0.f);
        m_Background = Vec2(0.f, 0.f);
        m_Offset = Vec2(0.f, 0.f);
        return;
    } 

    m_LeftTop = _LeftTopPixel / Vec2(m_Atlas->GetWidth(), m_Atlas->GetHeight());
}

void CSprite::SetSlice(Vec2 _SlicePixel)
{
    if (nullptr == m_Atlas)
    {
        m_LeftTop = Vec2(0.f, 0.f);
        m_Slice = Vec2(0.f, 0.f);
        m_Background = Vec2(0.f, 0.f);
        m_Offset = Vec2(0.f, 0.f);
        return;
    }

    m_Slice = _SlicePixel / Vec2(m_Atlas->GetWidth(), m_Atlas->GetHeight());
}

void CSprite::SetOffset(Vec2 _OffsetPixel)
{
    if (nullptr == m_Atlas)
    {
        m_LeftTop = Vec2(0.f, 0.f);
        m_Slice = Vec2(0.f, 0.f);
        m_Background = Vec2(0.f, 0.f);
        m_Offset = Vec2(0.f, 0.f);
        return;
    }
    m_Offset = _OffsetPixel / Vec2(m_Atlas->GetWidth(), m_Atlas->GetHeight());
}

void CSprite::SetBackground(Vec2 _BackgroundPixel)
{
    if (nullptr == m_Atlas)
    {
        m_LeftTop = Vec2(0.f, 0.f);
        m_Slice = Vec2(0.f, 0.f);
        m_Background = Vec2(0.f, 0.f);
        m_Offset = Vec2(0.f, 0.f);
        return;
    }

    m_Background = _BackgroundPixel / Vec2(m_Atlas->GetWidth(), m_Atlas->GetHeight());
}

int CSprite::Save(const wstring& _FilePath)
{
    SetRelativePathByFilePath(_FilePath);    

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, _FilePath.c_str(), L"wb");


    SaveAssetRef(m_Atlas, pFile);

    fwrite(&m_LeftTop, sizeof(Vec2), 1, pFile);
    fwrite(&m_Slice, sizeof(Vec2), 1, pFile);
    fwrite(&m_Offset, sizeof(Vec2), 1, pFile);
    fwrite(&m_Background, sizeof(Vec2), 1, pFile);

    fclose(pFile);

    return S_OK;
}

int CSprite::Load(const wstring& _FilePath)
{
    FILE* pFile = nullptr;
    _wfopen_s(&pFile, _FilePath.c_str(), L"rb");

    // 파일 스트림 열기 실패 시
    if (nullptr == pFile)
        return E_FAIL;

    m_Atlas = LoadAssetRef<CTexture>(pFile);

    fread(&m_LeftTop, sizeof(Vec2), 1, pFile);
    fread(&m_Slice, sizeof(Vec2), 1, pFile);
    fread(&m_Offset, sizeof(Vec2), 1, pFile);
    fread(&m_Background, sizeof(Vec2), 1, pFile);

    fclose(pFile);

    return S_OK;
}