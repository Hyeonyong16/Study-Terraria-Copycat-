#include "pch.h"
#include "Menu.h"

#include <commdlg.h>

#include <Engine/CPathMgr.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CGameObject.h>
#include <Engine/CScript.h>

#include <Engine/CTaskMgr.h>
#include <Lecture/CScriptMgr.h>

#include "ImGuiMgr.h"
#include "Inspector.h"

#include "CLevelSaveLoad.h"



Menu::Menu()
    : m_SpriteEditor(false)
    , m_FlipbookEditor(false)
    , m_CloneLevel(nullptr)
{
}

Menu::~Menu()
{
    if (nullptr != m_CloneLevel)
    {
        delete m_CloneLevel;
    }
}


void Menu::Render()
{
	if (!IsActive())
		return;
     
    if (ImGui::BeginMainMenuBar())
    {
        Render_UI();

        ImGui::EndMainMenuBar();
    }
}

void Menu::Update_UI()
{
}

void Menu::Render_UI()
{
    File();

    Level();

    Editor();

    Script();

    Asset();
}

void Menu::File()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Level Save"))
        {
            wstring strContentPath = CPathMgr::GetContentPath();
            strContentPath += L"Level";

            // 파일 경로 문자열
            wchar_t szFilePath[255] = {};

            OPENFILENAME Desc = {};

            Desc.lStructSize = sizeof(OPENFILENAME);
            Desc.hwndOwner = nullptr;
            Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
            Desc.nMaxFile = 255;
            Desc.lpstrFilter = L"Level\0*.lv\0ALL\0*.*";
            Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            Desc.lpstrInitialDir = strContentPath.c_str();

            if (GetSaveFileName(&Desc))
            {
                CLevelSaveLoad::SaveLevel(szFilePath);                
            }            

            wstring strBinPath = CPathMgr::GetBinPath();
            SetCurrentDirectory(strBinPath.c_str());
        }

        if (ImGui::MenuItem("Level Load"))
        {
            wstring strContentPath = CPathMgr::GetContentPath();
            strContentPath += L"Level";

            // 파일 경로 문자열
            wchar_t szFilePath[255] = {};

            OPENFILENAME Desc = {};

            Desc.lStructSize = sizeof(OPENFILENAME);
            Desc.hwndOwner = nullptr;
            Desc.lpstrFile = szFilePath;
            Desc.nMaxFile = 255;
            Desc.lpstrFilter = L"Level\0*.lv\0ALL\0*.*";
            Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            Desc.lpstrInitialDir = strContentPath.c_str();

            if (GetOpenFileName(&Desc))
            {
                CLevel* pNextLevel = CLevelSaveLoad::LoadLevel(szFilePath);

                tTask task = {};
                task.Type = TASK_TYPE::CHANGE_LEVEL;
                task.Param0 = (DWORD_PTR)pNextLevel;

                CTaskMgr::GetInst()->AddTask(task);
            }            

            wstring strBinPath = CPathMgr::GetBinPath();
            SetCurrentDirectory(strBinPath.c_str());
        }

        ImGui::EndMenu();
    }
}

void Menu::Level()
{
    if (ImGui::BeginMenu("Level"))
    {
        CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();        
        LEVEL_STATE State = pCurLevel->GetState();

        bool IsPlay = State == LEVEL_STATE::PLAY;
        bool IsPause = State == LEVEL_STATE::PAUSE;
        bool IsStop = State == LEVEL_STATE::STOP;

        tTask task = {};
        task.Type = TASK_TYPE::CHANGE_LEVEL_STATE;

        if (ImGui::MenuItem("Play", nullptr, &IsPlay, IsPause || IsStop))
        {
            // 현재 레벨을 복사해둠
            CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            m_CloneLevel = pCurLevel->Clone();

            task.Param0 = (DWORD_PTR)LEVEL_STATE::PLAY;
            CTaskMgr::GetInst()->AddTask(task);
        }

        if (ImGui::MenuItem("Pause", nullptr, &IsPause, IsPlay))
        {
            task.Param0 = (DWORD_PTR)LEVEL_STATE::PAUSE;
            CTaskMgr::GetInst()->AddTask(task);
        }

        if (ImGui::MenuItem("Stop", nullptr, &IsStop, IsPlay || IsPause))
        {
            // Play 버튼을 눌렀을 당시 상태를 복제해놨던 레벨로 다시 변경한다.
            tTask LevelChanetask = {};
            LevelChanetask.Type = TASK_TYPE::CHANGE_LEVEL;
            LevelChanetask.Param0 = (DWORD_PTR)m_CloneLevel;
            m_CloneLevel = nullptr;
            CTaskMgr::GetInst()->AddTask(LevelChanetask);

            // 변경한 레벨을 Stop 상태로 만든다.            
            task.Param0 = (DWORD_PTR)LEVEL_STATE::STOP;
            CTaskMgr::GetInst()->AddTask(task);

            // Inspector 가 보여주는 오브젝트를 날린다.
            Inspector* pInspector = ImGuiMgr::GetInst()->FindUI<Inspector>("Inspector");
            pInspector->SetTargetObject(nullptr);
        }

        ImGui::EndMenu();
    }
}

void Menu::Editor()
{
    if (ImGui::BeginMenu("Editor"))
    {
        if (ImGui::MenuItem("Sprite Editor", nullptr, &m_SpriteEditor))
        {
            if (m_SpriteEditor)
            {

            }
            else
            {

            }
        }

        if (ImGui::MenuItem("Flipbook Editor", nullptr, &m_FlipbookEditor))
        {
            if (m_FlipbookEditor)
            {

            }
            else
            {

            }
        }

        ImGui::EndMenu();
    }
}

void Menu::Script()
{
    if (ImGui::BeginMenu("Scripts"))
    {
        vector<wstring> vecScriptName;
        CScriptMgr::GetScriptInfo(vecScriptName);

        for (int i = 0; i < vecScriptName.size(); ++i)
        {
            if (ImGui::MenuItem(ToString(vecScriptName[i]).c_str()))
            {
                Inspector* pInspector = ImGuiMgr::GetInst()->FindUI<Inspector>("Inspector");

                CGameObject* pObject = pInspector->GetTargetObject();

                if (nullptr != pObject)
                {
                    pObject->AddComponent(CScriptMgr::GetScript(vecScriptName[i]));
                    pInspector->SetTargetObject(pObject);
                }
            }
        }    

        ImGui::EndMenu();
    }
}

void Menu::Asset()
{
    if (ImGui::BeginMenu("Asset"))
    {
        if (ImGui::MenuItem("Create Material"))
        {
            Ptr<CMaterial> pMtrl = new CMaterial;
            string MtrlName = GetMaterialName();
            CAssetMgr::GetInst()->AddAsset(ToWString(MtrlName), pMtrl.Get());

            wstring MtrlPath = CPathMgr::GetContentPath();
            MtrlPath = MtrlPath + L"Material\\" + ToWString(MtrlName) + L".mtrl";
            pMtrl->Save(MtrlPath);
        }

        ImGui::EndMenu();
    }
}

string Menu::GetMaterialName()
{
    char szMtrlName[255] = {};

    int i = 0;
    while (true)
    {
        sprintf_s(szMtrlName, 255, "Default Material %d", i++);
        
        Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(ToWString(szMtrlName));

        if (nullptr == pMtrl)
            break;
    }

    return szMtrlName;
}
