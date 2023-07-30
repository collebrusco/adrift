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
#include "util/fps.h"
#include "ecs/ECS.h"
#include "stopwatch/Stopwatch.h"
#include "GameDriver.h"
#include "RenderSystem.h"
#include "SkySystem.h"
#include "PhysicsSystem.h"
#include "components/all.h"
#include "design/Ships.h"
#include "SkySystem.h"
#include "ActionSystem.h"

class ai_test {
    entID self;
    ECS* home;
public:
    void init(ECS& scene);
    void update(float dt);
};

class Adrift : public GameDriver {
public:
    Adrift();
private:
    FPS fps;
    void userCreate()           override;
    void userUpdate(float dt)   override;
    void userDestroy()          override;
    
    entID player;
    RenderSystem render_system;
    SkySystem sky_system;
    PhysicsSystem physics_system;
    ai_test test;

    void camera_init();
    void player_init();
    void roll_system(float dt);
    void fly_system(float dt);
    
};

#endif /* Adrift_h */
