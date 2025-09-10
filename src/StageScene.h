//
// Created by un on 31/07/2025.
//
#pragma once

#include "../third_party/nugget/psyqo/scene.hh"
#include "fragment.h"

class StageScene final : public psyqo::Scene{
    void frame() override;
    void start(StartReason reason) override;
    SpriteFragment CreateNoteFragment(int pos);
    void SendNotes(eastl::vector<SpriteFragment> noteFrags);

    };
