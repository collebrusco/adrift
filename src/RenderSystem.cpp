#include "RenderSystem.h"

static Graphics gl;

RenderSystem::RenderSystem() {}

void RenderSystem::init() {
    auto& win = gl.getWindow();
    preprocess_buffer.create(win.frame.x, win.frame.y, true);
    // test_buffer.create(win.frame.x / 2, win.frame.y / 2, true);
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
#include <iostream>
#include <cstdio>
void RenderSystem::resize_preprocess_buffer() {
    auto& win = gl.getWindow();
    assert(preprocess_buffer.active());
    // printf("window is %d by %d, buffer is %d by %d\n",
    //     win.frame.x, win.frame.y,
    //     preprocess_buffer.w(), preprocess_buffer.h());
    if (win.frame.x != (int)preprocess_buffer.w() || win.frame.y != (int)preprocess_buffer.h()) {
        std::cout << "recreating:\n";
        preprocess_buffer.destroy();
        std::cout << "destroyed,\n";
        preprocess_buffer.create(win.frame.x, win.frame.y, true);
        std::cout << "recreated.\n";
        assert(preprocess_buffer.active());
    }
}

void RenderSystem::execute(GameDriver* state) {
    static int a = 0;
    static float pix = 200.f;
    sync_camera(state->scene);
    resize_preprocess_buffer();
    // std::cout << "binding framebuffer...\n";
    preprocess_buffer.bind();
    preprocess_buffer.clear();
    glViewport(0, 0, preprocess_buffer.w(), preprocess_buffer.h());

    // std::cout << "drawing to framebuffer...\n";
    for (auto e : state->scene.view<Render>()) {
        auto& render = state->scene.getComp<Render>(e);
        state->shaders[render.shader].bind();
        if (Transform* trans = state->scene.tryGetComp<Transform>(e))
            trans->sync(state->shaders[render.shader]);
        if (Texture* tex = state->scene.tryGetComp<Texture>(e)) {
            state->shaders[render.shader].bind();
            state->shaders[render.shader].uInt("uTexslot", preprocess_buffer.slot()); // TODO what?? we're drawing to FB not sampling
            // std::cout << "state->textures[tex->name]: " << state->textures[tex->name] << "\n";
            // glActiveTexture(GL_TEXTURE0 + state->textures[tex->name]);
            glBindTexture(GL_TEXTURE_2D, 1); // TODO this is atlas ID, no way to get it yet
		    state->shaders[render.shader].uIVec2("uSpriteWH", tex->dims);
		    state->shaders[render.shader].uVec2("uSpriteSheetPos", tex->pos);
		}
        gl.DrawMesh(state->meshes[render.vao]);
    }
    preprocess_buffer.unbind();
    // std::cout << "drawing to viewport, tex slot " << preprocess_buffer.slot() << "\n";
    state->shaders[SHADER_POSTPROCESS].bind();
    state->shaders[SHADER_POSTPROCESS].uInt("uTexslot", 0); // TODO what??
    state->shaders[SHADER_POSTPROCESS].uFloat("uTime", state->launch_timer.read());
    state->shaders[SHADER_POSTPROCESS].uVec2("uRes", glm::vec2(state->window.frame.x, state->window.frame.y));
    state->shaders[SHADER_POSTPROCESS].uFloat("uAspect", state->window.aspect);
    if (state->window.keyboard[GLFW_KEY_RIGHT].down) pix += 128.f * state->dt;
    if (state->window.keyboard[GLFW_KEY_LEFT].down) pix = (pix - (128.f * state->dt)) < 1.f ? 1.f : (pix - (128.f * state->dt));
    state->shaders[SHADER_POSTPROCESS].uFloat("PIXELATION_LEVEL", pix);

    // if (gl.getWindow().keyboard[GLFW_KEY_L].pressed) a ^= 0x01;
    // auto& tex = state->textures[TEX_ATLAS];
    // state->shaders[SHADER_SHIP].uIVec2("uSpriteWH", glm::ivec2(256));
    // state->shaders[SHADER_SHIP].uVec2("uSpriteSheetPos", glm::vec2(0.));
    // state->shaders[SHADER_POSTPROCESS].uInt("uTexslot",  a);
    // glViewport(0, 0, preprocess_buffer.w(), preprocess_buffer.h());
    // glActiveTexture(GL_TEXTURE0 + preprocess_buffer.slot());
    // glBindTexture(GL_TEXTURE_2D, preprocess_buffer.id());
    // GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    // glDrawBuffers(1, DrawBuffers);  
    // std::cout << "draw:\n";
    gl.std.drawTile();
}


