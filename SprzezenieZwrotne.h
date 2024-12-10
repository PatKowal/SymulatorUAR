#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A = { 0.0 }, const std::vector<double>& B = { 0.0 }, int delay = 1, double k = 0.0, double Ti = 0.0, double Td = 0.0)
		: pid(k, Ti, Td), model(A, B, delay, 0.0), U(0.0) {};

	~SprzezenieZwrotne() {};

	double SimEI(double wartZadana) { return wartZadana - model.SimY(U); }
	double SimPID(double EI) { return pid.SumU(EI); }
	double SimARX(double U) { return model.SimY(U); }
	double SimUAR(double wartZadana) {
		double EI = SimEI(wartZadana);
		U = SimPID(EI);
		return SimARX(U);
	}

	double getY_ost() const { return model.getY_ost(); }
	double getU_ost() const { return pid.getU_ost(); }
	void ResetPID() { pid.ResetPID(); }
	void setPID(std::vector<double>& ParametryPID) {
		pid.setPID(ParametryPID);
	}
	void setARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z) {
		model.setARX(A, B, delay, Z);
	}

private:
	PID pid;
	ModelARX model;
	double U;
};
