#pragma once
#include "Biblioteki.h"

class PID
{
public:
	PID(double k, double Ti = 0.0, double Td = 0.0)
		: k(k), Ti(Ti), Td(Td), Sum_EI(0.0), EI_ost(0.0), U_ost(0.0) {};

	~PID() {};

	double SumU(double EI) {

		double UI_P = k * EI;
		double UI_I = 0.0;
		if (Ti != 0) {
			Sum_EI += EI;
			UI_I = (1 / Ti) * Sum_EI;
		}

		double UI_D = Td * (EI - EI_ost);
		double U = UI_P + UI_I + UI_D;
		EI_ost = EI;
		U_ost = U;
		return U;
	};
	void ResetPID() { Sum_EI = 0.0;}
	double getU_ost() const { return U_ost; }
	void setPID(std::vector<double>& ParametryPID) {
		this->k = ParametryPID[0];
		this->Ti = ParametryPID[1];
		this->Td = ParametryPID[2];
	}
private:
	double k, Ti, Td, Sum_EI, EI_ost, U_ost;
};