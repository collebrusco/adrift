
#ifndef VELOCITY_H
#define VELOCITY_H

#include <glm/glm.hpp>

struct Velocity {
    glm::vec3 velo, avelo;
    Velocity(glm::vec3 v = glm::vec3(0.f), glm::vec3 av = glm::vec3(0.f));
};

#endif
