//
//  follower.h
//  risklike
//
//  Created by Frank Collebrusco on 6/4/23.
//
//

#ifndef follower_h
#define follower_h
#include "../lib/ecs/ECS.h"
#include "transform.h"
#include <glm/glm.hpp>

struct DifferentialFollower {
    entID target;
    float coeff;
    DifferentialFollower(entID tar, float co);
    void update(ECS& scene, entID selfID);
    static void follower_system(ECS& scene);
};

#endif /* follower_h */
