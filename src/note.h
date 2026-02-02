//
// Created by un on 26/09/2025.
//

#ifndef PS1HERO_NOTE_H
#define PS1HERO_NOTE_H
#include "fragment.h"
enum NoteTypes {
    REGULAR,
    CHORD,
    HOPO // note that dosent require strumming
};
struct Note {
    NoteTypes type = REGULAR;
    SpriteFragment noteFrag;
};


#endif //PS1HERO_NOTE_H