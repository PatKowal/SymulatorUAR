#pragma once
#include "Biblioteki.h"

class PID
{
public:
	PID(double k);
	PID(double k, double Ti);
	PID(double k, double Ti, double Td);
	~PID();

	double SumU(double EI);

private:
	double k, Ti, Td, Sum_EI, EI_ost;
};