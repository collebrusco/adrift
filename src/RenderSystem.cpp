#include "RenderSystem.h"

static Graphics gl;

RenderSystem::RenderSystem() {
    post_processing_shader = gl.loader.UploadShader("fullscreen_vert", "tex_frag.glsl");
}

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

void RenderSystem::resize_preprocess_buffer() {
    auto& win = gl.getWindow();
    if (!preprocess_buffer.active()) {        
        preprocess_buffer.create(win.frame.x, win.frame.y, true);
    }
    if (win.frame.x != preprocess_buffer.w() || win.frame.y != preprocess_buffer.h()) {
        preprocess_buffer.destroy();
        preprocess_buffer.create(win.frame.x, win.frame.y, true);
    }
}

void RenderSystem::execute(GameDriver* state) {
    sync_camera(state->scene);
    // resize_preprocess_buffer();
    preprocess_buffer.bind();
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
    preprocess_buffer.unbind();
    post_processing_shader.uInt("uTexslot", preprocess_buffer.texture_id());
    post_processing_shader.uIVec2("uSpriteWH", glm::ivec2(1024, 1024));
    post_processing_shader.uVec2("uSpriteSheetPos", glm::vec2(0.f));
    gl.std.drawTile();
}


