//
//  SkySystem.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/9/23.
//
//
//
//#include "SkySystem.h"
//#include "c/render.h"
//#include <iostream>
//using namespace glm;
//
//SkySystem::SkySystem(GameEngine *h) : System(h) {}
//
//void SkySystem::init() {
//    auto e = home.scene.newEntity();
//    home.scene.addComp<Render>(e, MESH_TILE, SHADER_STARS);
//}
//
//void SkySystem::execute(float dt) {
//    static vec2 pGamePos;
//    Camera* cam = home.renderer.fetch_camera(home.scene);
//    home.shaders[SHADER_STARS].uFloat("uTime", home.launch_timer.read());
//    home.shaders[SHADER_STARS].uVec2("uRes", vec2(home.window.frame.x, home.window.frame.y));
//    home.shaders[SHADER_STARS].uFloat("uAspect", home.window.aspect);
//    home.shaders[SHADER_STARS].uVec2("uGamePos", vec2(cam->readPos().x, cam->readPos().y) / 5.f);
//    home.shaders[SHADER_STARS].uVec2("uPGamePos", pGamePos / 5.f);
//    home.shaders[SHADER_STARS].uFloat("uZoom", ((OrthoCamera*)cam)->readViewWidth() / 10.f);
//    pGamePos = vec2(cam->readPos().x, cam->readPos().y);
//}
