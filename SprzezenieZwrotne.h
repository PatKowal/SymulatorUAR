#pragma once
#include "ModelARX.h"
#include "RegulatorPID.h"

class SprzezenieZwrotne
{
public:
	SprzezenieZwrotne(const std::vector<double>& A, const std::vector<double>& B, int opoznienie, double k, double Ti, double Td);
	~SprzezenieZwrotne();

private:

};
