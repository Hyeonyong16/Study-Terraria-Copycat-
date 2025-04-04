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
	// �Էµ� ��ü��ο��� ContentPath ������ ��θ� �����, ����θ� �߶󳻼� �������ش�.
	wstring strContentPath = CPathMgr::GetContentPath();
	wstring RelativePath = _FullPath.substr(strContentPath.length(), _FullPath.length());
	SetRelativePath(RelativePath);
}