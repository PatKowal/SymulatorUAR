#pragma once
#include "Biblioteki.h"
#include "SprzezenieZwrotne.h"
#include "GenWartZadana.h"

class Manager
{
public:
	Manager() : loop(), gen_w(), Stan(false) {};
	~Manager() {};

	void setGenerator(Sygnal typ, std::vector<double>& ParametryGen) {
		if (Stan) {
			std::cerr << "Nie mo¿na zmieniæ parametrów generatora wartoœci zadanej podczas pracu programu" << "\n";
		}
		assert(ParametryGen.size() == 4 && "Za ma³o parametów generatora");
		gen_w.setGen(typ, ParametryGen);
	};
	void setRegulatorPID(std::vector<double>& ParametryPID) {
		if (Stan) {
			std::cerr << "Nie mo¿na zmieniæ parametrów Regulatora PID podczas pracu programu" << "\n";
		}
		assert(ParametryPID.size() == 3 && "Za ma³o parametów regulatora");
		loop.setPID(ParametryPID);
		loop.ResetPID();
		std::cout << "Parametry PID zmienione" << "\n";
	};
	void setModelARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z) {
		if (Stan) {
			std::cerr << "Nie mo¿na zmieniæ parametrów ARX podczas pracu programu" << "\n";
		}
		assert(!A.empty() && "Wektor A jest pusty");
		assert(!B.empty() && "Wektor B jest pusty");
		assert(delay >= 0 && "OpóŸnienie musi byæ wiêksze lub równe 0");
		loop.setARX(A, B, delay, Z);
		std::cout << "Parametry ARX zmienione" << "\n";
	};
	std::vector<double> getWY() {
		return { gen_w.getWartZadana(),loop.getU_ost(),loop.getY_ost() };
	};
	void Symuluj(double czas) {
		if (!Stan) { std::cout << "Symulacja nie jest aktywna!" << "\n"; return; }
		double wartZadana = gen_w.GenerujSygnal(czas);
		loop.SimUAR(wartZadana);
	}
	void SimStart() {
		if (!Stan) {
			Stan = true;
			std::cout << "Start symulacji!" << "\n";
		}
		else {
			std::cerr << "Symulacja ju¿ dzia³a!" << "\n";
		}
	}
	void SimStop() {
		if (Stan) {
			Stan = false;
			std::cout << "Stop symulacji!" << "\n";
		}
		else {
			std::cerr << "Symulacja jest ju¿ wy³¹czona!" << "\n";
		}
	}
	void SimReset() {
		if (Stan) { SimStop(); }
		loop.ResetPID();
		std::cout << "Reset usatawieñ PID!" << "\n";
	}

private:
	SprzezenieZwrotne loop;
	GenWartZadana gen_w;
	bool Stan;
};