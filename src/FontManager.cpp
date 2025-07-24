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
// this feels wrong, the actual texture is embedded here at compile time, kill me.
IMPORT_BIN("assets/font.bin",fontData);
void FontManager::uploadFont(psyqo::GPU &gpu, psyqo::Vertex location, psyqo::Vertex size) {
     extern const uint16_t fontData[], _sizeof_fontData[];
     psyqo::Rect region = {.pos = location, .size = size};
     gpu.uploadToVRAM(fontData,region);
}
/**
 * @brief These method immediately print text to the screen.
 *
 * @details These methods immediately print text to the screen. They are meant to be used when not using
 * DMA chaining. When using DMA chaining, you should use the `chainprint` method family instead. When
 * a callback is provided, it will be called when the text has been printed, while the method will return
 * immediately. See the `GPU` class for more details on DMA callbacks.
 */
void FontManager::print(psyqo::GPU &gpu, const char* text, psyqo::Vertex location) {

}
