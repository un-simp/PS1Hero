
#include "../third_party/nugget/psyqo/application.hh"
#include "../third_party/nugget/psyqo/font.hh"
#include "../third_party/nugget/psyqo/gpu.hh"
#include "../third_party/nugget/psyqo/scene.hh"
#include "../third_party/nugget/psyqo/primitives.hh"
#include "FontManager.h"
namespace {

// A PSYQo software needs to declare one `Application` object.
// This is the one we're going to do for our hello world.
class Hello final : public psyqo::Application {
    void prepare() override;
    void createScene() override;

  public:
    psyqo::Font<> m_systemFont;
    psyqo::Font<> m_romFont;
    FontManager m_font;

};

// And we need at least one scene to be created.
// This is the one we're going to do for our hello world.
class HelloScene final : public psyqo::Scene {
    void frame() override;

    // We'll have some simple animation going on, so we
    // need to keep track of our state here.
    uint8_t m_anim = 0;
    bool m_direction = true;
};

// We're instantiating the two objects above right now.
Hello hello;
HelloScene helloScene;

}  // namespace

void Hello::prepare() {
    psyqo::GPU::Configuration config;
    config.set(psyqo::GPU::Resolution::W320)
        .set(psyqo::GPU::VideoMode::AUTO)
        .set(psyqo::GPU::ColorMode::C15BITS)
        .set(psyqo::GPU::Interlace::PROGRESSIVE);
    gpu().initialize(config);
}

void Hello::createScene() {
    // We're going to use two fonts, one from the system, and one from the kernel rom.
    // We need to upload them to VRAM first. The system font is 256x48x4bpp, and the
    // kernel rom font is 256x90x4bpp. We're going to upload them to the same texture
    // page, so we need to make sure they don't overlap. The default location for the
    // system font is {{.x = 960, .y = 464}}, and the default location for the kernel
    // rom font is {{.x = 960, .y = 422}}, so we need to nudge the kernel rom
    // font up a bit.
    // fontknife convert -G " !\"#\$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~" Sapface.ttf font1.png
 //  m_systemFont.uploadSystemFont(gpu());

    m_font.uploadFont(gpu(), {{.x = 767, .y = 256}}, {{.w = 256, .h = 71}});
    //m_romFont.uploadKromFont(gpu(), {{.x = 960, .y = static_cast<int16_t>(512 - 48 - 90)}});
    pushScene(&helloScene);
}

void HelloScene::frame() {
    psyqo::Color bg{{.r = 0, .g = 64, .b = 91}};
    hello.gpu().clear(bg);
//    hello.m_font.print(hello.gpu(), "Song: I was here (Live in Session)", {{.x = 16, .y = 32}});
//    hello.m_font.print(hello.gpu(), "Artist: Lava Pigeon", {{.x = 16, .y = 64}});
//    hello.m_font.print(hello.gpu(), "Tip: Get to the point John Lennon", {{.x = 16, .y = 79}});
//    hello.m_font.print(hello.gpu(), "Loading...", {{.x = 96, .y = 200}});
    hello.m_font.print(hello.gpu(), "the quick brown fox jumps over the lazy dog", {{.x = 0, .y = 100}});
    hello.m_font.print(hello.gpu(), "THE QUICK BROWN FOX JUMPS OVER THE LAZY", {{.x = 0, .y = 130}});
    hello.m_font.print(hello.gpu(), "!?/#`\"£$%^&*()@~' dog DOG", {{.x = 0, .y = 150}});


}

int main() { return hello.run(); }
//    hello.m_systemFont.print(hello.gpu(), "Song: I was here (Live in Session)", {{.x = 16, .y = 32}}, c);
//    hello.m_systemFont.print(hello.gpu(), "Artist: Lava Pigeon", {{.x = 16, .y = 64}}, c);
//    hello.m_systemFont.print(hello.gpu(), "Tip: Get to the point John Lennon", {{.x = 16, .y = 79}}, c);
//    hello.m_systemFont.print(hello.gpu(), "Loading...", {{.x = 96, .y = 200}}, c);
//    hello.m_systemFont.print(hello.gpu(), "the quick brown fox jumps over the lazy dog", {{.x = 0, .y = 100}}, c);
//    hello.m_systemFont.print(hello.gpu(), "THE QUICK BROWN FOX JUMPS OVER THE LAZY", {{.x = 0, .y = 130}}, c);
//    hello.m_systemFont.print(hello.gpu(), "!?/#`\"£$%^&*()@~' dog DOG", {{.x = 0, .y = 150}}, c);