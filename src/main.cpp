
#include "main.hh"



PS1HeroMain g_ps1hero;

int main() { return g_ps1hero.run(); }


void PS1HeroMain::prepare() {
    psyqo::GPU::Configuration config;
    config.set(psyqo::GPU::Resolution::W320)
        .set(psyqo::GPU::VideoMode::AUTO)
        .set(psyqo::GPU::ColorMode::C15BITS)
        .set(psyqo::GPU::Interlace::PROGRESSIVE);
    gpu().initialize(config);
}

void PS1HeroMain::createScene() {
    if (!m_init) {
        m_font.uploadFont(gpu(), {{.x = 767, .y = 256}}, {{.w = 256, .h = 71}});
        m_init = true;
    };
    pushScene(&m_stageScene);
}

//void HelloScene::frame() {
//    psyqo::Color bg{{.r = 0, .g = 64, .b = 91}};
//    ps1HeroMain.gpu().clear(bg);
////    hello.m_font.print(hello.gpu(), "Song: I was here (Live in Session)", {{.x = 16, .y = 32}});
////    hello.m_font.print(hello.gpu(), "Artist: Lava Pigeon", {{.x = 16, .y = 64}});
////    hello.m_font.print(hello.gpu(), "Tip: Get to the point John Lennon", {{.x = 16, .y = 79}});
////    hello.m_font.print(hello.gpu(), "Loading...", {{.x = 96, .y = 200}});
//    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "the quick brown fox jumps over the lazy dog", {{.x = 0, .y = 100}});
//    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "THE QUICK BROWN FOX JUMPS OVER THE LAZY", {{.x = 0, .y = 130}});
//    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "!?/#`\"£$%^&*()@~' dog DOG", {{.x = 0, .y = 150}});
//
//
//}


