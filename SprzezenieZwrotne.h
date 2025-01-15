#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A = { 0.0 }, const std::vector<double>& B = { 0.0 }, int delay = 0, double k = 0.0, double Ti = 0.0, double Td = 0.0)
        : pid(k, Ti, Td), model(A, B, delay), U(0.0), Y_ost(0.0) {};
    SprzezenieZwrotne(ModelARX& model, PID& pid)
        : pid(pid), model(model), U(0.0), Y_ost(0.0) {};

	~SprzezenieZwrotne() {};

    double SimUAR(double wartZadana) {
        double EI = wartZadana - Y_ost;
        U = pid.SumU(EI);
        double Y = model.SimY(U);
        Y_ost = Y;
        return Y;
	}

    double getU() const { return U; }

	void setPID(std::vector<double>& ParametryPID) {
		pid.setPID(ParametryPID);
	}
    void ResetSim() { U = 0.0; pid.ResetPID(); model.ResetARX(); }
    void setARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z = 0.0) {

        model.setARX(A, B, delay, Z);
	}
    double getLoopU() const { return U; };
private:
	PID pid;
	ModelARX model;
    double U, Y_ost;
};
