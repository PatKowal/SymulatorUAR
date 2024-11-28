#pragma once
#include "Biblioteki.h"

class ModelARX
{
public:
	ModelARX(const std::vector<double>& A, const std::vector<double>& B, int Delay, double Z);
	~ModelARX();

	double SimY(double signal);
private:
	std::vector<double> A, B;
	int QueueSize, Delay;
	double Z;
	std::deque<double> Queue_U, Queue_Y;
};