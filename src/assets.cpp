//
// Created by un on 01/08/2025.
//

#include "assets.h"
#include <cstdint>

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
IMPORT_BIN("assets/TestStage2.bin",stageData);
IMPORT_BIN("assets/testNote.bin",noteData);

extern uint16_t fontData[];
extern uint16_t stageData[];
extern uint16_t noteData[];

uint16_t* PS1HeroAssets::getFontData() {
    return fontData;
}

uint16_t* PS1HeroAssets::getStageData() {
    return stageData;
}
uint16_t* PS1HeroAssets::getNoteData() {
    return noteData;
}
