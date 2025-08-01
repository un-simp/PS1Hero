//
// Created by un on 31/07/2025.
//
#include "../third_party/nugget/psyqo/scene.hh"
class StageScene final : public psyqo::Scene{
    void frame() override;
    void start(StartReason reason) override;
};
