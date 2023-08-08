#version 410 core
/*
 this frag shader provides a perlin noise function, ubiquitous in computer graphics
 this implementation was written by Frank Collebrusco, based on wikipedia's implementation
 the perlin can be scaled, shifted, and animated (gradient vectors rotated by theta)
 
 INPUT: this shader relies on having the following uniforms uploaded:
    uTime:      float time since origin, seconds recommended
    uRes:       w/h of screen in pixels
    uAspect:    aspect ratio of screen (w / h)
 */
layout (location = 0) out vec3 outColor;
in vec2 iUV;
in vec3 iPos;

uniform float uTime;
uniform vec2 uRes;
uniform float uAspect;
uniform float uZoom;

uniform vec2 uGamePos;
uniform vec2 uPGamePos;

vec2 n_res = gl_FragCoord.xy / uRes;
vec2 i_res = (vec2(n_res.x * uAspect, n_res.y) - vec2(uAspect / 2, 0.5));// * mat2(vec2(cos(-uRotation), sin(-uRotation)), vec2(-sin(-uRotation), cos(-uRotation)));

float rand(vec2 co){
    return sin(dot(co, vec2(12.9898, 78.233)) * 43758.5453);
}

// smootherstep, ken perlin
float interp(float x){
    return ((x * (x * 6.0 - 15.0) + 10.0) * x * x * x);
}

// smootherstep between a and b
float interp(float a, float b, float x){
    float ab = (b - a);
    return (ab * interp(x)) + a;
}

// produces a "random" unit vector by a 2-dimensional seed
// random function based on a wikipedia implementation
// shuffles the bits of integer inputs to create theta
vec2 gradient(int x, int y){
    uint a = x;
    uint b = y;
    a *= 0xBAF3C90F;
    b ^= (a << 16) | (a >> 16);
    b *= 0x5454FAFF;
    a ^= (b << 16) | (b >> 16);
    a *= 0xDA442859;
    float theta = a * (3.14159265 / (2 * (0x10000000)));
    return vec2(cos(theta), sin(theta));
}

// identical to above gradient function, but rotates all vectors by time offset
vec2 gradient(int x, int y, float speed){
    uint a = x;
    uint b = y;
    a *= 0xBAF3C90F;
    b ^= (a << 16) | (a >> 16);
    b *= 0x5454FAFF;
    a ^= (b << 16) | (b >> 16);
    a *= 0xDA442859;
    float theta = a * (3.14159265 / (2 * (0x10000000)));
    return vec2(cos(theta+(uTime*speed)), sin(theta+(uTime*speed)));
}

float perlin(vec2 pos, float rotation, vec2 offset, vec2 scale, float cam_rotation) {
    // translate, scale
    pos += offset;
    pos *= scale;
    
//    vec2 d = vec2(0.5 * uAspect, 0.5) + offset + uGamePos;
//
//    float nx =      ((pos.x - d.x) * cos(cam_rotation)) - ((d.y - pos.y) * sin(cam_rotation)) + d.x;
//    float ny =      ((d.y - pos.y) * cos(cam_rotation)) + ((pos.x - d.x) * sin(cam_rotation)) + d.y;
//
//    pos.x = nx; pos.y = ny;
    
    // establish grid
    int x0 = int(floor(pos.x));
    int y0 = int(floor(pos.y));
    int x1 = x0 + 1;
    int y1 = y0 + 1;
    
    // offset vectors, from grid corners to fragment
    vec2 botL = (pos - vec2(float(x0), float(y0))) / 1.41;
    vec2 topR = (pos - vec2(float(x1), float(y1))) / 1.41;
    vec2 topL = (pos - vec2(float(x0), float(y1))) / 1.41;
    vec2 botR = (pos - vec2(float(x1), float(y0))) / 1.41;
    
    // dot each offset vector with random gradient at each grid corner
    float BL = dot(botL, gradient(x0, y0, rotation));
    float TR = dot(topR, gradient(x1, y1, rotation));
    float TL = dot(topL, gradient(x0, y1, rotation));
    float BR = dot(botR, gradient(x1, y0, rotation));
    
    // interpolate, scale 0 to 1
    return (interp(interp(BL, BR, pos.x - floor(pos.x)), interp(TL, TR, pos.x - floor(pos.x)), pos.y - floor(pos.y)) * 0.5) + 0.5;
}

float perlin(vec2 pos, float rotation, vec2 offset, vec2 scale) {
    return perlin(pos, rotation, offset, scale, 0);
}

float perlin(vec2 pos, float rotation, vec2 offset){
    return perlin(pos, rotation, offset, vec2(1));
}

float perlin(vec2 pos, float rotation){
    return perlin(pos, rotation, vec2(0), vec2(1));
}

float perlin(vec2 pos){
    return perlin(pos, 0, vec2(0), vec2(1));
}

float red_noise(float m, float dist) {
    float res = 0;
    int i;
    for (i = 0; i < 7; i++) {
        res += perlin(i_res, 0.02, uGamePos / (dist * 12.f), vec2((dist/12.f) * i));
    }
    return m * (res / i);
}

float blue_noise(float m, float dist) {
    float res = 0;
    int i;
    for (i = 0; i < 7; i++) {
        res += perlin(i_res, 0.02, uGamePos / (dist * 12.f), vec2((dist/16.f) * i));
    }
    return m * (res / i);
}

float green_noise(float m, float dist) {
    float res = 0;
    int i;
    for (i = 0; i < 7; i++) {
        res += perlin(i_res, 0.02, uGamePos / (dist * 10.f), vec2((dist/16.f) * i));
    }
    return m * (res / i);
}

#define STAR_COLOR (vec4(0.7f, 0.6f, 0.67f, 1.f) * (perlin(i_res * 50.f, 0.2f) + 0.3))
bool star() {
    for (int i = 1; i < 3; i++) {
        float sn = perlin(i_res + ivec2(i, -i), 0.02, (uGamePos + vec2(0.5)) / vec2(float((i<<1) + 200)), vec2(300.f / float((i))));
        if (sn > 0.7) {
            return true;
        }
    }
    return false;
}

#define DUST_COLOR vec4(0.502f, 0.5f, 0.505f, 1.f)
bool dust(vec2 gPos) {
    float sn = perlin(i_res,                0.02, (gPos + vec2(0.5)) / vec2(5.f * uZoom), vec2(75.f * uZoom));
    if (sn < 0.685) { return false; }
    float sn1 = perlin(i_res, 0.02, (gPos + vec2(0.22)) / vec2(5.f * uZoom), vec2(150.f * uZoom));
    return (sn1 > 0.65);
}

bool dust() {
    vec2 diff = uPGamePos - uGamePos;
    diff /= 4.;
    for (int i = 0; i < 10; i++) {
        if (dust(uGamePos + (float(i) * diff))) {
            return true;
        }
    }
    return false;
}

bool distanceToIntLessThan(float x, float d) {
    return abs(x - floor(x)) < d;
}

#define GRID_COLOR vec4(0.5, 0.5, 0.55, 1.)
bool grid(float div) {
    vec2 pos_in_game_coords = (uGamePos);
    pos_in_game_coords += vec2((n_res.x) - 0.5, (n_res.y / uAspect) - (1/(2.f*uAspect))) * uZoom;

    if (div != 0.f) {
       pos_in_game_coords /= div;
    }
    
    if (distanceToIntLessThan(pos_in_game_coords.x, 0.015) || 
        distanceToIntLessThan(pos_in_game_coords.y, 0.015)) {
        return true;
    }
    return false;
}

float grid() {
    if (uZoom < 24.f) {
        if (grid(0.f)) {
            return 1.f;
        }
        return 0.f;
    }
    if (grid(4.f)) {
        return 1.f;
    }
    if (grid(0.f)) {
        return 0.4f;
    }
    return 0.f;
}

void main(){
    vec4 clr = vec4(0., 0., 0., 1.);
    float gr = grid();
    if (star()){
        clr = STAR_COLOR;
    } else
        if (dust()) {
        clr = DUST_COLOR;
    } else 
        if (gr != 0.f) {
        clr = GRID_COLOR * gr;
    } else {
        const float bt = 4;
        clr.r = red_noise(0.1f * bt, 10.f);
        clr.g = green_noise(0.05f * bt, 12.f);
        clr.b = blue_noise(0.1f * bt, 4.f);
        clr.stp = max(vec3(0.f), clr.xyz - 0.15);
    }
    
    outColor = clr.xyz;
}
