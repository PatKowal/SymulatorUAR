#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"

class SprzezenieZwrotne
{
public:
    SprzezenieZwrotne(const std::vector<double>& A = { 0.0 }, const std::vector<double>& B = { 0.0 }, int delay = 0, double wzmocienie = 0.0, double stala_calkowania = 0.0, double stala_rozniczkowania = 0.0)
        : pid(wzmocienie, stala_calkowania, stala_rozniczkowania), model(A, B, delay), Y_ost(0.0) {};

	~SprzezenieZwrotne() {};

    std::vector<double>  SimUAR(double wartZadana) {
        double EI = wartZadana - Y_ost;
        std::vector<double> regulator = pid.SumU(EI);   
        Y_ost = model.SimY(regulator[3]);

        return { wartZadana, EI, regulator[0],regulator[1],regulator[2],regulator[3], Y_ost };
	}

	void setPID(std::vector<double>& ParametryPID) {
		pid.setPID(ParametryPID);
	}
    void ResetSim() { Y_ost = 0.0; pid.ResetPID(); model.ResetARX(); }
    void setARX(std::vector<double>& A, std::vector<double>& B, int delay = 0, bool zaklucenia = 0) {

        model.setARX(A, B, delay, zaklucenia);
	}
private:
	PID pid;
	ModelARX model;
    double Y_ost;
};
