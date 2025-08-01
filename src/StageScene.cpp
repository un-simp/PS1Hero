//
// Created by un on 31/07/2025.
//

#include "StageScene.h"

#include "assets.h"
void StageScene::frame() {

}

void StageScene::start(StartReason reason) {
    // TODO: upload the stage and notes to VRAM
    psyqo::Rect region = {.pos = {{770,5}}, .size = {{121,200}}};
    gpu().uploadToVRAM(PS1HeroAssets::getStageData(),region);
}
