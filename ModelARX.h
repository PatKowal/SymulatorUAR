#pragma once
#include <deque>
#include <vector>

class ModelARX
{
public:
    ModelARX(const std::vector<double>& A, const std::vector<double>& B, int delay = 0, bool Z = 0)
        : A(A), B(B), delay(delay), Z(Z) {
        Queue_U = std::deque<double>(B.size() + delay, 0.0);
        Queue_Y = std::deque<double>(A.size(), 0.0);
    }
    ~ModelARX() {}

    double SimY(double U) {
        Queue_U.push_front(U);
        Queue_U.pop_back();

        double y = 0.0;

        for (size_t i = 0; i < B.size(); i++) {
            y += B[i] * Queue_U[i + delay];
        }
        for (size_t i = 0; i < A.size(); i++) {
            y -= A[i] * Queue_Y[i];
        }
        if (Z == 1) {
            y += Z;
        }

        Queue_Y.push_front(y);
        Queue_Y.pop_back();
        return y;
    }

    void setARX(const std::vector<double>& A, const std::vector<double>& B, int delay, double Z = 0.0) {
        this->A = A;
        this->B = B;
        this->delay = delay;
        this->Z = Z;
        Queue_U.resize(B.size() + delay, 0.0);
        Queue_Y.resize(A.size(), 0.0);
    }

    void ResetARX() {
        for (size_t i = 0; i < B.size() + delay; i++) {
            Queue_U.push_front(0.0);
            Queue_U.pop_back();
        }
        for (size_t i = 0; i < A.size(); i++) {
            Queue_Y.push_front(0.0);
            Queue_Y.pop_back();
        }
    }

private:
    std::vector<double> A, B;
    int delay;
    bool Z;
    std::deque<double> Queue_U, Queue_Y;
};
