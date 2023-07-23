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
    TextureName name;
    glm::ivec2 dims;
    glm::vec2 pos;
    Texture() = default;
    Texture(TextureName s, glm::ivec2 d, glm::vec2 p);
};

#endif /* texture_h */
