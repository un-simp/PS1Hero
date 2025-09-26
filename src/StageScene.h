//
// Created by un on 31/07/2025.
//
#pragma once

#include "../third_party/nugget/psyqo/scene.hh"
#include "fragment.h"

class StageScene final : public psyqo::Scene{
    enum Notes {
        BROWN = 101,
        PINK = 125,
        BLUE = 149,
        GREEN = 173,
        YELLOW=197 };

    void frame() override;
    void start(StartReason reason) override;
    static void scoreNote();
    static SpriteFragment CreateNoteFragment(int pos);

    static void CreateAndScrollNote(int pos);

    static void TickNote();

    };
