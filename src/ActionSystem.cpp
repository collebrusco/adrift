////
////  ActionSystem.cpp
////  risklike
////
////  Created by Frank Collebrusco on 6/9/23.
////
////
//
//#include "ActionSystem.h"
//
//
//ActionSystem::ActionSystem(GameEngine *h) : home(*h) {}
//
//void ActionSystem::execute(float dt) {
//    // gather actions
//    for (auto e : home.scene.view<Actor*>()) {
//        home.scene.getComp<Actor*>(e)->act(actions);
//    }
//    // execute all actions
//    while (!actions.empty()) {
//        auto action = actions.front(); actions.pop(); // what the fuck is up with std queue that this takes two calls
//        action->perform(dt);
//        delete action;
//    }
//}
//
//Actor::Actor(entID e) : entity(e) {}
