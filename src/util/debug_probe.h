
#ifndef DEBUG_PROBE_H
#define DEBUG_PROBE_H

#include <stopwatch/Stopwatch.h>

// takes 2^n samples & averages
void debug_init(size_t n);
// takes sample, output if buffer full
void debug_start_sample();
void debug_stop_sample();

#endif DEBUG_PROBE_H // DEBUG_PROBE_H