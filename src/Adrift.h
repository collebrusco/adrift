//
//  Adrift.h
//  Adrift
//
//  Created by Frank Collebrusco on 6/6/23.
//
//

#ifndef Adrift_h
#define Adrift_h
#include "flgl/inc/flgl.h"
#include "flgl/inc/flgl_math.h"
#include "ecs/ECS.h"
#include "stopwatch/Stopwatch.h"
#include "GameEngine.h"
#include "components/all.h"
#include "design/Ships.h"
#include "SkySystem.h"
#include "ActionSystem.h"

class Adrift : public GameEngine {
public:
    Adrift() : GameEngine("adrift", 1280, 720) {}
//                 ss(this) {}
private:
//    SkySystem ss;
    void userCreate()           override;
    void userUpdate(float dt)   override;
    void userDestroy()          override;
    
    entID player;
    void camera_init();
    void player_init();
    void roll_system(float dt);
    void fly_system(float dt);
    void bg_init();
    void bg_system();
    
//    ActionSystem actionSystem;
};

#endif /* Adrift_h */
