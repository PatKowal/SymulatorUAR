#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A = { 0.0 }, const std::vector<double>& B = { 0.0 }, int delay = 0, double k = 0.0, double Ti = 0.0, double Td = 0.0)
       : pid(k, Ti, Td), model(A, B, delay), Y_ost(0.0) {};

	~SprzezenieZwrotne() {};

    std::vector<double>  SimUAR(double wartZadana) {
        double EI = wartZadana - Y_ost;
        double U = pid.SumU(EI);   
        Y_ost = model.SimY(U);

        return { wartZadana, EI, U, Y_ost };
	}

	void setPID(std::vector<double>& ParametryPID) {
		pid.setPID(ParametryPID);
	}
    void ResetSim() { pid.ResetPID(); model.ResetARX(); }
    void setARX(std::vector<double>& A, std::vector<double>& B, int delay = 0, bool Z = 0) {

        model.setARX(A, B, delay, Z);
	}
private:
	PID pid;
	ModelARX model;
    double Y_ost;
};
