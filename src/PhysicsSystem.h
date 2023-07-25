
#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "../lib/ecs/ECS.h"
#include "../lib/flgl/inc/flgl.h"
#include "../lib/stopwatch/Stopwatch.h"
#include "components/all.h"
#include "GameDriver.h"

class PhysicsSystem {
public:
	void execute(ECS& scene);
};

#endif