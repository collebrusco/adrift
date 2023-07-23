//
//  GameDriver.h
//  risklike
//
//  Created by Frank Collebrusco on 6/6/23.
//
//

#ifndef GameDriver_h
#define GameDriver_h
#include "../lib/ecs/ECS.h"
#include "../lib/flgl/inc/flgl.h"
#include "../lib/stopwatch/Stopwatch.h"
#include "renderer_enums.h"
#include <unordered_map>
#include <unordered_set>

class GameDriver {
public:
    bool create();
    void start();
    GameDriver(const char* title, uint32_t w = 1280, uint32_t h = 720);

    std::vector<Shader> shaders;
    std::vector<MeshDetails> meshes;
    std::vector<TEXTURE_SLOT> textures;
    Window& window;

    ECS scene;
    float dt;
    ftime::Stopwatch launch_timer;

private:
    ftime::Stopwatch delta_timer;
    virtual void userCreate() = 0;
    virtual void userUpdate(float dt) = 0;
    virtual void userDestroy() = 0;
    void exit();
};

#endif /* GameDriver_h */
