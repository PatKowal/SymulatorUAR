#pragma once
#include <vector>

class PID
{
public:
    PID(double k, double Ti = 0.0, double Td = 0.0)
        : k(k), Ti(Ti), Td(Td), Sum_EI(0.0), EI_ost(0.0), U(0.0) {};

    ~PID() {};

    double SumU(double EI) {

        double UI_P = k * EI;
        double UI_I = 0.0;
        if (Ti != 0) {
            Sum_EI += EI;
            UI_I = Sum_EI / Ti;
        }
        double UI_D = Td * (EI - EI_ost);
        U = UI_P + UI_I + UI_D;
        EI_ost = EI;
        return U;
    };
    void ResetPID() { Sum_EI = 0.0; }
    void setPID(const std::vector<double>& ParametryPID) {
        this->k = ParametryPID[0];
        this->Ti = ParametryPID[1];
        this->Td = ParametryPID[2];
        ResetPID();
    }
private:
    double k, Ti, Td, Sum_EI, EI_ost, U;
};
