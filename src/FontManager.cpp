//
// Created by un on 20/07/2025.
//
// ok so you know how we are embedding at compile time? yeah im importing this with assembly, this is so fucking cursed
#define IMPORT_BIN(file, sym) asm (\
    ".section .rodata." #sym "\n"        /* Change section */\
    ".balign 4\n"                        /* Word alignment */\
    ".global " #sym "\n"                 /* Export the object address */\
    #sym ":\n"                           /* Define the object label */\
    ".incbin \"" file "\"\n"             /* Import the file */\
    ".global " #sym "_size\n"            /* Export the object size */\
    ".set " #sym "_size, . - " #sym "\n" /* Define the object size */\
    ".balign 4\n"                        /* Word alignment */\
    ".section \".text\"\n")              /* Restore section */
#include "FontManager.h"
#include "psyqo/gpu.hh"
#include "../third_party/nugget/psyqo/primitives.hh"

// this feels wrong, the actual texture is embedded here at compile time, kill me.
IMPORT_BIN("assets/font.bin",fontData);
void FontManager::uploadFont(psyqo::GPU &gpu, psyqo::Vertex location, psyqo::Vertex size) {
     extern const uint16_t fontData[], _sizeof_fontData[];
     psyqo::Rect region = {.pos = location, .size = size};
     gpu.uploadToVRAM(fontData,region);
}
/**
 * @brief These method immediately print text to the screen.
 */
void FontManager::print(psyqo::GPU &gpu, const char* text, psyqo::Vertex location) {
    TPageFragment pageFrag;
    psyqo::Prim::TPage page;
    psyqo::PrimPieces::TPageAttr pageAttr;
    /**
     * when you want to draw something, instead of just giving the gpu the coords of the sprite, vram is split into a 16x2 grid of pixels
     * so you have to tell the gpu to select the areas of the grid you want to read from
     * then tell the gpu the coords of the sprite from that grid so it actually draws it
     * this command only needs to be sent to the gpu once if you are selecting from the same texture multiple times
     * gpu.sendFragment() "should" be blocking but this feels like a race condition waiting to happen, but ill deal with it when we get there
     */
    pageAttr.setPageX(12)
            .setPageY(1)
            // 16 bit textures can cross up to 4 texture pages
            .set(psyqo::Prim::TPageAttr::Tex16Bits);
    page.attr = pageAttr;
    pageFrag.page = page;
    gpu.sendFragment(pageFrag);
    const char* c = &text[0];
    while(*c != '\0') {
        //pull current character from lookup
        const int charIndex = *c - 0x20;
        const int* lookup = asciiLookup[charIndex];
        SpriteFragment spriteFrag;
        psyqo::Prim::Sprite sprite;
        psyqo::PrimPieces::TexInfo texInfo;
        texInfo.u = lookup[0];
        texInfo.v = lookup[1];
        sprite.texInfo = texInfo;
        sprite.position = location;
        // this vertex expects it to be a 16bit int
        sprite.size = {static_cast<int16_t>(lookup[2]), static_cast<int16_t>(lookup[3])};
        spriteFrag.sprite = sprite;
        gpu.sendFragment(spriteFrag);
        ++c;
        location = {static_cast<int16_t>(location.x + 15),location.y };
    }
}
