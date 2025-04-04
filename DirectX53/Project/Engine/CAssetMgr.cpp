#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"

CAssetMgr::CAssetMgr()
	: m_AssetChanged(false)
{

}

CAssetMgr::~CAssetMgr()
{

}

void CAssetMgr::AddAsset(const wstring& _Key, Ptr<CAsset> _Asset)
{
	ASSET_TYPE Type = _Asset->GetType();

	map<wstring, Ptr<CAsset>>::iterator iter  = m_mapAsset[Type].find(_Key);

	assert(iter == m_mapAsset[Type].end());

	_Asset->m_Key = _Key;
	m_mapAsset[Type].insert(make_pair(_Key, _Asset));

	m_AssetChanged = true;
}

Ptr<CAsset> CAssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{	
	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[_Type].find(_Key);

	if (iter == m_mapAsset[_Type].end())
		return nullptr;

	return iter->second.Get();
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height
									, DXGI_FORMAT _Format, UINT _BindFlag, D3D11_USAGE _Usage)
{
	Ptr<CTexture> pTex = FindAsset<CTexture>(_Key);
	if (nullptr != pTex)
		return pTex;

	pTex = new CTexture;
	if (FAILED(pTex->Create(_Width, _Height, _Format, _BindFlag, _Usage)))
	{
		MessageBox(nullptr, _Key.c_str(), L"텍스쳐 생성 실패", MB_OK);
		return nullptr;
	}

	AddAsset(_Key, pTex.Get());

	return pTex;
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _Key, ComPtr<ID3D11Texture2D> _tex2D)
{
	Ptr<CTexture> pTex = FindAsset<CTexture>(_Key);
	if (nullptr != pTex)
		return pTex;

	pTex = new CTexture;
	if (FAILED(pTex->Create(_tex2D)))
	{
		MessageBox(nullptr, _Key.c_str(), L"텍스쳐 생성 실패", MB_OK);
		return nullptr;
	}

	AddAsset(_Key, pTex.Get());

	return pTex;	
}

void CAssetMgr::GetAssetName(ASSET_TYPE _Type, vector<string>& _vecNames)
{
	map<wstring, Ptr<CAsset>>& mapAsset = m_mapAsset[_Type];

	for (const auto& pair : mapAsset)
	{
		_vecNames.push_back(string(pair.first.begin(), pair.first.end()));
	}
}

void CAssetMgr::DeleteAsset(Ptr<CAsset> _Asset)
{
	DeleteAsset(_Asset->GetType(), _Asset->GetKey());
}

void CAssetMgr::DeleteAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);

	if (iter == m_mapAsset[(UINT)_Type].end())
	{
		assert(nullptr);
		return;
	}

	m_mapAsset[(UINT)_Type].erase(iter);

	m_AssetChanged = true;
}

