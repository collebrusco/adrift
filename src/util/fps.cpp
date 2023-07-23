#include "fps.h"

#include <iostream>
#include <iomanip>

static size_t NUM_SAMPLES;
static float* buffer;
static size_t idx;

void fps_init(size_t n) {
	NUM_SAMPLES = ((0x01) << n);
	idx = NUM_SAMPLES - 1;
	buffer = new float[NUM_SAMPLES];
}

static void output() {
	float total = 0;
	for (uint32_t i = 0; i < NUM_SAMPLES; i++) {
		total += buffer[i];
	}
	total /= NUM_SAMPLES;
	std::cout << std::fixed << std::setprecision(1) << "FPS: " << 1 / total << "\n";
}

void fps_sample(float dt) {
	if (idx) {
		buffer[idx--] = dt;
	} else {
		buffer[idx] = dt;
		idx = NUM_SAMPLES - 1;
		output();
	}
}


