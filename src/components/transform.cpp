//
//  common_comps.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/4/23.
//
//

#include "transform.h"
#include "../../inc/flgl_math.h"

Transform::Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s, glm::vec3 a) {
    pos = p; rotation = r; scale = s; anchor = a;
}

void Transform::sync(Shader s) {
    s.uMat4("uModel", genModelMat3d(pos, rotation, scale, anchor));
}

