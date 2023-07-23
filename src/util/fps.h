
#ifndef FPS_h
#define FPS_h
#include <stddef.h>

// fps will output average fps 
// from the last 2^n frames every 2^n frames
void fps_init(size_t n);
// call sample with a measurement every frame
void fps_sample(float dt);

#endif // FPS_h