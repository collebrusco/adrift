#include "RenderSystem.h"

static Graphics gl;

void RenderSystem::use_camera(entID cam) {
    camera = cam;
}

Camera* RenderSystem::fetch_camera(ECS& scene) {
    Camera* cam = scene.tryGetComp<OrthoCamera>(camera);
    if (!cam)
        cam = scene.tryGetComp<PerspectiveCamera>(camera);
    if (!cam)
        throw("RenderSystem does not have a camera!");
    return cam;
}

void RenderSystem::sync_camera(ECS& scene) {
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

void RenderSystem::execute(GameDriver* state) {
    sync_camera(state->scene);
    uint32_t i = 0;
    for (auto e : state->scene.view<Render>()) {
        auto& render = state->scene.getComp<Render>(e);
        if (Transform* trans = state->scene.tryGetComp<Transform>(e))
            trans->sync(state->shaders[render.shader]);
        if (Texture* tex = state->scene.tryGetComp<Texture>(e)) {
            state->shaders[render.shader].uInt("uTexslot", tex->name);
		    state->shaders[render.shader].uIVec2("uSpriteWH", tex->dims);
		    state->shaders[render.shader].uVec2("uSpriteSheetPos", tex->pos);
		}
        state->shaders[render.shader].bind();
        gl.DrawMesh(state->meshes[render.vao]);
    }
}


