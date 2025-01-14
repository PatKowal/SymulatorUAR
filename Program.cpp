#include "Start.h"
#include "Manager.h"

#ifdef PROGRAM

void main() {
	setlocale(LC_ALL, "");
	std::vector<double>A = { 1,1,1 };
	std::vector<double>B = { 1,1,1 };
	int delay = 1;

	std::vector<double>ParametryPID = { 10,1,0.2 };
	std::vector<double>ParametryGen = { 1.0,1.0,1.0,1.0 };
	constexpr size_t PREC = 2;
	std::cout << std::fixed << std::setprecision(PREC);

	try {
		Manager manager;

		manager.setModelARX(A, B, delay);
		manager.setRegulatorPID(ParametryPID);
		manager.setGenerator(Sygnal::Sin, ParametryGen);

		for (size_t i = 0; i < 100; i++) {
			double czas = i * 0.1;
			manager.Symuluj(czas);
			std::vector<double> wynik = manager.getWY();
			std::cout << "Czas: " << i << "\t| W: " << wynik[0] << "\t| U: " << wynik[1] << "\t| Y: " << wynik[2] << "\n";
		};
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "B³¹d: " << e.what() << "\n";
	}
}

#endif