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
    // TODO: texture name here, have engine init them
    ships[SHIP_ASP].setMesh(MESH_ASP);
    ships[SHIP_ASP].setShader(SHADER_SHIP);
    ships[SHIP_ASP].setTexture(Texture(gl.loader.UploadTexture("atlas", true), glm::ivec2(256), glm::vec2(0.)));
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
                          engine(0.1f)
{
    
}

Engine::Engine(float t) : thrust(t) {}
