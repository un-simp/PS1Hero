//
// Created by un on 31/07/2025.
//
#pragma once


#include "../third_party/nugget/psyqo/scene.hh"
#include "fragment.h"
#include "note.h"
#include "psyqo/simplepad.hh"

class StageScene final : public psyqo::Scene{

    enum NoteColour {
        BROWN = 101,
        PINK = 125,
        BLUE = 149,
        GREEN = 173,
        YELLOW=197 };
    // static lookup table
   static constexpr eastl::array<eastl::pair<NoteColour,psyqo::SimplePad::Button>,5> ControllerBinds{{
        {BROWN,   psyqo::SimplePad::Button::L1},
        {PINK,    psyqo::SimplePad::Button::L2},
        {BLUE,    psyqo::SimplePad::Button::Triangle},
        {GREEN,   psyqo::SimplePad::Button::R2},
        {YELLOW,  psyqo::SimplePad::Button::R1}}
   };
    static constexpr psyqo::SimplePad::Button posToButton(int notePos) {
        // search through all the binds
        for (const auto& entry : ControllerBinds) {
            // match to control
            if (entry.first == noteColour) {
                return entry.second;
            }
        }

        return 0;
    }
    void frame() override;
    void start(StartReason reason) override;
    static void scoreNote(const NoteTypes &noteType);
    static SpriteFragment CreateNoteFragment(int pos);

    static void CreateAndScrollNote(int pos);

    static void TickNote();

    };
