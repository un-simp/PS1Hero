//
// Created by un on 31/07/2025.
//
#pragma once

#include "../third_party/nugget/psyqo/scene.hh"
#include "fragment.h"

class StageScene final : public psyqo::Scene{
    void frame() override;
    void start(StartReason reason) override;

    static SpriteFragment CreateNoteFragment(int pos);

    static void CreateAndScrollNote(int pos);

    static void TickNote();
    };
