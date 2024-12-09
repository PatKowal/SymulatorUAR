#include "Start.h"
#include "SprzezenieZwrotne.h"

#ifdef PROGRAM

void main() {
	setlocale(LC_ALL, "");
	std::vector<double>A = { -0.4 };
	std::vector<double>B = { 0.6 };
	int delay = 1;

	double k = 5.0, Ti = 1.0, Td = 0.0;
	constexpr size_t PREC = 2;
	std::cout << std::fixed << std::setprecision(PREC);

	try {
		SprzezenieZwrotne loop(A, B, delay, k, Ti);

		loop.setGen(Sygnal::Krok, 100, 5, 0.0, 0.0);

		for (size_t i = 0; i < 10; i++) {
			loop.SimUAR(i);
			std::cout << "Czas: " << i<< "\t| U: " << loop.getU_ost() << "\t| Y: " << loop.getY_ost() << "\n";
		};
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "B³¹d: " << e.what() << "\n";
	}
	


}

#endif