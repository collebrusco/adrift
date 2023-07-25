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

Adrift::Adrift() : GameDriver("adrift", 1280, 720), fps(8), sky_system(this) {}

void Adrift::camera_init() {
    auto e = scene.newEntity();
    auto& cam = scene.addComp<OrthoCamera>(e);
    auto& tf = scene.addComp<Transform>(e, cam.readPos());
    scene.addComp<DifferentialFollower>(e, player, 0.3);
    cam.setViewWidth(5.f);
    cam.update();
    render_system.use_camera(e);
}

void Adrift::player_init() {
    auto e = scene.newEntity();
    player = e;
    // auto const& asp = ShipTypeObject::getShip(SHIP_ASP);
    scene.addComp<Transform>(e);
    scene.addComp<Velocity>(e);
    auto& ship = scene.addComp<Ship>(e, SHIP_ASP);
    ship.place_on(scene, e);
    // scene.addComp<Render>(e, asp.getMesh(), asp.getShader());
    // scene.addComp<Texture>(e, asp.getTexture());
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
}

// ================================UP         ================================
// ================================   DATE    ================================
// ================================       LOOP================================
void Adrift::userUpdate(float dt) {
    if (window.keyboard[GLFW_KEY_F].pressed){
        static bool toggle = false;
        gl.setWireframe(toggle ^= 0x01);
    }
    if (window.mouse.scroll.y != 0.f) {
        ((OrthoCamera*)render_system.fetch_camera(scene))->getViewWidth() += window.mouse.scroll.y;
    }

    fps.sample(dt);
    
//    actionSystem.execute(dt);
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
    
    // trans.pos += velo.velo;
    // trans.rotation.z += velo.avelo.z;
}
