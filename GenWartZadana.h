#pragma once
#define M_PI 3.14159265358979323846 // pi
#include "Biblioteki.h"
enum class Sygnal { Skok, Prostokat, Sin };

class GenWartZadana
{
public:
	GenWartZadana(Sygnal typ = Sygnal::Skok, double t = 0.0, double Amp = 0.0, double T = 1.0, double p = 0.0)
		: typ(typ), t(t), Amp(Amp), T(T), p(p), i(0.0), WartZadana(0.0)
	{
		WalidacjaParametrow();
	}
	~GenWartZadana() {};

	double GenerujSygnal(double czas) {
		i += czas;
		switch (typ) {
		case Sygnal::Skok:
			return (i <= t) ? Amp : 0.0;
		case Sygnal::Prostokat:
			return (fmod(i, T) < p * T) ? Amp : 0.0;
		case Sygnal::Sin:
			WalidacjaParametrow();
			return (Amp * sin(2 * M_PI * fmod(i, T) / T));
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
		WalidacjaParametrow();
		i = 0.0;
	}
	double getWartZadana() {
		return WartZadana;
	}
private:
	Sygnal typ;
	double t;	// chwila aktywacji
	double Amp;	// wart stala
	double T;	// okres 
	double p;	// wypelnienie
	double i;	// czas??
	double WartZadana;

	void WalidacjaParametrow() {
		if (T <= 0) {
			throw std::invalid_argument("Okres musi byæ wiêkszy od 0!");
		}
	}
};