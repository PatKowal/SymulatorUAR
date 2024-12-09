#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"
#include "GenWartZadana.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k, double Ti, double Td)
		: pid(k, Ti, Td), model(A, B, delay, 0.0), gen_w(Sygnal::Krok), U(0.0) {}
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k, double Ti)
		: SprzezenieZwrotne(A, B, delay, k, Ti, 0.0) {}
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k)
		: SprzezenieZwrotne(A, B, delay, k, 0.0, 0.0) {}

	~SprzezenieZwrotne() {};

	double SimW(double czas) { return gen_w.GenerujSygnal(czas); }
	double SimEI(double wartZadana) { return wartZadana - model.SimY(U); }
	double SimPID(double EI) { return pid.SumU(EI); }
	double SimARX(double U) { return model.SimY(U); }

	double SimUAR(double czas) {
		double wartZadana = SimW(czas);
		double EI = SimEI(wartZadana);
		std::cout << EI;
		U = SimPID(EI);
		return SimARX(U);
	}

	double getY_ost() const { return model.getY_ost(); }
	double getU_ost() const { return pid.getU_ost(); }
	void setGen(Sygnal typ, double t, double Amp, double T, double p) { gen_w.setGen(typ, t, Amp, T, p); }

private:
	PID pid;
	ModelARX model;
	GenWartZadana gen_w;
	double U;
};
