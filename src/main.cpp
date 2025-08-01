
#include "../third_party/nugget/psyqo/application.hh"
#include "../third_party/nugget/psyqo/scene.hh"
#include "../third_party/nugget/psyqo/primitives.hh"
#include "FontManager.h"
#include "StageScene.h"
namespace {

// A PSYQo software needs to declare one `Application` object.
class PS1HeroMain final : public psyqo::Application {
    void prepare() override;
    void createScene() override;

  public:
    FontManager m_font;

};

class HelloScene final : public psyqo::Scene {
    void frame() override;

};

PS1HeroMain ps1HeroMain;
HelloScene helloScene;
StageScene stageScene;

}  // namespace

void PS1HeroMain::prepare() {
    psyqo::GPU::Configuration config;
    config.set(psyqo::GPU::Resolution::W320)
        .set(psyqo::GPU::VideoMode::AUTO)
        .set(psyqo::GPU::ColorMode::C15BITS)
        .set(psyqo::GPU::Interlace::PROGRESSIVE);
    gpu().initialize(config);
}

void PS1HeroMain::createScene() {
    m_font.uploadFont(gpu(), {{.x = 767, .y = 256}}, {{.w = 256, .h = 71}});
    pushScene(&stageScene);
}

void HelloScene::frame() {
    psyqo::Color bg{{.r = 0, .g = 64, .b = 91}};
    ps1HeroMain.gpu().clear(bg);
//    hello.m_font.print(hello.gpu(), "Song: I was here (Live in Session)", {{.x = 16, .y = 32}});
//    hello.m_font.print(hello.gpu(), "Artist: Lava Pigeon", {{.x = 16, .y = 64}});
//    hello.m_font.print(hello.gpu(), "Tip: Get to the point John Lennon", {{.x = 16, .y = 79}});
//    hello.m_font.print(hello.gpu(), "Loading...", {{.x = 96, .y = 200}});
    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "the quick brown fox jumps over the lazy dog", {{.x = 0, .y = 100}});
    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "THE QUICK BROWN FOX JUMPS OVER THE LAZY", {{.x = 0, .y = 130}});
    ps1HeroMain.m_font.print(ps1HeroMain.gpu(), "!?/#`\"£$%^&*()@~' dog DOG", {{.x = 0, .y = 150}});


}

int main() { return ps1HeroMain.run(); }
