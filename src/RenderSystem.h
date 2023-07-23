
#ifndef RenderSystem_h
#define RenderSystem_h

#include "../lib/ecs/ECS.h"
#include "../lib/flgl/inc/flgl.h"
#include "../lib/stopwatch/Stopwatch.h"
#include "components/all.h"
#include "renderer_enums.h"
#include "GameDriver.h"

class RenderSystem {
private:
    entID camera;
    void sync_camera(ECS& scene);
public:
    void use_camera(entID e);
    Camera* fetch_camera(ECS& scene);
    void execute(GameDriver* state);
    void destroy();
};

#endif // RenderSystem_h