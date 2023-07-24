
#ifndef FPS_h
#define FPS_h
#include <stddef.h>

// fps will output average fps periodically

class FPS {
	const size_t NUM_SAMPLES;
	float* buffer;
	size_t idx;
	void output();
public:
	// output average of last 2^n samples
	// every 2^n samples
	FPS(const size_t n);
	~FPS();

	// call sample with a measurement 
	void sample(float dt);
};

#endif // FPS_h