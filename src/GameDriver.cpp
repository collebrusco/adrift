//
//  GameDriver.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/6/23.
//
//

#include "GameDriver.h"
#include "components/all.h"
#include <cmath>
static Graphics gl;

GameDriver::GameDriver(const char *title, uint32_t w, uint32_t h) : window(gl.initCreateWindow(title, w, h)),
                                                                    delta_timer(ftime::SECONDS),
                                                                    launch_timer(ftime::SECONDS),
                                                                    dt(1.f/60.f)
{}

void GameDriver::exit() {
    userDestroy();
    gl.destroy();
}

bool GameDriver::create() { 
    launch_timer.start();
    userCreate();
    return true;
}
#include <iostream>
void GameDriver::start() {
    while (!window.should_close()) {
        gl.clear();
        userUpdate(dt);
        window.update();
        dt = delta_timer.stop_reset_start();
        if (std::isinf(dt) || std::isnan(dt)){
            dt = 1.f / 80.f; //TODO: hate this...
        }
    }
    exit();
}
