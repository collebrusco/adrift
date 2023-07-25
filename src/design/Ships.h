//
//  ship_types.h
//  risklike
//
//  Created by Frank Collebrusco on 6/5/23.
//
//

#ifndef ships_h
#define ships_h

#include "flgl/inc/flgl.h"
#include "../components/all.h"
#include "ecs/ECS.h"

/*
 this class is for use as a type object (flyweight)
 meaning it represents a type of ship, and any number of ship entities of that type
 reference these type objects for information about their class that is the same among all of them
 so these are immutible once constructed
 */

#define SHIP_LAST SHIP_ASP
enum ShipType {
    SHIP_ASP = 0
};

class ShipTypeObject {
    static ShipTypeObject* ships;
    MeshName mesh;
    Texture texture;
    ShaderName shader;
public:
    ShipTypeObject() = default;
    ShipTypeObject(MeshName m, Texture t, ShaderName s);
    
    static void initShips();
    static ShipTypeObject const& getShip(ShipType type);
    
    MeshName getMesh() const;
    Texture getTexture() const;
    ShaderName getShader() const;
    
    void setMesh(MeshName m);
    void setTexture(Texture m);
    void setShader(ShaderName s);
};

struct Engine {
    float max_forward_thrust;
    float max_reverse_thrust;
    float brake_thrust;
    float yaw_thrust;
    float boost_multiplier;
    Engine() = default;
    Engine(float, float, float, float, float);
    static Engine defaultEngine();
};

struct Weapon {
    uint32_t stuff; // ??
};

// hull strength, mass, acceleration, fun stuff! Weapon[], Defense[], System[] ooooh boy
class Ship {
private:
    ShipTypeObject const& type;
    Engine engine;
    ECS* home;
    entID self;
public:
    Ship(ShipType st);

    // ship controls
    void input_thrust(float dt);
    void input_reverse_thrust(float dt);
    void input_brake(float dt);
    void input_yaw_left(float dt);
    void input_yaw_right(float dt);



    // emplace / remove from scene
    void place_on(ECS& scene, entID tar);
    void place_new(ECS& scene);
    void remove();
};

#endif /* ships_h */
















