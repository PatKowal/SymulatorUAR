#pragma once
#include "Biblioteki.h"

class ModelARX : public Kolejki
{
public:
	ModelARX(const std::vector<double>& A, const std::vector<double>& B, int Delay, double Z)
		: A(A), B(B), QueueSize(std::max(A.size(), B.size() + Delay)) ,Delay(Delay), Z(Z)
	{
		Queue_U = std::deque<double>(QueueSize, 0.0);
		Queue_Y = std::deque<double>(QueueSize, 0.0);
	};
	~ModelARX() {};

	double SimY(double signal) {

		Queue_U.push_front(signal);
		Queue_U.pop_back();

		double y = 0.0;
		for (size_t i = 0; i < B.size(); i++) {
			y += B[i] * Queue_U[i + Delay];
		}

		for (size_t i = 0; i < A.size(); i++) {
			y -= A[i] * Queue_Y[i];
		}
		
		y += Z;

		Queue_Y.push_front(y);
		Queue_Y.pop_back();

		return y;
	}
private:
	std::vector<double> A, B;
	int QueueSize, Delay;
	double Z;

};