//
//  GameDriver.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/6/23.
//
//

#include "GameDriver.h"
#include "components/all.h"
static Graphics gl;

GameDriver::GameDriver(const char *title, uint32_t w, uint32_t h) : window(gl.initCreateWindow(title, w, h)),
                                                                    launch_timer(ftime::SECONDS),
                                                                    delta_timer(ftime::SECONDS),
                                                                    dt(1.f/60.f),
                                                                    shaders(SHADER_LAST + 1),
                                                                    meshes(MESH_LAST + 1),
                                                                    textures(TEX_LAST + 1),
                                                                    state(shaders, meshes, textures, window,
                                                                          scene, dt, launch_timer)
{
    launch_timer.start();
    gl.loader.setAssetPath("res/");
    gl.loader.setShaderPath("src/shaders/");
}

void GameDriver::exit() {
    userDestroy();
    gl.destroy();
}

bool GameDriver::create() { 
    userCreate();
    return true;
}

void GameDriver::start() {
    while (!window.should_close()) {
        gl.clear();
        userUpdate(dt);
        renderer.render_system(this);
        window.update();
        dt = delta_timer.stop_reset_start();
    }
    exit();
}

GameState::GameState(std::vector<Shader>& sh, std::vector<MeshDetails>& m, std::vector<TEXTURE_SLOT>& t,
                                 Window& w, ECS& sc, float& d, ftime::Stopwatch& sw) :
                                 shaders(sh), meshes(m), textures(t), window(w), scene(sc), dt(d), launch_timer(sw)
{}

void GameDriver::Renderer::use_camera(entID cam) {
    camera = cam;
}

Camera* GameDriver::Renderer::fetch_camera(ECS& scene) {
    Camera* cam = scene.tryGetComp<OrthoCamera>(camera);
    if (!cam)
        cam = scene.tryGetComp<PerspectiveCamera>(camera);
    if (!cam)
        throw("renderer does not have a camera!");
    return cam;
}

void GameDriver::Renderer::sync_camera(ECS& scene) {
    Camera* cam = fetch_camera(scene);
    
    Transform* trans = scene.tryGetComp<Transform>(camera);
    if (trans && trans->pos != cam->readPos())
        cam->getPos() = trans->pos;
    
    cam->update();
    gl.forEachShader([&](Shader s)->void {
        s.uMat4("uView", cam->view());
        s.uMat4("uProj", cam->proj());
    });
}

void GameDriver::Renderer::render_system(GameDriver* eng) {
    sync_camera(eng->scene);
    for (auto e : eng->scene.view<Render>()) {
        auto& render = eng->scene.getComp<Render>(e);
        if (Transform* trans = eng->scene.tryGetComp<Transform>(e))
            trans->sync(eng->shaders[render.shader]);
        if (Texture* tex = eng->scene.tryGetComp<Texture>(e))
            tex->sync(eng->shaders[render.shader]);
        eng->shaders[render.shader].bind();
        gl.DrawMesh(eng->meshes[render.vao]);
    }
}

