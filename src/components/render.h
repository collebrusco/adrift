//
//  render.h
//  risklike
//
//  Created by Frank Collebrusco on 6/4/23.
//
//

#ifndef render_h
#define render_h
#include "../lib/flgl/inc/flgl.h"
#include "../renderer_enums.h"

struct Render {
    MeshName vao;
    ShaderName shader;
    Render(MeshName v, ShaderName s);
};

#endif /* render_h */
