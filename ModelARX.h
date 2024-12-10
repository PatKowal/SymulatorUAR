#pragma once
#include "Biblioteki.h"

class ModelARX
{
public:
	ModelARX(const std::vector<double>& A, const std::vector<double>& B, int delay, double Z)
		: A(A), B(B), delay(delay), Z(Z), Y_ost(0.0) {
		QueueSize = std::max(A.size(), B.size() + delay);
		Queue_U = std::deque<double>(QueueSize, 0.0);
		Queue_Y = std::deque<double>(QueueSize, 0.0);
	}
	~ModelARX() {}

	double SimY(double signal) {

		Queue_U.push_front(signal);
		Queue_U.pop_back();

		double y = 0.0;
		for (size_t i = 0; i < B.size(); i++) {
			y += B[i] * Queue_U[i + delay];
		}
		for (size_t i = 0; i < A.size(); i++) {
			y -= A[i] * Queue_Y[i];
		}

		y += Z;
		Queue_Y.push_front(y);
		Queue_Y.pop_back();
		Y_ost = Queue_Y.back();
		return y;
	}

	double getY_ost() const { return Y_ost; }
	void setARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z) {
		this->A = A;
		this->B = B;
		this->delay = delay;
		this->Z = Z;
	}
private:
	std::vector<double> A, B;
	int QueueSize, delay;
	double Z;
	std::deque<double> Queue_U, Queue_Y;
	double Y_ost;
};