#include "ModelARX.h"

ModelARX::ModelARX(const std::vector<double>& A, const std::vector<double>& B, int Delay, double Z)
	: A(A), B(B), Delay(Delay), Z(Z) {
	QueueSize = std::max(A.size(), B.size() + Delay);
	Queue_U = std::deque<double>(QueueSize, 0.0);
	Queue_Y = std::deque<double>(QueueSize, 0.0);
}
ModelARX::~ModelARX() {}

double ModelARX::SimY(double signal) {

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