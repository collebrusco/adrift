//
//  ship_types.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/5/23.
//
//

#include "Ships.h"
static Graphics gl;

ShipTypeObject* ShipTypeObject::ships;

void ShipTypeObject::initShips() {
    ships = new ShipTypeObject[SHIP_LAST + 1];
    ships[SHIP_ASP].setMesh(MESH_ASP);
    ships[SHIP_ASP].setShader(SHADER_SHIP);
    ships[SHIP_ASP].setTexture(Texture(TEX_ATLAS, glm::ivec2(256), glm::vec2(0.)));
}

ShipTypeObject const& ShipTypeObject::getShip(ShipType type) {
    assert(type <= SHIP_LAST);
    return ships[type];
}

ShipTypeObject::ShipTypeObject(MeshName m, Texture t, ShaderName s){
    mesh = m; texture = t; shader = s;
}

MeshName ShipTypeObject::getMesh() const {
    return mesh;
}

Texture ShipTypeObject::getTexture() const {
    return texture;
}

ShaderName ShipTypeObject::getShader() const {
    return shader;
}

void ShipTypeObject::setMesh(MeshName m) { 
    mesh = m;
}

void ShipTypeObject::setTexture(Texture t) {
    texture = t;
}

void ShipTypeObject::setShader(ShaderName s) {
    shader = s;
}

Ship::Ship(ShipType st) : type(ShipTypeObject::getShip(st)),
                          engine(Engine::defaultEngine()),
                          home(0)
{
    
}

void Ship::place_on(ECS& scene, entID tar) {
    home = &scene;
    self = tar;
    scene.addComp<Render>(tar, type.getMesh(), type.getShader());
    scene.addComp<Texture>(tar, type.getTexture());
}

void Ship::place_new(ECS& scene) {
    auto e = scene.newEntity();
    this->place_on(scene, e);
}

void Ship::remove() {
    home->removeComp<Render>(self);
    home->removeComp<Texture>(self);
    home = 0;
    self = 0xFFFFFFFFFFFFFFFF;
}

#include <flgl_math.h>
void Ship::input_thrust(float dt) {
    auto& velo = home->getComp<Velocity>(self);
    auto& trans = home->getComp<Transform>(self);
    velo.velo = velo.velo + glm::vec3((angleToVector(trans.rotation.z + 90.f) * engine.max_forward_thrust) * dt, 0.f);
}

void Ship::input_reverse_thrust(float dt) {
    auto& velo = home->getComp<Velocity>(self);
    auto& trans = home->getComp<Transform>(self);
    velo.velo = velo.velo + glm::vec3((angleToVector(trans.rotation.z + 90.f) * engine.max_reverse_thrust) * dt, 0.f);
}

void Ship::input_brake(float dt) {
    auto& velo = home->getComp<Velocity>(self).velo;
    velo = velo - ((velo / length(velo)) * engine.brake_thrust * dt);
}

void Ship::input_yaw_left(float dt) {
    auto& avelo = home->getComp<Velocity>(self).avelo;
    avelo.z += (engine.yaw_thrust * dt);
}

void Ship::input_yaw_right(float dt) {
    this->input_yaw_left(-dt);
}

Engine::Engine(float fwd, float rev, float brk, float yaw, float boost) : 
               max_forward_thrust(fwd),
               max_reverse_thrust(rev),
               brake_thrust(brk),
               yaw_thrust(yaw),
               boost_multiplier(boost)
{}

Engine Engine::defaultEngine() {
    return Engine(0.1, 0.1, 0.1, 4., 2.);
}








