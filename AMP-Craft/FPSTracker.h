#ifndef __FPSTracker
#define __FPSTracker
#include <time.h>
#include <chrono>
#include <iostream>
#include <string>

namespace FPSTracker
{
	unsigned int frame_count = 0;

	time_t start = clock();

	void AddFPS() {
		frame_count++;

		if (std::difftime(clock(), start) >= 1000) {
			std::cout << "You Got " << frame_count << " FPS\n";
			frame_count = 0;
			start = clock();
		}
	}
};

#endif