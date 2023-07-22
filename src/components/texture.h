//
//  texture.h
//  risklike
//
//  Created by Frank Collebrusco on 6/4/23.
//
//

#ifndef texture_h
#define texture_h
#include <glm/glm.hpp>
#include "../lib/flgl/inc/flgl.h"
#include "../renderer_enums.h"

struct Texture {
    TEXTURE_SLOT slot;
    glm::ivec2 dims;
    glm::vec2 pos;
    Texture() = default;
    Texture(TEXTURE_SLOT s, glm::ivec2 d, glm::vec2 p);
    void sync(Shader s);
};

#endif /* texture_h */
