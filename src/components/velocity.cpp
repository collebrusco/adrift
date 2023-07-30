#include "velocity.h"

Velocity::Velocity() : velo(glm::vec3(0.)), avelo(glm::vec3(0.)) {}

Velocity::Velocity(glm::vec3 v, glm::vec3 av) : velo(v), avelo(av)
{}