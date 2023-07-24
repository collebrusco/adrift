#include "debug_probe.h"
#include <iostream>
using namespace ftime;

static Stopwatch timer(MILLISECONDS);
static size_t size;
static uint32_t idx = 0;
static float* buffer;

void debug_init(size_t n) {
	size = ((0x01u) << n);
	buffer = new float[size];
	idx = size - 1;
	timer.stop();
}

static void out() {
	float avg = 0;
	for (size_t i = 0; i < size; i++) {
		avg += buffer[i];
	}
	avg /= size;
	std::cout << "\tDEBUG:\t" << avg << "\n";
}

void debug_sample() {
	if (timer.running() && idx){
		// we've started & have more room, sample
		buffer[idx--] = timer.stop_reset_start();
		return;
	}
	if (timer.running()) {
		// buffer full, output & destroy
		out();
		delete [] buffer;
	}
	else {
		// first call, start
		timer.reset_start();
	}
}

