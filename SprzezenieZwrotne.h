#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A = { 0.0 }, const std::vector<double>& B = { 0.0 }, int delay = 0, double k = 0.0, double Ti = 0.0, double Td = 0.0)
        : pid(k, Ti, Td), model(A, B, delay), Y_ost(0.0), U(0.0) {};
    SprzezenieZwrotne(ModelARX& model, PID& pid)
        : pid(pid), model(model), Y_ost(0.0) {};

	~SprzezenieZwrotne() {};

    double SimUAR(double wartZadana) {
        double EI = wartZadana - model.SimY(Y_ost);
        double U = pid.SumU(EI);
        double Y = model.SimY(U);
        Y_ost = Y;
        return Y;
	}

    double getY() const { return Y_ost; }
    double getU() const { return U; }

	void setPID(std::vector<double>& ParametryPID) {
		pid.setPID(ParametryPID);
	}
    void ResetSim() { Y_ost = 0.0; pid.ResetPID(); model.ResetARX(); }
    void setARX(std::vector<double>& A, std::vector<double>& B, int delay = 0.0, bool Z = 0) {

        model.setARX(A, B, delay, Z);
	}
private:
	PID pid;
	ModelARX model;
    double Y_ost, U;
};
