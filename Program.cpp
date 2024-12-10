#include "Start.h"
#include "SprzezenieZwrotne.h"

#ifdef PROGRAM

void main() {
	setlocale(LC_ALL, "");
	std::vector<double>A = { -0.4 };
	std::vector<double>B = { 0.6 };
	int delay = 1;

	std::vector<double>ParametryPID = { 5.0,1.0,0.0 };
	constexpr size_t PREC = 2;
	std::cout << std::fixed << std::setprecision(PREC);

	try {
		SprzezenieZwrotne loop;

		loop.setARX(A, B, delay, 0);
		loop.setPID(ParametryPID);

		for (size_t i = 0; i < 10; i++) {
			double czas = i * 0.1;
			loop.SimUAR(czas);
			std::cout << "Czas: " << i<< "\t| U: " << loop.getU_ost() << "\t| Y: " << loop.getY_ost() << "\n";
		};
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "B³¹d: " << e.what() << "\n";
	}
}

#endif