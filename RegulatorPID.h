#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <iomanip>

class PID
{
public:
	PID(double k, double Ti, double Td)
		: k(k), Ti(Ti), Td(Td) {};
	~PID() {};

private:
	double k;
	std::deque <double> Queue_E;
	double Ti;
	double Td;
};