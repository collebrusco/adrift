////
////  ActionSystem.h
////  risklike
////
////  Created by Frank Collebrusco on 6/9/23.
////
////
//
//#ifndef ActionSystem_h
//#define ActionSystem_h
//#include <queue>
//#include "GameEngine.h"
//#include "lib/flgl/flgl.h"
//
//class Action {
//public:
//    virtual void perform(float dt) = 0;
//    virtual ~Action() = default;
//};
//
//class Actor {
//public:
//    entID entity;
//    Actor(entID e);
//    virtual ~Actor() = default;
//    virtual void act(std::queue<Action*>& acts) = 0;
//};
//
//class FireAction : public Action {
//    GameEngine& engine;
//public:
//    FireAction(GameEngine* eng);
//    virtual void perform(float dt) {
//        
//    }
//};
//
//class PlayerActor : public Actor {
//public:
//    PlayerActor(entID e) : Actor(e) {}
//    virtual void act(std::queue<Action*>& acts) override final {
//        if (Graphics::getWindow().keyboard[GLFW_KEY_P].pressed) {
//            acts.push(new FireAction());
//        }
//    }
//};
//
//class ActionSystem {
//    std::queue<Action*> actions;
//    GameEngine& home;
//public:
//    ActionSystem(GameEngine* h);
//    void execute(float dt);
//};
//
//#endif /* ActionSystem_h */
