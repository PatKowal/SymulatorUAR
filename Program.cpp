#include "Start.h"
#include "SprzezenieZwrotne.h"

#ifdef PROGRAM

void main() {

	std::vector<double>A = { -0.4 };
	std::vector<double>B = { 0.6 };
	int delay = 2;

	double k = 1, Ti = 1, Td = 1;
	constexpr size_t PREC = 2;
	std::cout << std::fixed << std::setprecision(PREC);

	SprzezenieZwrotne loop(A, B, delay, k);

	for (size_t i = 0; i < 40; i++) {
		loop.SimUAR(i);
		std::cout << "Czas: " << i << "|Y: " << loop.getY_ost()<< "|U: " << loop.getU_ost() << "\n";
	};


}

#endif