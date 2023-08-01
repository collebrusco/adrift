#include "velocity.h"

Velocity::Velocity() : velo(glm::vec3(0.)), avelo(glm::vec3(0.)) {
	velo.x = velo.y = velo.z = avelo.x = avelo.y = avelo.z = 0.f;
}

Velocity::Velocity(glm::vec3 v, glm::vec3 av) : velo(v), avelo(av)
{	
	velo.x = velo.y = velo.z = avelo.x = avelo.y = avelo.z = 0.f;
}