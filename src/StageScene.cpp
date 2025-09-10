//
// Created by un on 31/07/2025.
//

#include "StageScene.h"
#include "EASTL/vector.h"
#include "assets.h"
#include "main.hh"

TPageFragment StageTPageF;
SpriteFragment StageSpriteF;
eastl::vector<SpriteFragment> notes;



SpriteFragment StageScene::CreateNoteFragment(int pos) {
    SpriteFragment outputFrag;
    psyqo::PrimPieces::TexInfo noteTexInfo;
    noteTexInfo.v = 1;
    psyqo::Prim::Sprite noteSprite;
    // pos 1 is 101, +24 for each pos
//    eastl::string numStr = eastl::to_string(pos);
//    g_ps1hero.m_font.print(g_ps1hero.gpu(),numStr.c_str(), {{0,50}});
    switch (pos){
        case 1:
            noteTexInfo.u = 2;
            noteSprite.position = {{101,13}};
            break;
        case 2:
            noteTexInfo.u = 26;
            noteSprite.position = {{125,13}};
            break;
        case 3:
            noteTexInfo.u = 50;
            noteSprite.position = {{149,13}};
            break;
        case 4:
            noteTexInfo.u = 74;
            noteSprite.position = {{173,13}};
            break;
        case 5:
            noteTexInfo.u = 98;
            noteSprite.position = {{197,13}};
            break;

    }
//    numStr = eastl::to_string(noteSprite.position.x);
//    g_ps1hero.m_font.print(g_ps1hero.gpu(),numStr.c_str(), {{100,50}});
//    numStr = eastl::to_string(noteTexInfo.u);
//    g_ps1hero.m_font.print(g_ps1hero.gpu(),numStr.c_str(), {{150,50}});
    noteSprite.texInfo = noteTexInfo;
    noteSprite.size = {{21,4}};
    outputFrag.sprite = noteSprite;
//    g_ps1hero.gpu().sendFragment(StageTPageF);
    return outputFrag;
}
void StageScene::start(Scene::StartReason reason) {
    // upload notes and stage to vram
    psyqo::Rect StageRegion = {.pos = {{896,5}}, .size = {{121,200}}};
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
    notes.push_back(CreateNoteFragment(1));
    notes.push_back(CreateNoteFragment(2));
    notes.push_back(CreateNoteFragment(3));
    notes.push_back(CreateNoteFragment(4));
    notes.push_back(CreateNoteFragment(5));

}
// make sure you send your tPage before you send your notes
void StageScene::SendNotes(eastl::vector<SpriteFragment> noteFrags) {
    for (const auto &frag: noteFrags) {
        g_ps1hero.gpu().sendFragment(frag);
    }
}

void StageScene::frame() {
    psyqo::Color col = {{.r = 255,.g = 65, .b = 101}};
    g_ps1hero.gpu().clear(col);
    g_ps1hero.gpu().sendFragment(StageTPageF);
    g_ps1hero.gpu().sendFragment(StageSpriteF);
    StageScene::SendNotes(notes);

//    if (notePos.y >= static_cast<int16_t>(180)){
//        NoteSpriteFunc.sprite.position =  {{125+72,13}};
//    }else{
//        int16_t newPos = notePos.y+2;
//        NoteSpriteFunc.sprite.position = {{notePos.x, newPos}};
//    }
//    g_ps1hero.gpu().sendFragment(NoteSpriteFunc);

}


