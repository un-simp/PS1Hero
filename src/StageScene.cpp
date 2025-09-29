//
// Created by un on 31/07/2025.
//

#include "StageScene.h"
#include "EASTL/deque.h"
#include "assets.h"
#include "main.hh"
#include "note.h"
TPageFragment StageTPageF;
SpriteFragment StageSpriteF;
int mult;
int score;
int combo;
eastl::deque<Note> noteArr;

SpriteFragment StageScene::CreateNoteFragment(int pos) {
    SpriteFragment outputFrag;
    psyqo::PrimPieces::TexInfo noteTexInfo;
    noteTexInfo.v = 1;
    psyqo::Prim::Sprite noteSprite;
    // pos 1 is 101, +24 for each pos
    // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
    switch (pos){
        case 1:
            noteTexInfo.u = 2;
            noteSprite.position = {{Notes::BROWN,13}};
            break;
        case 2:
            noteTexInfo.u = 26;
            noteSprite.position = {{Notes::PINK,13}};
            break;
        case 3:
            noteTexInfo.u = 50;
            noteSprite.position = {{Notes::BLUE,13}};
            break;
        case 4:
            noteTexInfo.u = 74;
            noteSprite.position = {{Notes::GREEN,13}};
            break;
        case 5:
            noteTexInfo.u = 98;
            noteSprite.position = {{Notes::YELLOW,13}};
            break;

    }
    noteSprite.texInfo = noteTexInfo;
    noteSprite.size = {{21,4}};
    outputFrag.sprite = noteSprite;
    return outputFrag;
}

void StageScene::CreateAndScrollNote(int pos) {
    noteArr.push_back(Note{REGULAR,CreateNoteFragment(pos)});
}

void StageScene::TickNote() {
    for (auto it = noteArr.begin(); it != noteArr.end(); ) {
        auto &[type, noteFrag] = *it;
        SpriteFragment &note = noteFrag;
        g_ps1hero.gpu().sendFragment(note);
        // are you in the note acceptor range?
        note.sprite.position.y += 2;
        if (note.sprite.position.y >= static_cast<int16_t>(186)) {
            // did you press the key in time? if so hit
            if (g_ps1hero.m_pad.isButtonPressed(psyqo::SimplePad::Pad1,posToButton(note.sprite.position.x))) {
                scoreNote(type);
            }

            } else if (note.sprite.position.y >= static_cast<int16_t>(200)) {
                // went pass the note acceptor, miss
                it = noteArr.erase(it);
            }else {
                ++it;
            }

        }
    }

void StageScene::start(Scene::StartReason reason) {
    // upload notes and stage to vram
    psyqo::Rect StageRegion = {.pos = {{896,5}}, .size = {{121,190}}};
    g_ps1hero.gpu().uploadToVRAM(PS1HeroAssets::getStageData(),StageRegion);
    psyqo::Rect NoteRegion = {.pos = {{898,1}}, .size = {{120,4}}};
    g_ps1hero.gpu().uploadToVRAM(PS1HeroAssets::getNoteData(),NoteRegion);
    // we generate the fragments for the stage at scene start since they don't change at all
    psyqo::Prim::TPage StageTPage;
    psyqo::PrimPieces::TPageAttr StageAttr;
    psyqo::Prim::Sprite StageSprite;
    psyqo::PrimPieces::TexInfo StageTexInfo;
    StageAttr.setPageY(0)
             .setPageX(14)
             .set(psyqo::Prim::TPageAttr::Tex16Bits);
    StageTPage.attr = StageAttr;
    StageTPageF.page = StageTPage;
    StageTexInfo.u = 0;
    StageTexInfo.v = 5;
    StageSprite.texInfo = StageTexInfo;
    StageSprite.size = {{121,200}};
    StageSprite.position = {{99,10}};
    StageSpriteF.sprite = StageSprite;
    mult =1;
    score=0;
    CreateAndScrollNote(1);
}

void StageScene::scoreNote(const NoteTypes &noteType) {
    switch (noteType) {
        case NoteTypes::REGULAR:
            score = score + (10*mult);
            break;
        case NoteTypes::CHORD:
            // makes this easier by having the total of 30 being 15 handled in both notes (i dont want to do combo logic please)
            score = score + (15*mult);
        default: break;
    }

    ++combo;
    if ((combo % 10) == 0 & combo <50) {
        mult = mult+1;
    }
}


void StageScene::frame() {
    psyqo::Color col = {{.r = 255,.g = 65, .b = 101}};
    g_ps1hero.gpu().clear(col);
    g_ps1hero.gpu().sendFragment(StageTPageF);
    g_ps1hero.gpu().sendFragment(StageSpriteF);
    // run note logic
    TickNote();


}


