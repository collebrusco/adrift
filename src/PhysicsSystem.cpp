#include "PhysicsSystem.h"
#include <iostream>
void PhysicsSystem::execute(ECS& scene) {
	for (auto e : scene.view<Velocity, Transform>()) {
		auto& trans = scene.getComp<Transform>(e);
		auto& velo = scene.getComp<Velocity>(e);
		trans.pos += velo.velo;
		trans.rotation.z += velo.avelo.z;
	}
}
