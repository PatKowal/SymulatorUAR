#include "Start.h"
#include "SprzezenieZwrotne.h"

#ifdef PROGRAM

void main() {

	std::vector<double>A = { -0.4 };
	std::vector<double>B = { 0.6 };
	int delay = 1;

	double k = 1;

	SprzezenieZwrotne loop(A, B, delay, k);
	for (double i = 0.0; i < 31; i++) {
		loop.SimE(i);
		std::cout << "Czas: " << i << "|Y: " << loop.getY_ost()<< "|U: " << loop.getU_ost() << "\n";
	};
}

#endif