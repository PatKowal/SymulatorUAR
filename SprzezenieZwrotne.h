#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"
#include "GenWartZadana.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k, double Ti, double Td)
		: pid(k, Ti, Td), model(A, B, delay, 0), gen_w(Sygnal::Krok), U(0.0) {}
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k, double Ti)
		: SprzezenieZwrotne(A, B, delay, k, Ti, 0.0) {}
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k)
		: SprzezenieZwrotne(A, B, delay, k, 0.0, 0.0) {}

	~SprzezenieZwrotne() {};

	double SimE(double czas) {
		double wartZadana = gen_w.GenerujSygnal(czas);
		double E = wartZadana - model.SimY(U);
		U = pid.SumU(E);
		return model.SimY(U);
	}

	double getY_ost() { return model.getY_ost(); }
	double getU_ost() { return pid.getU_ost(); }

private:
	PID pid;
	ModelARX model;
	GenWartZadana gen_w;
	double U;
};
