//
// Created by un on 03/08/2025.
//

#ifndef PS1HERO_FRAGMENT_H
#include "psyqo/gpu.hh"
#include "../third_party/nugget/psyqo/primitives.hh"
#define PS1HERO_FRAGMENT_H
struct QuadFragment {
    uint32_t head;
    psyqo::Prim::TexturedQuad quad;
    size_t getActualFragmentSize() const {
        return sizeof(quad) /  sizeof(uint32_t);
    }
};
struct SpriteFragment {
    uint32_t head;
    psyqo::Prim::Sprite sprite;
    size_t getActualFragmentSize() const {
        return sizeof(sprite) /  sizeof(uint32_t);
    }
};
struct TPageFragment {
    uint32_t head;
    psyqo::Prim::TPage page;
    size_t getActualFragmentSize() const {
        return sizeof(page) /  sizeof(uint32_t);
    }
};
#endif //PS1HERO_FRAGMENT_H
