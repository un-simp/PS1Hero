#pragma once
#include "../third_party/nugget/psyqo/application.hh"
#include "FontManager.h"
#include "StageScene.h"
#include "psyqo/simplepad.hh"

// A PSYQo software needs to declare one `Application` object.
class PS1HeroMain final : public psyqo::Application {
    void prepare() override;
    void createScene() override;
    // check if we already initialized the hardware
    bool m_init = false;

public:
    FontManager m_font;
    StageScene m_stageScene;
    psyqo::SimplePad m_pad;

};


extern PS1HeroMain g_ps1hero;