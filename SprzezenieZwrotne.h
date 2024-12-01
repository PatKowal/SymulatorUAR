#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k, double Ti, double Td)
		: pid(k, Ti, Td), model(A, B, delay, 0), wartZadana(0.0)
	{
		U = pid.getULast();
		Y = model.getYLast();
	}
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k, double Ti)
		: SprzezenieZwrotne(A, B, delay, k, Ti, 0.0) {}
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int delay, double k)
		: SprzezenieZwrotne(A, B, delay, k, 0.0, 0.0) {}

	~SprzezenieZwrotne() {};

private:
	PID pid;
	ModelARX model;
	double wartZadana, Y, U;

};
