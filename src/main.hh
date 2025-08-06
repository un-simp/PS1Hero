#pragma once
#include "../third_party/nugget/psyqo/application.hh"
#include "../third_party/nugget/psyqo/scene.hh"
#include "FontManager.h"
#include "StageScene.h"

// A PSYQo software needs to declare one `Application` object.
class PS1HeroMain final : public psyqo::Application {
    void prepare() override;
    void createScene() override;
    // check if we already initialized the hardware
    bool m_init = false;

public:
    FontManager m_font;
    StageScene m_stageScene;

};


extern PS1HeroMain g_ps1hero;