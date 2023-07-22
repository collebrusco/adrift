//
//  texture.cpp
//  risklike
//
//  Created by Frank Collebrusco on 6/4/23.
//
//

#include "texture.h"

Texture::Texture(TEXTURE_SLOT s, glm::ivec2 d, glm::vec2 p) {
    slot = s; dims = d; pos = p;
}

void Texture::sync(Shader s) {
    s.uInt("uTexslot", slot);
    s.uIVec2("uSpriteWH", dims);
    s.uVec2("uSpriteSheetPos", pos);
}
