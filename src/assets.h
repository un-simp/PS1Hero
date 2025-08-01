//
// Created by un on 01/08/2025.
//
// header only class that embeds all the game assets as static objects in the binary
#ifndef PS1HERO_ASSETS_H
// function that actually does the embedding
#define IMPORT_BIN(file, sym) asm (\
    ".section .rodata." #sym "\n"        /* Change section */\
    ".balign 4\n"                        /* Word alignment */\
    ".global " #sym "\n"                 /* Export the object address */\
    #sym ":\n"                           /* Define the object label */\
    ".incbin \"" file "\"\n"             /* Import the file */\
    ".global " #sym "_size\n"            /* Export the object size */\
    ".set " #sym "_size, . - " #sym "\n" /* Define the object size */   \
    ".balign 4\n"                        /* Word alignment */\
    ".section \".text\"\n")              /* Restore section */
IMPORT_BIN("assets/font.bin",fontData);
#define PS1HERO_ASSETS_H
extern "C" {
extern const uint16_t fontData[];
extern const unsigned int _sizeof_fontData;
}
class ps1heroAssets{
public:
    static const uint16_t* getFontData() { return fontData; }
    static unsigned int getFontDataSize() { return _sizeof_fontData; }
};


#endif //PS1HERO_ASSETS_H
