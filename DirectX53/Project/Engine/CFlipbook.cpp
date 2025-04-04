#include "pch.h"
#include "CFlipbook.h"

#include "CAssetMgr.h"

CFlipbook::CFlipbook(bool _EngineAsset)
    : CAsset(ASSET_TYPE::FLIPBOOK, _EngineAsset)
{
}

CFlipbook::~CFlipbook()
{
}


int CFlipbook::Save(const wstring& _FilePath)
{
    FILE* pFile = nullptr;
    _wfopen_s(&pFile, _FilePath.c_str(), L"wb");

    // 스프라이트 개수
    size_t Count = m_vecSprite.size();
    fwrite(&Count, sizeof(size_t), 1, pFile);

    // 스프라이트 각각 정보
    for (size_t i = 0; i < m_vecSprite.size(); ++i)
    {
        SaveAssetRef(m_vecSprite[i], pFile);
    }

    fclose(pFile);

    return S_OK;
}

int CFlipbook::Load(const wstring& _FilePath)
{
    SetRelativePathByFilePath(_FilePath);

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, _FilePath.c_str(), L"rb");

    // 파일 스트림 열기 실패 시
    if (nullptr == pFile)
        return E_FAIL;

    // 스프라이트 개수
    size_t Count = 0;
    fread(&Count, sizeof(size_t), 1, pFile);

    // 스프라이트 각각 정보
    for (size_t i = 0; i < Count; ++i)
    {
        AddSprite(LoadAssetRef<CSprite>(pFile));        
    }

    fclose(pFile);

    return S_OK;
}
