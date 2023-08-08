#include "RenderSystem.h"

static Graphics gl;

RenderSystem::RenderSystem() {}

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
#include <iostream>
void RenderSystem::resize_preprocess_buffer() {
    auto& win = gl.getWindow();
    // std::cout << "got window\n";
    if (!preprocess_buffer.active()) {        
        // std::cout << "checked if buffer active, no\n";
        preprocess_buffer.create(win.frame.x, win.frame.y, true);
        // std::cout << "created at " << preprocess_buffer.w() << " by " << preprocess_buffer.h() << "\n";
    }
    assert(preprocess_buffer.active());
    // if (win.frame.x != preprocess_buffer.w() || win.frame.y != preprocess_buffer.h()) {
    //     std::cout << "recreating:\n";
    //     preprocess_buffer.destroy();
    //     std::cout << "destroyed,\n";
    //     preprocess_buffer.create(win.frame.x, win.frame.y, true);
    //     std::cout << "recreated.\n";
    // }
}

void RenderSystem::execute(GameDriver* state) {
    static int a = 0;
    sync_camera(state->scene);
    resize_preprocess_buffer();
    // std::cout << "binding framebuffer...\n";
    preprocess_buffer.bind();
    preprocess_buffer.clear();
    glViewport(0, 0, preprocess_buffer.w(), preprocess_buffer.h());

    uint32_t i = 0;
    // std::cout << "drawing to framebuffer...\n";
    for (auto e : state->scene.view<Render>()) {
        auto& render = state->scene.getComp<Render>(e);
        state->shaders[render.shader].bind();
        if (Transform* trans = state->scene.tryGetComp<Transform>(e))
            trans->sync(state->shaders[render.shader]);
        if (Texture* tex = state->scene.tryGetComp<Texture>(e)) {
            state->shaders[render.shader].bind();
            state->shaders[render.shader].uInt("uTexslot", preprocess_buffer.slot());
            glBindTexture(GL_TEXTURE_2D, 1);
		    state->shaders[render.shader].uIVec2("uSpriteWH", tex->dims);
		    state->shaders[render.shader].uVec2("uSpriteSheetPos", tex->pos);
		}
        gl.DrawMesh(state->meshes[render.vao]);
    }
    preprocess_buffer.unbind();
    // std::cout << "drawing to viewport, tex slot " << preprocess_buffer.slot() << "\n";
    state->shaders[SHADER_POSTPROCESS].bind();
    // state->shaders[SHADER_POSTPROCESS].uInt("uTexslot", preprocess_buffer.slot());
    if (gl.getWindow().keyboard[GLFW_KEY_L].pressed) a ^= 0x01;
            auto& tex = state->textures[TEX_ATLAS];
            state->shaders[SHADER_SHIP].uIVec2("uSpriteWH", glm::ivec2(256));
            state->shaders[SHADER_SHIP].uVec2("uSpriteSheetPos", glm::vec2(0.));
    state->shaders[SHADER_POSTPROCESS].uInt("uTexslot",  a);
    // glViewport(0, 0, preprocess_buffer.w(), preprocess_buffer.h());
    // glActiveTexture(GL_TEXTURE0 + preprocess_buffer.slot());
    // glBindTexture(GL_TEXTURE_2D, preprocess_buffer.id());
    // GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    // glDrawBuffers(1, DrawBuffers);  
    // std::cout << "draw:\n";
    gl.std.drawTile();
}


