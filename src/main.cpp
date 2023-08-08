//
//  main.cpp
//  Adrift
//
//  Created by Frank Collebrusco on 6/2/23.
//
#include <iostream>

#include "Adrift.h"

int main(int argc, const char * argv[]) {
    Graphics::loader.setAssetPath("res/");
    Graphics::loader.setShaderPath("src/shaders/");
    Adrift game;
    if (game.create())
        game.start();
    return 0;
}
