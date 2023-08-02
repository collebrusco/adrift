//
//  Adrift.cpp
//  Adrift
//
//  Created by Frank Collebrusco on 6/6/23.
//
//

#include "Adrift.h"
#include <../res/models.h>
MESH_DEFINE_ASP
#include "design/Ships.h"
#include <iostream>
using namespace glm;
static Graphics gl;

Adrift::Adrift() : GameDriver("adrift", 1280, 720), fps(6), sky_system(this) {}

void Adrift::camera_init() {
    auto e = scene.newEntity();
    auto& cam = scene.addComp<OrthoCamera>(e);
    auto& tf = scene.addComp<Transform>(e, cam.readPos());
    scene.addComp<DifferentialFollower>(e, player, 0.3);
    cam.setViewWidth(8.f);
    cam.update();
    render_system.use_camera(e);
}

void Adrift::player_init() {
    auto e = scene.newEntity();
    player = e;
    scene.addComp<Transform>(e);
    scene.addComp<Velocity>(e);
    auto& ship = scene.addComp<Ship>(e, SHIP_ASP);
    ship.place_on(scene, e);
}

void ai_test::init(ECS& scene) {
    self = scene.newEntity();
    home = &scene;
    home->addComp<Transform>(self, glm::vec3(1., 1., 0.));
    auto& velo = home->addComp<Velocity>(self);
    auto& ship = home->addComp<Ship>(self, SHIP_ASP);
    ship.place_on(scene, self);
}
void ai_test::update(float dt) {
    auto& ship = home->getComp<Ship>(self);
    auto& trans = home->getComp<Transform>(self);
    auto& velo = home->getComp<Velocity>(self);
    static const float targetAV = 1.;
    static const float targetV = 0.01;
    if (velo.avelo.z < targetAV)
        ship.input_yaw_left(dt);
    else
        ship.input_yaw_right(dt);

    if (glm::length(velo.velo) < targetV)
        ship.input_thrust(dt);
    else
        ship.input_brake(dt);
}

#include "util/debug_probe.h"
void Adrift::userCreate() {
    meshes.reserve(MESH_LAST + 1);
    shaders.reserve(SHADER_LAST + 1);
    textures.reserve(TEX_LAST + 1);
    meshes[MESH_ASP] = gl.loader.UploadMesh(asp_mesh);
    meshes[MESH_TILE] = gl.std.getTileMesh();
    shaders[SHADER_SHIP] = gl.loader.UploadShader("mvp_vert", "tex_frag");
    shaders[SHADER_STARS] = gl.loader.UploadShader("fullscreen_vert", "star2d_frag");
    textures[TEX_ATLAS] = gl.loader.UploadTexture("atlas", true);
    ShipTypeObject::initShips();
    gl.setDepthTestEnable(true);
    player_init();
    camera_init();
    sky_system.init();
    debug_init(10);
    test.init(scene);
}

#include <thread>
#include <chrono>
// ================================UP         ================================
// ================================   DATE    ================================
// ================================       LOOP================================
void Adrift::userUpdate(float dt) {
    if (window.keyboard[GLFW_KEY_F].pressed){
        static bool toggle = false;
        gl.setWireframe(toggle ^= 0x01);
    }
    if (window.mouse.scroll.y != 0.f) {
        auto newVW = ((OrthoCamera*)render_system.fetch_camera(scene))->getViewWidth() + window.mouse.scroll.y;
        if (newVW < 64 && newVW > 2) {
            ((OrthoCamera*)render_system.fetch_camera(scene))->getViewWidth() = newVW;
        }
    }
    if (window.keyboard[GLFW_KEY_ESCAPE].pressed) {
        window.close();
    }

    // ================================================================

    if (window.keyboard[GLFW_KEY_E].pressed) {
        std::cout << "switching engine...\n";
        auto& ship = scene.getComp<Ship>(player);
        static uint32_t i = 0;
        static const Engine engines[4] = {

            Engine(0.03, 0.008, 0.03, 2.),
            Engine(0.06, 0.01, 0.04, 3.),
            Engine(0.1, 0.08, 0.1, 4.),
            Engine(0.33, 0.2, 0.25, 5.5)
        };
        ship.engine = engines[++i & 0x03];
    }
    // ================================================================

    fps.sample(dt);
    // std::this_thread::sleep_for(std::chrono::microseconds(200000));

//    actionSystem.execute(dt);
    // test.update(dt);
    roll_system(dt);
    fly_system(dt);
    physics_system.execute(scene);
    DifferentialFollower::follower_system(scene);

    sky_system.execute(render_system.fetch_camera(scene));
    // debug_start_sample();
    render_system.execute(this);
    // debug_stop_sample();
}

void Adrift::userDestroy() {
    
}

void Adrift::roll_system(float dt){
    static const float rmax = 15.f;
    static const float coeff = 2.f;
    auto& win = gl.getWindow();
    auto& trans = scene.getComp<Transform>(player);
    if (win.keyboard[GLFW_KEY_A].down){
        float delta = coeff * (rmax - abs(trans.rotation.y));
        trans.rotation.y -= delta * dt;
    } else if (win.keyboard[GLFW_KEY_D].down){
        float delta = coeff * (rmax - abs(trans.rotation.y));
        trans.rotation.y += delta * dt;
    } else if (trans.rotation.y != 0){
        trans.rotation.y += ((5. * dt) * (-trans.rotation.y));
    }

    if (win.keyboard[GLFW_KEY_W].down){
        float delta = coeff * (rmax - abs(trans.rotation.x));
        trans.rotation.x += delta * dt;
    } else if (win.keyboard[GLFW_KEY_S].down){
        float delta = coeff * (rmax - abs(trans.rotation.x));
        trans.rotation.x -= delta * dt;
    } else if (trans.rotation.x != 0){
        trans.rotation.x += ((5. * dt) * (-trans.rotation.x));
    }
}

void Adrift::fly_system(float dt) {
    static const float ACCEL_MAX = 0.1f;
    auto& win = gl.getWindow();
    auto& trans = scene.getComp<Transform>(player);
    auto& velo = scene.getComp<Velocity>(player);
    Ship* ship = scene.tryGetComp<Ship>(player);
    if (ship) {
        if (win.keyboard[GLFW_KEY_A].down) {
            ship->input_yaw_left(dt);
        } else if (win.keyboard[GLFW_KEY_D].down){
            ship->input_yaw_right(dt);
        }

        if (win.keyboard[GLFW_KEY_W].down) {
            ship->input_thrust(dt);
        } else if (win.keyboard[GLFW_KEY_S].down){
            ship->input_reverse_thrust(dt);
        }
        
        if (win.keyboard[GLFW_KEY_SPACE].down) {
            ship->input_brake(dt);
        }
    }
}
