#pragma once
#include "Biblioteki.h"
#include "SprzezenieZwrotne.h"
#include "GenWartZadana.h"

class Manager
{
public:
	Manager() : loop(), gen_w() {};
	~Manager() {};

	void setGenerator(Sygnal typ, std::vector<double>& ParametryGen) {
		//assert(ParametryGen.size() == 4 && "Za ma³o parametów generatora");
		gen_w.setGen(typ, ParametryGen);
	};
	void setRegulatorPID(std::vector<double>& ParametryPID) {
		//assert(ParametryPID.size() == 3 && "Za ma³o parametów regulatora");
		loop.setPID(ParametryPID);
		loop.ResetPID();
		//std::cout << "Parametry PID zmienione" << "\n";
	};
	void setModelARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z = 0.0) {
		//assert(!A.empty() && "Wektor A jest pusty");
		//assert(!B.empty() && "Wektor B jest pusty");
		//assert(delay >= 0 && "OpóŸnienie musi byæ wiêksze lub równe 0");
		loop.setARX(A, B, delay, Z);
		//std::cout << "Parametry ARX zmienione" << "\n";
	};
	std::vector<double> getWY() {
		return { gen_w.getWartZadana(),loop.getRegU(),loop.getModelY() };
	};
	void Symuluj(double czas) {
		double wartZadana = gen_w.GenerujSygnal(czas);
		loop.SimUAR(wartZadana);
	}

private:
	SprzezenieZwrotne loop;
	GenWartZadana gen_w;
};