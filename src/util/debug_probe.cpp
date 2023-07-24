#include "debug_probe.h"
#include <iostream>
using namespace ftime;

static Stopwatch timer(MICROSECONDS);
static size_t size;
static uint32_t idx = 0;
static float* buffer;
static bool running;

void debug_init(size_t n) {
	size = ((0x01u) << n);
	buffer = new float[size];
	idx = size - 1;
	timer.stop();
	running = true;
}

static void out() {
	float avg = 0;
	for (size_t i = 0; i < size; i++) {
		avg += buffer[i];
	}
	avg /= size;
	std::cout << "\tDEBUG:\t" << avg << " us\n";
}

void debug_start_sample() {
	timer.reset_start();
}

void debug_stop_sample() {
	if (idx && running) {
		float s = timer.stop();
		// std::cout << "sampling: \n\tidx: " << idx << "\n\tsmp: " << s << "\n";
		buffer[idx--] = s; //timer.stop();
		return;
	}
	out();
	if (running)
		delete [] buffer;
	running = false;
}

