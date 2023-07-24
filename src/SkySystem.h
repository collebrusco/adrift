//
//  SkySystem.h
//  risklike
//
//  Created by Frank Collebrusco on 6/9/23.
//
//

#ifndef SkySystem_h
#define SkySystem_h

#include "GameDriver.h"
#include <flgl.h>

class SkySystem {
	GameDriver& home;
	entID backdrop;
public:
   SkySystem(GameDriver* h);
   void init();
   void execute(Camera* cam);
};


#endif /* SkySystem_h */
