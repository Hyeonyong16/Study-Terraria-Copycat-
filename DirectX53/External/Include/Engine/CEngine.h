#pragma once

class CEngine
	: public singleton<CEngine>
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// ���μ��� �ּ�
	HWND		m_hMainWnd;		// ���� ������ �ڵ�
	Vec2		m_vResolution;	// ���� ������ �ػ�
	
public:
	int Init(HINSTANCE _Inst, UINT _Width, UINT _Height);
	void Progress();

	Vec2 GetResolution() { return m_vResolution; }
	HWND GetMainWndHwnd() { return m_hMainWnd; }

private:
	int CreateMainWindow();
};

