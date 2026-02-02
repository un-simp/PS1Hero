
#include "main.hh"



PS1HeroMain g_ps1hero;

int main() { return g_ps1hero.run(); }


void PS1HeroMain::prepare() {
    psyqo::GPU::Configuration config;
    // 320p is a common resolution for PS1 games
    config.set(psyqo::GPU::Resolution::W320)
    // Will dynamically change between PAL and NTSC depending on console
        .set(psyqo::GPU::VideoMode::AUTO)
    // 15 bits of colour, 32768 possible colors for each pixel.
        .set(psyqo::GPU::ColorMode::C15BITS)
    // progressive scan instead of interlacing frames - looks better on modern televisions and screens
        .set(psyqo::GPU::Interlace::PROGRESSIVE);
    gpu().initialize(config);
}

void PS1HeroMain::createScene() {
    // prevents font uploading and pad init from being executed twice on initialisation
    if (!m_init) {
        m_font.uploadFont(gpu(), {{.x = 767, .y = 256}}, {{.w = 256, .h = 71}});
        m_pad.initialize();
        m_init = true;

    };
    // main scene starts
    pushScene(&m_stageScene);
}

//void HelloScene::frame() {
//    psyqo::Color bg{{.r = 0, .g = 64, .b = 91}};
//    ps1HeroMain.gpu().clear(bg);
////     hello.m_font.print(hello.gpu(), "Song: I was here (Live in Session)", {{.x = 16, .y = 32}});
////    hello.m_font.print(hello.gpu(), "Artist: Lava Pigeon", {{.x = 16, .y = 64}});
////    hello.m_font.print(hello.gpu(), "Tip: Get to the point John Lennon", {{.x = 16, .y = 79}});
////    hello.m_font.print(hello.gpu(), "Loading...", {{.x = 96, .y = 200}});
//    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "the quick brown fox jumps over the lazy dog", {{.x = 0, .y = 100}});
//    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "THE QUICK BROWN FOX JUMPS OVER THE LAZY", {{.x = 0, .y = 130}});
//    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "!?/#`\"£$%^&*()@~' dog DOG", {{.x = 0, .y = 150}});
//
//
//}


