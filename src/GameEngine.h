//
//  GameEngine.h
//  risklike
//
//  Created by Frank Collebrusco on 6/6/23.
//
//

#ifndef GameEngine_h
#define GameEngine_h
#include "../lib/ecs/ECS.h"
#include "../lib/flgl/inc/flgl.h"
#include "../lib/stopwatch/Stopwatch.h"
#include "renderer_enums.h"
#include <unordered_map>
#include <unordered_set>

struct GameState {
    std::vector<Shader>& shaders;
    std::vector<MeshDetails>& meshes;
    std::vector<TEXTURE_SLOT>& textures;
    Window& window;
    ECS& scene;
    float& dt;
    ftime::Stopwatch& launch_timer;
    GameState(std::vector<Shader>&,
              std::vector<MeshDetails>&,
              std::vector<TEXTURE_SLOT>&,
              Window&,
              ECS&,
              float&,
              ftime::Stopwatch&);
};

class GameEngine {
public:
    bool create();
    void start();
    GameEngine(const char* title, uint32_t w = 1280, uint32_t h = 720);

    // game state reference object
    GameState state;

    std::vector<Shader> shaders;
    std::vector<MeshDetails> meshes;
    std::vector<TEXTURE_SLOT> textures;
    Window& window;
    ECS scene;
    float dt;
    ftime::Stopwatch launch_timer;

    class Renderer {
    private:
        entID camera;
        void sync_camera(ECS& scene);
    public:
        void use_camera(entID e);
        Camera* fetch_camera(ECS& scene);
        void render_system(GameEngine* eng);
        void destroy();
    };
    Renderer renderer;
private:
    ftime::Stopwatch delta_timer;
    virtual void userCreate() = 0;
    virtual void userUpdate(float dt) = 0;
    virtual void userDestroy() = 0;
    void exit();
};

#endif /* GameEngine_h */
