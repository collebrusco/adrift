//
//  follower.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/4/23.
//
//

#include "follower.h"
using namespace glm;

DifferentialFollower::DifferentialFollower(entID tar, float co){ target = tar; coeff = co;}

// TODO: add ability to select which derivative we apply the coeff to
// TODO: e.g. for ship in space, if it's moving a fraction of delta pos,
// TODO: a spaceship steadily accelerating with no top speed will just move off camera
// TODO: we need to move a fraction of delta velo not delta pos for this case

void DifferentialFollower::update(ECS& scene, entID selfID) {
    auto& self = scene.getComp<Transform>(selfID);
    auto& tar = scene.getComp<Transform>(target);
    vec3 delta = tar.pos - self.pos;
    delta.z = 0;
    self.pos += (delta * coeff);
}

void DifferentialFollower::follower_system(ECS& scene) {
    for (auto e : scene.view<DifferentialFollower>()){
       scene.getComp<DifferentialFollower>(e).update(scene, e);
    }
}
