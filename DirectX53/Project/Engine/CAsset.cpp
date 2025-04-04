#include "pch.h"
#include "CAsset.h"

#include "CPathMgr.h"

CAsset::CAsset(ASSET_TYPE _Type, bool _EngineAsset)
	: m_Type(_Type)
	, m_EngineAsset(_EngineAsset)
{
}

CAsset::~CAsset()
{
}

void CAsset::SetRelativePathByFilePath(const wstring& _FullPath)
{
	// 입력된 전체경로에서 ContentPath 까지의 경로를 덜어내고, 상대경로만 잘라내서 설정해준다.
	wstring strContentPath = CPathMgr::GetContentPath();
	wstring RelativePath = _FullPath.substr(strContentPath.length(), _FullPath.length());
	SetRelativePath(RelativePath);
}