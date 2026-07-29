#include <iostream>
#include <thread>
#include <chrono>

static bool flag1{ false };
static bool flag2{ false };
static bool flag3{ false };
static bool flag4{ false };

using namespace std::literals::chrono_literals;

void Work() {
	while (!flag1) {
		std::cout << "Working ... " << std::endl;
		std::this_thread::sleep_for(0.1s);
	}
}
void Play() {
	while (!flag2) {
		std::cout << "Playing ... " << std::endl;
		std::this_thread::sleep_for(0.5s);
	}
}
void Load() {
	while (!flag3) {
		std::cout << "Loading ... " << std::endl;
		std::this_thread::sleep_for(1s);
	}
}
void Copy() {
	while (!flag4) {
		std::cout << "Coping ... " << std::endl;
		std::this_thread::sleep_for(0.2s);
	}
}


int main() {
	auto start = std::chrono::high_resolution_clock::now();
	std::thread work(Work), play(Play), copy(Copy), load(Load);
	std::cin.get();
	flag1 = true;
	std::cin.get();
	flag3 = true;
	std::cin.get();
	flag4 = true;
	std::cin.get();
	flag2 = true;

	work.join();
	copy.join();
	play.join();
	load.join();
	auto end  = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration_ = end - start;
	std::cout << "Finished in " << duration_.count() << std::endl;

}