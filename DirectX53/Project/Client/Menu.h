#pragma once
#include "EditorUI.h"

class CLevel;

class Menu :
    public EditorUI
{
private:
    bool    m_SpriteEditor;
    bool    m_FlipbookEditor;

    CLevel* m_CloneLevel;

private:
    void File();
    void Level();
    void Editor();
    void Script();
    void Asset();

    string GetMaterialName();


public:
    virtual void Render() override;
    virtual void Update_UI() override;
    virtual void Render_UI() override;

public:
    Menu();
    ~Menu();
};

