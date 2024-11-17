#pragma once
#include "Biblioteki.h"

class PID : public Kolejki
{
public:
	PID(double k)
		: k(k), Ti(0.0), Td(0.0), Sum_EI(0.0) {};
	PID(double k, double Ti)
		: k(k), Ti(Ti), Td(0.0), Sum_EI(0.0) {};
	PID(double k, double Ti, double Td)
		: k(k), Ti(Ti), Td(Td), Sum_EI(0.0) {};
	~PID() {};

	double SumU(double EI) {
		Queue_EI.push_front(EI);
		if (Queue_EI.size() > 2) {
			Queue_EI.pop_back();
		}

		double UI_P = k * EI;
		double UI_I = 0.0;
		if (Ti != 0) {
			Sum_EI += EI;
			UI_I = (1 / Ti) * Sum_EI;
		}

		double UI_D = Td * (Queue_EI.front() - Queue_EI.back());

		double U = UI_P + UI_I + UI_D;
		return U;
	};

private:
	double k, Ti, Td, Sum_EI;
};