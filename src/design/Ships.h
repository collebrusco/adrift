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
    float thrust;
    Engine(float t);
};

// hull strength, mass, acceleration, fun stuff! Weapon[], Defense[], System[] ooooh boy
class Ship {
private:
    ShipTypeObject const& type;
    Engine engine;
public:
    Ship(ShipType st);
};

#endif /* ships_h */
