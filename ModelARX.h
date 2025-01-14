#pragma once
#include <deque>
#include <vector>
#include <QDebug>

class ModelARX
{
public:
    ModelARX(const std::vector<double>& A, const std::vector<double>& B, int delay, double Z = 0.0)
		: A(A), B(B), delay(delay), Z(Z), WY(0.0) {
		Queue_U = std::deque<double>(B.size() + delay, 0.0);
		Queue_Y = std::deque<double>(A.size(), 0.0);
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
		WY = y;

		return y;
	}
	
    double getY() const { return WY; }
    void setARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z = 0.0) {

        this->A = A;
		this->B = B;
		this->delay = delay;
        this->Z = Z;
		Queue_U.resize(B.size() + delay, 0.0);
		Queue_Y.resize(A.size(), 0.0);
	}
private:
	std::vector<double> A, B;
	int delay;
	double Z, WY;
	std::deque<double> Queue_U, Queue_Y;
};
