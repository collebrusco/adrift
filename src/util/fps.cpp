#include "fps.h"

#include <iostream>
#include <iomanip>



FPS::FPS(const size_t n) : NUM_SAMPLES(((0x01) << n)) {
	idx = NUM_SAMPLES - 1;
	buffer = new float[NUM_SAMPLES];
}

FPS::~FPS() {
	delete [] buffer;
}

void FPS::output() {
	float total = 0;
	for (uint32_t i = 0; i < NUM_SAMPLES; i++) {
		total += buffer[i];
	}
	total /= NUM_SAMPLES;
	std::cout << std::fixed << std::setprecision(1) << "FPS: " << 1 / total << "\n";
}

static uint32_t sorryaboutthis = 0;

void FPS::sample(float dt) {
	if (idx) {
		buffer[idx--] = dt;
	} else {
		buffer[idx] = dt;
		idx = NUM_SAMPLES - 1;
		if (!(++sorryaboutthis & 0x03))
			output();
	}
}


