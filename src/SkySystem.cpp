//
//  SkySystem.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/9/23.
//
//

#include "SkySystem.h"
#include "renderer_enums.h"
#include "components/render.h"
using namespace glm;

SkySystem::SkySystem(GameDriver* h) : home(*h) {}

void SkySystem::init() {
   backdrop = home.scene.newEntity();
   home.scene.addComp<Render>(backdrop, MESH_TILE, SHADER_STARS);
}
#include <iostream>
void SkySystem::execute(Camera* cam) {
   static vec2 pGamePos;
   home.shaders[SHADER_STARS].uFloat("uTime", home.launch_timer.read());
   home.shaders[SHADER_STARS].uVec2("uRes", vec2(home.window.frame.x, home.window.frame.y));
   home.shaders[SHADER_STARS].uFloat("uAspect", home.window.aspect);
   home.shaders[SHADER_STARS].uVec2("uGamePos", vec2(cam->readPos().x, cam->readPos().y));
   home.shaders[SHADER_STARS].uVec2("uPGamePos", pGamePos);
   home.shaders[SHADER_STARS].uFloat("uZoom", ((OrthoCamera*)cam)->readViewWidth());
   home.shaders[SHADER_STARS].uInt("u_grid", home.window.keyboard[GLFW_KEY_G].down ? 1 : 0);
   pGamePos = vec2(cam->readPos().x, cam->readPos().y);
}
