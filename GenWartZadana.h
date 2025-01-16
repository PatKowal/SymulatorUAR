#pragma once
#include <cmath>
#include <vector>
#define M_PI 3.14159265358979323846

enum class Sygnal { Skok, Prostokat, Sin, Nieustawiony };

class GenWartZadana
{
public:
    GenWartZadana(Sygnal typ = Sygnal::Skok, double t = 0.0, double Amp = 0.0, double T = 1.0, double p = 0.0)
        : typ(typ), t(t), Amp(Amp), T(T), p(p), i(0.0) {}
    ~GenWartZadana() {};

    double GenerujSygnal(double czas) {
        //qDebug() << "czas symulacji" << czas;

        i += czas;
        switch (typ) {
        case Sygnal::Skok:
            return (i <= t) ? Amp : 0.0;
        case Sygnal::Prostokat:
            return (fmod(i, T) < p * T) ? Amp : 0.0;
        case Sygnal::Sin:
            return Amp * std::sin(2 * M_PI * (fmod(i, T) / T));
        default:
            return 0.0;
        }
    }
    void setGen(Sygnal typ, std::vector<double>& ParametryGen) {

        this->typ = typ;
        t = ParametryGen[0];
        Amp = ParametryGen[1];
        T = ParametryGen[2];
        p = ParametryGen[3];
        i = 0.0;
    }
    void ResetCzas() { i = 0.0; };
private:
    Sygnal typ;
    double t;	// chwila aktywacji
    double Amp;	// wart stala
    double T;	// okres
    double p;	// wypelnienie
    double i;	// czas??
};
