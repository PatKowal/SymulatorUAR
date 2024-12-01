#pragma once
#include "Biblioteki.h"

class PID
{
public:
	PID(double k, double Ti, double Td)
		: k(k), Ti(Ti), Td(Td), Sum_EI(0.0), EI_ost(0.0) {};
	PID(double k, double Ti)
		: PID(k, Ti, 0.0) {};
	PID(double k)
		: PID(k, 0.0, 0.0) {};

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
		return U;
	};

private:
	double k, Ti, Td, Sum_EI, EI_ost;
};