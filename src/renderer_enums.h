//
//  renderer_enums.h
//  risklike
//
//  Created by Frank Collebrusco on 6/5/23.
//

#ifndef renderer_enums_h
#define renderer_enums_h

enum ShaderName {
    SHADER_SHIP = 0,
    SHADER_STARS,
    SHADER_POSTPROCESS
};
#define SHADER_LAST SHADER_POSTPROCESS

enum MeshName {
    MESH_ASP = 0,
    MESH_TILE = 1
};
#define MESH_LAST MESH_TILE

enum TextureName {
    TEX_ATLAS = 0
};
#define TEX_LAST TEX_ATLAS

#endif /* renderer_enums_h */
