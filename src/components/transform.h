//
//  common_comps.h
//  risklike
//
//  Created by Frank Collebrusco on 6/4/23.
//
//

#ifndef common_comps_h
#define common_comps_h
#include <glm/glm.hpp>
#include <flgl/inc/flgl.h>

struct Transform {
    glm::vec3 pos, rotation, scale, anchor;
    Transform(glm::vec3 p = glm::vec3(0.f), glm::vec3 r = glm::vec3(0.f), glm::vec3 s = glm::vec3(1.f), glm::vec3 a = glm::vec3(0.f));
    void sync(Shader s);
};

#endif /* common_comps_h */
